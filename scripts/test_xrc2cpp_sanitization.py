#!/usr/bin/env python3
"""
Test script to verify xrc2cpp.py control ID sanitization
"""

import sys
sys.path.insert(0, '/workspace/project/GeneralsGameCode/scripts')

from xrc2cpp import sanitize_cpp_identifier

print("Testing xrc2cpp.py control ID sanitization...")
print("=" * 70)

test_cases = [
    # (input, expected_output, description)
    ("20627", "_20627", "Numeric ID - should prefix with underscore"),
    ("-1", "_1", "Negative ID - should sanitize minus sign and prefix"),
    ("20627,7,7,92", "_20627_7_7_92", "ID with commas - should replace commas with underscores"),
    ("-1,7,107,92", "_1_7_107_92", "Negative ID with commas - should sanitize both"),
    ("IDC_BUTTON1", "IDC_BUTTON1", "Valid identifier - should remain unchanged"),
    ("my-control", "my_control", "Hyphenated name - should replace hyphen"),
    ("", "ctrl", "Empty string - should use default"),
    ("123", "_123", "Pure numeric - should prefix"),
    ("ABC", "ABC", "Uppercase letters - should remain unchanged"),
]

all_pass = True
for input_name, expected, description in test_cases:
    result = sanitize_cpp_identifier(input_name)
    
    if result == expected:
        print(f"✓ '{input_name}' → '{result}' ({description})")
    else:
        print(f"❌ '{input_name}' → '{result}' (expected '{expected}') - {description}")
        all_pass = False

print()
print("=" * 70)
print("Real-world test case from XxxBrowseDirectory dialog:")
print()

# Test the actual problematic IDs
problematic_ids = [
    ("20627,7,7,92", "_20627_7_7_92"),
    ("-1,7,107,92", "_1_7_107_92"),
]

for input_id, expected_var in problematic_ids:
    sanitized = sanitize_cpp_identifier(input_id)
    var_name = f"m_{sanitized.lower()}"
    expected_full = f"m_{expected_var.lower()}"
    
    if var_name == expected_full:
        print(f"✓ Control ID '{input_id}' → variable '{var_name}'")
    else:
        print(f"❌ Control ID '{input_id}' → variable '{var_name}' (expected '{expected_full}')")
        all_pass = False

print()
print("Before fix:")
print("  wxStaticText *m_20627,7,7,92;  // ❌ INVALID C++!")
print("  wxStaticText *m_-1,7,107,92;   // ❌ INVALID C++!")
print()
print("After fix:")
print("  wxStaticText *m__20627_7_7_92; // ✅ Valid C++ identifier")
print("  wxStaticText *m__1_7_107_92;   // ✅ Valid C++ identifier")
print()

print("=" * 70)
if all_pass:
    print("✅ ALL TESTS PASSED! The sanitization works correctly.")
    sys.exit(0)
else:
    print("❌ SOME TESTS FAILED!")
    sys.exit(1)
