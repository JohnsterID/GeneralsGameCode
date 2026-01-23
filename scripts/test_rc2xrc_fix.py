#!/usr/bin/env python3
"""
Test script to verify rc2xrc.py control ID parsing fix
"""

import sys
sys.path.insert(0, '/workspace/project/GeneralsGameCode/scripts')

from rc2xrc import parse_rc_dialog

# Test RC content with the problematic control IDs from XxxBrowseDirectory
test_rc = """
IDD_XXX_BROWSE_DIRECTORY DIALOGEX 0, 0, 217, 178
STYLE DS_MODALFRAME | WS_POPUP | WS_CAPTION | WS_SYSMENU
CAPTION "Select Directory"
FONT 8, "MS Sans Serif"
BEGIN
    LTEXT           "Directory &name:",20627,7,7,92,16
    EDITTEXT        20626,7,26,143,12,ES_AUTOHSCROLL
    LISTBOX         1121,7,41,143,64,LBS_SORT | WS_VSCROLL
    LTEXT           "Dri&ves:",-1,7,107,92,9
    COMBOBOX        1137,7,117,143,68,CBS_DROPDOWNLIST | WS_VSCROLL
    DEFPUSHBUTTON   "OK",1,160,7,50,14,WS_GROUP
    PUSHBUTTON      "Cancel",2,160,24,50,14,WS_GROUP
END
"""

print("Testing rc2xrc.py control ID parsing fix...")
print("=" * 60)

dialog = parse_rc_dialog(test_rc, "IDD_XXX_BROWSE_DIRECTORY")

if dialog is None:
    print("❌ FAILED: Dialog not parsed!")
    sys.exit(1)

print(f"✓ Dialog parsed: {dialog.id}")
print(f"✓ Controls found: {len(dialog.controls)}")
print()

# Check the problematic controls
expected = [
    ("LTEXT", "20627", "Directory &name:"),
    ("EDITTEXT", "20626", ""),
    ("LISTBOX", "1121", ""),
    ("LTEXT", "-1", "Dri&ves:"),
    ("COMBOBOX", "1137", ""),
    ("DEFPUSHBUTTON", "1", "OK"),
    ("PUSHBUTTON", "2", "Cancel"),
]

all_pass = True
for i, (expected_type, expected_id, expected_text) in enumerate(expected):
    if i >= len(dialog.controls):
        print(f"❌ Control {i}: Missing!")
        all_pass = False
        continue
    
    ctrl = dialog.controls[i]
    
    # Check type
    if ctrl.type != expected_type:
        print(f"❌ Control {i}: Type mismatch - expected {expected_type}, got {ctrl.type}")
        all_pass = False
    
    # Check ID (this is the critical test!)
    if ctrl.id != expected_id:
        print(f"❌ Control {i}: ID mismatch - expected '{expected_id}', got '{ctrl.id}'")
        print(f"   This is the bug! ID should be '{expected_id}', not '{ctrl.id}'")
        all_pass = False
    else:
        print(f"✓ Control {i}: {ctrl.type} ID={ctrl.id} (correct!)")
    
    # Check text
    if ctrl.text != expected_text:
        print(f"   Warning: Text mismatch - expected '{expected_text}', got '{ctrl.text}'")

print()
print("=" * 60)
if all_pass:
    print("✅ ALL TESTS PASSED! The fix works correctly.")
    print()
    print("Before fix:")
    print("  - ID for LTEXT would be: '20627,7,7,92' (INVALID C++ identifier!)")
    print("  - ID for LTEXT would be: '-1,7,107,92' (INVALID C++ identifier!)")
    print()
    print("After fix:")
    print("  - ID for LTEXT is: '20627' (valid)")
    print("  - ID for LTEXT is: '-1' (valid)")
    sys.exit(0)
else:
    print("❌ SOME TESTS FAILED! The fix needs more work.")
    sys.exit(1)
