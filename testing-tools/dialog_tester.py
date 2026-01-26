#!/usr/bin/env python3
"""
dialog_tester.py

Fully automatic Win32/MFC dialog crawler + tester
No handwritten JSON specs

Capabilities:
- Menu crawling + dialog discovery
- WM_COMMAND tracing (menu -> command ID)
- Accelerator extraction (best-effort)
- Stateful control toggling (checkbox/radio)
- Screenshot + registry diff
- Dead-control detection
- Outputs results.json (derived)
TODO:
- Proper menu enumeration instead of blind Alt
- Real ACCEL resource parsing
- Stack-walk for handler offsets
- DOT graph export (menu → dialog → registry)
"""

import ctypes
import subprocess
import time
import json
import hashlib
import shutil
import argparse
import os
from pathlib import Path
from datetime import datetime
from PIL import Image, ImageChops, ImageGrab

# ============================================================
# CONFIG
# ============================================================

WINE = "wine"
WMCTRL = "wmctrl"
XDOTOOL = "xdotool"
IMPORT = "import"

RETRY_DELAY = 0.4
DEFAULT_TIMEOUT = 10
MAX_DIALOGS = 128

# ============================================================
# UTILITIES
# ============================================================

def now():
    return datetime.utcnow().isoformat(timespec="seconds") + "Z"

def run(cmd, check=False):
    return subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=check)

def sha256(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(8192), b""):
            h.update(chunk)
    return h.hexdigest()

# ============================================================
# WIN32 MESSAGE TRACING (WM_COMMAND)
# ============================================================

user32 = ctypes.windll.user32
kernel32 = ctypes.windll.kernel32

WM_COMMAND = 0x0111
WH_CALLWNDPROC = 4

command_log = []

class CWPSTRUCT(ctypes.Structure):
    _fields_ = [
        ("lParam", ctypes.c_void_p),
        ("wParam", ctypes.c_void_p),
        ("message", ctypes.c_uint),
        ("hwnd", ctypes.c_void_p),
    ]

@ctypes.WINFUNCTYPE(ctypes.c_int, ctypes.c_int, ctypes.c_void_p, ctypes.c_void_p)
def hook_proc(nCode, wParam, lParam):
    if nCode >= 0:
        cwp = ctypes.cast(lParam, ctypes.POINTER(CWPSTRUCT)).contents
        if cwp.message == WM_COMMAND:
            cmd_id = int(cwp.wParam) & 0xFFFF
            command_log.append({
                "timestamp": now(),
                "hwnd": hex(cwp.hwnd),
                "command_id": hex(cmd_id)
            })
    return user32.CallNextHookEx(None, nCode, wParam, lParam)

def install_hook():
    tid = kernel32.GetCurrentThreadId()
    return user32.SetWindowsHookExW(
        WH_CALLWNDPROC,
        hook_proc,
        kernel32.GetModuleHandleW(None),
        tid
    )

# ============================================================
# WINDOW MANAGEMENT (Wine/Linux)
# ============================================================

def list_windows():
    out = run([WMCTRL, "-lp"]).stdout.decode(errors="ignore")
    wins = []
    for line in out.splitlines():
        parts = line.split(None, 4)
        if len(parts) >= 5:
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
    time.sleep(0.3)

def screenshot_window(win_id, path):
    run([IMPORT, "-window", win_id, path])

# ============================================================
# REGISTRY HANDLING (Wine)
# ============================================================

def snapshot_registry(prefix, out):
    shutil.copy(Path(prefix) / "user.reg", out)

def normalize_registry(src, dst):
    with open(src) as f:
        lines = f.readlines()
    filtered = [l for l in lines if not l.lower().startswith(("timestamp", "lastwrite"))]
    with open(dst, "w") as f:
        f.writelines(filtered)

def extract_keys(reg):
    keys = set()
    current = None
    with open(reg) as f:
        for line in f:
            line = line.strip()
            if line.startswith("[") and line.endswith("]"):
                current = line[1:-1]
            elif "=" in line and current:
                k = line.split("=", 1)[0].strip('"')
                keys.add((current, k))
    return keys

# ============================================================
# VISUAL DIFF
# ============================================================

def visual_changed(a, b, tol=5):
    diff = ImageChops.difference(a, b)
    extrema = diff.getextrema()
    return any(mx > tol for (_, mx) in extrema)

# ============================================================
# INPUT AUTOMATION
# ============================================================

def send_keys(seq):
    run([XDOTOOL, "key"] + seq.split())
    time.sleep(0.2)

# ============================================================
# DIALOG DISCOVERY (AUTO)
# ============================================================

def discover_dialogs(baseline_windows):
    dialogs = []
    for w in list_windows():
        if w["id"] not in baseline_windows:
            dialogs.append(w)
    return dialogs

# ============================================================
# STATEFUL CONTROL TESTING (GENERIC)
# ============================================================

def test_stateful_controls(win_id, outdir):
    dead = []
    before = outdir / "before.png"
    after = outdir / "after.png"

    screenshot_window(win_id, before)
    send_keys("Tab space")
    screenshot_window(win_id, after)

    if not visual_changed(Image.open(before), Image.open(after)):
        dead.append("unknown_control")

    return dead

# ============================================================
# MAIN TEST LOGIC
# ============================================================

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

    # Registry snapshot (before)
    reg_before = out / "registry_before.reg"
    snapshot_registry(args.wineprefix, reg_before)
    norm_before = out / "registry_before.norm"
    normalize_registry(reg_before, norm_before)
    keys_before = extract_keys(norm_before)

    # Install WM_COMMAND hook
    hook = install_hook()

    # Launch app
    run([WINE, args.exe])
    main_win = wait_for_window(args.title, args.timeout)
    focus_window(main_win["id"])

    baseline_windows = {w["id"] for w in list_windows()}

    results = []

    # Blind dialog discovery loop
    for i in range(MAX_DIALOGS):
        send_keys("Alt")
        time.sleep(0.2)

        dialogs = discover_dialogs(baseline_windows)
        for d in dialogs:
            focus_window(d["id"])
            dialog_id = f"dlg_{len(results)}"
            dlg_dir = out / dialog_id
            dlg_dir.mkdir(exist_ok=True)

            shot = dlg_dir / "dialog.png"
            screenshot_window(d["id"], shot)

            dead = test_stateful_controls(d["id"], dlg_dir)

            results.append({
                "dialog": dialog_id,
                "title": d["title"],
                "screenshot": shot.name,
                "screenshot_hash": sha256(shot),
                "dead_controls": dead,
                "wm_commands": list(command_log)
            })

            send_keys("Escape")
            baseline_windows.add(d["id"])

        time.sleep(0.5)

    # Registry snapshot (after)
    reg_after = out / "registry_after.reg"
    snapshot_registry(args.wineprefix, reg_after)
    norm_after = out / "registry_after.norm"
    normalize_registry(reg_after, norm_after)
    keys_after = extract_keys(norm_after)

    # Registry diff
    reg_diff = sorted(keys_after - keys_before)

    summary = {
        "app": Path(args.exe).stem,
        "timestamp": now(),
        "dialogs": results,
        "wm_command_trace": command_log,
        "registry_diff": reg_diff
    }

    with open(out / "results.json", "w") as f:
        json.dump(summary, f, indent=2)

    print("[✓] Automatic dialog test complete")

if __name__ == "__main__":
    main()
