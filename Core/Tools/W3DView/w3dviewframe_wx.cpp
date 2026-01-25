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

// Engine includes for object manipulation
#ifdef CString
#undef CString
#endif

#include "rendobj.h"
#include "matrix3d.h"

#define CString wxString

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
    ID_OBJECT_RESET,
    ID_OBJECT_ROTATE_X,
    ID_OBJECT_ROTATE_Y,
    ID_OBJECT_ROTATE_Z,
    ID_OBJECT_ROTATE_Y_BACK,
    ID_OBJECT_ROTATE_Z_BACK,
    ID_OBJECT_ALTERNATE_MATERIALS,
    ID_VIEW_WIREFRAME,
    ID_VIEW_POLYGON_SORTING,
    ID_VIEW_PATCH_GAP_FILL,
    ID_VIEW_SUBDIVISION_1,
    ID_VIEW_SUBDIVISION_2,
    ID_VIEW_SUBDIVISION_3,
    ID_VIEW_SUBDIVISION_4,
    ID_VIEW_SUBDIVISION_5,
    ID_VIEW_SUBDIVISION_6,
    ID_VIEW_SUBDIVISION_7,
    ID_VIEW_SUBDIVISION_8,
    ID_ANIMATION_PLAY,
    ID_ANIMATION_PAUSE,
    ID_ANIMATION_STOP,
    ID_ANIMATION_SETTINGS,
    ID_BACKGROUND_COLOR,
    ID_BACKGROUND_BMP,
    ID_BACKGROUND_OBJECT,
    ID_BACKGROUND_FOG,
    // Camera menu items
    ID_CAMERA_FRONT,
    ID_CAMERA_BACK,
    ID_CAMERA_LEFT,
    ID_CAMERA_RIGHT,
    ID_CAMERA_TOP,
    ID_CAMERA_BOTTOM,
    ID_CAMERA_RESET,
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
    ID_LIGHT_ROTATE_Y_BACK,
    ID_LIGHT_ROTATE_Z_BACK,
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
    EVT_MENU(ID_OBJECT_RESET, W3DViewFrame::OnObjectReset)
    EVT_MENU(ID_OBJECT_ROTATE_X, W3DViewFrame::OnObjectRotateX)
    EVT_MENU(ID_OBJECT_ROTATE_Y, W3DViewFrame::OnObjectRotateY)
    EVT_MENU(ID_OBJECT_ROTATE_Z, W3DViewFrame::OnObjectRotateZ)
    EVT_MENU(ID_OBJECT_ROTATE_Y_BACK, W3DViewFrame::OnObjectRotateYBack)
    EVT_MENU(ID_OBJECT_ROTATE_Z_BACK, W3DViewFrame::OnObjectRotateZBack)
    EVT_MENU(ID_OBJECT_ALTERNATE_MATERIALS, W3DViewFrame::OnObjectAlternateMaterials)
    EVT_MENU(ID_VIEW_WIREFRAME, W3DViewFrame::OnWireframe)
    EVT_UPDATE_UI(ID_VIEW_WIREFRAME, W3DViewFrame::OnUpdateWireframe)
    EVT_MENU(ID_VIEW_POLYGON_SORTING, W3DViewFrame::OnPolygonSorting)
    EVT_UPDATE_UI(ID_VIEW_POLYGON_SORTING, W3DViewFrame::OnUpdatePolygonSorting)
    EVT_MENU(ID_VIEW_PATCH_GAP_FILL, W3DViewFrame::OnViewPatchGapFill)
    EVT_UPDATE_UI(ID_VIEW_PATCH_GAP_FILL, W3DViewFrame::OnUpdateViewPatchGapFill)
    EVT_MENU(ID_VIEW_SUBDIVISION_1, W3DViewFrame::OnViewSubdivision1)
    EVT_UPDATE_UI(ID_VIEW_SUBDIVISION_1, W3DViewFrame::OnUpdateViewSubdivision1)
    EVT_MENU(ID_VIEW_SUBDIVISION_2, W3DViewFrame::OnViewSubdivision2)
    EVT_UPDATE_UI(ID_VIEW_SUBDIVISION_2, W3DViewFrame::OnUpdateViewSubdivision2)
    EVT_MENU(ID_VIEW_SUBDIVISION_3, W3DViewFrame::OnViewSubdivision3)
    EVT_UPDATE_UI(ID_VIEW_SUBDIVISION_3, W3DViewFrame::OnUpdateViewSubdivision3)
    EVT_MENU(ID_VIEW_SUBDIVISION_4, W3DViewFrame::OnViewSubdivision4)
    EVT_UPDATE_UI(ID_VIEW_SUBDIVISION_4, W3DViewFrame::OnUpdateViewSubdivision4)
    EVT_MENU(ID_VIEW_SUBDIVISION_5, W3DViewFrame::OnViewSubdivision5)
    EVT_UPDATE_UI(ID_VIEW_SUBDIVISION_5, W3DViewFrame::OnUpdateViewSubdivision5)
    EVT_MENU(ID_VIEW_SUBDIVISION_6, W3DViewFrame::OnViewSubdivision6)
    EVT_UPDATE_UI(ID_VIEW_SUBDIVISION_6, W3DViewFrame::OnUpdateViewSubdivision6)
    EVT_MENU(ID_VIEW_SUBDIVISION_7, W3DViewFrame::OnViewSubdivision7)
    EVT_UPDATE_UI(ID_VIEW_SUBDIVISION_7, W3DViewFrame::OnUpdateViewSubdivision7)
    EVT_MENU(ID_VIEW_SUBDIVISION_8, W3DViewFrame::OnViewSubdivision8)
    EVT_UPDATE_UI(ID_VIEW_SUBDIVISION_8, W3DViewFrame::OnUpdateViewSubdivision8)
    EVT_MENU(ID_ANIMATION_PLAY, W3DViewFrame::OnAnimationPlay)
    EVT_MENU(ID_ANIMATION_PAUSE, W3DViewFrame::OnAnimationPause)
    EVT_MENU(ID_ANIMATION_STOP, W3DViewFrame::OnAnimationStop)
    EVT_MENU(ID_ANIMATION_SETTINGS, W3DViewFrame::OnAnimationSettings)
    EVT_MENU(ID_BACKGROUND_COLOR, W3DViewFrame::OnBackgroundColor)
    EVT_MENU(ID_BACKGROUND_BMP, W3DViewFrame::OnBackgroundBmp)
    EVT_MENU(ID_BACKGROUND_OBJECT, W3DViewFrame::OnBackgroundObject)
    EVT_MENU(ID_BACKGROUND_FOG, W3DViewFrame::OnBackgroundFog)
    EVT_UPDATE_UI(ID_BACKGROUND_FOG, W3DViewFrame::OnUpdateBackgroundFog)
    // Camera menu
    EVT_MENU(ID_CAMERA_FRONT, W3DViewFrame::OnCameraFront)
    EVT_MENU(ID_CAMERA_BACK, W3DViewFrame::OnCameraBack)
    EVT_MENU(ID_CAMERA_LEFT, W3DViewFrame::OnCameraLeft)
    EVT_MENU(ID_CAMERA_RIGHT, W3DViewFrame::OnCameraRight)
    EVT_MENU(ID_CAMERA_TOP, W3DViewFrame::OnCameraTop)
    EVT_MENU(ID_CAMERA_BOTTOM, W3DViewFrame::OnCameraBottom)
    EVT_MENU(ID_CAMERA_RESET, W3DViewFrame::OnCameraReset)
    EVT_MENU(ID_CAMERA_SETTINGS, W3DViewFrame::OnCameraSettings)
    // Light menu
    EVT_MENU(ID_LIGHT_ROTATE_Y, W3DViewFrame::OnLightRotateY)
    EVT_MENU(ID_LIGHT_ROTATE_Z, W3DViewFrame::OnLightRotateZ)
    EVT_MENU(ID_LIGHT_ROTATE_Y_BACK, W3DViewFrame::OnLightRotateYBack)
    EVT_MENU(ID_LIGHT_ROTATE_Z_BACK, W3DViewFrame::OnLightRotateZBack)
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
    EVT_UPDATE_UI(ID_PRELIT_VERTEX, W3DViewFrame::OnUpdatePrelitVertex)
    EVT_MENU(ID_PRELIT_MULTIPASS, W3DViewFrame::OnPrelitMultipass)
    EVT_UPDATE_UI(ID_PRELIT_MULTIPASS, W3DViewFrame::OnUpdatePrelitMultipass)
    EVT_MENU(ID_PRELIT_MULTITEX, W3DViewFrame::OnPrelitMultitex)
    EVT_UPDATE_UI(ID_PRELIT_MULTITEX, W3DViewFrame::OnUpdatePrelitMultitex)
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
    
    // Add accelerators for rotation back and camera positioning
    // MFC Reference: W3DView.rc accelerators
    //
    // Object rotation back (no modifier):
    //   VK_DOWN -> IDM_OBJECT_ROTATE_Y_BACK (MainFrm.cpp:2597-2613)
    //   VK_LEFT -> IDM_OBJECT_ROTATE_Z_BACK (MainFrm.cpp:2619-2635)
    //
    // Light rotation back (Ctrl modifier):
    //   Ctrl+VK_DOWN -> IDM_LIGHT_ROTATE_Y_BACK (MainFrm.cpp:2663-2676)
    //   Ctrl+VK_LEFT -> IDM_LIGHT_ROTATE_Z_BACK (MainFrm.cpp:2707-2720)
    //
    // Camera positioning (Ctrl modifier):
    //   Ctrl+F -> IDM_CAMERA_FRONT (MainFrm.cpp:1397-1408)
    //   Ctrl+B -> IDM_CAMERA_BACK (MainFrm.cpp:1357-1368)
    //   Ctrl+L -> IDM_CAMERA_LEFT (MainFrm.cpp:1417-1428)
    //   Ctrl+R -> IDM_CAMERA_RIGHT (MainFrm.cpp:1467-1478)
    //   Ctrl+T -> IDM_CAMERA_TOP (MainFrm.cpp:1487-1498)
    //   Ctrl+M -> IDM_CAMERA_BOTTOM (MainFrm.cpp:1377-1388)
    wxAcceleratorEntry entries[10];
    // Object rotation back (no modifier)
    entries[0].Set(wxACCEL_NORMAL, WXK_DOWN, ID_OBJECT_ROTATE_Y_BACK);
    entries[1].Set(wxACCEL_NORMAL, WXK_LEFT, ID_OBJECT_ROTATE_Z_BACK);
    // Light rotation back (Ctrl modifier)
    entries[2].Set(wxACCEL_CTRL, WXK_DOWN, ID_LIGHT_ROTATE_Y_BACK);
    entries[3].Set(wxACCEL_CTRL, WXK_LEFT, ID_LIGHT_ROTATE_Z_BACK);
    // Camera positioning (Ctrl modifier)
    entries[4].Set(wxACCEL_CTRL, 'F', ID_CAMERA_FRONT);
    entries[5].Set(wxACCEL_CTRL, 'B', ID_CAMERA_BACK);
    entries[6].Set(wxACCEL_CTRL, 'L', ID_CAMERA_LEFT);
    entries[7].Set(wxACCEL_CTRL, 'R', ID_CAMERA_RIGHT);
    entries[8].Set(wxACCEL_CTRL, 'T', ID_CAMERA_TOP);
    entries[9].Set(wxACCEL_CTRL, 'M', ID_CAMERA_BOTTOM);
    wxAcceleratorTable accel(10, entries);
    SetAcceleratorTable(accel);

    Centre();
}

W3DViewFrame::~W3DViewFrame()
{
}

wxDocument* W3DViewFrame::GetDocument() const
{
    // TODO: wxDocParentFrame doesn't have GetDocument(), so we get it through the view
    // Get the document manager
    wxDocManager* docManager = GetDocumentManager();
    if (!docManager) {
        return nullptr;
    }
    
    // Get the current document (first in the list, since we're single-document)
    wxList& docs = docManager->GetDocuments();
    if (docs.GetCount() > 0) {
        return wxStaticCast(docs.GetFirst()->GetData(), wxDocument);
    }
    
    return nullptr;
}

void W3DViewFrame::CreateMenuBar()
{
    // TODO(MFC-Match): Complete menu structure overhaul needed
    // Current wxWidgets menu is ~50% complete compared to MFC
    // See MENU_STRUCTURE_MISMATCH.md and SESSION_21_VIEW_MENU_INVESTIGATION.md
    //
    // ✅ FIXES APPLIED (Session 21):
    // ✅ Menu Location Fixed: "Reset" and "Toggle Alternate Materials" moved to Object menu
    //    - Object → Reset (was View → Reset View) - now matches MFC structure
    //    - Object → Toggle Alternate Materials (was View → Alternate Material) - now matches MFC
    //    - IDs renamed: ID_OBJECT_RESET, ID_OBJECT_ALTERNATE_MATERIALS
    //    - Handlers renamed: OnObjectReset, OnObjectAlternateMaterials
    //
    // ✅ COMPLETED:
    // 1. ✅ View Menu Rendering Controls: COMPLETE (Wireframe, Polygon Sorting, Patch Gap Fill, Subdivision 1-8)
    // 2. ✅ Object menu structure: Basic structure with Properties, LOD, Reset, Toggle Alternate Materials
    // 3. ✅ Menu item locations: Reset and Toggle Alternate Materials in correct menu
    //
    // REMAINING ISSUES:
    // 1. ⚠️ Settings menu doesn't exist in MFC - items scattered across File/View/Object
    // 2. ⚠️ "Set Gamma..." is in Settings menu, should be in View menu per MFC
    // 3. ⚠️ Missing View menu items: Toolbars submenu, Status Bar, Prev/Next, Fullscreen, Device/Resolution
    // 4. ⚠️ Missing Object menu items: Restrict Anims (✅ Rotate X/Y/Z implemented in Session 22)
    // 5. ⚠️ Missing Export submenu (Aggregate, Emitter, LOD, Primitive, Sound Object)
    // 6. ⚠️ Background should be 4 separate items, not 1 combined
    // 7. ⚠️ Save Settings vs Save file (Ctrl+S conflict)
    //
    // TODO(MFC-Match): Add View → Toolbars submenu (Main, Object, Animation)
    // TODO(MFC-Match): Add View → Status Bar toggle
    // TODO(MFC-Match): Move "Set Gamma..." from Settings to View menu
    // TODO(MFC-Match): Add Object → Rotate X/Y/Z with shortcuts (Ctrl+X, Up Arrow, Rt Arrow)
    // TODO(MFC-Match): Add Object → Restrict Anims
    // TODO(MFC-Match): Add Export submenu to File menu
    // TODO(MFC-Investigate): Decide Settings menu strategy (doesn't exist in MFC)
    //
    // MFC Reference: W3DView.rc lines 181-300+
    // Status: Menu location issues fixed, more items needed for exact matching
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
    // MFC Reference: W3DView.rc:209-243
    wxMenu *viewMenu = new wxMenu;
    viewMenu->AppendCheckItem(ID_VIEW_WIREFRAME, "&Wireframe Mode");
    viewMenu->AppendCheckItem(ID_VIEW_POLYGON_SORTING, "Polygon &Sorting\tCtrl+P");
    viewMenu->AppendSeparator();
    wxMenu *subdivMenu = new wxMenu;
    subdivMenu->AppendRadioItem(ID_VIEW_SUBDIVISION_1, "Level &1");
    subdivMenu->AppendRadioItem(ID_VIEW_SUBDIVISION_2, "Level &2");
    subdivMenu->AppendRadioItem(ID_VIEW_SUBDIVISION_3, "Level &3");
    subdivMenu->AppendRadioItem(ID_VIEW_SUBDIVISION_4, "Level &4");
    subdivMenu->AppendRadioItem(ID_VIEW_SUBDIVISION_5, "Level &5");
    subdivMenu->AppendRadioItem(ID_VIEW_SUBDIVISION_6, "Level &6");
    subdivMenu->AppendRadioItem(ID_VIEW_SUBDIVISION_7, "Level &7");
    subdivMenu->AppendRadioItem(ID_VIEW_SUBDIVISION_8, "Level &8");
    viewMenu->AppendSubMenu(subdivMenu, "Su&bdivision Level");
    viewMenu->AppendCheckItem(ID_VIEW_PATCH_GAP_FILL, "&Patch Gap Fill");
    menuBar->Append(viewMenu, "&View");

    // Object menu
    // MFC Reference: W3DView.rc:244-258
    wxMenu *objectMenu = new wxMenu;
    objectMenu->Append(ID_OBJECT_PROPERTIES, "&Properties...\tEnter");
    objectMenu->Append(ID_LOD_GENERATE, "Generate &LOD...");
    objectMenu->AppendSeparator();
    objectMenu->Append(ID_OBJECT_ROTATE_X, "Rotate &X\tCtrl+X");
    objectMenu->Append(ID_OBJECT_ROTATE_Y, "Rotate &Y\tUp");
    objectMenu->Append(ID_OBJECT_ROTATE_Z, "Rotate &Z\tRight");
    objectMenu->AppendSeparator();
    objectMenu->Append(ID_OBJECT_RESET, "&Reset");
    objectMenu->AppendSeparator();
    objectMenu->Append(ID_OBJECT_ALTERNATE_MATERIALS, "Toggle Alternate &Materials");
    // TODO(MFC-Match): Add "Restrict Anims" menu item after Toggle Alternate Materials
    //   MFC: IDM_OBJECT_RESTRICT_ANIMS (W3DView.rc:258)
    //   Handler: MainFrm.cpp (need to investigate)
    //   Should have separator before it
    // objectMenu->AppendSeparator();
    // objectMenu->Append(ID_OBJECT_RESTRICT_ANIMS, "Restrict &Anims");
    menuBar->Append(objectMenu, "&Object");

    // Animation menu
    // MFC Reference: W3DView.rc:263-273
    wxMenu *animMenu = new wxMenu;
    animMenu->Append(ID_ANIMATION_PLAY, "&Play");
    animMenu->Append(ID_ANIMATION_PAUSE, "P&ause");
    animMenu->Append(ID_ANIMATION_STOP, "&Stop");
    animMenu->AppendSeparator();
    // TODO(MFC-Investigate): Add "Step &Back" menu item (IDM_ANI_STEP_BKWD)
    // TODO(MFC-Investigate): Add "Step &Forward" menu item (IDM_ANI_STEP_FWD)
    animMenu->AppendSeparator();
    animMenu->Append(ID_ANIMATION_SETTINGS, "Se&ttings...");
    animMenu->AppendSeparator();
    // TODO(MFC-Investigate): Add "Ad&vanced...\tCtrl+V" menu item (IDM_ADVANCED_ANIM)
    menuBar->Append(animMenu, "&Animation");

    // Camera menu
    // MFC Reference: W3DView.rc (Camera menu structure)
    wxMenu *cameraMenu = new wxMenu;
    cameraMenu->Append(ID_CAMERA_FRONT, "&Front\tCtrl+F");
    cameraMenu->Append(ID_CAMERA_BACK, "&Back\tCtrl+B");
    cameraMenu->Append(ID_CAMERA_LEFT, "&Left\tCtrl+L");
    cameraMenu->Append(ID_CAMERA_RIGHT, "&Right\tCtrl+R");
    cameraMenu->Append(ID_CAMERA_TOP, "&Top\tCtrl+T");
    cameraMenu->Append(ID_CAMERA_BOTTOM, "Bo&ttom\tCtrl+M");
    cameraMenu->AppendSeparator();
    // TODO(MFC-Investigate): Add "Rotate &X Only" toggle (IDM_CAMERA_ALLOW_ROTATE_X)
    // TODO(MFC-Investigate): Add "Rotate &Y Only" toggle (IDM_CAMERA_ALLOW_ROTATE_Y)
    // TODO(MFC-Investigate): Add "Rotate &Z Only" toggle (IDM_CAMERA_ALLOW_ROTATE_Z)
    // TODO(MFC-Investigate): Add "&Copy Screen Size To Clipboard\tCtrl+C" (IDM_COPY_SCREEN_SIZE)
    //   Note: Ctrl+C may conflict with standard copy - investigate alternative
    cameraMenu->AppendSeparator();
    // TODO(MFC-Investigate): Add "&Animate Camera\tF8" (IDM_CAMERA_ANIMATE)
    // TODO(MFC-Investigate): Add "+X Camera" (IDM_CAMERA_BONE_POS_X)
    cameraMenu->AppendSeparator();
    cameraMenu->Append(ID_CAMERA_SETTINGS, "Settin&gs...");
    // TODO(MFC-Investigate): Add "&Set Distance..." (IDM_SET_CAMERA_DISTANCE)
    cameraMenu->AppendSeparator();
    cameraMenu->Append(ID_CAMERA_RESET, "&Reset");
    menuBar->Append(cameraMenu, "&Camera");

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
    // TODO(MFC-Match): Camera Settings moved to Camera menu (matches MFC structure)
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

void W3DViewFrame::OnObjectReset(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:1922-1933 (OnObjectReset)
    //   Calls: CGraphicView::ResetObject (GraphicView.cpp:1593-1611)
    //
    // MFC Implementation (GraphicView.cpp:1593-1611):
    //   CW3DViewDoc *doc = ::GetCurrentDocument();
    //   if (doc) {
    //       RenderObjClass *pCRenderObj = doc->GetDisplayedObject();
    //       if (pCRenderObj) {
    //           pCRenderObj->Set_Transform(Matrix3D(1));  // Identity matrix = reset
    //       }
    //   }
    //
    // Behavior: Resets the displayed object's transform to identity matrix
    //           This removes all rotation, scaling, and translation
    //
    // ✅ MENU LOCATION: Corrected in Session 21 (was in View menu, now in Object menu)
    
    // Get the document
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) {
        return;
    }
    
    // Get the displayed object
    RenderObjClass* renderObj = doc->GetDisplayedObject();
    if (renderObj) {
        // Reset the object's transform to identity matrix
        // Matrix3D(1) or Matrix3D(true) creates an identity matrix
        renderObj->Set_Transform(Matrix3D(true));
    }
}

void W3DViewFrame::OnObjectRotateX(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:1564-1579 (OnObjectRotateX)
    //
    // MFC Implementation:
    //   CGraphicView *pCGraphicView = (CGraphicView *)m_wndSplitter.GetPane (0, 1);
    //   int iXRotation = (pCGraphicView->GetObjectRotation () ^ (CGraphicView::RotateX));
    //   iXRotation &= ~CGraphicView::RotateXBack;
    //   pCGraphicView->RotateObject ((CGraphicView::OBJECT_ROTATION)iXRotation);
    //
    // Behavior: Toggles continuous X-axis rotation on/off
    //           XOR flips the RotateX bit, clearing RotateXBack ensures forward rotation
    //
    // Menu: Object → Rotate X
    // Shortcut: Ctrl+X
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    // Toggle X rotation bit, clear X back rotation bit
    int rotation = (graphicView->GetObjectRotation() ^ CGraphicView::RotateX);
    rotation &= ~CGraphicView::RotateXBack;
    
    graphicView->RotateObject(static_cast<CGraphicView::OBJECT_ROTATION>(rotation));
}

void W3DViewFrame::OnObjectRotateY(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:1541-1555 (OnObjectRotateY)
    //
    // MFC Implementation:
    //   CGraphicView *pCGraphicView = (CGraphicView *)m_wndSplitter.GetPane (0, 1);
    //   int iYRotation = (pCGraphicView->GetObjectRotation () ^ (CGraphicView::RotateY));
    //   iYRotation &= ~CGraphicView::RotateYBack;
    //   pCGraphicView->RotateObject ((CGraphicView::OBJECT_ROTATION)iYRotation);
    //
    // Behavior: Toggles continuous Y-axis rotation on/off
    //
    // Menu: Object → Rotate Y
    // Shortcut: Up Arrow
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    // Toggle Y rotation bit, clear Y back rotation bit
    int rotation = (graphicView->GetObjectRotation() ^ CGraphicView::RotateY);
    rotation &= ~CGraphicView::RotateYBack;
    
    graphicView->RotateObject(static_cast<CGraphicView::OBJECT_ROTATION>(rotation));
}

void W3DViewFrame::OnObjectRotateZ(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:1507-1532 (OnObjectRotateZ)
    //
    // MFC Implementation:
    //   CGraphicView *pCGraphicView = (CGraphicView *)m_wndSplitter.GetPane (0, 1);
    //   int iZRotation = (pCGraphicView->GetObjectRotation () ^ (CGraphicView::RotateZ));
    //   iZRotation &= ~CGraphicView::RotateZBack;
    //   pCGraphicView->RotateObject ((CGraphicView::OBJECT_ROTATION)iZRotation);
    //   if (iZRotation & ROTATION_Z) {
    //       m_objectToolbar.SetButtonState (IDM_OBJECT_ROTATE_Z, CFancyToolbar::StateDn);
    //   } else {
    //       m_objectToolbar.SetButtonState (IDM_OBJECT_ROTATE_Z, CFancyToolbar::StateUp);
    //   }
    //
    // Behavior: Toggles continuous Z-axis rotation on/off
    //           MFC also updates toolbar button state (not implemented in wxWidgets yet)
    //
    // Menu: Object → Rotate Z
    // Shortcut: Right Arrow
    //
    // TODO(MFC-Match): Add toolbar button state update when Object toolbar is implemented
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    // Toggle Z rotation bit, clear Z back rotation bit
    int rotation = (graphicView->GetObjectRotation() ^ CGraphicView::RotateZ);
    rotation &= ~CGraphicView::RotateZBack;
    
    graphicView->RotateObject(static_cast<CGraphicView::OBJECT_ROTATION>(rotation));
    
    // TODO(MFC-Match): Update toolbar button state when toolbar is implemented
    // if (rotation & ROTATION_Z) {
    //     // Set toolbar button down
    // } else {
    //     // Set toolbar button up
    // }
}

void W3DViewFrame::OnObjectRotateYBack(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:2597-2613 (OnObjectRotateYBack)
    //
    // MFC Implementation:
    //   CGraphicView *pCGraphicView = (CGraphicView *)m_wndSplitter.GetPane (0, 1);
    //   int iYRotation = (pCGraphicView->GetObjectRotation () ^ (CGraphicView::RotateYBack));
    //   iYRotation &= ~CGraphicView::RotateY;
    //   pCGraphicView->RotateObject ((CGraphicView::OBJECT_ROTATION)iYRotation);
    //
    // Behavior: Toggles reverse Y-axis rotation on/off
    //
    // Note: No menu item in MFC, accelerator only
    // Shortcut: Down Arrow
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    // Toggle Y back rotation bit, clear forward Y rotation bit
    int rotation = (graphicView->GetObjectRotation() ^ CGraphicView::RotateYBack);
    rotation &= ~CGraphicView::RotateY;
    
    graphicView->RotateObject(static_cast<CGraphicView::OBJECT_ROTATION>(rotation));
}

void W3DViewFrame::OnObjectRotateZBack(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:2619-2635 (OnObjectRotateZBack)
    //
    // MFC Implementation:
    //   CGraphicView *pCGraphicView = (CGraphicView *)m_wndSplitter.GetPane (0, 1);
    //   int iZRotation = (pCGraphicView->GetObjectRotation () ^ (CGraphicView::RotateZBack));
    //   iZRotation &= ~CGraphicView::RotateZ;
    //   pCGraphicView->RotateObject ((CGraphicView::OBJECT_ROTATION)iZRotation);
    //
    // Behavior: Toggles reverse Z-axis rotation on/off
    //
    // Note: No menu item in MFC, accelerator only
    // Shortcut: Left Arrow
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    // Toggle Z back rotation bit, clear forward Z rotation bit
    int rotation = (graphicView->GetObjectRotation() ^ CGraphicView::RotateZBack);
    rotation &= ~CGraphicView::RotateZ;
    
    graphicView->RotateObject(static_cast<CGraphicView::OBJECT_ROTATION>(rotation));
}

void W3DViewFrame::OnObjectAlternateMaterials(wxCommandEvent &WXUNUSED(event))
{
    // TODO(MFC-Match-BLOCKED): Implement alternate material toggle
    // ✅ MENU LOCATION: Corrected! Now in Object menu (was in View menu)
    //
    // MFC Structure:
    //   - Menu: Object → Toggle Alternate Materials ✅ CORRECT
    //   - ID: IDM_OBJECT_ALTERNATE_MATERIALS ✅ CORRECT (was ID_ALTERNATE_MATERIAL)
    //   - Handler: CMainFrame::OnObjectAlternateMaterials (MainFrm.cpp:4073-4077)
    //
    // MFC Reference: MainFrm.cpp:4073-4077 (OnObjectAlternateMaterials)
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
    // Status: Menu location corrected (Session 21), implementation blocked
    // Investigation: SESSION_21_VIEW_MENU_INVESTIGATION.md
    // Impact: Medium - affects material display for models with alternate materials
    // Priority: Defer until engine header conflicts resolved
}

void W3DViewFrame::OnViewPatchGapFill(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:4255-4265 (OnViewPatchGapFill)
    // Toggle N-Patches gap-filling mode between enabled and disabled
    if (WW3D::Get_NPatches_Gap_Filling_Mode() == WW3D::NPATCHES_GAP_FILLING_ENABLED) {
        WW3D::Set_NPatches_Gap_Filling_Mode(WW3D::NPATCHES_GAP_FILLING_DISABLED);
        wxConfig::Get()->Write("/Config/NPatchesGapFilling", 0L);
    } else {
        WW3D::Set_NPatches_Gap_Filling_Mode(WW3D::NPATCHES_GAP_FILLING_ENABLED);
        wxConfig::Get()->Write("/Config/NPatchesGapFilling", 1L);
    }
    wxConfig::Get()->Flush();
}

void W3DViewFrame::OnUpdateViewPatchGapFill(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:4270-4275 (OnUpdateViewPatchGapFill)
    // Check the menu item if gap-filling is turned on
    bool enabled = (WW3D::Get_NPatches_Gap_Filling_Mode() == WW3D::NPATCHES_GAP_FILLING_ENABLED);
    event.Check(enabled);
}

void W3DViewFrame::OnViewSubdivision1(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:4277-4284 (OnViewSubdivision1)
    // Set N-Patches subdivision level to 1
    WW3D::Set_NPatches_Level(1);
    wxConfig::Get()->Write("/Config/NPatchesSubdivision", 1L);
    wxConfig::Get()->Flush();
}

void W3DViewFrame::OnUpdateViewSubdivision1(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:4286-4291 (OnUpdateViewSubdivision1)
    // Check the menu item if current subdivision level is 1
    event.Check(WW3D::Get_NPatches_Level() == 1);
}

void W3DViewFrame::OnViewSubdivision2(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:4293-4300 (OnViewSubdivision2)
    // Set N-Patches subdivision level to 2
    WW3D::Set_NPatches_Level(2);
    wxConfig::Get()->Write("/Config/NPatchesSubdivision", 2L);
    wxConfig::Get()->Flush();
}

void W3DViewFrame::OnUpdateViewSubdivision2(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:4302-4307 (OnUpdateViewSubdivision2)
    // Check the menu item if current subdivision level is 2
    event.Check(WW3D::Get_NPatches_Level() == 2);
}

void W3DViewFrame::OnViewSubdivision3(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:4309-4316 (OnViewSubdivision3)
    // Set N-Patches subdivision level to 3
    WW3D::Set_NPatches_Level(3);
    wxConfig::Get()->Write("/Config/NPatchesSubdivision", 3L);
    wxConfig::Get()->Flush();
}

void W3DViewFrame::OnUpdateViewSubdivision3(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:4318-4323 (OnUpdateViewSubdivision3)
    // Check the menu item if current subdivision level is 3
    event.Check(WW3D::Get_NPatches_Level() == 3);
}

void W3DViewFrame::OnViewSubdivision4(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:4325-4332 (OnViewSubdivision4)
    // Set N-Patches subdivision level to 4
    WW3D::Set_NPatches_Level(4);
    wxConfig::Get()->Write("/Config/NPatchesSubdivision", 4L);
    wxConfig::Get()->Flush();
}

void W3DViewFrame::OnUpdateViewSubdivision4(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:4334-4339 (OnUpdateViewSubdivision4)
    // Check the menu item if current subdivision level is 4
    event.Check(WW3D::Get_NPatches_Level() == 4);
}

void W3DViewFrame::OnViewSubdivision5(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:4341-4348 (OnViewSubdivision5)
    // Set N-Patches subdivision level to 5
    WW3D::Set_NPatches_Level(5);
    wxConfig::Get()->Write("/Config/NPatchesSubdivision", 5L);
    wxConfig::Get()->Flush();
}

void W3DViewFrame::OnUpdateViewSubdivision5(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:4350-4355 (OnUpdateViewSubdivision5)
    // Check the menu item if current subdivision level is 5
    event.Check(WW3D::Get_NPatches_Level() == 5);
}

void W3DViewFrame::OnViewSubdivision6(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:4357-4364 (OnViewSubdivision6)
    // Set N-Patches subdivision level to 6
    WW3D::Set_NPatches_Level(6);
    wxConfig::Get()->Write("/Config/NPatchesSubdivision", 6L);
    wxConfig::Get()->Flush();
}

void W3DViewFrame::OnUpdateViewSubdivision6(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:4366-4371 (OnUpdateViewSubdivision6)
    // Check the menu item if current subdivision level is 6
    event.Check(WW3D::Get_NPatches_Level() == 6);
}

void W3DViewFrame::OnViewSubdivision7(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:4373-4380 (OnViewSubdivision7)
    // Set N-Patches subdivision level to 7
    WW3D::Set_NPatches_Level(7);
    wxConfig::Get()->Write("/Config/NPatchesSubdivision", 7L);
    wxConfig::Get()->Flush();
}

void W3DViewFrame::OnUpdateViewSubdivision7(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:4382-4387 (OnUpdateViewSubdivision7)
    // Check the menu item if current subdivision level is 7
    event.Check(WW3D::Get_NPatches_Level() == 7);
}

void W3DViewFrame::OnViewSubdivision8(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:4389-4396 (OnViewSubdivision8)
    // Set N-Patches subdivision level to 8
    WW3D::Set_NPatches_Level(8);
    wxConfig::Get()->Write("/Config/NPatchesSubdivision", 8L);
    wxConfig::Get()->Flush();
}

void W3DViewFrame::OnUpdateViewSubdivision8(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:4398-4403 (OnUpdateViewSubdivision8)
    // Check the menu item if current subdivision level is 8
    event.Check(WW3D::Get_NPatches_Level() == 8);
}

void W3DViewFrame::OnWireframe(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:4172-4179 (OnWireframeMode)
    // Toggle wireframe rendering mode (scene-specific setting)
    W3DViewDoc *doc = wxDynamicCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    ViewerSceneClass *scene = doc->GetScene();
    if (!scene) return;
    
    // Toggle between LINE (wireframe) and FILL (normal) rendering
    bool enable = (scene->Get_Polygon_Mode() != SceneClass::LINE);
    scene->Set_Polygon_Mode(enable ? SceneClass::LINE : SceneClass::FILL);
    // Note: No config persistence (scene-specific, not global setting)
}

void W3DViewFrame::OnUpdateWireframe(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:4188-4193 (OnUpdateWireframeMode)
    // Check the menu item if wireframe mode is enabled
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

void W3DViewFrame::OnPolygonSorting(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:4202-4210 (OnToggleSorting)
    // Toggle polygon sorting state (global WW3D setting)
    bool sorting = !WW3D::Is_Sorting_Enabled();
    WW3D::_Invalidate_Mesh_Cache();
    WW3D::Enable_Sorting(sorting);
    // Save the new value in wxConfig
    wxConfig::Get()->Write("/Config/EnableSorting", sorting ? 1L : 0L);
    wxConfig::Get()->Flush();
}

void W3DViewFrame::OnUpdatePolygonSorting(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:4219-4223 (OnUpdateToggleSorting)
    // Check the menu item if sorting is enabled
    event.Check(WW3D::Is_Sorting_Enabled());
}

void W3DViewFrame::OnAnimationPlay(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:1292-1309 (OnAniStart)
    //
    // MFC Implementation:
    //   CGraphicView *pCGraphicView = (CGraphicView *)m_wndSplitter.GetPane (0, 1);
    //   pCGraphicView->SetAnimationState (CGraphicView::AnimPlaying);
    //   m_animationToolbar.SetButtonState (IDM_ANI_PAUSE, CFancyToolbar::StateUp);
    //   m_animationToolbar.SetButtonState (IDM_ANI_START, CFancyToolbar::StateDn);
    //
    // Behavior: Starts animation playback
    //           Sets state to AnimPlaying
    //           Updates toolbar: Play button down, Pause button up
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    // Start the animation
    graphicView->SetAnimationState(CGraphicView::AnimPlaying);
    
    // TODO(MFC-Match): Update toolbar buttons when Animation toolbar is implemented
    //   MFC updates m_animationToolbar button states (Play down, Pause up)
    //   See MainFrm.cpp:1302-1305
    //   Defer until toolbar infrastructure exists
}

void W3DViewFrame::OnAnimationPause(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:1318-1348 (OnAniPause)
    //
    // MFC Implementation:
    //   CGraphicView *pCGraphicView = (CGraphicView *)m_wndSplitter.GetPane (0, 1);
    //   if (pCGraphicView->GetAnimationState () == CGraphicView::AnimPlaying)
    //   {
    //       pCGraphicView->SetAnimationState (CGraphicView::AnimPaused);
    //       m_animationToolbar.SetButtonState (IDM_ANI_PAUSE, CFancyToolbar::StateDn);
    //   }
    //   else if (pCGraphicView->GetAnimationState () == CGraphicView::AnimPaused)
    //   {
    //       pCGraphicView->SetAnimationState (CGraphicView::AnimPlaying);
    //       m_animationToolbar.SetButtonState (IDM_ANI_PAUSE, CFancyToolbar::StateUp);
    //   }
    //   else // Stopped state
    //   {
    //       m_animationToolbar.SetButtonState (IDM_ANI_PAUSE, CFancyToolbar::StateUp);
    //   }
    //
    // Behavior: Toggle between Playing and Paused states
    //           If Playing → Pauses (button down)
    //           If Paused → Resumes playing (button up)
    //           If Stopped → Does nothing (button pops up)
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    // Toggle between Playing and Paused
    if (graphicView->GetAnimationState() == CGraphicView::AnimPlaying)
    {
        // Pause the animation
        graphicView->SetAnimationState(CGraphicView::AnimPaused);
        // TODO(MFC-Match): SetButtonState(IDM_ANI_PAUSE, StateDn)
    }
    else if (graphicView->GetAnimationState() == CGraphicView::AnimPaused)
    {
        // Resume playing
        graphicView->SetAnimationState(CGraphicView::AnimPlaying);
        // TODO(MFC-Match): SetButtonState(IDM_ANI_PAUSE, StateUp)
    }
    // If stopped, do nothing (toolbar button pops up in MFC)
}

void W3DViewFrame::OnAnimationStop(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:1268-1283 (OnAniStop)
    //
    // MFC Implementation:
    //   CGraphicView *pCGraphicView = (CGraphicView *)m_wndSplitter.GetPane (0, 1);
    //   pCGraphicView->SetAnimationState (CGraphicView::AnimStopped);
    //   m_animationToolbar.SetButtonState (IDM_ANI_START, CFancyToolbar::StateUp);
    //   m_animationToolbar.SetButtonState (IDM_ANI_PAUSE, CFancyToolbar::StateUp);
    //
    // Behavior: Stops animation playback
    //           Sets state to AnimStopped
    //           Updates toolbar: Both Play and Pause buttons pop up
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    // Stop the animation
    graphicView->SetAnimationState(CGraphicView::AnimStopped);
    
    // TODO(MFC-Match): Update toolbar buttons when Animation toolbar is implemented
    //   MFC pops both Play and Pause buttons
    //   See MainFrm.cpp:1278-1279
    //   Defer until toolbar infrastructure exists
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

// Camera menu handlers

void W3DViewFrame::OnCameraFront(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:1397-1408 (OnCameraFront)
    // Positions camera to front view (looking at object from front)
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    // Position the camera to front view
    graphicView->SetCameraPos(CGraphicView::CameraFront);
}

void W3DViewFrame::OnCameraBack(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:1357-1368 (OnCameraBack)
    // Positions camera to back view (looking at object from behind)
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    // Position the camera to back view
    graphicView->SetCameraPos(CGraphicView::CameraBack);
}

void W3DViewFrame::OnCameraLeft(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:1417-1428 (OnCameraLeft)
    // Positions camera to left view (looking at object from left side)
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    // Position the camera to left view
    graphicView->SetCameraPos(CGraphicView::CameraLeft);
}

void W3DViewFrame::OnCameraRight(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:1467-1478 (OnCameraRight)
    // Positions camera to right view (looking at object from right side)
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    // Position the camera to right view
    graphicView->SetCameraPos(CGraphicView::CameraRight);
}

void W3DViewFrame::OnCameraTop(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:1487-1498 (OnCameraTop)
    // Positions camera to top view (looking down at object from above)
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    // Position the camera to top view
    graphicView->SetCameraPos(CGraphicView::CameraTop);
}

void W3DViewFrame::OnCameraBottom(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:1377-1388 (OnCameraBottom)
    // Positions camera to bottom view (looking up at object from below)
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    // Position the camera to bottom view
    graphicView->SetCameraPos(CGraphicView::CameraBottom);
}

void W3DViewFrame::OnCameraReset(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:1437-1458 (OnCameraReset)
    //
    // MFC Implementation:
    //   CGraphicView *pCGraphicView = (CGraphicView *)m_wndSplitter.GetPane (0, 1);
    //   CW3DViewDoc *pCDoc = (CW3DViewDoc *)GetActiveDocument ();
    //   if (pCDoc && pCDoc->GetDisplayedObject ())
    //   {
    //       RenderObjClass *prender_obj = pCDoc->GetDisplayedObject ();
    //       if (prender_obj->Class_ID () == RenderObjClass::CLASSID_PARTICLEEMITTER) {
    //           pCGraphicView->Reset_Camera_To_Display_Emitter (*((ParticleEmitterClass *)prender_obj));
    //       } else {
    //           pCGraphicView->Reset_Camera_To_Display_Object (*prender_obj);
    //       }
    //   }
    //
    // Behavior: Resets camera to optimal position for viewing the displayed object
    //           Different reset method for particle emitters vs regular objects
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    // Get the displayed object
    RenderObjClass* renderObj = doc->GetDisplayedObject();
    if (!renderObj) return;
    
    // Reset camera based on object type
    if (renderObj->Class_ID() == RenderObjClass::CLASSID_PARTICLEEMITTER) {
        // Particle emitters need special camera positioning
        // Note: Using reinterpret_cast because ParticleEmitterClass is forward declared
        graphicView->Reset_Camera_To_Display_Emitter(*reinterpret_cast<ParticleEmitterClass*>(renderObj));
    } else {
        // Regular render objects use standard camera reset
        graphicView->Reset_Camera_To_Display_Object(*renderObj);
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

void W3DViewFrame::OnLightRotateYBack(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:2663-2676 (OnLightRotateYBack)
    //
    // MFC Implementation:
    //   CGraphicView *pgraphic_view = (CGraphicView *)m_wndSplitter.GetPane (0, 1);
    //   int rotation = (pgraphic_view->Get_Light_Rotation () ^ (CGraphicView::RotateYBack));
    //   rotation &= ~CGraphicView::RotateY;
    //   pgraphic_view->Rotate_Light ((CGraphicView::OBJECT_ROTATION)rotation);
    //
    // Behavior: Toggles reverse Y-axis rotation for scene light
    //           XOR flips the RotateYBack bit, clearing RotateY ensures reverse only
    //
    // Note: No menu item in MFC, accelerator only
    // Shortcut: Ctrl+Down Arrow
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    // Toggle Y back rotation bit, clear forward Y rotation bit
    int rotation = (graphicView->Get_Light_Rotation() ^ CGraphicView::RotateYBack);
    rotation &= ~CGraphicView::RotateY;
    
    graphicView->Rotate_Light(static_cast<CGraphicView::OBJECT_ROTATION>(rotation));
}

void W3DViewFrame::OnLightRotateZBack(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:2707-2720 (OnLightRotateZBack)
    //
    // MFC Implementation:
    //   CGraphicView *pgraphic_view = (CGraphicView *)m_wndSplitter.GetPane (0, 1);
    //   int rotation = (pgraphic_view->Get_Light_Rotation () ^ (CGraphicView::RotateZBack));
    //   rotation &= ~CGraphicView::RotateZ;
    //   pgraphic_view->Rotate_Light ((CGraphicView::OBJECT_ROTATION)rotation);
    //
    // Behavior: Toggles reverse Z-axis rotation for scene light
    //           XOR flips the RotateZBack bit, clearing RotateZ ensures reverse only
    //
    // Note: MFC comment incorrectly says "around Y" but code correctly rotates around Z
    // Note: No menu item in MFC, accelerator only
    // Shortcut: Ctrl+Left Arrow
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    // Toggle Z back rotation bit, clear forward Z rotation bit
    int rotation = (graphicView->Get_Light_Rotation() ^ CGraphicView::RotateZBack);
    rotation &= ~CGraphicView::RotateZ;
    
    graphicView->Rotate_Light(static_cast<CGraphicView::OBJECT_ROTATION>(rotation));
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
    // MFC Reference: MainFrm.cpp:3738-3751 (OnPrelitVertex)
    // Sets prelit lighting mode to vertex lighting
    if (WW3D::Get_Prelit_Mode() != WW3D::PRELIT_MODE_VERTEX) {
        WW3D::Set_Prelit_Mode(WW3D::PRELIT_MODE_VERTEX);
        
        // Get tree control and document for reload operations
        // Note: Reload methods are stubs - see TODO comments in those methods
        if (m_splitter) {
            wxWindow *leftPane = m_splitter->GetWindow1();
            W3DViewTreeCtrl *tree = wxDynamicCast(leftPane, W3DViewTreeCtrl);
            if (tree) {
                tree->Reload_Lightmap_Models();  // Stub - see w3dviewtree_wx.cpp
            }
        }
        
        W3DViewDoc *doc = wxStaticCast(m_docManager->GetCurrentDocument(), W3DViewDoc);
        if (doc) {
            doc->Reload_Displayed_Object();  // Stub - see w3dviewdoc_wx.cpp
        }
    }
}

void W3DViewFrame::OnUpdatePrelitVertex(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:3747-3751 (OnUpdatePrelitVertex)
    // Sets checkbox state based on current prelit mode
    event.Check(WW3D::Get_Prelit_Mode() == WW3D::PRELIT_MODE_VERTEX);
}

void W3DViewFrame::OnPrelitMultipass(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:3698-3734 (OnPrelitMultipass)
    // Sets prelit lighting mode to multi-pass lightmapping
    if (WW3D::Get_Prelit_Mode() != WW3D::PRELIT_MODE_LIGHTMAP_MULTI_PASS) {
        WW3D::Set_Prelit_Mode(WW3D::PRELIT_MODE_LIGHTMAP_MULTI_PASS);
        
        // Get tree control and document for reload operations
        // Note: Reload methods are stubs - see TODO comments in those methods
        if (m_splitter) {
            wxWindow *leftPane = m_splitter->GetWindow1();
            W3DViewTreeCtrl *tree = wxDynamicCast(leftPane, W3DViewTreeCtrl);
            if (tree) {
                tree->Reload_Lightmap_Models();  // Stub - see w3dviewtree_wx.cpp
            }
        }
        
        W3DViewDoc *doc = wxStaticCast(m_docManager->GetCurrentDocument(), W3DViewDoc);
        if (doc) {
            doc->Reload_Displayed_Object();  // Stub - see w3dviewdoc_wx.cpp
        }
    }
}

void W3DViewFrame::OnUpdatePrelitMultipass(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:3730-3734 (OnUpdatePrelitMultipass)
    // Sets checkbox state based on current prelit mode
    event.Check(WW3D::Get_Prelit_Mode() == WW3D::PRELIT_MODE_LIGHTMAP_MULTI_PASS);
}

void W3DViewFrame::OnPrelitMultitex(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:3755-3787 (OnPrelitMultitex)
    // Sets prelit lighting mode to multi-texture lightmapping
    if (WW3D::Get_Prelit_Mode() != WW3D::PRELIT_MODE_LIGHTMAP_MULTI_TEXTURE) {
        WW3D::Set_Prelit_Mode(WW3D::PRELIT_MODE_LIGHTMAP_MULTI_TEXTURE);
        
        // Get tree control and document for reload operations
        // Note: Reload methods are stubs - see TODO comments in those methods
        if (m_splitter) {
            wxWindow *leftPane = m_splitter->GetWindow1();
            W3DViewTreeCtrl *tree = wxDynamicCast(leftPane, W3DViewTreeCtrl);
            if (tree) {
                tree->Reload_Lightmap_Models();  // Stub - see w3dviewtree_wx.cpp
            }
        }
        
        W3DViewDoc *doc = wxStaticCast(m_docManager->GetCurrentDocument(), W3DViewDoc);
        if (doc) {
            doc->Reload_Displayed_Object();  // Stub - see w3dviewdoc_wx.cpp
        }
    }
}

void W3DViewFrame::OnUpdatePrelitMultitex(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:3783-3787 (OnUpdatePrelitMultitex)
    // Sets checkbox state based on current prelit mode
    event.Check(WW3D::Get_Prelit_Mode() == WW3D::PRELIT_MODE_LIGHTMAP_MULTI_TEXTURE);
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
