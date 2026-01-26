# Comment Pattern Guide for W3DView wxWidgets Conversion

## Purpose
Establish clear patterns for when to use NOTE vs TODO comments, and when to remove them.

---

## Pattern 1: NOTE (Permanent - Never Remove)

**Usage**: Permanent architectural or design information

**Examples**:
```cpp
// NOTE: Lighting comes BEFORE Camera in MFC IDR_MAINFRAME menu order
// NOTE: In MFC, Animation is in separate menu resource (IDR_ANI_MENU)
// NOTE: These methods exist in MFC but are NOT USED in AnimationSpeed dialog
```

**When to use**:
- Documenting permanent MFC architectural differences
- Explaining design decisions that won't change
- Noting unused MFC features that we're keeping for compatibility

**When to remove**: NEVER - these stay forever

---

## Pattern 2: TODO (Temporary - Remove When Fixed)

**Usage**: Incomplete implementations or blockers

**Examples**:
```cpp
// TODO(MFC-Infrastructure): Full implementation requires 2D scene support
// TODO(MFC-Match): Investigate if these are used elsewhere in codebase
// BLOCKER TODO: dx8wrapper.h inclusion causes StringClass conflicts
```

**When to use**:
- Missing infrastructure that blocks full implementation
- Incomplete MFC matching that needs investigation
- Known blockers that need resolution

**When to remove**: When the issue is fixed/implemented

---

## Pattern 3: Frame Handler Comments (Minimal)

**Frame handlers should have minimal comments**:
```cpp
void W3DViewFrame::OnBackgroundBmp(wxCommandEvent &event)
{
    // MFC: MainFrm.cpp (OnBackgroundBmp - shows dialog)
    // Dialog: BackgroundBMPDialog.cpp:38-92 (OnInitDialog, OnOK)
    BackgroundBmp dialog(this);
    dialog.ShowModal();
}
```

**Keep detailed TODOs in implementations, not frame handlers**:
- Frame handler: Just MFC reference (2-3 lines)
- Implementation: Detailed TODO with what's needed

**Example**:
```cpp
// Frame handler (w3dviewframe_wx.cpp):
void W3DViewFrame::OnBackgroundBmp(wxCommandEvent &event)
{
    // MFC: MainFrm.cpp (OnBackgroundBmp)
    // Dialog: BackgroundBMPDialog.cpp:38-92
    BackgroundBmp dialog(this);
    dialog.ShowModal();
}

// Implementation (w3dviewdoc_wx.cpp):
void W3DViewDoc::SetBackgroundBMP(const wxString& filename)
{
    // TODO(MFC-Infrastructure): Full implementation requires 2D scene support
    // MFC uses separate m_pC2DScene (SceneClass*) for 2D overlay elements
    // MFC implementation:
    //   1. Remove old background BMP: m_pCBackgroundBMP->Remove(), Release_Ref()
    //   2. Create new Bitmap2DObjClass: new Bitmap2DObjClass(filename, 0.5f, 0.5f, TRUE, FALSE)
    //   3. Add to 2D scene: m_pC2DScene->Add_Render_Object(m_pCBackgroundBMP)
    //   4. Store filename: m_stringBackgroundBMP = filename
    //
    // Current implementation: Store filename only (dialog can save/load setting)
    // Full implementation requires:
    //   - SceneClass *m_2DScene member in document
    //   - 2D scene creation/management in document lifecycle
    //   - 2D rendering support in graphics view
    
    m_backgroundBMPFilename = filename;
    Modify(true);
}
```

---

## Pattern 4: When to Remove Comments

### Remove NOTE: NEVER
- NOTEs are permanent architectural documentation

### Remove TODO when:
1. **Infrastructure implemented**:
   ```cpp
   // TODO(MFC-Infrastructure): Full implementation requires 2D scene support
   ```
   Remove when: 2D scene infrastructure is added

2. **Blocker resolved**:
   ```cpp
   // BLOCKER TODO: dx8wrapper.h inclusion causes conflicts
   ```
   Remove when: StringClass conflicts resolved and dx8wrapper.h can be included

3. **Investigation complete**:
   ```cpp
   // TODO(MFC-Match): Investigate if these are used elsewhere
   ```
   Remove when: Investigation done and decision made

4. **Implementation complete**:
   ```cpp
   // TODO(MFC-Verify): Verify dialog matches MFC exactly
   ```
   Remove when: Dialog verified and fully implemented

---

## Decision Tree

```
Is this information permanent? (menu structure, design decision)
├─ YES → Use NOTE: (never remove)
└─ NO → Is functionality incomplete/blocked?
    ├─ YES → Use TODO(category): (remove when fixed)
    └─ NO → Just use MFC reference (no NOTE/TODO)
```

---

## Examples from Codebase

### ✅ Correct NOTE (Permanent):
```cpp
// NOTE: Lighting comes BEFORE Camera in MFC IDR_MAINFRAME menu order
wxMenu *lightMenu = new wxMenu;
```

### ✅ Correct TODO (Temporary):
```cpp
// TODO(MFC-Infrastructure): Full implementation requires 2D scene support
m_backgroundBMPFilename = filename;
```

### ✅ Correct Frame Handler (Minimal):
```cpp
void W3DViewFrame::OnCameraSettings(wxCommandEvent &event)
{
    // MFC: MainFrm.cpp (OnCameraSettings - shows dialog)
    // Dialog: CameraSettingsDialog.cpp:85-197 (OnInitDialog, OnOK)
    CameraSettings dialog(this);
    dialog.ShowModal();
}
```

### ❌ Incorrect (was using NOTE for incomplete feature):
```cpp
// NOTE: Full BMP display requires 2D scene infrastructure  // WRONG - should be TODO
```

---

## Summary

| Comment Type | Purpose | Lifetime | Location |
|--------------|---------|----------|----------|
| **NOTE:** | Permanent architectural info | Forever | Anywhere needed |
| **TODO(category):** | Incomplete/blocked functionality | Until fixed | Implementation |
| **MFC reference** | Just line numbers | Forever | Frame handlers |
| **None** | Complete, no special notes | N/A | Most code |

**Key principle**: If it will be removed someday, it's a TODO. If it stays forever, it's a NOTE.
