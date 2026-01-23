# Phase 1 RC to XRC Control ID Parsing Bug Fix

**Date:** January 23, 2026  
**Branch:** `dev/mfc-to-wxwidgets-tools`  
**Severity:** HIGH - Causes compilation failures  
**Status:** ✅ FIXED  

---

## Executive Summary

Fixed a critical bug in `rc2xrc.py` that incorrectly parsed control IDs from RC files, causing invalid C++ identifiers to be generated. This bug affected the XxxBrowseDirectory dialog and would affect any dialog with controls positioned at specific coordinates.

**Impact:**
- 1 of 59 Phase 2 dialogs affected (XxxBrowseDirectory)
- Compilation failure with invalid C++ syntax
- Affects both Linux and MinGW builds

**Root Cause:**
- Greedy regex pattern `(\S+)` captured too much (coordinates + commas)
- No sanitization of control names into valid C++ identifiers

**Fix:**
- Changed regex to match only valid IDs: `(-?\d+|[a-zA-Z_]\w*)`
- Added `sanitize_cpp_identifier()` to `xrc2cpp.py` for defense-in-depth

---

## Bug Discovery

### Symptoms
During MinGW cross-compilation testing of Phase 2 dialogs:

```
Core/Tools/W3DView/dialogs/XxxBrowseDirectory_wx.h:48:23: 
error: expected unqualified-id before ',' token
   48 |     wxStaticText *m_20627,7,7,92;
      |                       ^
```

### Analysis
The generated header contained invalid member variable declarations:
```cpp
wxStaticText *m_20627,7,7,92;    // INVALID C++!
wxStaticText *m_-1,7,107,92;     // INVALID C++!
```

Valid C++ identifiers cannot contain:
- Commas (`,`)
- Hyphens (`-`) at the start
- Start with digits without prefix

---

## Root Cause Analysis

### Original RC File Format
```rc
IDD_XXX_BROWSE_DIRECTORY DIALOGEX 0, 0, 217, 178
BEGIN
    LTEXT  "Directory &name:",20627,7,7,92,16,0,0,0xd09e5093
    LTEXT  "Dri&ves:",-1,7,107,92,9,0,0,0xd04affff
END
```

**RC Control Format:**
```
LTEXT "text", ID, x, y, width, height, [style], [exstyle], [helpid]
```

So for the first LTEXT:
- Text: `"Directory &name:"`
- ID: `20627`
- X: `7`, Y: `7`, Width: `92`, Height: `16`

### Bug in rc2xrc.py

**Original Code (Line 198):**
```python
coords_match = re.match(r',\s*(\S+)\s*,\s*(-?\d+)\s*,\s*(-?\d+)\s*,\s*(-?\d+)\s*,\s*(-?\d+)', rest)
```

**Problem:**
- Pattern `(\S+)` means "match one or more non-whitespace characters"
- In `,20627,7,7,92,16`, there are NO spaces between the numbers!
- So `(\S+)` greedily matches `20627,7,7,92` as a single token
- Stopped only when it hit the pattern `,\s*(-?\d+)` for the height field

**Result:**
- Extracted ID: `"20627,7,7,92"` ❌ (should be `"20627"`)
- Extracted ID: `"-1,7,107,92"` ❌ (should be `"-1"`)

### Propagation to XRC

Generated invalid XRC file:
```xml
<object class="wxStaticText" name="20627,7,7,92">
  <label>Directory &amp;name:</label>
</object>
<object class="wxStaticText" name="-1,7,107,92">
  <label>Dri&amp;ves:</label>
</object>
```

### Propagation to C++

`xrc2cpp.py` then generated:
```cpp
m_20627,7,7,92 = XRCCTRL(*this, "20627,7,7,92", wxStaticText);
wxStaticText *m_20627,7,7,92;  // ❌ INVALID C++!
```

---

## The Fix

### Fix #1: rc2xrc.py - Correct ID Extraction

**Changed Pattern:**
```python
# OLD: coords_match = re.match(r',\s*(\S+)\s*,', rest)
# NEW:
coords_match = re.match(r',\s*(-?\d+|[a-zA-Z_]\w*)\s*,', rest)
```

**Pattern Explanation:**
- `(-?\d+|[a-zA-Z_]\w*)` matches ONLY valid RC identifiers:
  - `-?\d+`: Optional minus + digits (e.g., `-1`, `20627`)
  - `[a-zA-Z_]\w*`: Identifier (e.g., `IDC_BUTTON1`)
- Stops at first comma, doesn't capture coordinates

**Files Changed:**
- Line 169: ICON control ID parsing
- Line 199: Labeled controls (LTEXT, PUSHBUTTON, etc.)
- Line 215: Unlabeled controls (EDITTEXT, COMBOBOX, LISTBOX)
- Line 239: CONTROL with text
- Line 255: CONTROL with bitmap

### Fix #2: xrc2cpp.py - Defensive Sanitization

**Added Function:**
```python
def sanitize_cpp_identifier(name):
    """
    Convert a control name to a valid C++ identifier.
    - Replace invalid characters (commas, hyphens, etc.) with underscores
    - Ensure it doesn't start with a digit
    - Ensure it's not empty
    """
    if not name:
        return "ctrl"
    
    # Replace invalid characters with underscores
    sanitized = re.sub(r'[^a-zA-Z0-9_]', '_', name)
    
    # Ensure it doesn't start with a digit
    if sanitized and sanitized[0].isdigit():
        sanitized = '_' + sanitized
    
    # Ensure it's not empty
    if not sanitized:
        return "ctrl"
    
    return sanitized
```

**Usage (Line 125):**
```python
# OLD: var_name = f"m_{ctrl_name.lower()}"
# NEW:
var_name = f"m_{sanitize_cpp_identifier(ctrl_name).lower()}"
```

**Benefits:**
- Defense-in-depth: Even if bad IDs slip through rc2xrc, they're sanitized
- Handles future edge cases (hyphens, special chars, etc.)
- Ensures valid C++ identifiers always

---

## Test Results

### Test 1: rc2xrc.py Control ID Parsing

**Test Script:** `scripts/test_rc2xrc_fix.py`

```
✓ Control 0: LTEXT ID=20627 (correct!)
✓ Control 1: EDITTEXT ID=20626 (correct!)
✓ Control 2: LISTBOX ID=1121 (correct!)
✓ Control 3: LTEXT ID=-1 (correct!)
✓ Control 4: COMBOBOX ID=1137 (correct!)
✓ Control 5: DEFPUSHBUTTON ID=1 (correct!)
✓ Control 6: PUSHBUTTON ID=2 (correct!)

✅ ALL TESTS PASSED!

Before fix:
  - ID for LTEXT would be: '20627,7,7,92' (INVALID!)
  - ID for LTEXT would be: '-1,7,107,92' (INVALID!)

After fix:
  - ID for LTEXT is: '20627' (valid)
  - ID for LTEXT is: '-1' (valid)
```

### Test 2: xrc2cpp.py Sanitization

**Test Script:** `scripts/test_xrc2cpp_sanitization.py`

```
✓ '20627' → '_20627' (Numeric ID - prefix with underscore)
✓ '-1' → '_1' (Negative ID - sanitize minus and prefix)
✓ '20627,7,7,92' → '_20627_7_7_92' (Replace commas)
✓ '-1,7,107,92' → '_1_7_107_92' (Sanitize both)
✓ 'IDC_BUTTON1' → 'IDC_BUTTON1' (Valid - unchanged)

✅ ALL TESTS PASSED!

Before fix:
  wxStaticText *m_20627,7,7,92;  // ❌ INVALID C++!
  wxStaticText *m_-1,7,107,92;   // ❌ INVALID C++!

After fix:
  wxStaticText *m__20627_7_7_92; // ✅ Valid C++ identifier
  wxStaticText *m__1_7_107_92;   // ✅ Valid C++ identifier
```

---

## Impact Assessment

### Dialogs Affected
- **XxxBrowseDirectory:** Only known affected dialog
- **Potential:** Any dialog with controls using numeric IDs positioned without spaces

### Build Impact
- **Before fix:** 58/59 dialogs compiled (98.3% success)
- **After fix:** Expected 59/59 dialogs (100% success)

### Breaking Changes
**None.** The fix only affects:
1. Future re-conversions of RC files
2. Sanitization is backward-compatible

### Migration Required
**Yes**, for XxxBrowseDirectory:
1. Re-run `rc2xrc.py` on original W3DView.rc
2. Re-run `xrc2cpp.py` to regenerate C++ files
3. Recompile and test

---

## Prevention Measures

### Immediate
- ✅ Fixed regex patterns in rc2xrc.py
- ✅ Added sanitization in xrc2cpp.py
- ✅ Created test suite

### Future
1. **Add Validation:** Check generated XRC for invalid control names
2. **Add CI Test:** Parse all RC files and validate XRC output
3. **Documentation:** Update toolkit README with known edge cases
4. **Regression Tests:** Add XxxBrowseDirectory to test suite

---

## Lessons Learned

### What Went Right
- MinGW cross-compilation testing caught the bug
- Minimal dialogs affected (1/59)
- Root cause identified quickly through compilation error

### What Went Wrong
- Original rc2xrc.py used greedy regex without validation
- No sanitization defense layer
- No test suite for RC parsing edge cases

### Improvements
- Always use specific patterns, never greedy `\S+` for structured data
- Add defense-in-depth sanitization layers
- Test with diverse RC files (numeric IDs, negative IDs, etc.)
- Add validation between pipeline stages (RC → XRC → C++)

---

## Files Modified

### dev/mfc-to-wxwidgets-tools Branch

**scripts/rc2xrc.py:**
- Line 169: Fixed ICON ID parsing
- Line 199: Fixed labeled control ID parsing (LTEXT, PUSHBUTTON, etc.)
- Line 215: Fixed unlabeled control ID parsing (EDITTEXT, COMBOBOX, LISTBOX)
- Line 239: Fixed CONTROL with text ID parsing
- Line 255: Fixed CONTROL bitmap ID parsing

**scripts/xrc2cpp.py:**
- Lines 13-34: Added `sanitize_cpp_identifier()` function
- Line 125: Applied sanitization to variable name generation

**scripts/test_rc2xrc_fix.py:**
- NEW: Test suite for RC parsing fix

**scripts/test_xrc2cpp_sanitization.py:**
- NEW: Test suite for C++ identifier sanitization

---

## Verification Checklist

After fix is applied:

- [ ] Re-run rc2xrc.py on W3DView.rc for XxxBrowseDirectory dialog
- [ ] Verify XRC file has valid control IDs (no commas)
- [ ] Re-run xrc2cpp.py to regenerate C++ files
- [ ] Verify generated C++ has valid member variable names
- [ ] Compile XxxBrowseDirectory_wx.cpp on Linux (GCC)
- [ ] Compile XxxBrowseDirectory_wx.cpp on MinGW (cross-compilation)
- [ ] Run test suite: `test_rc2xrc_fix.py`
- [ ] Run test suite: `test_xrc2cpp_sanitization.py`
- [ ] Update Phase 2 MinGW test results (expect 59/59 success)

---

## Related Documentation

- Phase 2 MinGW Test Results: `/workspace/project/PHASE_2_MINGW_TEST_RESULTS.md`
- Toolkit README: `scripts/README.md`
- Phase 2 Script Consolidation Plan: `docs/PHASE2_SCRIPT_CONSOLIDATION_PLAN.md`

---

**Status:** ✅ FIXED  
**Tests:** ✅ PASSING  
**Ready for:** Re-conversion of XxxBrowseDirectory dialog
