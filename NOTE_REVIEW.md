# NOTE Comment Review - Pattern Compliance Check

Per user request: Review all NOTEs to ensure they match our established pattern.

**Pattern Rule**: NOTE = Permanent info (stays forever), TODO = Incomplete (remove when fixed)

---

## ✅ Correct NOTEs (Permanent Info - Keep Forever)

### 1. StdAfx_wx.h:36
```cpp
// NOTE: DynamicVectorClass is provided by Vector.h from engine headers
```
**Status**: ✅ CORRECT - Permanent architectural info about engine header source  
**Reason**: Explains where DynamicVectorClass comes from (stays forever)

---

### 2. w3dviewdoc_wx.h:128
```cpp
// NOTE: These methods exist in MFC but are NOT USED in AnimationSpeed dialog
//       (OnCompressq, On16bit, On8bit are commented out in AnimationSpeed.cpp)
```
**Status**: ✅ CORRECT - Permanent info about unused MFC features  
**Reason**: Documents that MFC has compression features we're keeping but not using

---

### 3. w3dviewdoc_wx.h:205
```cpp
// NOTE: These exist in MFC but are unused in AnimationSpeed dialog
```
**Status**: ✅ CORRECT - Permanent info about unused MFC features  
**Reason**: Documents unused MFC member variables we're keeping for compatibility

---

### 4. EngineString.h:36
```cpp
// NOTE: Engine data is ANSI (Windows codepage), not UTF-8!
```
**Status**: ✅ CORRECT - Permanent architectural info  
**Reason**: Critical encoding information (stays forever)

---

### 5. w3dviewframe_wx.cpp:664
```cpp
// NOTE: Lighting comes BEFORE Camera in MFC IDR_MAINFRAME menu order
```
**Status**: ✅ CORRECT - Permanent architectural info  
**Reason**: Documents intentional menu ordering difference from typical UI conventions

---

### 6. w3dviewframe_wx.cpp:727
```cpp
// NOTE: In MFC, Animation is in separate menu resource (IDR_ANI_MENU) that gets swapped contextually
//   For now, keeping it in main menu bar for wxWidgets compatibility
//   TODO(MFC-Match): Implement context-sensitive menu swapping (IDR_MAINFRAME <-> IDR_ANI_MENU)
```
**Status**: ✅ CORRECT - Permanent info with related TODO  
**Reason**: NOTE explains MFC architecture (permanent), TODO describes incomplete feature (temporary)

---

### 7. dialogs/Displayspeed_wx.cpp:118, 134, 148
```cpp
// NOTE: This method is COMMENTED OUT in MFC AnimationSpeed.cpp!
```
**Status**: ✅ CORRECT - Permanent info about MFC behavior  
**Reason**: Documents that MFC intentionally has these methods commented out

---

### 8. dialogs/Displayspeed_wx.cpp:178
```cpp
// NOTE: Compression features are commented out in MFC dialog handlers
```
**Status**: ✅ CORRECT - Permanent info about MFC behavior  
**Reason**: Documents intentional MFC design decision

---

### 9. dialogs/Displayspeed_wx.cpp:185
```cpp
// NOTE: Radio button logic is commented out in MFC dialog handlers
```
**Status**: ✅ CORRECT - Permanent info about MFC behavior  
**Reason**: Documents intentional MFC design decision

---

### 10. dialogs/Displayspeed_wx.cpp:208
```cpp
// NOTE: MFC uses range 1-200, not 1-100 as documented in earlier TODO
```
**Status**: ✅ CORRECT - Permanent info clarifying MFC behavior  
**Reason**: Corrects documentation (MFC range is permanent info)

---

### 11. dialogs/Aboutbox_wx.cpp:33
```cpp
// NOTE: MFC version reads from executable version resource (VS_VERSION_INFO).
```
**Status**: ✅ CORRECT - Permanent info about MFC architecture  
**Reason**: Documents how MFC version works (different from wxWidgets approach)

---

## ❌ Incorrect NOTE (Should be TODO)

### 12. dialogs/PropPageEmitterLineprops_wx.cpp:106
```cpp
// NOTE: Control enable/disable logic requires m_pEmitterList which should be
// set via a SetEmitterList() method before showing the dialog. Implementation:
//   bool enable = (m_pEmitterList && m_pEmitterList->Get_Render_Mode() == W3D_EMITTER_RENDER_MODE_LINE);
//   Enable(enable);  // Enable/disable all dialog controls
// This will be implemented when the emitter list is wired to the dialog.
```
**Status**: ❌ INCORRECT - Should be TODO  
**Reason**: "This will be implemented when..." describes incomplete functionality  
**Should Be**: 
```cpp
// TODO(MFC-Implementation): Control enable/disable logic requires m_pEmitterList
// which should be set via a SetEmitterList() method before showing the dialog.
// MFC implementation:
//   bool enable = (m_pEmitterList && m_pEmitterList->Get_Render_Mode() == W3D_EMITTER_RENDER_MODE_LINE);
//   Enable(enable);  // Enable/disable all dialog controls
// Required when: Emitter property pages are wired to document emitter list
```

**Key Signal**: "This will be implemented when" = TODO, not NOTE

---

## Summary

**Total NOTEs Reviewed**: 12  
**Correct (Permanent info)**: 11 ✅  
**Incorrect (Should be TODO)**: 1 ❌

**Action Required**: Fix PropPageEmitterLineprops_wx.cpp:106

---

## Pattern Validation

All NOTEs except one correctly match the pattern:

| Pattern | Count | Examples |
|---------|-------|----------|
| Architectural differences | 4 | Menu structure, engine encoding, header sources |
| Unused MFC features | 3 | Compression, unused methods |
| MFC behavior documentation | 4 | Commented-out features, range values |
| **Incomplete functionality** | **1** | **❌ Should be TODO** |

**Conclusion**: 92% compliance (11/12). One fix needed.
