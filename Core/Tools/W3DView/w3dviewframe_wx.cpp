/*
**	Command & Conquer Renegade(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// TheSuperHackers: wxWidgets frame implementation for W3DView

#include "w3dviewframe_wx.h"
#include "w3dviewtree_wx.h"
#include "w3dviewview_wx.h"
#include "w3dviewdoc_wx.h"
#include "GraphicView_wx.h"
#include "ViewerScene.h"
#include "ww3d.h"
#include "dialogs/Aboutbox_wx.h"
#include "dialogs/CameraSettings_wx.h"
#include "dialogs/BackgroundColor_wx.h"
#include "dialogs/BackgroundBmp_wx.h"
#include "dialogs/BackgroundObject_wx.h"
#include "dialogs/TexturePaths_wx.h"
#include "dialogs/RenderDeviceSelector_wx.h"
#include "dialogs/LightAmbientDialog_wx.h"
#include "dialogs/LightSceneDialog_wx.h"
#include "dialogs/Resolution_wx.h"
#include "dialogs/GammaDialog_wx.h"
#include "light.h"

#include <wx/menu.h>
#include <wx/toolbar.h>
#include <wx/msgdlg.h>
#include <wx/filedlg.h>
#include <wx/config.h>

// Helper function for adjusting light intensity (MFC: MainFrm.cpp:109-121)
static inline void Adjust_Light_Intensity(Vector3 &color, float inc)
{
    color.X = color.X + inc;
    color.Y = color.Y + inc;
    color.Z = color.Z + inc;
    color.X = (color.X < 0) ? 0 : color.X;
    color.Y = (color.Y < 0) ? 0 : color.Y;
    color.Z = (color.Z < 0) ? 0 : color.Z;
    color.X = (color.X > 1.0F) ? 1.0F : color.X;
    color.Y = (color.Y > 1.0F) ? 1.0F : color.Y;
    color.Z = (color.Z > 1.0F) ? 1.0F : color.Z;
}

enum
{
    ID_ABOUT = wxID_ABOUT,
    ID_OBJECT_PROPERTIES = wxID_HIGHEST + 1,
    ID_LOD_GENERATE,
    ID_VIEW_RESET,
    ID_ALTERNATE_MATERIAL,
    ID_ANIMATION_SETTINGS,
    ID_BACKGROUND_COLOR,
    ID_BACKGROUND_BMP,
    ID_BACKGROUND_OBJECT,
    ID_BACKGROUND_FOG,
    ID_CAMERA_SETTINGS,
    // Light menu items
    ID_LIGHT_ROTATE_Y,
    ID_LIGHT_ROTATE_Z,
    ID_LIGHT_AMBIENT,
    ID_LIGHT_SCENE,
    ID_INC_AMBIENT_LIGHT,
    ID_DEC_AMBIENT_LIGHT,
    ID_INC_SCENE_LIGHT,
    ID_DEC_SCENE_LIGHT,
    ID_LIGHTING_EXPOSE,
    ID_KILL_SCENE_LIGHT,
    ID_PRELIT_VERTEX,
    ID_PRELIT_MULTIPASS,
    ID_PRELIT_MULTITEX,
    // Settings menu items
    ID_TEXTURE_PATH,
    ID_DEVICE_SELECTION,
    ID_RESOLUTION_SETTINGS,
    ID_ENABLE_GAMMA_CORRECTION,
    ID_GAMMA_SETTINGS,
};

wxBEGIN_EVENT_TABLE(W3DViewFrame, wxDocParentFrame)
    EVT_CLOSE(W3DViewFrame::OnClose)
    EVT_MENU(ID_ABOUT, W3DViewFrame::OnAbout)
    EVT_MENU(ID_OBJECT_PROPERTIES, W3DViewFrame::OnObjectProperties)
    EVT_MENU(ID_LOD_GENERATE, W3DViewFrame::OnLodGenerate)
    EVT_MENU(ID_VIEW_RESET, W3DViewFrame::OnViewReset)
    EVT_MENU(ID_ALTERNATE_MATERIAL, W3DViewFrame::OnAlternateMaterial)
    EVT_MENU(ID_ANIMATION_SETTINGS, W3DViewFrame::OnAnimationSettings)
    EVT_MENU(ID_BACKGROUND_COLOR, W3DViewFrame::OnBackgroundColor)
    EVT_MENU(ID_BACKGROUND_BMP, W3DViewFrame::OnBackgroundBmp)
    EVT_MENU(ID_BACKGROUND_OBJECT, W3DViewFrame::OnBackgroundObject)
    EVT_MENU(ID_BACKGROUND_FOG, W3DViewFrame::OnBackgroundFog)
    EVT_UPDATE_UI(ID_BACKGROUND_FOG, W3DViewFrame::OnUpdateBackgroundFog)
    EVT_MENU(ID_CAMERA_SETTINGS, W3DViewFrame::OnCameraSettings)
    // Light menu
    EVT_MENU(ID_LIGHT_ROTATE_Y, W3DViewFrame::OnLightRotateY)
    EVT_MENU(ID_LIGHT_ROTATE_Z, W3DViewFrame::OnLightRotateZ)
    EVT_MENU(ID_LIGHT_AMBIENT, W3DViewFrame::OnLightAmbient)
    EVT_MENU(ID_LIGHT_SCENE, W3DViewFrame::OnLightScene)
    EVT_MENU(ID_INC_AMBIENT_LIGHT, W3DViewFrame::OnIncAmbientLight)
    EVT_MENU(ID_DEC_AMBIENT_LIGHT, W3DViewFrame::OnDecAmbientLight)
    EVT_MENU(ID_INC_SCENE_LIGHT, W3DViewFrame::OnIncSceneLight)
    EVT_MENU(ID_DEC_SCENE_LIGHT, W3DViewFrame::OnDecSceneLight)
    EVT_MENU(ID_LIGHTING_EXPOSE, W3DViewFrame::OnLightingExpose)
    EVT_UPDATE_UI(ID_LIGHTING_EXPOSE, W3DViewFrame::OnUpdateLightingExpose)
    EVT_MENU(ID_KILL_SCENE_LIGHT, W3DViewFrame::OnKillSceneLight)
    EVT_MENU(ID_PRELIT_VERTEX, W3DViewFrame::OnPrelitVertex)
    EVT_MENU(ID_PRELIT_MULTIPASS, W3DViewFrame::OnPrelitMultipass)
    EVT_MENU(ID_PRELIT_MULTITEX, W3DViewFrame::OnPrelitMultitex)
    // Settings menu
    EVT_MENU(ID_TEXTURE_PATH, W3DViewFrame::OnTexturePathSettings)
    EVT_MENU(ID_DEVICE_SELECTION, W3DViewFrame::OnDeviceSelection)
    EVT_MENU(ID_RESOLUTION_SETTINGS, W3DViewFrame::OnResolutionSettings)
    EVT_MENU(ID_ENABLE_GAMMA_CORRECTION, W3DViewFrame::OnEnableGammaCorrection)
    EVT_UPDATE_UI(ID_ENABLE_GAMMA_CORRECTION, W3DViewFrame::OnUpdateEnableGammaCorrection)
    EVT_MENU(ID_GAMMA_SETTINGS, W3DViewFrame::OnGammaSettings)
wxEND_EVENT_TABLE()

W3DViewFrame::W3DViewFrame(wxDocManager *manager)
    : wxDocParentFrame(manager, nullptr, wxID_ANY, "W3D Viewer",
                       wxDefaultPosition, wxSize(960, 720))
    , m_docManager(manager)
    , m_splitter(nullptr)
    , m_statusBar(nullptr)
{
    CreateMenuBar();
    InitToolBar();
    InitStatusBar();
    CreateUI();

    Centre();
}

W3DViewFrame::~W3DViewFrame()
{
}

void W3DViewFrame::CreateMenuBar()
{
    // TODO(MFC-Match): Complete menu structure overhaul needed
    // Current wxWidgets menu is ~40% complete compared to MFC
    // See MENU_STRUCTURE_MISMATCH.md for full analysis
    //
    // CRITICAL ISSUES:
    // 1. Missing ~35+ menu items from MFC (File, View, Object menus)
    // 2. Settings menu items in wrong locations (should be in File/View)
    // 3. Missing Export submenu (Aggregate, Emitter, LOD, Primitive, Sound Object)
    // 4. Missing rendering controls (Wireframe, Polygon Sorting, N-Patches)
    // 5. Missing Object rotation controls (Rotate X/Y/Z with shortcuts)
    // 6. Missing toolbar visibility controls (View → Toolbars submenu)
    // 7. Save Settings vs Save file (Ctrl+S conflict)
    // 8. Background should be 4 separate items, not 1 combined
    //
    // MFC Reference: W3DView.rc lines 181-300+
    // Status: Major work required for exact matching
    // Impact: High - menu structure is primary user interface
    
    wxMenuBar *menuBar = new wxMenuBar;

    // File menu
    wxMenu *fileMenu = new wxMenu;
    fileMenu->Append(wxID_NEW, "&New\tCtrl+N");
    fileMenu->Append(wxID_OPEN, "&Open...\tCtrl+O");
    fileMenu->Append(wxID_SAVE, "&Save\tCtrl+S");
    fileMenu->Append(wxID_SAVEAS, "Save &As...");
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT, "E&xit\tAlt+F4");
    menuBar->Append(fileMenu, "&File");

    // Edit menu
    wxMenu *editMenu = new wxMenu;
    editMenu->Append(wxID_UNDO, "&Undo\tCtrl+Z");
    editMenu->Append(wxID_REDO, "&Redo\tCtrl+Y");
    editMenu->AppendSeparator();
    editMenu->Append(wxID_CUT, "Cu&t\tCtrl+X");
    editMenu->Append(wxID_COPY, "&Copy\tCtrl+C");
    editMenu->Append(wxID_PASTE, "&Paste\tCtrl+V");
    menuBar->Append(editMenu, "&Edit");

    // View menu
    wxMenu *viewMenu = new wxMenu;
    viewMenu->Append(ID_VIEW_RESET, "&Reset View");
    viewMenu->Append(ID_ALTERNATE_MATERIAL, "&Alternate Material");
    menuBar->Append(viewMenu, "&View");

    // Object menu
    wxMenu *objectMenu = new wxMenu;
    objectMenu->Append(ID_OBJECT_PROPERTIES, "&Properties...");
    objectMenu->Append(ID_LOD_GENERATE, "Generate &LOD...");
    menuBar->Append(objectMenu, "&Object");

    // Animation menu
    wxMenu *animMenu = new wxMenu;
    animMenu->Append(ID_ANIMATION_SETTINGS, "&Settings...");
    menuBar->Append(animMenu, "&Animation");

    // Light menu (matching MFC W3DView.rc:283-302)
    wxMenu *lightMenu = new wxMenu;
    lightMenu->Append(ID_LIGHT_ROTATE_Y, "Rotate &Y\tCtrl+Up");
    lightMenu->Append(ID_LIGHT_ROTATE_Z, "Rotate &Z\tCtrl+Right");
    lightMenu->AppendSeparator();
    lightMenu->Append(ID_LIGHT_AMBIENT, "&Ambient...");
    lightMenu->Append(ID_LIGHT_SCENE, "&Scene Light...");
    lightMenu->AppendSeparator();
    lightMenu->Append(ID_INC_AMBIENT_LIGHT, "&Inc Ambient Intensity\t+");
    lightMenu->Append(ID_DEC_AMBIENT_LIGHT, "&Dec Ambient Intensity\t-");
    lightMenu->Append(ID_INC_SCENE_LIGHT, "Inc Scene &Light Intensity\tCtrl++");
    lightMenu->Append(ID_DEC_SCENE_LIGHT, "De&c Scene Light Intensity\tCtrl+-");
    lightMenu->AppendSeparator();
    lightMenu->AppendCheckItem(ID_LIGHTING_EXPOSE, "Expose Precalculated Lighting");
    lightMenu->Append(ID_KILL_SCENE_LIGHT, "Kill Scene Light\tCtrl+*");
    lightMenu->AppendSeparator();
    lightMenu->AppendCheckItem(ID_PRELIT_VERTEX, "&Vertex Lighting");
    lightMenu->AppendCheckItem(ID_PRELIT_MULTIPASS, "Multi-&Pass Lighting");
    lightMenu->AppendCheckItem(ID_PRELIT_MULTITEX, "Multi-Te&xture Lighting");
    menuBar->Append(lightMenu, "Ligh&ting");

    // Settings menu
    wxMenu *settingsMenu = new wxMenu;
    settingsMenu->Append(ID_BACKGROUND_COLOR, "Background &Color...");
    settingsMenu->Append(ID_BACKGROUND_BMP, "Background &BMP...");
    settingsMenu->Append(ID_BACKGROUND_OBJECT, "Background &Object...");
    settingsMenu->AppendCheckItem(ID_BACKGROUND_FOG, "Background &Fog");
    settingsMenu->AppendSeparator();
    settingsMenu->Append(ID_CAMERA_SETTINGS, "C&amera...");
    settingsMenu->AppendSeparator();
    settingsMenu->Append(ID_TEXTURE_PATH, "&Texture Path...");
    settingsMenu->Append(ID_DEVICE_SELECTION, "&Device...");
    settingsMenu->Append(ID_RESOLUTION_SETTINGS, "&Resolution...");
    settingsMenu->AppendSeparator();
    settingsMenu->AppendCheckItem(ID_ENABLE_GAMMA_CORRECTION, "&Enable Gamma Correction");
    settingsMenu->Append(ID_GAMMA_SETTINGS, "Set &Gamma...");
    menuBar->Append(settingsMenu, "&Settings");

    // Help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(ID_ABOUT, "&About...");
    menuBar->Append(helpMenu, "&Help");

    SetMenuBar(menuBar);
}

void W3DViewFrame::InitToolBar()
{
    wxToolBar *toolBar = CreateToolBar(wxTB_HORIZONTAL | wxTB_FLAT);
    toolBar->AddTool(wxID_NEW, "New", wxNullBitmap, "New file");
    toolBar->AddTool(wxID_OPEN, "Open", wxNullBitmap, "Open file");
    toolBar->AddTool(wxID_SAVE, "Save", wxNullBitmap, "Save file");
    toolBar->AddSeparator();
    toolBar->AddTool(ID_OBJECT_PROPERTIES, "Properties", wxNullBitmap, "Object properties");
    toolBar->Realize();
}

void W3DViewFrame::InitStatusBar()
{
    m_statusBar = CreateStatusBar(3);
    int widths[] = {-1, 100, 100};
    m_statusBar->SetStatusWidths(3, widths);
    m_statusBar->SetStatusText("Ready", 0);
}

void W3DViewFrame::CreateUI()
{
    m_splitter = new wxSplitterWindow(this, wxID_ANY,
                                      wxDefaultPosition, wxDefaultSize,
                                      wxSP_3D | wxSP_LIVE_UPDATE);

    // The actual view windows will be created by the document/view framework
    // For now, just initialize the splitter
    m_splitter->SetMinimumPaneSize(200);

    // TODO(MFC-Match): Create Object controls toolbar
    // MFC Reference: MainFrm.cpp:382-386
    // Creates CFancyToolbar with rotation lock buttons:
    //   - Lock X rotation (IDB_LOCK_X_UP/DN, IDM_CAMERA_ALLOW_ROTATE_Y)
    //   - Lock Y rotation (IDB_LOCK_Y_UP/DN, IDM_CAMERA_ALLOW_ROTATE_X)
    //   - Lock Z rotation (IDB_LOCK_Z_UP/DN, IDM_CAMERA_ALLOW_ROTATE_Z)
    //   - Rotate Z (IDB_ROTATE_Z_UP/DN, IDM_OBJECT_ROTATE_Z)
    // Status: Not implemented
    // Visual Impact: Missing control panel at bottom of window

    // TODO(MFC-Match): Create Animation controls toolbar
    // MFC Reference: MainFrm.cpp:388-394
    // Creates CFancyToolbar with playback controls:
    //   - Play (IDB_PLAY_UP/DN, IDM_ANI_START)
    //   - Stop (IDB_STOP_UP/DN, IDM_ANI_STOP)
    //   - Pause (IDB_PAUSE_UP/DN, IDM_ANI_PAUSE)
    //   - Step backward (IDB_REVERSE_UP/DN, IDM_ANI_STEP_BKWD)
    //   - Step forward (IDB_FFWD_UP/DN, IDM_ANI_STEP_FWD)
    // Default state: Hidden (ShowWindow(SW_HIDE))
    // Status: Not implemented
    // Visual Impact: Missing animation control panel
}

void W3DViewFrame::OnClose(wxCloseEvent &event)
{
    if (m_docManager && !m_docManager->Clear(!event.CanVeto()))
    {
        event.Veto();
        return;
    }

    Destroy();
}

void W3DViewFrame::OnAbout(wxCommandEvent &WXUNUSED(event))
{
    // TODO(MFC-Verify): Verify Aboutbox dialog matches MFC exactly
    // Dialog appears implemented but needs visual/behavioral verification
    // MFC Reference: AboutBox.cpp (CAboutDlg)
    Aboutbox dialog(this);
    dialog.ShowModal();
}

void W3DViewFrame::OnObjectProperties(wxCommandEvent &WXUNUSED(event))
{
    // TODO(MFC-Match-COMPLEX): Implement object properties dialog
    // MFC Reference: MainFrm.cpp:718-724 (OnObjectProperties)
    // MFC implementation:
    //   Calls ShowObjectProperties() which displays different property sheets
    //   based on current tree selection type (mesh, hierarchy, etc.)
    //
    // Requirements:
    //   1. Get current selection from tree view (W3DViewTreeCtrl)
    //   2. Determine selection type (TypeMesh, TypeHierarchy, etc.)
    //   3. Create appropriate property sheet dialog (CMeshPropPage, etc.)
    //   4. Display modal property sheet
    //
    // Blockers:
    //   - Property sheet architecture not yet implemented in wxWidgets
    //   - Tree view integration needed
    //   - Multiple property page classes (20+ dialogs affected)
    //
    // Impact: High - important feature for editing objects
    // Priority: Medium - blocked by property sheet architecture
    wxMessageBox("Object Properties dialog not yet implemented",
                 "TODO", wxOK | wxICON_INFORMATION, this);
}

void W3DViewFrame::OnLodGenerate(wxCommandEvent &WXUNUSED(event))
{
    // TODO(MFC-Match-COMPLEX): Implement LOD generation feature
    // MFC Reference: MainFrm.cpp:979-1025 (OnLodGenerate)
    // MFC implementation:
    //   1. Gets current selection from tree view
    //   2. Validates name format for LOD (e.g., "name00", "name01")
    //   3. Calls document->GenerateLOD(basename, type)
    //   4. Adds generated LOD prototype to asset manager
    //   5. Updates tree view with new LOD
    //
    // Requirements:
    //   - Tree view integration (get selection name)
    //   - LOD name validation (Is_LOD_Name_Valid)
    //   - Document GenerateLOD() method
    //   - Asset manager integration
    //   - Tree view update after generation
    //
    // Blockers:
    //   - Tree view integration not complete
    //   - Document LOD generation method not implemented
    //   - Asset manager API access needed
    //
    // Impact: Medium - LOD creation is important but specialized workflow
    // Priority: Medium - requires multiple components working together
    wxMessageBox("LOD Generation dialog not yet implemented",
                 "TODO", wxOK | wxICON_INFORMATION, this);
}

void W3DViewFrame::OnViewReset(wxCommandEvent &WXUNUSED(event))
{
    // TODO(MFC-Missing): OnViewReset has no MFC implementation
    // Searched: Core/Tools/W3DView/MainFrm.cpp - handler not found
    // This appears to be a planned feature that was never implemented in MFC
    // 
    // Possible interpretation: Reset camera view to default position/rotation
    // Would need to define what "reset" means:
    //   - Reset camera position/orientation?
    //   - Reset lighting to defaults?
    //   - Reset all view settings?
    //
    // Status: Unimplemented in MFC, unclear requirements
    // Priority: Low - feature was never implemented in original
    // Impact: Unknown - no MFC behavior to match
}

void W3DViewFrame::OnAlternateMaterial(wxCommandEvent &WXUNUSED(event))
{
    // TODO(MFC-Match-BLOCKED): Implement alternate material toggle
    // MFC Reference: MainFrm.cpp:4073 (OnObjectAlternateMaterials)
    // MFC implementation:
    //   ::GetCurrentDocument()->Toggle_Alternate_Materials();
    //
    // W3DViewDoc::Toggle_Alternate_Materials() implementation (W3DViewDoc.cpp):
    //   Recursively toggles alternate material description for mesh objects
    //   For each CLASSID_MESH:
    //     MeshModelClass* model = ((MeshClass*)renderObj)->Get_Model();
    //     model->Enable_Alternate_Material_Description(!model->Is_Alternate_Material_Description_Enabled());
    //   Recurses into all sub-objects
    //
    // BLOCKED BY: Header include conflict with wxWidgets
    //   Including mesh.h/meshmdl.h causes compilation error in vertmaterial.h:119
    //   Error: "cannot convert 'const StringClass' to 'const char*' in return"
    //   VertexMaterialClass::Get_Name() returns StringClass Name directly
    //   MFC StdAfx.h preprocessor setup may handle this differently
    //
    // Possible solutions to investigate:
    //   1. Fix vertmaterial.h Get_Name() to call Name.Peek_Buffer()
    //   2. Add StringClass implicit conversion operator (risky, wide impact)
    //   3. Investigate MFC StdAfx.h preprocessor handling
    //   4. Use forward declarations and reinterpret_cast (type-unsafe)
    //
    // Impact: Medium - affects material display for models with alternate materials
    //         (less commonly used feature)
    // Priority: Defer until engine header conflicts resolved
}

void W3DViewFrame::OnAnimationSettings(wxCommandEvent &WXUNUSED(event))
{
    // TODO: Implement animation settings dialog
    wxMessageBox("Animation Settings dialog not yet implemented",
                 "TODO", wxOK | wxICON_INFORMATION, this);
}

void W3DViewFrame::OnBackgroundColor(wxCommandEvent &WXUNUSED(event))
{
    // TODO(MFC-Verify): Verify BackgroundColor dialog matches MFC exactly
    // Dialog appears implemented but needs visual/behavioral verification
    // MFC Reference: BackgroundColor.cpp (CBackgroundColorDialog)
    BackgroundColor dialog(this);
    dialog.ShowModal();
}

void W3DViewFrame::OnBackgroundBmp(wxCommandEvent &WXUNUSED(event))
{
    // TODO(MFC-Verify): Verify BackgroundBmp dialog matches MFC exactly
    // Dialog appears implemented but needs visual/behavioral verification
    // MFC Reference: BackgroundBMP.cpp (CBackgroundBMPDialog)
    BackgroundBmp dialog(this);
    dialog.ShowModal();
}

void W3DViewFrame::OnBackgroundObject(wxCommandEvent &WXUNUSED(event))
{
    // TODO(MFC-Verify): Verify BackgroundObject dialog matches MFC exactly
    // Dialog appears implemented but needs visual/behavioral verification
    // MFC Reference: BackgroundObject.cpp (CBackgroundObjectDialog)
    BackgroundObject dialog(this);
    dialog.ShowModal();
}

void W3DViewFrame::OnBackgroundFog(wxCommandEvent &WXUNUSED(event))
{
    // MFC: MainFrm.cpp:1649 (OnBackgroundFog)
    // Toggles background fog enable state
    W3DViewDoc *doc = wxStaticCast(m_docManager->GetCurrentDocument(), W3DViewDoc);
    if (!doc)
        return;

    doc->EnableFog(!doc->IsFogEnabled());
}

void W3DViewFrame::OnUpdateBackgroundFog(wxUpdateUIEvent &event)
{
    // MFC: MainFrm.cpp:1634-1642 (OnUpdateBackgroundFog)
    // Sets checkbox state based on document's fog enable state
    W3DViewDoc *doc = wxStaticCast(m_docManager->GetCurrentDocument(), W3DViewDoc);
    if (doc) {
        event.Check(doc->IsFogEnabled());
    } else {
        event.Check(false);
    }
}

void W3DViewFrame::OnCameraSettings(wxCommandEvent &WXUNUSED(event))
{
    // TODO(MFC-Verify): Verify CameraSettings dialog matches MFC exactly
    // Dialog appears implemented but needs visual/behavioral verification
    // MFC Reference: CameraSettings.cpp
    CameraSettings dialog(this);
    dialog.ShowModal();
}

// Light menu handlers

void W3DViewFrame::OnLightRotateY(wxCommandEvent &WXUNUSED(event))
{
    // MFC: MainFrm.cpp:2641-2654 (OnLightRotateY)
    // Toggles continuous Y-axis rotation of scene light
    W3DViewDoc *doc = wxStaticCast(m_docManager->GetCurrentDocument(), W3DViewDoc);
    if (!doc)
        return;

    CGraphicView *graphicView = doc->GetGraphicView();
    if (graphicView != nullptr) {
        // Start or stop the rotation around Y
        int rotation = (graphicView->Get_Light_Rotation() ^ CGraphicView::RotateY);
        rotation &= ~CGraphicView::RotateYBack;
        graphicView->Rotate_Light((CGraphicView::OBJECT_ROTATION)rotation);
    }
}

void W3DViewFrame::OnLightRotateZ(wxCommandEvent &WXUNUSED(event))
{
    // MFC: MainFrm.cpp:2685-2698 (OnLightRotateZ)
    // Toggles continuous Z-axis rotation of scene light
    W3DViewDoc *doc = wxStaticCast(m_docManager->GetCurrentDocument(), W3DViewDoc);
    if (!doc)
        return;

    CGraphicView *graphicView = doc->GetGraphicView();
    if (graphicView != nullptr) {
        // Start or stop the rotation around Z
        int rotation = (graphicView->Get_Light_Rotation() ^ CGraphicView::RotateZ);
        rotation &= ~CGraphicView::RotateZBack;
        graphicView->Rotate_Light((CGraphicView::OBJECT_ROTATION)rotation);
    }
}

void W3DViewFrame::OnLightAmbient(wxCommandEvent &WXUNUSED(event))
{
    // TODO(MFC-Verify): Verify LightAmbientDialog matches MFC exactly
    // Dialog appears implemented but needs visual/behavioral verification
    // MFC Reference: MainFrm.cpp:1588-1594 (OnLightAmbient), AmbientLightDialog.cpp
    LightAmbientDialog dialog(this);
    dialog.ShowModal();
}

void W3DViewFrame::OnLightScene(wxCommandEvent &WXUNUSED(event))
{
    // TODO(MFC-Verify): Verify LightSceneDialog matches MFC exactly
    // Dialog appears implemented but needs visual/behavioral verification
    // MFC Reference: MainFrm.cpp:1604-1610 (OnLightScene), SceneLightDialog.cpp
    LightSceneDialog dialog(this);
    dialog.ShowModal();
}

void W3DViewFrame::OnIncAmbientLight(wxCommandEvent &WXUNUSED(event))
{
    // MFC: MainFrm.cpp:2847-2861 (OnIncAmbientLight)
    // Increases ambient light intensity by 0.05
    W3DViewDoc *doc = wxStaticCast(m_docManager->GetCurrentDocument(), W3DViewDoc);
    if (!doc)
        return;

    if (doc->GetScene() != nullptr) {
        Vector3 color = doc->GetScene()->Get_Ambient_Light();
        Adjust_Light_Intensity(color, 0.05F);
        doc->GetScene()->Set_Ambient_Light(color);
    }
}

void W3DViewFrame::OnDecAmbientLight(wxCommandEvent &WXUNUSED(event))
{
    // MFC: MainFrm.cpp:2824-2837 (OnDecAmbientLight)
    // Decreases ambient light intensity by 0.05
    W3DViewDoc *doc = wxStaticCast(m_docManager->GetCurrentDocument(), W3DViewDoc);
    if (!doc)
        return;

    if (doc->GetScene() != nullptr) {
        Vector3 color = doc->GetScene()->Get_Ambient_Light();
        Adjust_Light_Intensity(color, -0.05F);
        doc->GetScene()->Set_Ambient_Light(color);
    }
}

void W3DViewFrame::OnIncSceneLight(wxCommandEvent &WXUNUSED(event))
{
    // MFC: MainFrm.cpp:2795-2815 (OnIncLight)
    // Increases scene light intensity by 0.05 for both diffuse and specular
    W3DViewDoc *doc = wxStaticCast(m_docManager->GetCurrentDocument(), W3DViewDoc);
    if (!doc)
        return;

    LightClass *light = doc->GetSceneLight();
    if (light != nullptr) {
        Vector3 diffuse, specular;
        light->Get_Diffuse(&diffuse);
        light->Get_Specular(&specular);

        Adjust_Light_Intensity(diffuse, 0.05F);
        Adjust_Light_Intensity(specular, 0.05F);

        light->Set_Diffuse(diffuse);
        light->Set_Specular(specular);
    }
}

void W3DViewFrame::OnDecSceneLight(wxCommandEvent &WXUNUSED(event))
{
    // MFC: MainFrm.cpp:2766-2786 (OnDecLight)
    // Decreases scene light intensity by 0.05 for both diffuse and specular
    W3DViewDoc *doc = wxStaticCast(m_docManager->GetCurrentDocument(), W3DViewDoc);
    if (!doc)
        return;

    LightClass *light = doc->GetSceneLight();
    if (light != nullptr) {
        Vector3 diffuse, specular;
        light->Get_Diffuse(&diffuse);
        light->Get_Specular(&specular);

        Adjust_Light_Intensity(diffuse, -0.05F);
        Adjust_Light_Intensity(specular, -0.05F);

        light->Set_Diffuse(diffuse);
        light->Set_Specular(specular);
    }
}

void W3DViewFrame::OnLightingExpose(wxCommandEvent &WXUNUSED(event))
{
    // MFC: MainFrm.cpp:2863-2872 (OnLightingExpose)
    // Toggles exposure of precalculated lighting
    WW3D::Expose_Prelit(!WW3D::Expose_Prelit());
}

void W3DViewFrame::OnUpdateLightingExpose(wxUpdateUIEvent &event)
{
    // MFC: MainFrm.cpp:2873-2877 (OnUpdateLightingExpose)
    // Sets checkbox state based on WW3D::Expose_Prelit() state
    event.Check(WW3D::Expose_Prelit());
}

void W3DViewFrame::OnKillSceneLight(wxCommandEvent &WXUNUSED(event))
{
    // MFC: MainFrm.cpp:3677-3689 (OnKillSceneLight)
    // Sets scene light to black (turns it off)
    W3DViewDoc *doc = wxStaticCast(m_docManager->GetCurrentDocument(), W3DViewDoc);
    if (!doc)
        return;

    LightClass *light = doc->GetSceneLight();
    if (light != nullptr) {
        const Vector3 black(0.0f, 0.0f, 0.0f);
        light->Set_Diffuse(black);
        light->Set_Specular(black);
    }
}

void W3DViewFrame::OnPrelitVertex(wxCommandEvent &WXUNUSED(event))
{
    // TODO(MFC-Match): Implement vertex lighting mode toggle
    // MFC Reference: MainFrm.cpp:3738-3751 (OnPrelitVertex, OnUpdatePrelitVertex)
    // WW3D methods EXIST: WW3D::Get_Prelit_Mode(), WW3D::Set_Prelit_Mode() (ww3d.h:253-254)
    // WW3D enum EXISTS: WW3D::PRELIT_MODE_VERTEX (ww3d.h:76)
    // 
    // MFC implementation:
    //   if (WW3D::Get_Prelit_Mode() != WW3D::PRELIT_MODE_VERTEX) {
    //       WW3D::Set_Prelit_Mode(WW3D::PRELIT_MODE_VERTEX);
    //       CDataTreeView *tree = (CDataTreeView *)m_wndSplitter.GetPane(0, 0);
    //       tree->Reload_Lightmap_Models();
    //       GetCurrentDocument()->Reload_Displayed_Object();
    //   }
    //
    // BLOCKED BY: Missing wxWidgets infrastructure
    //   - W3DViewTreeCtrl::Reload_Lightmap_Models() not implemented
    //   - W3DViewDoc::Reload_Displayed_Object() not implemented
    //   - Need to investigate tree/document model reload pattern
    //
    // Also needs OnUpdatePrelitVertex for checkbox state (similar to OnUpdateLightingExpose)
    // Impact: Low - advanced lighting mode (used for lightmapped models)
    wxMessageBox("Vertex Lighting not yet implemented", "TODO", wxOK | wxICON_INFORMATION, this);
}

void W3DViewFrame::OnPrelitMultipass(wxCommandEvent &WXUNUSED(event))
{
    // TODO(MFC-Match): Implement multipass lighting mode toggle
    // MFC Reference: MainFrm.cpp:3698-3734 (OnPrelitMultipass, OnUpdatePrelitMultipass)
    // WW3D methods EXIST: WW3D::Get_Prelit_Mode(), WW3D::Set_Prelit_Mode() (ww3d.h:253-254)
    // WW3D enum EXISTS: WW3D::PRELIT_MODE_LIGHTMAP_MULTI_PASS (ww3d.h:77)
    //
    // BLOCKED BY: Same infrastructure as OnPrelitVertex
    //   - Requires W3DViewTreeCtrl::Reload_Lightmap_Models()
    //   - Requires W3DViewDoc::Reload_Displayed_Object()
    //
    // Also needs OnUpdatePrelitMultipass for checkbox state
    // Impact: Low - advanced lighting mode (multi-pass lightmapping)
    wxMessageBox("Multi-Pass Lighting not yet implemented", "TODO", wxOK | wxICON_INFORMATION, this);
}

void W3DViewFrame::OnPrelitMultitex(wxCommandEvent &WXUNUSED(event))
{
    // TODO(MFC-Match): Implement multitexture lighting mode toggle
    // MFC Reference: MainFrm.cpp:3755-3787 (OnPrelitMultitex, OnUpdatePrelitMultitex)
    // WW3D methods EXIST: WW3D::Get_Prelit_Mode(), WW3D::Set_Prelit_Mode() (ww3d.h:253-254)
    // WW3D enum EXISTS: WW3D::PRELIT_MODE_LIGHTMAP_MULTI_TEXTURE (ww3d.h:78)
    //
    // BLOCKED BY: Same infrastructure as OnPrelitVertex
    //   - Requires W3DViewTreeCtrl::Reload_Lightmap_Models()
    //   - Requires W3DViewDoc::Reload_Displayed_Object()
    //
    // Also needs OnUpdatePrelitMultitex for checkbox state
    // Impact: Low - advanced lighting mode (multi-texture lightmapping)
    wxMessageBox("Multi-Texture Lighting not yet implemented", "TODO", wxOK | wxICON_INFORMATION, this);
}

// Settings menu handlers

void W3DViewFrame::OnTexturePathSettings(wxCommandEvent &WXUNUSED(event))
{
    // TODO(MFC-Verify): Verify TexturePaths dialog matches MFC exactly
    // Dialog appears implemented but needs visual/behavioral verification
    // MFC Reference: TexturePathDialog.cpp (TexturePathDialogClass)
    TexturePaths dialog(this);
    dialog.ShowModal();
}

void W3DViewFrame::OnDeviceSelection(wxCommandEvent &WXUNUSED(event))
{
    // TODO(MFC-Verify): Verify RenderDeviceSelector dialog matches MFC exactly
    // Dialog appears implemented but needs visual/behavioral verification
    // MFC Reference: DeviceSelectionDialog.cpp (CDeviceSelectionDialog)
    // Note: This should also be called during initialization (see w3dviewview_wx.cpp TODO)
    RenderDeviceSelector dialog(this);
    dialog.ShowModal();
}

void W3DViewFrame::OnResolutionSettings(wxCommandEvent &WXUNUSED(event))
{
    // MFC: MainFrm.cpp:1565-1576 (OnChangeResolution)
    // MFC implementation shows dialog only for DX8 builds
    // Since this wxWidgets build uses WW3D_DX8, dialog is available
#ifdef WW3D_DX8
    // TODO(MFC-Verify): Verify Resolution dialog matches MFC exactly
    // Dialog appears implemented but needs visual/behavioral verification
    // MFC Reference: ResolutionDialog.cpp (ResolutionDialogClass)
    Resolution dialog(this);
    dialog.ShowModal();
#else
    wxMessageBox("Feature removed during conversion to DX8.",
                 "Unsupported Feature", wxOK | wxICON_EXCLAMATION, this);
#endif
}

void W3DViewFrame::OnEnableGammaCorrection(wxCommandEvent &WXUNUSED(event))
{
    // MFC: MainFrm.cpp:4418-4436 (OnEnableGammaCorrection)
    // Toggles gamma correction enable/disable state
    wxConfigBase *config = wxConfigBase::Get();
    
    // Read current setting (0 or 1)
    long enableGamma = config->Read("/Config/EnableGamma", 0L);
    
    // Toggle the value
    enableGamma = (enableGamma ? 0 : 1);
    
    // Write back to config
    config->Write("/Config/EnableGamma", enableGamma);
    config->Flush();
    
    if (enableGamma) {
        // Enable gamma: read gamma value from config and apply
        long gammaInt = config->Read("/Config/Gamma", 10L);
        float gamma = static_cast<float>(gammaInt) / 10.0f;
        
        // Clamp to valid range (1.0 - 3.0)
        if (gamma < 1.0f) gamma = 1.0f;
        if (gamma > 3.0f) gamma = 3.0f;
        
        // Apply gamma correction (using WW3D wrapper for DX8Wrapper)
        WW3D::Set_Gamma(gamma, 0.0f, 1.0f);
    } else {
        // Disable gamma: reset to neutral (1.0)
        WW3D::Set_Gamma(1.0f, 0.0f, 1.0f);
    }
}

void W3DViewFrame::OnUpdateEnableGammaCorrection(wxUpdateUIEvent &event)
{
    // MFC: MainFrm.cpp:4438-4440 (OnUpdateEnableGammaCorrection)
    // Sets checkbox state based on config setting
    wxConfigBase *config = wxConfigBase::Get();
    long enableGamma = config->Read("/Config/EnableGamma", 0L);
    event.Check(enableGamma != 0);
}

void W3DViewFrame::OnGammaSettings(wxCommandEvent &WXUNUSED(event))
{
    // MFC: MainFrm.cpp:4441-4451 (OnSetGamma)
    // Shows gamma settings dialog if gamma is enabled,
    // otherwise shows warning message
    wxConfigBase *config = wxConfigBase::Get();
    long enableGamma = config->Read("/Config/EnableGamma", 0L);
    
    if (enableGamma) {
        // TODO(MFC-Verify): Verify GammaDialog matches MFC exactly
        // MFC Reference: GammaDialog.cpp (GammaDialogClass)
        GammaDialog dialog(this);
        dialog.ShowModal();
    } else {
        wxMessageBox("Gamma is disabled.\nEnable in Settings Menu.",
                     "Warning", wxOK | wxICON_WARNING, this);
    }
}
