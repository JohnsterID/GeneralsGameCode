#!/usr/bin/env python3
"""
dialog_tester.py
"""

import subprocess
import time
import json
import hashlib
import shutil
import argparse
import os
from pathlib import Path
from datetime import datetime
from PIL import Image, ImageChops

# -------------------------------------------------
# CONFIG
# -------------------------------------------------

WINE = "wine"
WMCTRL = "wmctrl"
XDOTOOL = "xdotool"
IMPORT = "import"
XPROP = "xprop"

RETRY_DELAY = 0.4
DEFAULT_TIMEOUT = 10
MAX_ACTIONS = 64

# -------------------------------------------------
# UTILS
# -------------------------------------------------

def run(cmd):
    return subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

def now():
    return datetime.utcnow().isoformat(timespec="seconds") + "Z"

def sha256(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for c in iter(lambda: f.read(8192), b""):
            h.update(c)
    return h.hexdigest()

# -------------------------------------------------
# WINDOW HANDLING (X11)
# -------------------------------------------------

def list_windows():
    out = run([WMCTRL, "-lp"]).stdout.decode(errors="ignore")
    wins = []
    for line in out.splitlines():
        parts = line.split(None, 4)
        if len(parts) == 5:
            wins.append({
                "id": parts[0],
                "pid": parts[2],
                "title": parts[4]
            })
    return wins

def wait_for_window(title, timeout):
    deadline = time.time() + timeout
    while time.time() < deadline:
        for w in list_windows():
            if title.lower() in w["title"].lower():
                return w
        time.sleep(RETRY_DELAY)
    raise TimeoutError(title)

def focus_window(win_id):
    run([WMCTRL, "-i", "-R", win_id])
    time.sleep(0.2)

def screenshot_window(win_id, path):
    run([IMPORT, "-window", win_id, path])

# -------------------------------------------------
# REGISTRY HANDLING (Wine)
# -------------------------------------------------

def snapshot_registry(prefix, out):
    shutil.copy(Path(prefix) / "user.reg", out)

def normalize_registry(src, dst):
    with open(src) as f:
        lines = f.readlines()
    lines = [l for l in lines if not l.lower().startswith(("timestamp", "lastwrite"))]
    with open(dst, "w") as f:
        f.writelines(lines)

def extract_registry_keys(path):
    keys = set()
    current = None
    with open(path) as f:
        for line in f:
            line = line.strip()
            if line.startswith("[") and line.endswith("]"):
                current = line[1:-1]
            elif "=" in line and current:
                k = line.split("=", 1)[0].strip('"')
                keys.add((current, k))
    return keys

# -------------------------------------------------
# VISUAL DIFF
# -------------------------------------------------

def visual_changed(a, b, tol=5):
    diff = ImageChops.difference(a, b)
    return any(mx > tol for (_, mx) in diff.getextrema())

# -------------------------------------------------
# INPUT AUTOMATION
# -------------------------------------------------

def send_keys(seq):
    run([XDOTOOL, "key"] + seq.split())
    time.sleep(0.2)

# -------------------------------------------------
# AUTO DIALOG DISCOVERY
# -------------------------------------------------

def discover_new_windows(before):
    after = list_windows()
    return [w for w in after if w["id"] not in before]

# -------------------------------------------------
# STATEFUL INTERACTION
# -------------------------------------------------

def test_stateful(win_id, outdir):
    before = outdir / "before.png"
    after = outdir / "after.png"

    screenshot_window(win_id, before)
    send_keys("Tab space")
    screenshot_window(win_id, after)

    return visual_changed(Image.open(before), Image.open(after))

# -------------------------------------------------
# MAIN
# -------------------------------------------------

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--exe", required=True)
    ap.add_argument("--title", required=True)
    ap.add_argument("--wineprefix", required=True)
    ap.add_argument("--out", default="results")
    ap.add_argument("--timeout", type=int, default=DEFAULT_TIMEOUT)
    args = ap.parse_args()

    out = Path(args.out)
    out.mkdir(parents=True, exist_ok=True)

    # Registry baseline
    reg_before = out / "registry_before.reg"
    snapshot_registry(args.wineprefix, reg_before)
    norm_before = out / "registry_before.norm"
    normalize_registry(reg_before, norm_before)
    keys_before = extract_registry_keys(norm_before)

    # Launch app
    run([WINE, args.exe])
    main_win = wait_for_window(args.title, args.timeout)
    focus_window(main_win["id"])

    baseline_windows = {w["id"] for w in list_windows()}
    results = []

    # Blind exploration loop
    for step in range(MAX_ACTIONS):
        send_keys("Alt")
        time.sleep(0.3)

        new_windows = discover_new_windows(baseline_windows)
        for w in new_windows:
            focus_window(w["id"])
            dlg_id = f"dialog_{len(results)}"
            dlg_dir = out / dlg_id
            dlg_dir.mkdir()

            shot = dlg_dir / "dialog.png"
            screenshot_window(w["id"], shot)

            stateful = test_stateful(w["id"], dlg_dir)

            results.append({
                "id": dlg_id,
                "title": w["title"],
                "screenshot": shot.name,
                "screenshot_hash": sha256(shot),
                "stateful_effect": stateful
            })

            send_keys("Escape")
            baseline_windows.add(w["id"])

        time.sleep(0.5)

    # Registry after
    reg_after = out / "registry_after.reg"
    snapshot_registry(args.wineprefix, reg_after)
    norm_after = out / "registry_after.norm"
    normalize_registry(reg_after, norm_after)
    keys_after = extract_registry_keys(norm_after)

    summary = {
        "app": Path(args.exe).stem,
        "timestamp": now(),
        "dialogs": results,
        "registry_diff": sorted(keys_after - keys_before)
    }

    with open(out / "results.json", "w") as f:
        json.dump(summary, f, indent=2)

    print("[✓] Dialog crawl complete")

if __name__ == "__main__":
    main()
