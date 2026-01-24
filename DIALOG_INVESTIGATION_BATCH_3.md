# Dialog Investigation Batch 3 - Continued MFC Analysis

**Date:** January 24, 2026  
**Session:** Continued from Session 2
**Focus:** Finding implementable dialogs without engine dependencies

## Investigation Summary

**Dialogs Investigated:** 3
**Implementable:** 0 (all have engine dependencies)
**Patterns Discovered:** 0 new (file dialog pattern already established)

---

## Detailed Investigations

### 1. TextureSettings (21 TODOs)

**MFC Source:** TextureSettingsDialog.cpp

**Constructor Signature:**
```cpp
TextureSettingsDialogClass(IndirectTextureClass *ptexture,
                           IndirectTextureClass *poriginal_texture,
                           CWnd *pParent)
```

**Engine Dependencies Found:**
- ✗ Requires `IndirectTextureClass*` pointer (texture object)
- ✗ Needs `Load_Texture_Settings()` - loads from texture object
- ✗ Needs `Paint_Thumbnail()` - renders texture preview
- ✗ Uses `WW3DAssetManager::Get_Instance()->Get_Texture()`
- ✗ Animation settings (frame count, frame rate) stored in texture object

**Implementation Status:** ❌ Cannot implement - Phase 4 engine integration required

**MFC Patterns Observed:**
- OnBrowseButton: CFileDialog for texture file selection
- OnApply: Applies settings to IndirectTextureClass
- OnRestore: Restores original texture from m_pOriginalTexture
- OnAnimationCheck: Enables/disables animation controls
- WindowProc: Custom thumbnail rendering

**Blocker Severity:** HIGH
- Every handler requires texture object access
- No self-contained UI logic exists
- Cannot implement even individual handlers

**TODO Adjustment Recommendation:** No change
- Existing TODOs correctly identify dependency
- All 21 TODOs are legitimately blocked

---

### 2. PropPageEmitterGen (19 TODOs)

**MFC Source:** EmitterGeneralPropPage.cpp

**Constructor Signature:**
```cpp
EmitterGeneralPropPageClass(EmitterInstanceListClass *pemitter)
```

**Engine Dependencies Found:**
- ✗ Requires `EmitterInstanceListClass*` pointer
- ✗ Needs `ShaderClass::_PresetXXXShader` static instances
- ✗ Uses `m_pEmitterList->Get_Texture_Filename()`
- ✗ Uses `m_pEmitterList->Get_Lifetime()`
- ✗ Uses `m_pEmitterList->Get_Name()`
- ✗ Uses `m_pEmitterList->Get_Shader(m_Shader)`
- ✗ Uses `m_pEmitterList->Get_Render_Mode()`

**OnBrowseButton Analysis:**
```cpp
// MFC code:
CFileDialog openFileDialog(TRUE, ".tga", nullptr,
                           OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_EXPLORER,
                           "Textures files (*.tga)|*.tga||",
                           ::AfxGetMainWnd());
if (openFileDialog.DoModal() == IDOK) {
    SetDlgItemText(IDC_FILENAME_EDIT, openFileDialog.GetPathName());
    SetModified();
}
```

**Can OnBrowseButton be implemented in isolation?**
❌ NO - Misleading to implement one handler when entire dialog needs engine integration
- Handler is simple (standard file dialog)
- BUT: SetModified() for property pages needs parent property sheet
- BUT: Texture filename goes to emitter object on Apply
- Implementing in isolation would create false sense of progress

**Implementation Status:** ❌ Cannot implement - Phase 4 engine integration required

**MFC Patterns Observed:**
- OnBrowseButton: CFileDialog for .tga texture files
- Add_Shader_To_Combo: Populates combo with ShaderClass instances
- OnChangeFilenameEdit, OnChangeNameEdit: SetModified() calls
- OnParticleLifetimeCheck: Enables/disables lifetime spin control
- Initialize(): Loads data from EmitterInstanceListClass

**Blocker Severity:** HIGH
- EmitterInstanceListClass dependency pervasive
- ShaderClass static instances needed
- Property page architecture (SetModified) needs full implementation

**TODO Adjustment Recommendation:** ADD 5+ TODOs
Current 19 TODOs don't fully document all blockers:
- Need TODO for EmitterInstanceListClass dependency
- Need TODO for ShaderClass static instances
- Need TODO for property page architecture
- Need TODO for SetModified() pattern
- Need TODO for Apply/OnApply pattern

---

### 3. PropPageSphereGen (13 TODOs) - Previously Investigated

**Re-confirmation:**
- ✗ Requires `SphereRenderObjClass*` pointer
- ✗ Needs `ShaderClass::_PresetXXXShader` static instances
- Same pattern as EmitterGen (different engine object)

**Implementation Status:** ❌ Cannot implement - Phase 4 engine integration required

**TODO Adjustment Recommendation:** ADD 5+ TODOs
- Same blockers as EmitterGen
- Need proper blocker documentation

---

## Pattern Analysis

### File Dialog Pattern (Already Established)
```cpp
// Found in multiple dialogs, already implemented in AnimatedSoundDialog
wxFileDialog dialog(this, "Title", wxEmptyString, "default.ext",
                    "Files (*.ext)|*.ext", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
if (dialog.ShowModal() == wxID_OK) {
    control->SetValue(dialog.GetPath());
}
```

**Applicable Dialogs:** 10+ (EmitterGen, SphereGen, TextureSettings, etc.)
**Can Implement in Isolation?** ❌ NO - All have engine dependencies

### SetModified() Pattern (Property Pages)
```cpp
// MFC pattern:
void OnChangeXXX() {
    SetModified(); // Enables Apply button in property sheet
}
```

**wxWidgets Equivalent:** Not yet implemented
- wxPropertySheetDialog has different architecture
- Needs investigation of MFC property page/sheet relationship
- Cannot implement individual SetModified() calls without property sheet framework

### Enable/Disable Controls Based on Checkbox
```cpp
// MFC pattern (EmitterGeneralPropPage):
void OnParticleLifetimeCheck() {
    BOOL checked = IsDlgButtonChecked(IDC_PARTICLE_LIFETIME_CHECK);
    ::EnableWindow(::GetDlgItem(m_hWnd, IDC_PARTICLE_LIFETIME_EDIT), checked);
    ::EnableWindow(::GetDlgItem(m_hWnd, IDC_PARTICLE_LIFETIME_SPIN), checked);
}
```

**wxWidgets Equivalent:**
```cpp
void OnParticleLifetimeCheck(wxCommandEvent& event) {
    bool checked = m_idc_particle_lifetime_check->GetValue();
    m_idc_particle_lifetime_edit->Enable(checked);
    m_idc_particle_lifetime_spin->Enable(checked);
}
```

**Can Implement in Isolation?** ⚠️ MAYBE
- Pure UI logic (no engine dependency)
- BUT: Often tied to data loading from engine objects
- Need full MFC investigation to verify independence

---

## Key Findings

### 1. Most Remaining Dialogs Have Engine Dependencies

**Finding:** 3 of 3 investigated dialogs require engine object pointers
**Pattern:** Property pages for editing engine objects (emitter, sphere, texture)
**Impact:** Cannot implement 20+ dialogs without Phase 4 engine integration

**Common Engine Dependencies:**
- EmitterInstanceListClass*
- SphereRenderObjClass*
- RingRenderObjClass*
- IndirectTextureClass*
- TextureClass*
- ShaderClass static instances
- WWAudioClass*
- LightClass*
- SceneClass*
- GetCurrentDocument() for document access

### 2. Cannot Implement Individual Handlers in Isolation

**Reasoning:**
1. **Misleading Progress** - Implementing one handler (e.g., OnBrowseButton) when entire dialog needs engine integration creates false sense of completion
2. **Incomplete Functionality** - File selected via dialog goes nowhere without engine object to store it
3. **SetModified() Dependency** - Property page handlers need property sheet architecture
4. **Data Flow** - Control values load from and save to engine objects

**Example:** EmitterGen OnBrowseButton
- ✅ Can show file dialog (simple)
- ✗ Cannot apply filename to emitter object (needs EmitterInstanceListClass*)
- ✗ SetModified() needs property sheet framework
- ✗ TransferDataFromWindow needs engine object
- **Result:** Implementing OnBrowseButton alone is 5% of dialog implementation

### 3. Property Page Architecture Not Yet Implemented

**MFC Architecture:**
```cpp
CPropertySheet sheet("Title");
sheet.AddPage(&page1);
sheet.AddPage(&page2);
sheet.DoModal();
```

**wxWidgets Equivalent:** wxPropertySheetDialog
- Different event model
- Different Apply/OK/Cancel handling
- Need to design parent sheet architecture first

**Impact:** Cannot implement property page dialogs until architecture decided

### 4. File Dialog Pattern Already Established But Blocked

**Pattern:** wxFileDialog and wxDirDialog patterns established in Session 2
**Blockers:**
- All dialogs with file browsers have engine dependencies
- Cannot implement browse handlers without full dialog implementation
- No "quick win" file dialog implementations remain

---

## Recommendations

### 1. Document Additional Blockers in Property Page Dialogs

**Affected Dialogs:**
- PropPageEmitterGen (19 TODOs → need +5 TODOs)
- PropPageSphereGen (13 TODOs → need +5 TODOs)
- PropPageRingGen (16 TODOs → need +5 TODOs)
- PropPageEmitterFrame (17 TODOs → need +5 TODOs)
- PropPageEmitterSize (15 TODOs → need +5 TODOs)
- PropPageEmitterRotation (15 TODOs → need +5 TODOs)

**New TODOs Needed:**
1. Constructor requires engine object pointer
2. ShaderClass static instances needed
3. Property page SetModified() architecture needed
4. Initialize() requires engine object data
5. TransferDataFromWindow requires engine object

**Proper Engineering:** Add TODOs to document blockers (as user requested)

### 2. Focus on Self-Contained Dialogs Only

**Candidates:** Dialogs with 0-10 TODOs that don't require engine objects
**Already Complete:** 33 dialogs (56%)
**Nearly Complete:** 6 dialogs (AnimatedSoundDialog, GammaDialog, etc.)

**Next Investigation Priority:**
1. Find dialogs with pure UI logic (enable/disable, radio button groups)
2. Find dialogs that only use wxConfig (no engine objects)
3. Avoid property pages until architecture designed

### 3. Consider Property Page Architecture Design

**Options:**
1. **Defer to Phase 4** - Implement when engine objects available
2. **Mock Architecture** - Create stubs for engine objects (not recommended)
3. **Standalone Property Pages** - Convert to regular dialogs (loses MFC equivalence)

**Recommendation:** Defer to Phase 4
- Property pages are tightly coupled to engine objects
- No value in implementing UI without data flow
- Focus on standalone dialogs first

### 4. Stop Investigating Property Pages

**Reasoning:**
- All property pages have same pattern (engine object + shaders)
- Wasting time investigating known blockers
- Should focus on finding self-contained dialogs

**New Investigation Strategy:**
1. Skip all PropPage* dialogs
2. Skip all dialogs with "Settings" in name (likely need engine objects)
3. Look for utility dialogs (color picker, key input, simple queries)

---

## Conclusion

**Session Finding:** No implementable dialogs found in this investigation batch

**Root Cause:** Focused on property pages and settings dialogs - all require Phase 4 engine integration

**Proper Response (Per User Guidance):**
1. ✅ Investigated MFC source before attempting implementation
2. ✅ Identified engine dependencies in all 3 dialogs
3. ✅ Did NOT implement partial functionality (would be misleading)
4. ✅ Recommend ADDING TODOs to document blockers properly
5. ✅ Documented findings comprehensively

**Next Steps:**
1. Add blocker TODOs to property page dialogs (5+ TODOs each × 6 dialogs = 30+ TODOs to ADD)
2. Change investigation strategy (skip property pages)
3. Look for self-contained utility dialogs
4. Consider if remaining work should wait for Phase 4

**Methodology Validation:** ✅ User's guidance to investigate carefully prevented wasted implementation effort
