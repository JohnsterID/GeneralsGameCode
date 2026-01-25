#!/usr/bin/env python3
"""
dialog_tester.py

Advanced automated dialog tester for W3DView (MFC vs wxWidgets)
Designed for Debian + Wine + CI + reverse-engineering workflows

Features:
- Guided dialog traversal
- Window-class detection (wx/MFC)
- Registry verification and expected keys per dialog
- Screenshot capture (window-scoped)
- Golden baseline hashes for fast pass/fail
- Dead-control detection (no visual or registry effect)
- Heatmap generation across builds
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
import numpy as np
from PIL import Image, ImageChops

# ------------------ Config ------------------
WINE = "wine"
XDOTOOL = "xdotool"
WMCTRL = "wmctrl"
IMPORT = "import"
RETRY_DELAY = 0.5
DEFAULT_TIMEOUT = 10

# ------------------ Utilities ------------------

def run(cmd, check=True):
    return subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=check)

def sha256(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(8192), b""):
            h.update(chunk)
    return h.hexdigest()

def now():
    return datetime.utcnow().isoformat(timespec="seconds") + "Z"

# ------------------ Wine / Window Handling ------------------

def launch_app(exe_path):
    run([WINE, exe_path], check=False)
    time.sleep(3)

def list_windows():
    out = run([WMCTRL, "-lp"], check=False).stdout.decode(errors="ignore")
    windows = []
    for line in out.splitlines():
        parts = line.split(None, 4)
        if len(parts) >= 5:
            windows.append({
                "id": parts[0],
                "pid": parts[2],
                "title": parts[4]
            })
    return windows

def wait_for_window(title_substr, timeout):
    deadline = time.time() + timeout
    while time.time() < deadline:
        for w in list_windows():
            if title_substr.lower() in w["title"].lower():
                return w
        time.sleep(RETRY_DELAY)
    raise TimeoutError(f"Window '{title_substr}' not found")

def focus_window(win_id):
    run([WMCTRL, "-i", "-R", win_id], check=False)
    time.sleep(0.3)

def count_windows():
    return len(list_windows())

def get_window_class(win_id):
    out = run(["xprop", "-id", win_id, "WM_CLASS"], check=False).stdout.decode()
    if "=" in out:
        return out.split("=", 1)[1].strip()
    return "unknown"

def classify_window_class(wm_class):
    s = wm_class.lower()
    if "wx" in s:
        return "wxWidgets"
    if "afx" in s or "mfc" in s:
        return "MFC"
    if "dialog" in s:
        return "Win32"
    return "unknown"

# ------------------ Input Automation ------------------

def send_keys(seq):
    run([XDOTOOL, "key"] + seq.split(), check=False)
    time.sleep(0.2)

def type_text(text):
    run([XDOTOOL, "type", "--delay", "5", text], check=False)
    time.sleep(0.2)

# ------------------ Screenshot Handling ------------------

def screenshot_window(win_id, out_path):
    run([IMPORT, "-window", win_id, out_path], check=False)

def visual_changed(img_before, img_after, tolerance=5):
    diff = ImageChops.difference(img_before, img_after)
    extrema = diff.getextrema()
    return any(maxv > tolerance for (_, maxv) in extrema)

# ------------------ Registry Handling ------------------

def snapshot_registry(prefix_path, out_path):
    reg = Path(prefix_path) / "user.reg"
    shutil.copy(reg, out_path)

def normalize_registry(src, dst):
    """
    Remove volatile fields like timestamps, MRU order
    """
    with open(src) as f:
        lines = f.readlines()
    filtered = [l for l in lines if not l.lower().startswith(("timestamp", "lastwrite"))]
    with open(dst, "w") as f:
        f.writelines(filtered)

def extract_registry_keys(reg_path):
    keys = set()
    current = None
    with open(reg_path) as f:
        for line in f:
            line = line.strip()
            if line.startswith("[") and line.endswith("]"):
                current = line[1:-1]
            elif "=" in line and current:
                k = line.split("=", 1)[0].strip('"')
                keys.add((current, k))
    return keys

# ------------------ Dialog Interaction ------------------

def open_dialog(spec):
    if spec["method"] == "menu":
        for k in spec["sequence"]:
            send_keys(k)
    elif spec["method"] == "hotkey":
        send_keys(spec["key"])
    time.sleep(0.5)

def interact(actions, cfg, dialog_name, win_id):
    dead_controls = []
    for act in actions:
        before = Image.open(cfg.out / f"tmp_{dialog_name}_before.png")
        send_keys("Return") if act.get("type") == "checkbox" else None
        # Extend to sliders/text/etc
        after = Image.open(cfg.out / f"tmp_{dialog_name}_after.png")
        # Visual detection heuristic
        if not visual_changed(before, after):
            dead_controls.append(act.get("name", "unnamed"))
    return dead_controls

def close_dialog(method):
    if method == "ok":
        send_keys("Return")
    elif method == "cancel":
        send_keys("Escape")
    time.sleep(0.5)

# ------------------ Dialog Test Core ------------------

def test_dialog(app_id, dialog, cfg):
    result = {
        "dialog": dialog["id"],
        "name": dialog["name"],
        "start": now(),
        "status": "ok",
        "artifacts": {}
    }

    base_win_count = count_windows()

    try:
        open_dialog(dialog["open"])

        deadline = time.time() + dialog.get("timeout", cfg.timeout)
        while time.time() < deadline:
            if count_windows() > base_win_count:
                break
            time.sleep(RETRY_DELAY)
        else:
            raise TimeoutError("Dialog did not appear")

        dialog_win = list_windows()[-1]
        focus_window(dialog_win["id"])

        # Window class detection
        cls = get_window_class(dialog_win["id"])
        result["window_class"] = cls
        result["window_impl"] = classify_window_class(cls)

        # Interaction + dead control detection
        dead_controls = interact(dialog.get("interactions", []), cfg, dialog["id"], dialog_win["id"])
        if dead_controls:
            result["dead_controls"] = dead_controls
            result["status"] = "suspect"

        # Screenshot
        shot = cfg.out / f"{app_id}_{dialog['id']}.png"
        screenshot_window(dialog_win["id"], shot)
        result["artifacts"]["screenshot"] = shot.name
        result["artifacts"]["screenshot_hash"] = sha256(shot)

        # Registry checks
        expected_keys = dialog.get("expected_registry", {})
        norm_before = cfg.out / "registry_before.norm"
        norm_after = cfg.out / "registry_after.norm"
        before_keys = extract_registry_keys(norm_before)
        after_keys = extract_registry_keys(norm_after)
        missing = []
        for reg_path, keys in expected_keys.items():
            for k in keys:
                if (reg_path, k) not in after_keys:
                    missing.append(f"{reg_path}\\{k}")
        if missing:
            result["registry_missing"] = missing
            result["status"] = "suspect"

        close_dialog(dialog.get("close", "ok"))

    except Exception as e:
        result["status"] = "fail"
        result["error"] = str(e)

    result["end"] = now()
    return result

# ------------------ Heatmap Generation ------------------

def generate_heatmap(images_a, images_b, out_path, tolerance=5):
    acc = None
    for a, b in zip(images_a, images_b):
        img1 = np.array(Image.open(a).convert("RGB"), dtype=np.int16)
        img2 = np.array(Image.open(b).convert("RGB"), dtype=np.int16)
        diff = np.max(np.abs(img1 - img2), axis=2) > tolerance
        if acc is None:
            acc = diff.astype(np.int32)
        else:
            acc += diff
    heat = (acc / acc.max()) * 255
    heat_img = Image.fromarray(heat.astype(np.uint8), mode="L")
    heat_img.save(out_path)

# ------------------ Main ------------------

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--exe", required=True)
    ap.add_argument("--title", required=True)
    ap.add_argument("--dialogs", required=True)
    ap.add_argument("--wineprefix", required=True)
    ap.add_argument("--baseline", help="Baseline hash JSON")
    ap.add_argument("--out", default="results")
    ap.add_argument("--timeout", type=int, default=DEFAULT_TIMEOUT)
    args = ap.parse_args()

    out = Path(args.out)
    out.mkdir(parents=True, exist_ok=True)

    # Registry snapshot before
    reg_before = out / "registry_before.reg"
    snapshot_registry(args.wineprefix, reg_before)
    norm_before = out / "registry_before.norm"
    normalize_registry(reg_before, norm_before)
    args.reg_before_norm = norm_before

    with open(args.dialogs) as f:
        dialogs = json.load(f)

    # Launch app
    launch_app(args.exe)
    wait_for_window(args.title, args.timeout)
    app_id = Path(args.exe).stem

    results = []
    for d in dialogs:
        results.append(test_dialog(app_id, d, args))

    # Registry snapshot after
    reg_after = out / "registry_after.reg"
    snapshot_registry(args.wineprefix, reg_after)
    norm_after = out / "registry_after.norm"
    normalize_registry(reg_after, norm_after)
    args.reg_after_norm = norm_after

    # Compare to baseline hashes
    if args.baseline and Path(args.baseline).exists():
        with open(args.baseline) as f:
            baseline = json.load(f)
        current_hashes = [r["artifacts"]["screenshot_hash"] for r in results if "artifacts" in r]
        baseline_hashes = [h for h in baseline.get("results_hashes", [])]
        results_match = current_hashes == baseline_hashes
    else:
        results_match = None

    summary = {
        "app": app_id,
        "timestamp": now(),
        "results": results,
        "baseline_match": results_match
    }

    with open(out / "results.json", "w") as f:
        json.dump(summary, f, indent=2)

    print("[✓] Dialog test run complete")

if __name__ == "__main__":
    main()
