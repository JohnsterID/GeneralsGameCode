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
#include "ViewerScene.h"
#include "dialogs/Aboutbox_wx.h"
#include "dialogs/CameraSettings_wx.h"
#include "dialogs/BackgroundColor_wx.h"
#include "dialogs/BackgroundBmp_wx.h"
#include "dialogs/BackgroundObject_wx.h"
#include "dialogs/TexturePaths_wx.h"
#include "dialogs/RenderDeviceSelector_wx.h"
#include "dialogs/LightAmbientDialog_wx.h"
#include "dialogs/LightSceneDialog_wx.h"
#include "light.h"

#include <wx/menu.h>
#include <wx/toolbar.h>
#include <wx/msgdlg.h>
#include <wx/filedlg.h>

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
    EVT_MENU(ID_KILL_SCENE_LIGHT, W3DViewFrame::OnKillSceneLight)
    EVT_MENU(ID_PRELIT_VERTEX, W3DViewFrame::OnPrelitVertex)
    EVT_MENU(ID_PRELIT_MULTIPASS, W3DViewFrame::OnPrelitMultipass)
    EVT_MENU(ID_PRELIT_MULTITEX, W3DViewFrame::OnPrelitMultitex)
    // Settings menu
    EVT_MENU(ID_TEXTURE_PATH, W3DViewFrame::OnTexturePathSettings)
    EVT_MENU(ID_DEVICE_SELECTION, W3DViewFrame::OnDeviceSelection)
    EVT_MENU(ID_RESOLUTION_SETTINGS, W3DViewFrame::OnResolutionSettings)
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
    settingsMenu->Append(ID_GAMMA_SETTINGS, "&Gamma...");
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
    // TODO: Implement object properties dialog
    wxMessageBox("Object Properties dialog not yet implemented",
                 "TODO", wxOK | wxICON_INFORMATION, this);
}

void W3DViewFrame::OnLodGenerate(wxCommandEvent &WXUNUSED(event))
{
    // TODO: Implement LOD generation dialog
    wxMessageBox("LOD Generation dialog not yet implemented",
                 "TODO", wxOK | wxICON_INFORMATION, this);
}

void W3DViewFrame::OnViewReset(wxCommandEvent &WXUNUSED(event))
{
    // TODO: Implement view reset
}

void W3DViewFrame::OnAlternateMaterial(wxCommandEvent &WXUNUSED(event))
{
    // TODO: Implement alternate material
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
    // TODO(MFC-Match): Implement fog toggle functionality
    // MFC Reference: MainFrm.cpp:1649 (OnBackgroundFog)
    // MFC implementation:
    //   CW3DViewDoc *pdoc = (CW3DViewDoc *)GetActiveDocument();
    //   if (pdoc) {
    //       pdoc->EnableFog(!pdoc->IsFogEnabled());
    //   }
    // Also needs OnUpdateBackgroundFog for checkbox state (MainFrm.cpp:1634)
    // Status: Requires document methods IsFogEnabled() and EnableFog()
    wxMessageBox("Background Fog toggle not yet implemented\n\n"
                 "Requires:\n"
                 "- W3DViewDoc::IsFogEnabled()\n"
                 "- W3DViewDoc::EnableFog(bool)\n"
                 "- Menu checkbox state update handler",
                 "TODO", wxOK | wxICON_INFORMATION, this);
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
    // TODO(MFC-Match): Implement light Y rotation toggle
    // MFC Reference: MainFrm.cpp:2641-2654 (OnLightRotateY)
    // MFC implementation:
    //   CGraphicView *pgraphic_view = (CGraphicView *)m_wndSplitter.GetPane(0, 1);
    //   if (pgraphic_view != nullptr) {
    //       int rotation = (pgraphic_view->Get_Light_Rotation() ^ CGraphicView::RotateY);
    //       rotation &= ~CGraphicView::RotateYBack;
    //       pgraphic_view->Rotate_Light((CGraphicView::OBJECT_ROTATION)rotation);
    //   }
    // Status: Requires GraphicView Get_Light_Rotation() and Rotate_Light() methods
    // Impact: Medium - light rotation control
    wxMessageBox("Light Rotate Y not yet implemented", "TODO", wxOK | wxICON_INFORMATION, this);
}

void W3DViewFrame::OnLightRotateZ(wxCommandEvent &WXUNUSED(event))
{
    // TODO(MFC-Match): Implement light Z rotation toggle
    // MFC Reference: MainFrm.cpp:2685-2698 (OnLightRotateZ)
    // Similar to OnLightRotateY but for Z axis
    // Status: Requires GraphicView rotation methods
    // Impact: Medium - light rotation control
    wxMessageBox("Light Rotate Z not yet implemented", "TODO", wxOK | wxICON_INFORMATION, this);
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
    // TODO(MFC-Match): Implement precalculated lighting expose toggle
    // MFC Reference: MainFrm.cpp:2863-2872 (OnLightingExpose, OnUpdateLightingExpose)
    // MFC implementation:
    //   WW3D::Expose_Prelit(!WW3D::Expose_Prelit());  // toggle
    // Also needs OnUpdateLightingExpose for checkbox state:
    //   pcmdui->SetCheck(WW3D::Expose_Prelit());
    // Status: Requires WW3D engine method access
    // Impact: Low - advanced lighting feature
    wxMessageBox("Lighting Expose not yet implemented", "TODO", wxOK | wxICON_INFORMATION, this);
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
    // MFC implementation:
    //   if (WW3D::Get_Prelit_Mode() != WW3D::PRELIT_MODE_LIGHTMAP_MULTI_VERTEX) {
    //       WW3D::Set_Prelit_Mode(WW3D::PRELIT_MODE_LIGHTMAP_MULTI_VERTEX);
    //       // Reload lightmap models (see OnPrelitMultipass for pattern)
    //   }
    // Also needs OnUpdatePrelitVertex for checkbox state
    // Status: Requires WW3D engine mode access
    // Impact: Low - advanced lighting mode
    wxMessageBox("Vertex Lighting not yet implemented", "TODO", wxOK | wxICON_INFORMATION, this);
}

void W3DViewFrame::OnPrelitMultipass(wxCommandEvent &WXUNUSED(event))
{
    // TODO(MFC-Match): Implement multipass lighting mode toggle
    // MFC Reference: MainFrm.cpp:3698-3734 (OnPrelitMultipass, OnUpdatePrelitMultipass)
    // Changes prelit mode and reloads lightmap models
    // Status: Requires WW3D engine mode access and model reload
    // Impact: Low - advanced lighting mode
    wxMessageBox("Multi-Pass Lighting not yet implemented", "TODO", wxOK | wxICON_INFORMATION, this);
}

void W3DViewFrame::OnPrelitMultitex(wxCommandEvent &WXUNUSED(event))
{
    // TODO(MFC-Match): Implement multitexture lighting mode toggle
    // MFC Reference: MainFrm.cpp:3755-3787 (OnPrelitMultitex, OnUpdatePrelitMultitex)
    // Similar to OnPrelitMultipass but for multitexture mode
    // Status: Requires WW3D engine mode access
    // Impact: Low - advanced lighting mode
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
    // TODO: Implement resolution settings dialog
    wxMessageBox("Resolution Settings dialog not yet implemented",
                 "TODO", wxOK | wxICON_INFORMATION, this);
}

void W3DViewFrame::OnGammaSettings(wxCommandEvent &WXUNUSED(event))
{
    // TODO: Implement gamma settings dialog
    wxMessageBox("Gamma Settings dialog not yet implemented",
                 "TODO", wxOK | wxICON_INFORMATION, this);
}
