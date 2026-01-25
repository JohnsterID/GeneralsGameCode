# Session 20: Wireframe and Polygon Sorting Investigation

**Date**: January 26, 2026  
**Feature**: View Menu Rendering Controls (Wireframe Mode + Polygon Sorting)  
**Status**: Pre-Implementation Analysis

---

## MFC Implementation Analysis

### 1. Wireframe Mode

**Menu Item**: 
- MFC: W3DView.rc:227 - "&Wireframe Mode" (IDM_WIREFRAME_MODE)
- Position: View menu, after separator, before Polygon Sorting
- Type: Checkbox (has OnUpdate with SetCheck)

**Event Table** (MainFrm.cpp:265-266):
```cpp
ON_COMMAND(IDM_WIREFRAME_MODE, OnWireframeMode)
ON_UPDATE_COMMAND_UI(IDM_WIREFRAME_MODE, OnUpdateWireframeMode)
```

**Handler: OnWireframeMode** (MainFrm.cpp:4172-4179):
```cpp
void CMainFrame::OnWireframeMode (void)
{
    ViewerSceneClass *scene = ::GetCurrentDocument ()->GetScene ();
    
    bool enable = (scene->Get_Polygon_Mode () != SceneClass::LINE);
    scene->Set_Polygon_Mode (enable ? SceneClass::LINE : SceneClass::FILL);
    return ;
}
```

**Handler: OnUpdateWireframeMode** (MainFrm.cpp:4188-4193):
```cpp
void CMainFrame::OnUpdateWireframeMode (CCmdUI *pCmdUI)
{
    ViewerSceneClass *scene = ::GetCurrentDocument ()->GetScene ();
    pCmdUI->SetCheck (scene->Get_Polygon_Mode () == SceneClass::LINE);
    return ;
}
```

**API Used**:
- `ViewerSceneClass::Get_Polygon_Mode()` → returns PolyRenderType
- `ViewerSceneClass::Set_Polygon_Mode(PolyRenderType)` → sets mode
- Enum: `SceneClass::PolyRenderType` (scene.h:130-135)
  - POINT = 0
  - LINE = 1 (wireframe)
  - FILL = 2 (normal)

**Key Characteristics**:
- ✅ Scene-specific setting (not global WW3D setting)
- ✅ Uses GetScene() from document
- ❌ **NO config persistence** (not saved to registry)
- ✅ Simple toggle: LINE ↔ FILL
- ✅ Checkbox reflects current state

---

### 2. Polygon Sorting

**Menu Item**:
- MFC: W3DView.rc:228 - "Polygon Sorting\tCtrl+P" (IDM_TOGGLE_SORTING)
- Position: View menu, after Wireframe Mode, before Set Gamma
- Type: Checkbox (has OnUpdate with SetCheck)
- Shortcut: Ctrl+P
- Accelerator: W3DView.rc:432 - `"P", IDM_TOGGLE_SORTING, VIRTKEY, CONTROL`

**Event Table** (MainFrm.cpp:271-272):
```cpp
ON_UPDATE_COMMAND_UI(IDM_TOGGLE_SORTING, OnUpdateToggleSorting)
ON_COMMAND(IDM_TOGGLE_SORTING, OnToggleSorting)
```

**Handler: OnToggleSorting** (MainFrm.cpp:4202-4210):
```cpp
void CMainFrame::OnToggleSorting()
{
    // Toggle the polygon sorting state.
    bool sorting=!WW3D::Is_Sorting_Enabled();
    WW3D::_Invalidate_Mesh_Cache();
    WW3D::Enable_Sorting(sorting);
    // Save the new value in the registry.
    ::AfxGetApp()->WriteProfileInt("Config", "EnableSorting",sorting?1:0);
}
```

**Handler: OnUpdateToggleSorting** (MainFrm.cpp:4219-4223):
```cpp
void CMainFrame::OnUpdateToggleSorting(CCmdUI* pCmdUI)
{
    // Check the menu item if sorting is enabled, clear it otherwise.
    pCmdUI->SetCheck(WW3D::Is_Sorting_Enabled() ? 1 : 0);
}
```

**API Used**:
- `WW3D::Is_Sorting_Enabled()` → returns bool
- `WW3D::Enable_Sorting(bool)` → sets sorting state
- `WW3D::_Invalidate_Mesh_Cache()` → clears mesh cache before changing

**Key Characteristics**:
- ✅ Global WW3D setting
- ✅ Config persistence: WriteProfileInt("Config", "EnableSorting", 0 or 1)
- ✅ Cache invalidation required before setting
- ✅ Simple toggle: true ↔ false
- ✅ Checkbox reflects current state
- ✅ Keyboard shortcut: Ctrl+P

---

## wxWidgets Requirements

### Current View Menu Structure (w3dviewframe_wx.cpp:225-242)

```cpp
// View menu
wxMenu *viewMenu = new wxMenu;
viewMenu->Append(ID_VIEW_RESET, "&Reset View");
viewMenu->Append(ID_ALTERNATE_MATERIAL, "&Alternate Material");
viewMenu->AppendSeparator();
viewMenu->AppendCheckItem(ID_VIEW_PATCH_GAP_FILL, "&Patch Gap Fill");
viewMenu->AppendSeparator();
wxMenu *subdivMenu = new wxMenu;
subdivMenu->AppendRadioItem(ID_VIEW_SUBDIVISION_1, "Level &1");
// ... (subdivision levels 2-8)
viewMenu->AppendSubMenu(subdivMenu, "Su&bdivision Level");
menuBar->Append(viewMenu, "&View");
```

### Proposed View Menu Structure (MFC-Matching)

```cpp
// View menu
wxMenu *viewMenu = new wxMenu;
viewMenu->Append(ID_VIEW_RESET, "&Reset View");
viewMenu->Append(ID_ALTERNATE_MATERIAL, "&Alternate Material");
viewMenu->AppendSeparator();
viewMenu->AppendCheckItem(ID_VIEW_WIREFRAME, "&Wireframe Mode");          // NEW
viewMenu->AppendCheckItem(ID_VIEW_POLYGON_SORTING, "Polygon Sorting\tCtrl+P"); // NEW
viewMenu->AppendSeparator();
wxMenu *subdivMenu = new wxMenu;
// ... (subdivision level submenu)
viewMenu->AppendSubMenu(subdivMenu, "Su&bdivision Level");
viewMenu->AppendCheckItem(ID_VIEW_PATCH_GAP_FILL, "&Patch Gap Fill");
menuBar->Append(viewMenu, "&View");
```

**Changes**:
1. Remove separator before Patch Gap Fill
2. Add Wireframe Mode checkbox (before Polygon Sorting)
3. Add Polygon Sorting checkbox with Ctrl+P shortcut (after Wireframe)
4. Add separator after Polygon Sorting
5. Keep Subdivision Level submenu
6. Keep Patch Gap Fill checkbox at end

---

## API Verification

### SceneClass APIs ✅

**File**: GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/scene.h

**Enum** (lines 130-135):
```cpp
enum PolyRenderType
{
    POINT,
    LINE,
    FILL
};
```

**Methods** (lines 137-138):
```cpp
void Set_Polygon_Mode(PolyRenderType mode) { PolyRenderMode = mode; }
PolyRenderType Get_Polygon_Mode(void) { return PolyRenderMode; }
```

**Status**: ✅ Available in scene.h

---

### WW3D Sorting APIs ⚠️ NEED VERIFICATION

**Expected APIs**:
- `WW3D::Is_Sorting_Enabled()` → returns bool
- `WW3D::Enable_Sorting(bool)` → sets state
- `WW3D::_Invalidate_Mesh_Cache()` → clears cache

**Need to verify in**: GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/ww3d.h

---

### wxWidgets Document APIs ✅

**File**: Core/Tools/W3DView/w3dviewdoc_wx.h

**Method** (line 58):
```cpp
ViewerSceneClass *GetScene() { return m_scene; }
```

**Status**: ✅ Available for wireframe implementation

---

## Implementation Plan

### Phase 1: Verify Sorting APIs (10 minutes)

**Action**: Search ww3d.h for sorting methods
```bash
grep -n "Is_Sorting_Enabled\|Enable_Sorting\|_Invalidate_Mesh_Cache" ww3d.h
```

**Expected**: All 3 methods should exist
**If missing**: Will need to investigate alternative approach or add TODO

---

### Phase 2: Wireframe Implementation (15-20 minutes)

**Menu ID** (add to enum at top of w3dviewframe_wx.cpp):
```cpp
ID_VIEW_WIREFRAME = wxID_HIGHEST + 150,  // Choose appropriate ID
```

**Menu Item** (in CreateMenuBar, View menu section):
```cpp
viewMenu->AppendCheckItem(ID_VIEW_WIREFRAME, "&Wireframe Mode");
```

**Event Table** (add to BEGIN_EVENT_TABLE):
```cpp
EVT_MENU(ID_VIEW_WIREFRAME, W3DViewFrame::OnWireframe)
EVT_UPDATE_UI(ID_VIEW_WIREFRAME, W3DViewFrame::OnUpdateWireframe)
```

**Header Declarations** (w3dviewframe_wx.h):
```cpp
void OnWireframe(wxCommandEvent &event);
void OnUpdateWireframe(wxUpdateUIEvent &event);
```

**Implementation** (w3dviewframe_wx.cpp):
```cpp
// MFC Reference: MainFrm.cpp:4172-4179
void W3DViewFrame::OnWireframe(wxCommandEvent &WXUNUSED(event))
{
    W3DViewDoc *doc = wxDynamicCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    ViewerSceneClass *scene = doc->GetScene();
    if (!scene) return;
    
    bool enable = (scene->Get_Polygon_Mode() != SceneClass::LINE);
    scene->Set_Polygon_Mode(enable ? SceneClass::LINE : SceneClass::FILL);
}

// MFC Reference: MainFrm.cpp:4188-4193
void W3DViewFrame::OnUpdateWireframe(wxUpdateUIEvent &event)
{
    W3DViewDoc *doc = wxDynamicCast(GetDocument(), W3DViewDoc);
    if (!doc) {
        event.Enable(false);
        return;
    }
    
    ViewerSceneClass *scene = doc->GetScene();
    if (!scene) {
        event.Enable(false);
        return;
    }
    
    event.Check(scene->Get_Polygon_Mode() == SceneClass::LINE);
}
```

**Notes**:
- NO wxConfig persistence (matches MFC)
- Scene-specific setting
- Requires null-check on doc and scene
- Exact MFC logic match

---

### Phase 3: Polygon Sorting Implementation (15-20 minutes)

**Depends on**: Phase 1 API verification

**Menu ID** (add to enum):
```cpp
ID_VIEW_POLYGON_SORTING = wxID_HIGHEST + 151,
```

**Menu Item** (in CreateMenuBar, View menu section):
```cpp
viewMenu->AppendCheckItem(ID_VIEW_POLYGON_SORTING, "Polygon &Sorting\tCtrl+P");
```

**Event Table** (add to BEGIN_EVENT_TABLE):
```cpp
EVT_MENU(ID_VIEW_POLYGON_SORTING, W3DViewFrame::OnPolygonSorting)
EVT_UPDATE_UI(ID_VIEW_POLYGON_SORTING, W3DViewFrame::OnUpdatePolygonSorting)
```

**Header Declarations** (w3dviewframe_wx.h):
```cpp
void OnPolygonSorting(wxCommandEvent &event);
void OnUpdatePolygonSorting(wxUpdateUIEvent &event);
```

**Implementation** (w3dviewframe_wx.cpp):
```cpp
// MFC Reference: MainFrm.cpp:4202-4210
void W3DViewFrame::OnPolygonSorting(wxCommandEvent &WXUNUSED(event))
{
    // Toggle the polygon sorting state.
    bool sorting = !WW3D::Is_Sorting_Enabled();
    WW3D::_Invalidate_Mesh_Cache();
    WW3D::Enable_Sorting(sorting);
    // Save the new value in wxConfig.
    wxConfig::Get()->Write("/Config/EnableSorting", sorting ? 1L : 0L);
    wxConfig::Get()->Flush();
}

// MFC Reference: MainFrm.cpp:4219-4223
void W3DViewFrame::OnUpdatePolygonSorting(wxUpdateUIEvent &event)
{
    // Check the menu item if sorting is enabled, clear it otherwise.
    event.Check(WW3D::Is_Sorting_Enabled());
}
```

**Notes**:
- Global WW3D setting
- Requires cache invalidation
- wxConfig persistence: /Config/EnableSorting (0 or 1)
- Exact MFC logic match
- Ctrl+P shortcut in menu text

---

### Phase 4: Menu Restructure (5 minutes)

**Current**:
```cpp
viewMenu->AppendCheckItem(ID_VIEW_PATCH_GAP_FILL, "&Patch Gap Fill");
viewMenu->AppendSeparator();
wxMenu *subdivMenu = new wxMenu;
```

**New (MFC-matching)**:
```cpp
viewMenu->AppendCheckItem(ID_VIEW_WIREFRAME, "&Wireframe Mode");
viewMenu->AppendCheckItem(ID_VIEW_POLYGON_SORTING, "Polygon &Sorting\tCtrl+P");
viewMenu->AppendSeparator();
wxMenu *subdivMenu = new wxMenu;
// ... subdivision items ...
viewMenu->AppendSubMenu(subdivMenu, "Su&bdivision Level");
viewMenu->AppendCheckItem(ID_VIEW_PATCH_GAP_FILL, "&Patch Gap Fill");
```

**Changes**:
- Remove old separator before Patch Gap Fill
- Add Wireframe and Polygon Sorting after Alternate Material
- Add separator after Polygon Sorting
- Move Patch Gap Fill to end (after Subdivision)

---

### Phase 5: TODO Update (CAREFUL!) (5 minutes)

**Current TODO** (line 193):
```cpp
// 4. Missing rendering controls (Wireframe, Polygon Sorting)
```

**Proposed Update** (IF both features implemented successfully):
```cpp
// 4. Additional rendering controls may be needed (verify against MFC)
```

**⚠️ IMPORTANT**: 
- Do NOT remove TODO completely
- Keep reminder to verify against MFC for other missing controls
- User guidance: "may even need to add more TODOs"

**Additional TODO to ADD** (if appropriate):
```cpp
// TODO(MFC-Verify): View menu rendering controls - verify complete list
// Implemented: Wireframe Mode, Polygon Sorting, Patch Gap Fill, Subdivision Level 1-8
// Verify MFC has no additional rendering controls beyond these
// MFC Reference: W3DView.rc:227-242
```

---

## Testing Plan

### Compile Test ✅
```bash
cd /workspace/project/GeneralsGameCode/build
cmake --build . --target g_w3dview_wx -j$(nproc)
```

**Expected**:
- 0 errors
- 0 warnings
- Build time: 4-6 seconds (incremental)

### Runtime Test (requires environment setup)
1. Launch W3DViewV.exe with Wine
2. Open View menu
3. Verify Wireframe Mode checkbox present
4. Verify Polygon Sorting checkbox present (with Ctrl+P)
5. Click Wireframe Mode → should toggle wireframe rendering
6. Click Polygon Sorting → should toggle sorting
7. Test Ctrl+P shortcut → should toggle sorting

---

## Risk Assessment

### Low Risk ✅
- **Wireframe**: Simple scene setting, well-defined API, no persistence needed
- **Pattern**: Similar to previous checkbox implementations
- **APIs**: All verified to exist

### Medium Risk ⚠️
- **Polygon Sorting**: Needs API verification first
- **Cache Invalidation**: _Invalidate_Mesh_Cache might have dependencies
- **Menu Restructure**: Small risk of breaking existing items

### High Risk ❌
- None identified

---

## Comparison with Previous Sessions

### Session 17: Enable Gamma Correction
- Pattern: Global WW3D toggle with config persistence
- Similar to: **Polygon Sorting** ✅

### Session 18: Prelit Lighting Modes
- Pattern: Radio button group for mode selection
- Similar to: Neither (both are simple toggles)

### Session 19: N-Patches Rendering
- Pattern: Checkbox toggle + radio button group
- Gap Fill: Global WW3D toggle with config persistence
- Similar to: **Polygon Sorting** ✅
- Subdivision: Radio buttons for level selection
- Similar to: Neither

### Session 20: Wireframe + Polygon Sorting
- **Wireframe**: NEW PATTERN - Scene-specific toggle WITHOUT persistence
- **Polygon Sorting**: ESTABLISHED PATTERN - Global toggle WITH persistence

---

## Expected Outcomes

### If All APIs Available ✅
- Implementation time: 45-60 minutes total
- Handlers added: 4 (2 pairs)
- Menu items added: 2 checkboxes
- Build: Clean (0 errors, 0 warnings)
- TODO: Updated carefully (not removed completely)

### If Sorting APIs Missing ⚠️
- Wireframe: Can still implement (15-20 min)
- Polygon Sorting: Add comprehensive TODO, defer implementation
- Document exactly what's missing
- Update TODO with investigation findings

---

## Next Steps

1. ✅ Complete API verification (Phase 1) - 10 minutes
2. ⏳ Implement Wireframe (Phase 2) - 15-20 minutes
3. ⏳ Implement Polygon Sorting (Phase 3) - 15-20 minutes (if APIs available)
4. ⏳ Restructure menu (Phase 4) - 5 minutes
5. ⏳ Update TODO carefully (Phase 5) - 5 minutes
6. ⏳ Compile test - 5 minutes
7. ⏳ Document (summary + handoff) - 15 minutes

**Total Time**: 45-60 minutes

---

**Analysis Status**: COMPLETE  
**Ready for**: API verification → Implementation  
**Confidence**: HIGH (for Wireframe), MEDIUM (for Polygon Sorting - needs API check)
