# Test Crash Dialog Branch

## ⚠️ DO NOT MERGE THIS BRANCH ⚠️

This branch exists solely for testing and documentation purposes related to PR #2069.

## Purpose

This branch adds a deliberate crash trigger to capture screenshots of the improved crash dialog for review purposes.

## Changes

**File:** `GeneralsMD/Code/Main/WinMain.cpp`
- Added `-testcrash` command line flag handler (lines 877-884)
- Triggers a null pointer dereference crash after MiniDumper initialization
- Crash occurs before window initialization, ensuring crash handler is active

## Usage

### Build the game:
```bash
cmake --preset vc6
cmake --build build/vc6 --target generalszh
```

### Run with test crash:
```bash
generalszh.exe -testcrash
```

## What to Capture

When you run with `-testcrash`, you should see:

### 1. Release Build (without debug symbols)
The crash dialog should show:
```
Game Crash
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
The game encountered a critical error and needs to close.

Crash report saved to:
C:\Users\[Username]\Documents\Command and Conquer Generals Zero Hour Data\CrashInfo.txt

Minidump files saved to:
C:\Users\[Username]\Documents\Command and Conquer Generals Zero Hour Data\CrashDumps\

Please report the issue:
https://github.com/TheSuperHackers/GeneralsCrashReports/issues

                        [ OK ]
```

**Note:** Without debug symbols, the "Location:" section will not appear because the crash location cannot be determined.

### 2. Debug Build (with debug symbols/PDB)
The crash dialog should additionally show:
```
Location:
  C:\...\GeneralsMD\Code\Main\WinMain.cpp(883) : WinMain 0x00401234
```

## Files to Check After Crash

1. **CrashInfo.txt** - Contains full stack trace and crash details
2. **CrashDumps\\** - Contains .dmp files for debugging

## Screenshots Needed for PR #2069

Capture screenshots of:
1. ✅ Dialog without crash location (Release build)
2. ✅ Dialog with crash location (Debug build with PDB)
3. ✅ CrashInfo.txt file content
4. ✅ CrashDumps folder showing .dmp files

## Testing Both Games

The change is in GeneralsMD (Zero Hour). To test Generals:

```bash
# Build Generals
cmake --build build/vc6 --target generals

# Run with test crash
generals.exe -testcrash
```

## After Testing

Once screenshots are captured and posted to PR #2069:
1. **Do NOT merge this branch**
2. **Delete this branch** or keep it archived for future testing reference
3. Return to `improve-crash-message` branch for actual PR work

## Related Files

- **PR:** https://github.com/TheSuperHackers/GeneralsGameCode/pull/2069
- **Analysis:** See `crash-message-review-analysis` branch for detailed Q&A
- **Draft Responses:** `/workspace/project/DRAFT_PR_RESPONSES.md`

---

**Branch created:** 2026-01-11
**Purpose:** Screenshot capture for PR #2069 review
**Status:** Test-only, DO NOT MERGE
