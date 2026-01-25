# MFC to wxWidgets Visual Comparison Testing Tools

## Overview
This directory contains tools for visual and behavioral comparison between the original MFC W3DView and the wxWidgets conversion.

## Available Executables

### MFC Versions (from CI artifacts)
1. **W3DViewV.exe** (Generals, MSVC build, 1.8MB)
   - Location: `/workspace/project/mfc-artifacts/W3DViewV.exe`
   - Built with: Modern MSVC compiler
   - Branch: main (latest CI)

2. **W3DViewZH.exe** (Zero Hour, MSVC build, 1.8MB)
   - Location: `/workspace/project/mfc-artifacts/ZH/W3DViewZH.exe`
   - Built with: Modern MSVC compiler
   - Branch: main (latest CI)

### wxWidgets Version (our conversion)
3. **W3DViewV.exe** (Generals, MinGW build, 59MB)
   - Location: `/workspace/project/GeneralsGameCode/build/Generals/W3DViewV.exe`
   - Built with: MinGW-w64 i686 cross-compiler
   - Branch: feat/w3dview-wxwidgets-conversion

## Size Difference Explanation
- **MFC:** 1.8MB (dynamically linked to Windows MFC libraries)
- **wxWidgets:** 59MB (statically linked wxWidgets + all dialogs XRC resources)

## Testing Strategy

### Phase 1: Smoke Test (30 min)
Test if executables run under Wine:
1. Launch MFC W3DViewZH.exe
2. Launch wxWidgets W3DViewV.exe
3. Verify basic functionality (open, close)

### Phase 2: Dialog Comparison (2-3 hours)
For each "complete" dialog (34 total):
1. Open in MFC version, screenshot
2. Open in wxWidgets version, screenshot
3. Compare visually
4. Document differences

### Phase 3: Interaction Testing (2-3 hours)
Test dialog functionality:
1. Slider movements
2. Checkbox states
3. Text input
4. File dialogs
5. wxConfig persistence

### Phase 4: Report Generation (1 hour)
Create comparison report with:
1. Screenshots side-by-side
2. Difference highlights
3. Pass/fail for each dialog
4. Issues found and recommended fixes

## Tools Provided

1. **screenshot_compare.py** - Screenshot comparison tool
2. **dialog_tester.py** - Automated dialog interaction
3. **run_comparison.py** - Main test runner
4. **generate_report.py** - HTML report generator

## Test Environment

### Wine Setup
```bash
export DISPLAY=:99
export WINEARCH=win32
export WINEPREFIX=/opt/wineprefix32
```

### Game Directory
```
/workspace/project/Command & Conquer Generals - Zero Hour/
```

## Expected Results

### Success Criteria
- All 34 "complete" dialogs open without crashes
- Visual layout matches MFC version (±5% tolerance)
- Controls are functional
- Settings persist correctly via wxConfig

### Known Acceptable Differences
1. Font rendering (Windows GDI vs Wine rendering)
2. Minor pixel shifts (±3px acceptable)
3. Control themes (Windows XP vs default wxWidgets theme)

## Failure Criteria
- Dialog doesn't open
- Crash on interaction
- Controls non-functional
- Data not persisting
- Major layout differences (>10%)

## Next Steps After Testing
1. If all pass: Continue with remaining 25 dialogs
2. If issues found: Fix patterns, update TODOs, re-test
3. Document all findings in testing report
