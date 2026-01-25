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
#include "dialogs/Aboutbox_wx.h"
#include "dialogs/CameraSettings_wx.h"
#include "dialogs/BackgroundColor_wx.h"
#include "dialogs/BackgroundObject_wx.h"
#include "dialogs/TexturePaths_wx.h"
#include "dialogs/RenderDeviceSelector_wx.h"

#include <wx/menu.h>
#include <wx/toolbar.h>
#include <wx/msgdlg.h>
#include <wx/filedlg.h>

enum
{
    ID_ABOUT = wxID_ABOUT,
    ID_OBJECT_PROPERTIES = wxID_HIGHEST + 1,
    ID_LOD_GENERATE,
    ID_VIEW_RESET,
    ID_ALTERNATE_MATERIAL,
    ID_ANIMATION_SETTINGS,
    ID_BACKGROUND_SETTINGS,
    ID_CAMERA_SETTINGS,
    ID_LIGHT_SETTINGS,
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
    EVT_MENU(ID_BACKGROUND_SETTINGS, W3DViewFrame::OnBackgroundSettings)
    EVT_MENU(ID_CAMERA_SETTINGS, W3DViewFrame::OnCameraSettings)
    EVT_MENU(ID_LIGHT_SETTINGS, W3DViewFrame::OnLightSettings)
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

    // Settings menu
    wxMenu *settingsMenu = new wxMenu;
    settingsMenu->Append(ID_BACKGROUND_SETTINGS, "&Background...");
    settingsMenu->Append(ID_CAMERA_SETTINGS, "&Camera...");
    settingsMenu->Append(ID_LIGHT_SETTINGS, "&Lighting...");
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

void W3DViewFrame::OnBackgroundSettings(wxCommandEvent &WXUNUSED(event))
{
    // TODO(MFC-Match): Fix menu structure mismatch
    // MFC has separate menu items:
    //   - IDM_BACKGROUND_COLOR (OnBackgroundColor) -> BackgroundColor_wx
    //   - IDM_BACKGROUND_BMP (OnBackgroundBMP) -> BackgroundBmp_wx
    //   - IDM_BACKGROUND_OBJECT (OnBackgroundObject) -> BackgroundObject_wx
    //   - IDM_BACKGROUND_FOG (OnBackgroundFog) -> needs dialog
    // wxWidgets currently has single "Background..." menu item
    // Status: Menu structure needs reorganization to match MFC
    wxMessageBox("Background Settings dialog not yet implemented\n\n"
                 "MFC has multiple background menu items that need to be added:\n"
                 "- Background Color\n- Background BMP\n- Background Object\n- Background Fog",
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

void W3DViewFrame::OnLightSettings(wxCommandEvent &WXUNUSED(event))
{
    // TODO: Implement light settings dialog
    wxMessageBox("Light Settings dialog not yet implemented",
                 "TODO", wxOK | wxICON_INFORMATION, this);
}

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
