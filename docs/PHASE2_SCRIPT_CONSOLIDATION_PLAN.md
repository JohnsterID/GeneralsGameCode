# Phase 2 Script Consolidation Plan

**Date:** January 23, 2026  
**Branch:** `dev/mfc-to-wxwidgets-tools`  
**Status:** TODO - Future Work

---

## Overview

Phase 2 event handler integration revealed bugs in the original automation that required new fix scripts. These scripts contain improvements that need to be consolidated back into the main automation pipeline.

---

## Scripts Added

### 1. `integrate_phase2_events.py` (Original)
- **Purpose:** Original Phase 2 event integration automation
- **Issues Found:**
  - Mapped all ON_NOTIFY events to generic `various &event` type
  - Used EVT_TREE_SEL_CHANGED for all notifications regardless of control type
  - Resulted in 22 compilation errors across 8 dialogs

### 2. `fix_phase2_notify_events.py` (Fix Script)
- **Purpose:** Automated fix for ON_NOTIFY event type bugs
- **Features:**
  - Complete MFC notification code mapping table
  - Proper event type detection (wxSpinEvent, wxListEvent, wxTreeEvent)
  - Proper event macro selection (EVT_SPIN, EVT_LIST_*, EVT_TREE_*)
  - Successfully fixed all 22 broken handlers

---

## Consolidation Tasks

### Priority 1: Update Event Type Mapping

**Target Script:** `mfc2wx_events.py` (or equivalent Phase 2 generator)

**Required Changes:**
1. Add notification code mapping table from `fix_phase2_notify_events.py`:
   ```python
   NOTIFY_CODE_MAP = {
       'UDN_DELTAPOS': ('EVT_SPIN', 'wxSpinEvent'),
       'LVN_ITEMCHANGED': ('EVT_LIST_ITEM_SELECTED', 'wxListEvent'),
       'TVN_SELCHANGED': ('EVT_TREE_SEL_CHANGED', 'wxTreeEvent'),
       'NM_DBLCLK': ('EVT_LIST_ITEM_ACTIVATED', 'wxListEvent'),
       'NM_RELEASEDCAPTURE': ('EVT_SLIDER', 'wxCommandEvent'),
       'LVN_KEYDOWN': ('EVT_LIST_KEY_DOWN', 'wxListEvent'),
       # ... add remaining codes
   }
   ```

2. Replace generic `various &event` handling with notification-specific types

3. Add control type detection logic (spin, list, tree, etc.)

### Priority 2: Improve ON_NOTIFY Parsing

**Current Issue:** Original script doesn't differentiate notification types

**Required Improvements:**
1. Parse notification code from MFC ON_NOTIFY macro:
   ```cpp
   ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN, OnDeltaposSpin)
   ```
   Extract: `UDN_DELTAPOS`, `IDC_SPIN`, `OnDeltaposSpin`

2. Look up proper wxWidgets event from notification code

3. Generate correct event macro and parameter type

### Priority 3: Validation Integration

**Add Compilation Test:**
1. After generating event handlers, run compilation test
2. Detect type mismatches early
3. Report specific errors with fix suggestions

---

## Implementation Plan

### Phase A: Analysis (1-2 hours)
1. Review `mfc2wx_events.py` current implementation
2. Identify where ON_NOTIFY handling occurs
3. Document current logic flow

### Phase B: Integration (2-3 hours)
1. Add notification code mapping table
2. Implement control type detection
3. Update event type generation logic
4. Add proper event macro selection

### Phase C: Testing (1-2 hours)
1. Re-run Phase 2 automation on all 59 dialogs
2. Verify 0 compilation errors
3. Compare output with manually-fixed versions
4. Ensure 100% match

### Phase D: Cleanup (30 minutes)
1. Archive `fix_phase2_notify_events.py` (keep for reference)
2. Archive `integrate_phase2_events.py` (keep for reference)
3. Update documentation
4. Update README with improved capabilities

---

## Testing Checklist

After consolidation, verify:
- [ ] All 59 dialogs generate correct event tables
- [ ] All 203 event handlers have correct types
- [ ] All notification events properly mapped
- [ ] No compilation errors
- [ ] No manual fixes needed
- [ ] Linux build: 59/59 success
- [ ] MinGW build: 58/59 success (XxxBrowseDirectory is Phase 1 issue)

---

## Known Notification Codes

From `fix_phase2_notify_events.py`, the complete mapping table:

| MFC Notification Code | wxWidgets Event Macro | Event Type |
|----------------------|----------------------|------------|
| UDN_DELTAPOS | EVT_SPIN | wxSpinEvent |
| LVN_ITEMCHANGED | EVT_LIST_ITEM_SELECTED | wxListEvent |
| TVN_SELCHANGED | EVT_TREE_SEL_CHANGED | wxTreeEvent |
| NM_DBLCLK | EVT_LIST_ITEM_ACTIVATED | wxListEvent |
| NM_RELEASEDCAPTURE | EVT_SLIDER | wxCommandEvent |
| LVN_KEYDOWN | EVT_LIST_KEY_DOWN | wxListEvent |

Additional codes to research and add:
- LVN_COLUMNCLICK
- TVN_ITEMEXPANDING
- TVN_ITEMEXPANDED
- NM_CLICK
- NM_RCLICK
- HDN_ITEMCLICK
- etc.

---

## Success Metrics

The consolidation is successful when:
1. ✅ Original automation generates Phase 2 code with ZERO bugs
2. ✅ No manual fixes needed after automation
3. ✅ Compilation succeeds on first try (Linux + MinGW)
4. ✅ All event types correct (203/203)
5. ✅ All event macros correct (203/203)

---

## Files Involved

### Current Dev Branch Scripts
- `scripts/mfc2wx_events.py` - Main event integration automation
- `scripts/batch_convert_all_dialogs.py` - Batch processing
- `scripts/rc2xrc.py` - RC to XRC conversion
- `scripts/xrc2cpp.py` - XRC to C++ class generation

### New Scripts (to be consolidated)
- `scripts/integrate_phase2_events.py` - Original Phase 2 automation
- `scripts/fix_phase2_notify_events.py` - ON_NOTIFY bug fixes

### Archive After Consolidation
- Move to `scripts/archive/phase2-v1/`:
  - `integrate_phase2_events.py` (original, buggy)
  - `fix_phase2_notify_events.py` (manual fix, reference)

---

## Timeline

**Recommended Schedule:**
- Week 1: Complete Phase 3 implementation migration
- Week 2: Return to tools branch for consolidation
- Week 3: Re-test entire pipeline end-to-end
- Week 4: Documentation and archival

**Reason for Delay:** Focus on completing Phase 3 first, then improve tooling based on lessons learned.

---

## Related Documentation

- `/workspace/project/PHASE_2_FIX_COMPLETE.md` - Bug fix details
- `/workspace/project/PHASE_2_VALIDATION_FAILURE_REPORT.md` - Original issue discovery
- `/workspace/project/PHASE_2_MINGW_TEST_RESULTS.md` - Cross-platform validation
- `scripts/README.md` - Toolkit usage documentation

---

**Status:** Deferred until after Phase 3  
**Priority:** Medium (tooling improvement, not blocking)  
**Assignee:** Future automation work
