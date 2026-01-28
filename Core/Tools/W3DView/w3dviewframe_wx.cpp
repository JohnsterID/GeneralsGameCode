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
#include "dialogs/CameraDistance_wx.h"
#include "dialogs/BackgroundColor_wx.h"
#include "dialogs/BackgroundBmp_wx.h"
#include "dialogs/BackgroundObject_wx.h"
#include "dialogs/TexturePaths_wx.h"
#include "dialogs/RenderDeviceSelector_wx.h"
#include "dialogs/LightAmbientDialog_wx.h"
#include "dialogs/LightSceneDialog_wx.h"
#include "dialogs/Resolution_wx.h"
#include "dialogs/GammaDialog_wx.h"
#include "dialogs/AnimatedSoundDialog_wx.h"
#include "dialogs/Displayspeed_wx.h"
#include "dialogs/SaveSettings_wx.h"
#include "dialogs/PropPageAdvanimMixing_wx.h"
#include "dialogs/PropPageAdvanimReport_wx.h"
#include "dialogs/PropPageAnimation_wx.h"
#include "dialogs/PropPageEmitterGen_wx.h"
#include "dialogs/PropPageSphereGen_wx.h"
#include "dialogs/PropPageRingGen_wx.h"
#include "dialogs/SoundEdit_wx.h"
#include "light.h"

#include <wx/menu.h>
#include <wx/toolbar.h>
#include <wx/filedlg.h>
#include <wx/msgdlg.h>
#include <wx/config.h>
#include <wx/clipbrd.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/filehistory.h>

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
    // File menu
    ID_MUNGE_SORT_ON_LOAD = wxID_HIGHEST + 1,
    ID_ENABLE_GAMMA_CORRECTION_FILE,  // File menu version (different from View menu)
    ID_SAVE_SETTINGS,
    ID_LOAD_SETTINGS,
    ID_IMPORT_FACIAL_ANIMS,
    ID_TEXTURE_PATH_FILE,  // Will replace ID_TEXTURE_PATH from Settings menu
    ID_ANIMATED_SOUND_OPTIONS,
    // File menu - Export submenu
    ID_EXPORT_AGGREGATE,
    ID_EXPORT_EMITTER,
    ID_EXPORT_LOD,
    ID_EXPORT_PRIMITIVE,
    ID_EXPORT_SOUND_OBJECT,
    // Object menu
    ID_OBJECT_PROPERTIES,
    ID_LOD_GENERATE,
    ID_OBJECT_RESET,
    ID_OBJECT_ROTATE_X,
    ID_OBJECT_ROTATE_Y,
    ID_OBJECT_ROTATE_Z,
    ID_OBJECT_ROTATE_Y_BACK,
    ID_OBJECT_ROTATE_Z_BACK,
    ID_OBJECT_RESTRICT_ANIMS,
    ID_OBJECT_ALTERNATE_MATERIALS,
    // Emitters menu
    ID_CREATE_EMITTER,
    ID_SCALE_EMITTER,
    ID_EDIT_EMITTER,
    // Primitives menu
    ID_CREATE_SPHERE,
    ID_CREATE_RING,
    ID_EDIT_PRIMITIVE,
    // Sound menu
    ID_CREATE_SOUND_OBJECT,
    ID_EDIT_SOUND_OBJECT,
    // Movie menu
    ID_MAKE_MOVIE,
    ID_SAVE_SCREENSHOT,
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
    // View menu - Toolbars and UI
    ID_VIEW_TOOLBAR,
    ID_VIEW_OBJECT_BAR,
    ID_VIEW_ANIMATION_BAR,
    ID_VIEW_STATUS_BAR,
    // View menu - Slideshow
    ID_SLIDESHOW_PREV,
    ID_SLIDESHOW_NEXT,
    // View menu - Display
    ID_VIEW_FULLSCREEN,
    ID_CHANGE_DEVICE,
    ID_CHANGE_RESOLUTION,
    ID_ANIMATION_PLAY,
    ID_ANIMATION_PAUSE,
    ID_ANIMATION_STOP,
    ID_ANIMATION_STEP_BACK,
    ID_ANIMATION_STEP_FORWARD,
    ID_ANIMATION_SETTINGS,
    ID_ANIMATION_ADVANCED,
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
    ID_CAMERA_ALLOW_ROTATE_X,
    ID_CAMERA_ALLOW_ROTATE_Y,
    ID_CAMERA_ALLOW_ROTATE_Z,
    ID_COPY_SCREEN_SIZE,
    ID_CAMERA_ANIMATE,
    ID_CAMERA_BONE_POS_X,
    ID_SET_CAMERA_DISTANCE,
    ID_CAMERA_RESET_ON_LOAD,
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
    // File menu
    EVT_MENU(ID_MUNGE_SORT_ON_LOAD, W3DViewFrame::OnMungeSortOnLoad)
    EVT_UPDATE_UI(ID_MUNGE_SORT_ON_LOAD, W3DViewFrame::OnUpdateMungeSortOnLoad)
    EVT_MENU(ID_ENABLE_GAMMA_CORRECTION_FILE, W3DViewFrame::OnEnableGammaCorrectionFile)
    EVT_UPDATE_UI(ID_ENABLE_GAMMA_CORRECTION_FILE, W3DViewFrame::OnUpdateEnableGammaCorrectionFile)
    EVT_MENU(ID_SAVE_SETTINGS, W3DViewFrame::OnSaveSettings)
    EVT_MENU(ID_LOAD_SETTINGS, W3DViewFrame::OnLoadSettings)
    EVT_MENU(ID_IMPORT_FACIAL_ANIMS, W3DViewFrame::OnImportFacialAnims)
    EVT_MENU(ID_TEXTURE_PATH_FILE, W3DViewFrame::OnTexturePathFile)
    EVT_MENU(ID_ANIMATED_SOUND_OPTIONS, W3DViewFrame::OnAnimatedSoundOptions)
    // File menu - Export submenu
    EVT_MENU(ID_EXPORT_AGGREGATE, W3DViewFrame::OnExportAggregate)
    EVT_MENU(ID_EXPORT_EMITTER, W3DViewFrame::OnExportEmitter)
    EVT_MENU(ID_EXPORT_LOD, W3DViewFrame::OnExportLOD)
    EVT_MENU(ID_EXPORT_PRIMITIVE, W3DViewFrame::OnExportPrimitive)
    EVT_MENU(ID_EXPORT_SOUND_OBJECT, W3DViewFrame::OnExportSoundObject)
    // Object menu
    EVT_MENU(ID_OBJECT_PROPERTIES, W3DViewFrame::OnObjectProperties)
    EVT_MENU(ID_LOD_GENERATE, W3DViewFrame::OnLodGenerate)
    EVT_MENU(ID_OBJECT_RESET, W3DViewFrame::OnObjectReset)
    EVT_MENU(ID_OBJECT_ROTATE_X, W3DViewFrame::OnObjectRotateX)
    EVT_MENU(ID_OBJECT_ROTATE_Y, W3DViewFrame::OnObjectRotateY)
    EVT_MENU(ID_OBJECT_ROTATE_Z, W3DViewFrame::OnObjectRotateZ)
    EVT_MENU(ID_OBJECT_ROTATE_Y_BACK, W3DViewFrame::OnObjectRotateYBack)
    EVT_MENU(ID_OBJECT_ROTATE_Z_BACK, W3DViewFrame::OnObjectRotateZBack)
    EVT_MENU(ID_OBJECT_RESTRICT_ANIMS, W3DViewFrame::OnObjectRestrictAnims)
    EVT_UPDATE_UI(ID_OBJECT_RESTRICT_ANIMS, W3DViewFrame::OnUpdateObjectRestrictAnims)
    EVT_MENU(ID_OBJECT_ALTERNATE_MATERIALS, W3DViewFrame::OnObjectAlternateMaterials)
    // Emitters menu
    EVT_MENU(ID_CREATE_EMITTER, W3DViewFrame::OnCreateEmitter)
    EVT_MENU(ID_SCALE_EMITTER, W3DViewFrame::OnScaleEmitter)
    EVT_MENU(ID_EDIT_EMITTER, W3DViewFrame::OnEditEmitter)
    // Primitives menu
    EVT_MENU(ID_CREATE_SPHERE, W3DViewFrame::OnCreateSphere)
    EVT_MENU(ID_CREATE_RING, W3DViewFrame::OnCreateRing)
    EVT_MENU(ID_EDIT_PRIMITIVE, W3DViewFrame::OnEditPrimitive)
    // Sound menu
    EVT_MENU(ID_CREATE_SOUND_OBJECT, W3DViewFrame::OnCreateSoundObject)
    EVT_MENU(ID_EDIT_SOUND_OBJECT, W3DViewFrame::OnEditSoundObject)
    // Movie menu
    EVT_MENU(ID_MAKE_MOVIE, W3DViewFrame::OnMakeMovie)
    EVT_MENU(ID_SAVE_SCREENSHOT, W3DViewFrame::OnSaveScreenshot)
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
    // View menu - Toolbars
    EVT_MENU(ID_VIEW_TOOLBAR, W3DViewFrame::OnViewToolbar)
    EVT_UPDATE_UI(ID_VIEW_TOOLBAR, W3DViewFrame::OnUpdateViewToolbar)
    EVT_MENU(ID_VIEW_OBJECT_BAR, W3DViewFrame::OnViewObjectBar)
    EVT_UPDATE_UI(ID_VIEW_OBJECT_BAR, W3DViewFrame::OnUpdateViewObjectBar)
    EVT_MENU(ID_VIEW_ANIMATION_BAR, W3DViewFrame::OnViewAnimationBar)
    EVT_UPDATE_UI(ID_VIEW_ANIMATION_BAR, W3DViewFrame::OnUpdateViewAnimationBar)
    // View menu - Status Bar
    EVT_MENU(ID_VIEW_STATUS_BAR, W3DViewFrame::OnViewStatusBar)
    EVT_UPDATE_UI(ID_VIEW_STATUS_BAR, W3DViewFrame::OnUpdateViewStatusBar)
    // View menu - Slideshow
    EVT_MENU(ID_SLIDESHOW_PREV, W3DViewFrame::OnSlideshowPrev)
    EVT_MENU(ID_SLIDESHOW_NEXT, W3DViewFrame::OnSlideshowNext)
    // View menu - Display
    EVT_MENU(ID_VIEW_FULLSCREEN, W3DViewFrame::OnViewFullscreen)
    EVT_UPDATE_UI(ID_VIEW_FULLSCREEN, W3DViewFrame::OnUpdateViewFullscreen)
    EVT_MENU(ID_CHANGE_DEVICE, W3DViewFrame::OnChangeDevice)
    EVT_MENU(ID_CHANGE_RESOLUTION, W3DViewFrame::OnChangeResolution)
    EVT_MENU(ID_ANIMATION_PLAY, W3DViewFrame::OnAnimationPlay)
    EVT_MENU(ID_ANIMATION_PAUSE, W3DViewFrame::OnAnimationPause)
    EVT_MENU(ID_ANIMATION_STOP, W3DViewFrame::OnAnimationStop)
    EVT_MENU(ID_ANIMATION_STEP_BACK, W3DViewFrame::OnAnimationStepBack)
    EVT_MENU(ID_ANIMATION_STEP_FORWARD, W3DViewFrame::OnAnimationStepForward)
    EVT_MENU(ID_ANIMATION_SETTINGS, W3DViewFrame::OnAnimationSettings)
    EVT_MENU(ID_ANIMATION_ADVANCED, W3DViewFrame::OnAnimationAdvanced)
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
    EVT_MENU(ID_CAMERA_ALLOW_ROTATE_X, W3DViewFrame::OnCameraAllowRotateX)
    EVT_UPDATE_UI(ID_CAMERA_ALLOW_ROTATE_X, W3DViewFrame::OnUpdateCameraAllowRotateX)
    EVT_MENU(ID_CAMERA_ALLOW_ROTATE_Y, W3DViewFrame::OnCameraAllowRotateY)
    EVT_UPDATE_UI(ID_CAMERA_ALLOW_ROTATE_Y, W3DViewFrame::OnUpdateCameraAllowRotateY)
    EVT_MENU(ID_CAMERA_ALLOW_ROTATE_Z, W3DViewFrame::OnCameraAllowRotateZ)
    EVT_UPDATE_UI(ID_CAMERA_ALLOW_ROTATE_Z, W3DViewFrame::OnUpdateCameraAllowRotateZ)
    EVT_MENU(ID_COPY_SCREEN_SIZE, W3DViewFrame::OnCopyScreenSize)
    EVT_MENU(ID_CAMERA_ANIMATE, W3DViewFrame::OnCameraAnimate)
    EVT_UPDATE_UI(ID_CAMERA_ANIMATE, W3DViewFrame::OnUpdateCameraAnimate)
    EVT_MENU(ID_CAMERA_BONE_POS_X, W3DViewFrame::OnCameraBonePosX)
    EVT_UPDATE_UI(ID_CAMERA_BONE_POS_X, W3DViewFrame::OnUpdateCameraBonePosX)
    EVT_MENU(ID_SET_CAMERA_DISTANCE, W3DViewFrame::OnSetCameraDistance)
    EVT_MENU(ID_CAMERA_RESET_ON_LOAD, W3DViewFrame::OnCameraResetOnLoad)
    EVT_UPDATE_UI(ID_CAMERA_RESET_ON_LOAD, W3DViewFrame::OnUpdateCameraResetOnLoad)
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
    // Recent Files (MRU)
    EVT_MENU_RANGE(wxID_FILE1, wxID_FILE9, W3DViewFrame::OnMRUFile)
wxEND_EVENT_TABLE()

W3DViewFrame::W3DViewFrame(wxDocManager *manager)
    : wxDocParentFrame(manager, nullptr, wxID_ANY, "W3D Viewer",
                       wxDefaultPosition, wxSize(960, 720))
    , m_docManager(manager)
    , m_splitter(nullptr)
    , m_statusBar(nullptr)
    , m_fileHistory(nullptr)
{
    // Create file history (MRU - Most Recently Used files)
    // MFC Reference: W3DView.rc:205 - "Recent File" menu item
    m_fileHistory = new wxFileHistory(9);  // MFC default is 4-9 files
    m_fileHistory->Load(*wxConfig::Get());
    
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

    // Restore application settings from wxConfig
    InitializeApplicationSettings();

    Centre();
}

W3DViewFrame::~W3DViewFrame()
{
    // Save file history to config and cleanup
    // MFC Reference: Automatic cleanup in CWinApp
    if (m_fileHistory) {
        m_fileHistory->Save(*wxConfig::Get());
        delete m_fileHistory;
        m_fileHistory = nullptr;
    }
}

void W3DViewFrame::InitializeApplicationSettings()
{
    // MFC Reference: MainFrm.cpp constructor and InitInstance
    // Restores application settings from registry/wxConfig on startup
    // Ensures user preferences persist across application sessions
    
    wxConfigBase *config = wxConfig::Get();
    
    // 1. Restore Munge Sort on Load setting
    //    MFC: Registry key "Config\MungeSortOnLoad" (default: 0/false)
    //    MFC Ref: App initialization in W3DViewApp.cpp
    long mungeSortEnabled = config->Read("/Config/MungeSortOnLoad", 0L);
    WW3D::Enable_Munge_Sort_On_Load(mungeSortEnabled != 0);
    
    // 2. Restore Gamma Correction setting
    //    MFC: Registry key "Config\EnableGamma" (default: 0/false)
    //    If enabled, also reads "Config\Gamma" (integer * 10, default: 10 = 1.0)
    long enableGamma = config->Read("/Config/EnableGamma", 0L);
    if (enableGamma != 0) {
        // Read gamma value (stored as integer * 10, range 10-30 = 1.0-3.0)
        long gammaInt = config->Read("/Config/Gamma", 10L);
        float gamma = gammaInt / 10.0f;
        
        // Clamp to valid range
        if (gamma < 1.0f) gamma = 1.0f;
        if (gamma > 3.0f) gamma = 3.0f;
        
        // Apply gamma correction
        WW3D::Set_Gamma(gamma, 0.0f, 1.0f);
    } else {
        // Gamma disabled: reset to linear (1.0)
        WW3D::Set_Gamma(1.0f, 0.0f, 1.0f);
    }
    
    // 3. Restore Polygon Sorting setting
    //    MFC: Registry key "Config\EnableSorting" (default: 1/true)
    //    MFC Ref: MainFrm.cpp OnCreate - GetProfileInt("Config", "EnableSorting", 1)
    long enableSorting = config->Read("/Config/EnableSorting", 1L);  // Default: enabled
    WW3D::Enable_Sorting(enableSorting != 0);
    
    // 4. Restore N-Patches Subdivision Level
    //    MFC: Registry key "Config\NPatchesSubdivision" (default: 4)
    //    Range: 1-8 subdivision levels
    //    MFC Ref: MainFrm.cpp OnCreate - GetProfileInt("Config", "NPatchesSubdivision", 4)
    long subdivisionLevel = config->Read("/Config/NPatchesSubdivision", 4L);
    if (subdivisionLevel < 1) subdivisionLevel = 1;
    if (subdivisionLevel > 8) subdivisionLevel = 8;
    WW3D::Set_NPatches_Level(static_cast<unsigned int>(subdivisionLevel));
    
    // 5. Restore N-Patches Gap Filling setting
    //    MFC: Registry key "Config\NPatchesGapFilling" (default: 0/false)
    //    MFC Ref: MainFrm.cpp OnCreate - GetProfileInt("Config", "NPatchesGapFilling", 0)
    long gapFilling = config->Read("/Config/NPatchesGapFilling", 0L);  // Default: disabled
    WW3D::Set_NPatches_Gap_Filling_Mode(gapFilling != 0 ? 
        WW3D::NPATCHES_GAP_FILLING_ENABLED : WW3D::NPATCHES_GAP_FILLING_DISABLED);
    
    // Note: Status bar visibility is restored in InitStatusBar()
    // Note: Camera reset on load is applied when files are loaded (see OnFileOpen)
    // Note: Wireframe mode is per-document (not global), no persistence needed
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

    // File menu - EXACT MFC matching (W3DView.rc:181-208)
    wxMenu *fileMenu = new wxMenu;
    fileMenu->Append(wxID_NEW, "&New\tCtrl+N");
    fileMenu->Append(wxID_OPEN, "&Open...\tCtrl+O");
    fileMenu->AppendCheckItem(ID_MUNGE_SORT_ON_LOAD, "&Munge Sort on Load");
    fileMenu->AppendCheckItem(ID_ENABLE_GAMMA_CORRECTION_FILE, "&Enable Gamma Correction");
    fileMenu->AppendSeparator();
    fileMenu->Append(ID_SAVE_SETTINGS, "&Save Settings...\tCtrl+S");
    fileMenu->Append(ID_LOAD_SETTINGS, "Load Settings...");
    fileMenu->AppendSeparator();
    fileMenu->Append(ID_IMPORT_FACIAL_ANIMS, "&Import Facial Anims...");
    // Export submenu (MFC: W3DView.rc:193-199)
    wxMenu *exportMenu = new wxMenu;
    exportMenu->Append(ID_EXPORT_AGGREGATE, "&Aggregate...");
    exportMenu->Append(ID_EXPORT_EMITTER, "&Emitter...");
    exportMenu->Append(ID_EXPORT_LOD, "&LOD...");
    exportMenu->Append(ID_EXPORT_PRIMITIVE, "&Primitive...");
    exportMenu->Append(ID_EXPORT_SOUND_OBJECT, "&Sound Object...");
    fileMenu->AppendSubMenu(exportMenu, "Ex&port...");
    fileMenu->AppendSeparator();
    fileMenu->Append(ID_TEXTURE_PATH_FILE, "&Texture Path...");
    fileMenu->Append(ID_ANIMATED_SOUND_OPTIONS, "&Animated Sound Options...");
    fileMenu->AppendSeparator();
    // Add Recent Files (MRU) menu
    // MFC Reference: W3DView.rc:205 - "Recent File" (ID_FILE_MRU_FILE1)
    // wxWidgets automatically manages MRU list with wxFileHistory
    if (m_fileHistory) {
        m_fileHistory->UseMenu(fileMenu);
        m_fileHistory->AddFilesToMenu();
    }
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT, "E&xit\tAlt+F4");
    menuBar->Append(fileMenu, "&File");

    // Note: Edit menu removed - doesn't exist in MFC IDR_MAINFRAME menu (W3DView.rc:178-343)
    //   MFC W3DView doesn't have standard Edit menu (Undo/Redo/Cut/Copy/Paste)
    //   If needed, edit operations are handled through context menus or specialized dialogs

    // View menu
    // MFC Reference: W3DView.rc:209-243 (EXACT MATCH)
    // Structure: Toolbars submenu → Status Bar → Prev/Next → Fullscreen/Device/Resolution → Wireframe/Sorting/Gamma → Subdivision/Patch
    wxMenu *viewMenu = new wxMenu;
    
    // Toolbars submenu
    wxMenu *toolbarsMenu = new wxMenu;
    toolbarsMenu->AppendCheckItem(ID_VIEW_TOOLBAR, "&Main");
    toolbarsMenu->AppendCheckItem(ID_VIEW_OBJECT_BAR, "Object");
    toolbarsMenu->AppendCheckItem(ID_VIEW_ANIMATION_BAR, "Animation");
    viewMenu->AppendSubMenu(toolbarsMenu, "&Toolbars");
    
    // Status Bar
    viewMenu->AppendCheckItem(ID_VIEW_STATUS_BAR, "&Status Bar");
    viewMenu->AppendSeparator();
    
    // Slideshow navigation
    viewMenu->Append(ID_SLIDESHOW_PREV, "&Prev\tPgUp");
    viewMenu->Append(ID_SLIDESHOW_NEXT, "&Next\tPgDn");
    viewMenu->AppendSeparator();
    
    // Fullscreen and device settings
    viewMenu->Append(ID_VIEW_FULLSCREEN, "&View Fullscreen");  // Note: No checkmark, was GRAYED in MFC
    viewMenu->Append(ID_CHANGE_DEVICE, "&Change Device...");  // Note: GRAYED in MFC
    viewMenu->Append(ID_CHANGE_RESOLUTION, "Change &Resolution...");  // Note: GRAYED in MFC
    viewMenu->AppendSeparator();
    
    // Rendering controls
    viewMenu->AppendCheckItem(ID_VIEW_WIREFRAME, "&Wireframe Mode");
    viewMenu->AppendCheckItem(ID_VIEW_POLYGON_SORTING, "Polygon Sorting\tCtrl+P");  // Note: No & on Polygon
    viewMenu->Append(ID_GAMMA_SETTINGS, "Set &Gamma");  // Moved from Settings menu to match MFC
    viewMenu->AppendSeparator();
    
    // N-Patches subdivision submenu
    wxMenu *subdivMenu = new wxMenu;
    subdivMenu->AppendRadioItem(ID_VIEW_SUBDIVISION_1, "1");  // Note: No "Level " prefix in MFC
    subdivMenu->AppendRadioItem(ID_VIEW_SUBDIVISION_2, "2");
    subdivMenu->AppendRadioItem(ID_VIEW_SUBDIVISION_3, "3");
    subdivMenu->AppendRadioItem(ID_VIEW_SUBDIVISION_4, "4");
    subdivMenu->AppendRadioItem(ID_VIEW_SUBDIVISION_5, "5");
    subdivMenu->AppendRadioItem(ID_VIEW_SUBDIVISION_6, "6");
    subdivMenu->AppendRadioItem(ID_VIEW_SUBDIVISION_7, "7");
    subdivMenu->AppendRadioItem(ID_VIEW_SUBDIVISION_8, "8");
    viewMenu->AppendSubMenu(subdivMenu, "N-Patches Subdivision Level");  // Exact MFC text
    
    // N-Patches gap filling
    viewMenu->AppendCheckItem(ID_VIEW_PATCH_GAP_FILL, "N-Patches Gap Filling");  // Exact MFC text
    
    menuBar->Append(viewMenu, "&View");

    // Object menu - EXACT MFC matching (W3DView.rc:244-258)
    wxMenu *objectMenu = new wxMenu;
    // Rotate items first (MFC: W3DView.rc:246-248)
    objectMenu->Append(ID_OBJECT_ROTATE_X, "Rotate &X\tCtrl+X");
    objectMenu->Append(ID_OBJECT_ROTATE_Y, "Rotate &Y\tUp");
    objectMenu->Append(ID_OBJECT_ROTATE_Z, "Rotate &Z\tRight");
    objectMenu->AppendSeparator();
    // Properties (MFC: W3DView.rc:250)
    objectMenu->Append(ID_OBJECT_PROPERTIES, "&Properties...\tEnter");
    objectMenu->AppendSeparator();
    // Restrict Anims (MFC: W3DView.rc:252)
    objectMenu->AppendCheckItem(ID_OBJECT_RESTRICT_ANIMS, "&Restrict Anims");
    objectMenu->AppendSeparator();
    // Reset (MFC: W3DView.rc:254)
    objectMenu->Append(ID_OBJECT_RESET, "&Reset");
    objectMenu->AppendSeparator();
    // Toggle Alternate Materials (MFC: W3DView.rc:256)
    objectMenu->Append(ID_OBJECT_ALTERNATE_MATERIALS, "Toggle Alternate &Materials");
    // TODO(MFC-Match): Generate LOD removed from Object menu (doesn't exist in MFC)
    //   Generate LOD belongs in separate LOD menu (IDR_LOD_MENU in resource.h)
    //   LOD menu appears contextually when LOD objects are selected
    //   Need to implement context-sensitive menu switching
    menuBar->Append(objectMenu, "&Object");

    // Emitters menu - EXACT MFC matching (W3DView.rc:259-268)
    wxMenu *emittersMenu = new wxMenu;
    emittersMenu->Append(ID_CREATE_EMITTER, "&Create Emitter...");
    emittersMenu->Append(ID_SCALE_EMITTER, "&Scale Emitter...");
    emittersMenu->AppendSeparator();
    emittersMenu->Append(ID_EDIT_EMITTER, "&Edit Emitter\tEnter");
    // Note: MFC has "Edit" submenu with just a separator (W3DView.rc:266-267)
    //   This appears to be unused/placeholder - not implementing empty submenu
    menuBar->Append(emittersMenu, "&Emitters");

    // Primitives menu - EXACT MFC matching (W3DView.rc:269-275)
    wxMenu *primitivesMenu = new wxMenu;
    primitivesMenu->Append(ID_CREATE_SPHERE, "Create &Sphere...");
    primitivesMenu->Append(ID_CREATE_RING, "Create &Ring...");
    primitivesMenu->AppendSeparator();
    primitivesMenu->Append(ID_EDIT_PRIMITIVE, "&Edit Primitive...\tEnter");
    menuBar->Append(primitivesMenu, "&Primitives");

    // Sound menu - EXACT MFC matching (W3DView.rc:276-281)
    wxMenu *soundMenu = new wxMenu;
    soundMenu->Append(ID_CREATE_SOUND_OBJECT, "&Create Sound Object...");
    soundMenu->AppendSeparator();
    soundMenu->Append(ID_EDIT_SOUND_OBJECT, "&Edit Sound Object...\tEnter");
    menuBar->Append(soundMenu, "&Sound");

    // Light menu - EXACT MFC matching (W3DView.rc:283-302)
    // NOTE: Lighting comes BEFORE Camera in MFC IDR_MAINFRAME menu order
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

    // Camera menu - MFC Reference: W3DView.rc:303-326
    wxMenu *cameraMenu = new wxMenu;
    cameraMenu->Append(ID_CAMERA_FRONT, "&Front\tCtrl+F");
    cameraMenu->Append(ID_CAMERA_BACK, "&Back\tCtrl+B");
    cameraMenu->Append(ID_CAMERA_LEFT, "&Left\tCtrl+L");
    cameraMenu->Append(ID_CAMERA_RIGHT, "&Right\tCtrl+R");
    cameraMenu->Append(ID_CAMERA_TOP, "&Top\tCtrl+T");
    cameraMenu->Append(ID_CAMERA_BOTTOM, "Bo&ttom\tCtrl+M");
    cameraMenu->AppendSeparator();
    cameraMenu->AppendCheckItem(ID_CAMERA_ALLOW_ROTATE_X, "Rotate &X Only");
    cameraMenu->AppendCheckItem(ID_CAMERA_ALLOW_ROTATE_Y, "Rotate &Y Only");
    cameraMenu->AppendCheckItem(ID_CAMERA_ALLOW_ROTATE_Z, "Rotate &Z Only");
    cameraMenu->Append(ID_COPY_SCREEN_SIZE, "&Copy Screen Size To Clipboard\tCtrl+C");
    // TODO(MFC-Investigate): Ctrl+C shortcut may conflict with standard copy
    //   Consider alternative shortcut if clipboard copy conflicts arise
    cameraMenu->AppendSeparator();
    cameraMenu->AppendCheckItem(ID_CAMERA_ANIMATE, "&Animate Camera\tF8");
    cameraMenu->AppendCheckItem(ID_CAMERA_BONE_POS_X, "+X Camera");
    cameraMenu->AppendSeparator();
    cameraMenu->Append(ID_CAMERA_SETTINGS, "Settin&gs...");
    cameraMenu->Append(ID_SET_CAMERA_DISTANCE, "&Set Distance...");
    cameraMenu->AppendSeparator();
    cameraMenu->AppendCheckItem(ID_CAMERA_RESET_ON_LOAD, "Reset on &Display");
    cameraMenu->Append(ID_CAMERA_RESET, "R&eset");
    menuBar->Append(cameraMenu, "&Camera");

    // Background menu - EXACT MFC matching (W3DView.rc:327-333)
    wxMenu *backgroundMenu = new wxMenu;
    backgroundMenu->Append(ID_BACKGROUND_COLOR, "&Color...");
    backgroundMenu->Append(ID_BACKGROUND_BMP, "&Bitmap...");
    backgroundMenu->Append(ID_BACKGROUND_OBJECT, "&Object...");
    backgroundMenu->AppendSeparator();
    backgroundMenu->AppendCheckItem(ID_BACKGROUND_FOG, "Fog (CTRL+ALT+F)");
    menuBar->Append(backgroundMenu, "&Background");

    // Movie menu - EXACT MFC matching (W3DView.rc:334-338)
    wxMenu *movieMenu = new wxMenu;
    movieMenu->Append(ID_MAKE_MOVIE, "&Make Movie...");
    movieMenu->Append(ID_SAVE_SCREENSHOT, "&Capture Screen Shot...\tF7");
    menuBar->Append(movieMenu, "&Movie");

    // Animation menu - EXACT MFC matching (W3DView.rc:363-373 in IDR_ANI_MENU)
    // NOTE: In MFC, Animation is in separate menu resource (IDR_ANI_MENU) that gets swapped contextually
    //   For now, keeping it in main menu bar for wxWidgets compatibility
    //   TODO(MFC-Match): Implement context-sensitive menu swapping (IDR_MAINFRAME <-> IDR_ANI_MENU)
    wxMenu *animMenu = new wxMenu;
    animMenu->Append(ID_ANIMATION_PLAY, "&Play");
    animMenu->Append(ID_ANIMATION_PAUSE, "P&ause");
    animMenu->Append(ID_ANIMATION_STOP, "&Stop");
    animMenu->AppendSeparator();
    animMenu->Append(ID_ANIMATION_STEP_BACK, "Step &Back");
    animMenu->Append(ID_ANIMATION_STEP_FORWARD, "Step &Forward");
    animMenu->AppendSeparator();
    animMenu->Append(ID_ANIMATION_SETTINGS, "Se&ttings...");
    animMenu->AppendSeparator();
    animMenu->Append(ID_ANIMATION_ADVANCED, "Ad&vanced...\tCtrl+V");
    menuBar->Append(animMenu, "&Animation");
    
    // Help menu - MFC Reference: W3DView.rc:339-342
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
    
    // Restore status bar visibility from wxConfig (default: visible)
    wxConfigBase *config = wxConfig::Get();
    bool statusBarVisible = config->Read("/View/StatusBarVisible", true);
    m_statusBar->Show(statusBarVisible);
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
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: W3DView.cpp:317-361 (CAboutDlg::OnInitDialog), AboutBox.cpp
    // 
    // Implemented (Aboutbox_wx.cpp):
    // ✅ Dialog with version display
    // ✅ OK button closes dialog
    // ✅ Version text: "W3DView Version 1.0" (default)
    // 
    // TODO(Enhancement-Future): Dynamic version reading from executable
    //   MFC uses GetFileVersionInfo/VerQueryValue to read from exe resources
    //   Options: Windows API, CMake version embedding, or hybrid approach
    //   Priority: LOW (cosmetic, defaults to 1.0 same as MFC when resource missing)
    //   See Aboutbox_wx.cpp:38-51 for detailed implementation notes
    //
    // Dialog ready for use
    Aboutbox dialog(this);
    dialog.ShowModal();
}

void W3DViewFrame::OnMRUFile(wxCommandEvent &event)
{
    // MFC Reference: Automatic MRU handling in CWinApp/CDocument framework
    // wxWidgets: Manual implementation using wxFileHistory
    // Handler for Recent Files menu selection (File → Recent Files → [filename])
    
    if (!m_fileHistory) {
        return;
    }
    
    // Get the selected file from history
    wxString filename = m_fileHistory->GetHistoryFile(event.GetId() - wxID_FILE1);
    
    if (!filename.empty()) {
        // Open the document through the document manager
        // This matches MFC's automatic MRU behavior
        if (m_docManager) {
            m_docManager->CreateDocument(filename, wxDOC_SILENT);
        }
    }
}

void W3DViewFrame::AddFileToHistory(const wxString& filename)
{
    // Add file to recent files list
    // MFC Reference: Automatic in CWinApp::AddToRecentFileList
    // wxWidgets: Manual update using wxFileHistory::AddFileToHistory
    
    if (m_fileHistory && !filename.empty()) {
        m_fileHistory->AddFileToHistory(filename);
        
        // Update menu items to show new history
        // GetMenuBar()->FindItem() would work, but wxFileHistory manages it
        m_fileHistory->Save(*wxConfig::Get());
        wxConfig::Get()->Flush();
    }
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
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:1922-1933 (OnObjectReset)
    // Function: Reset object transform to identity matrix
    //
    // Implemented:
    // ✅ Get displayed object from document
    // ✅ Set transform to identity matrix Matrix3D(true)
    // ✅ Removes all rotation, scaling, translation
    // ✅ Menu location corrected (Session 21: Object menu)
    //
    // Exact MFC Matching: ✅ Complete
    // Ready for runtime testing
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) {
        return;
    }
    
    RenderObjClass* renderObj = doc->GetDisplayedObject();
    if (renderObj) {
        renderObj->Set_Transform(Matrix3D(true));
    }
}

void W3DViewFrame::OnObjectRotateX(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:1564-1579 (OnObjectRotateX)
    // Function: Toggle continuous X-axis rotation
    //
    // Implemented:
    // ✅ Get graphic view from document
    // ✅ Toggle RotateX bit via XOR
    // ✅ Clear RotateXBack bit (ensures forward rotation)
    // ✅ Apply rotation via RotateObject
    // ✅ Menu: Object → Rotate X, Shortcut: Ctrl+X
    //
    // Exact MFC Matching: ✅ Complete
    // Ready for runtime testing
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    int rotation = (graphicView->GetObjectRotation() ^ CGraphicView::RotateX);
    rotation &= ~CGraphicView::RotateXBack;
    
    graphicView->RotateObject(static_cast<CGraphicView::OBJECT_ROTATION>(rotation));
}

void W3DViewFrame::OnObjectRotateY(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:1541-1555 (OnObjectRotateY)
    // Function: Toggle continuous Y-axis rotation
    //
    // Implemented:
    // ✅ Get graphic view from document
    // ✅ Toggle RotateY bit via XOR
    // ✅ Clear RotateYBack bit (ensures forward rotation)
    // ✅ Apply rotation via RotateObject
    // ✅ Menu: Object → Rotate Y, Shortcut: Up Arrow
    //
    // Exact MFC Matching: ✅ Complete
    // Ready for runtime testing
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    int rotation = (graphicView->GetObjectRotation() ^ CGraphicView::RotateY);
    rotation &= ~CGraphicView::RotateYBack;
    
    graphicView->RotateObject(static_cast<CGraphicView::OBJECT_ROTATION>(rotation));
}

void W3DViewFrame::OnObjectRotateZ(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅ (core complete, toolbar deferred)
    // MFC Reference: MainFrm.cpp:1507-1532 (OnObjectRotateZ)
    // Function: Toggle continuous Z-axis rotation
    //
    // Implemented:
    // ✅ Get graphic view from document
    // ✅ Toggle RotateZ bit via XOR
    // ✅ Clear RotateZBack bit (ensures forward rotation)
    // ✅ Apply rotation via RotateObject
    // ✅ Menu: Object → Rotate Z, Shortcut: Right Arrow
    // ⏸️ Toolbar button updates (deferred - infrastructure pending)
    //
    // MFC Matching: ✅ Core functionality complete
    // Note: Toolbar button state updates will be added when
    //       object toolbar infrastructure is implemented
    // Ready for runtime testing (rotation works correctly)
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    int rotation = (graphicView->GetObjectRotation() ^ CGraphicView::RotateZ);
    rotation &= ~CGraphicView::RotateZBack;
    
    graphicView->RotateObject(static_cast<CGraphicView::OBJECT_ROTATION>(rotation));
    
    // TODO(MFC-Infrastructure): Update toolbar button state when toolbar is implemented
}

void W3DViewFrame::OnObjectRotateYBack(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:2597-2613 (OnObjectRotateYBack)
    // Function: Toggle reverse Y-axis rotation
    //
    // Implemented:
    // ✅ Get graphic view from document
    // ✅ Toggle RotateYBack bit via XOR
    // ✅ Clear RotateY bit (ensures backward rotation)
    // ✅ Apply rotation via RotateObject
    // ✅ Shortcut: Down Arrow (no menu item in MFC)
    //
    // Exact MFC Matching: ✅ Complete
    // Ready for runtime testing
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    int rotation = (graphicView->GetObjectRotation() ^ CGraphicView::RotateYBack);
    rotation &= ~CGraphicView::RotateY;
    
    graphicView->RotateObject(static_cast<CGraphicView::OBJECT_ROTATION>(rotation));
}

void W3DViewFrame::OnObjectRotateZBack(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:2619-2635 (OnObjectRotateZBack)
    // Function: Toggle reverse Z-axis rotation
    //
    // Implemented:
    // ✅ Get graphic view from document
    // ✅ Toggle RotateZBack bit via XOR
    // ✅ Clear RotateZ bit (ensures backward rotation)
    // ✅ Apply rotation via RotateObject
    // ✅ Shortcut: Left Arrow (no menu item in MFC)
    //
    // Exact MFC Matching: ✅ Complete
    // Ready for runtime testing
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
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
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:4255-4265 (OnViewPatchGapFill)
    // Function: Toggle N-Patches gap-filling mode
    //
    // Implemented:
    // ✅ Check current gap-filling mode
    // ✅ Toggle between ENABLED and DISABLED
    // ✅ Persist to wxConfig ("/Config/NPatchesGapFilling")
    // ✅ UI update handler (OnUpdateViewPatchGapFill) implemented
    //
    // Exact MFC Matching: ✅ Complete
    // Ready for runtime testing
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
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:4277-4284 (OnViewSubdivision1)
    // Function: Set N-Patches subdivision level to 1
    // ✅ Exact MFC match - Ready for runtime testing
    WW3D::Set_NPatches_Level(1);
    wxConfig::Get()->Write("/Config/NPatchesSubdivision", 1L);
    wxConfig::Get()->Flush();
}

void W3DViewFrame::OnUpdateViewSubdivision1(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:4286-4291 (OnUpdateViewSubdivision1)
    event.Check(WW3D::Get_NPatches_Level() == 1);
}

void W3DViewFrame::OnViewSubdivision2(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:4293-4300 (OnViewSubdivision2)
    // Function: Set N-Patches subdivision level to 2
    // ✅ Exact MFC match - Ready for runtime testing
    WW3D::Set_NPatches_Level(2);
    wxConfig::Get()->Write("/Config/NPatchesSubdivision", 2L);
    wxConfig::Get()->Flush();
}

void W3DViewFrame::OnUpdateViewSubdivision2(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:4302-4307 (OnUpdateViewSubdivision2)
    event.Check(WW3D::Get_NPatches_Level() == 2);
}

void W3DViewFrame::OnViewSubdivision3(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:4309-4316 (OnViewSubdivision3)
    // Function: Set N-Patches subdivision level to 3
    // ✅ Exact MFC match - Ready for runtime testing
    WW3D::Set_NPatches_Level(3);
    wxConfig::Get()->Write("/Config/NPatchesSubdivision", 3L);
    wxConfig::Get()->Flush();
}

void W3DViewFrame::OnUpdateViewSubdivision3(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:4318-4323 (OnUpdateViewSubdivision3)
    event.Check(WW3D::Get_NPatches_Level() == 3);
}

void W3DViewFrame::OnViewSubdivision4(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:4325-4332 (OnViewSubdivision4)
    // Function: Set N-Patches subdivision level to 4
    // ✅ Exact MFC match - Ready for runtime testing
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
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:4341-4348 (OnViewSubdivision5)
    // Function: Set N-Patches subdivision level to 5
    // ✅ Exact MFC match - Ready for runtime testing
    WW3D::Set_NPatches_Level(5);
    wxConfig::Get()->Write("/Config/NPatchesSubdivision", 5L);
    wxConfig::Get()->Flush();
}

void W3DViewFrame::OnUpdateViewSubdivision5(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:4350-4355 (OnUpdateViewSubdivision5)
    event.Check(WW3D::Get_NPatches_Level() == 5);
}

void W3DViewFrame::OnViewSubdivision6(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:4357-4364 (OnViewSubdivision6)
    // Function: Set N-Patches subdivision level to 6
    // ✅ Exact MFC match - Ready for runtime testing
    WW3D::Set_NPatches_Level(6);
    wxConfig::Get()->Write("/Config/NPatchesSubdivision", 6L);
    wxConfig::Get()->Flush();
}

void W3DViewFrame::OnUpdateViewSubdivision6(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:4366-4371 (OnUpdateViewSubdivision6)
    event.Check(WW3D::Get_NPatches_Level() == 6);
}

void W3DViewFrame::OnViewSubdivision7(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:4373-4380 (OnViewSubdivision7)
    // Function: Set N-Patches subdivision level to 7
    // ✅ Exact MFC match - Ready for runtime testing
    WW3D::Set_NPatches_Level(7);
    wxConfig::Get()->Write("/Config/NPatchesSubdivision", 7L);
    wxConfig::Get()->Flush();
}

void W3DViewFrame::OnUpdateViewSubdivision7(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:4382-4387 (OnUpdateViewSubdivision7)
    event.Check(WW3D::Get_NPatches_Level() == 7);
}

void W3DViewFrame::OnViewSubdivision8(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:4389-4396 (OnViewSubdivision8)
    // Function: Set N-Patches subdivision level to 8
    // ✅ Exact MFC match - Ready for runtime testing
    WW3D::Set_NPatches_Level(8);
    wxConfig::Get()->Write("/Config/NPatchesSubdivision", 8L);
    wxConfig::Get()->Flush();
}

void W3DViewFrame::OnUpdateViewSubdivision8(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:4398-4403 (OnUpdateViewSubdivision8)
    event.Check(WW3D::Get_NPatches_Level() == 8);
}

void W3DViewFrame::OnWireframe(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:4172-4179 (OnWireframeMode)
    // Function: Toggle wireframe rendering mode
    //
    // Implemented:
    // ✅ Get scene from document
    // ✅ Check current polygon mode
    // ✅ Toggle between LINE (wireframe) and FILL (normal)
    // ✅ Scene-specific setting (no config persistence)
    // ✅ UI update handler (OnUpdateWireframe) implemented
    //
    // Exact MFC Matching: ✅ Complete
    // Ready for runtime testing
    W3DViewDoc *doc = wxDynamicCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    ViewerSceneClass *scene = doc->GetScene();
    if (!scene) return;
    
    bool enable = (scene->Get_Polygon_Mode() != SceneClass::LINE);
    scene->Set_Polygon_Mode(enable ? SceneClass::LINE : SceneClass::FILL);
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
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:4202-4210 (OnToggleSorting)
    // Function: Toggle polygon sorting (global setting)
    //
    // Implemented:
    // ✅ Toggle WW3D sorting state
    // ✅ Invalidate mesh cache (required after toggle)
    // ✅ Enable/disable sorting via WW3D API
    // ✅ Persist to wxConfig ("/Config/EnableSorting")
    // ✅ UI update handler (OnUpdatePolygonSorting) implemented
    //
    // Exact MFC Matching: ✅ Complete
    // Ready for runtime testing
    bool sorting = !WW3D::Is_Sorting_Enabled();
    WW3D::_Invalidate_Mesh_Cache();
    WW3D::Enable_Sorting(sorting);
    wxConfig::Get()->Write("/Config/EnableSorting", sorting ? 1L : 0L);
    wxConfig::Get()->Flush();
}

void W3DViewFrame::OnUpdatePolygonSorting(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:4219-4223 (OnUpdateToggleSorting)
    // Check the menu item if sorting is enabled
    event.Check(WW3D::Is_Sorting_Enabled());
}

void W3DViewFrame::OnViewObjectBar(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:1859-1873 (OnViewObjectBar)
    //
    // MFC Implementation:
    //   if (m_objectToolbar.IsWindowVisible () == FALSE)
    //   {
    //       ShowControlBar (&m_objectToolbar, TRUE, FALSE);
    //   }
    //   else
    //   {
    //       ShowControlBar (&m_objectToolbar, FALSE, FALSE);
    //   }
    //
    // Expected Behavior:
    //   - Toggles visibility of Object toolbar (rotation controls, etc.)
    //   - Object toolbar contains: Rotate X/Y/Z buttons, Reset, etc.
    //   - MFC: CFancyToolbar with custom button states
    //
    // TODO(MFC-Match): Implement Object toolbar infrastructure
    //   Current wxWidgets implementation has basic toolbar in InitToolBar()
    //   but MFC has separate specialized toolbars (m_objectToolbar, m_animationToolbar)
    //   Need to:
    //   1. Create separate wxToolBar for object controls
    //   2. Add rotation lock buttons (IDM_OBJECT_ROTATE_X/Y/Z)
    //   3. Add reset, properties, etc. buttons
    //   4. Implement toggle show/hide functionality
    //   5. Persist toolbar visibility state in wxConfig
    //   Until then, this handler does nothing (menu item should be disabled)
    //   See MainFrm.cpp:532-591 for toolbar creation
    //   See Toolbar.cpp for CFancyToolbar implementation
    
    // Placeholder: No action until Object toolbar is implemented
    wxLogWarning("Object Toolbar not yet implemented in wxWidgets version");
}

void W3DViewFrame::OnUpdateViewObjectBar(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:1815-1821 (OnUpdateViewObjectBar)
    //
    // MFC Implementation:
    //   pCmdUI->Enable (TRUE);
    //   pCmdUI->SetCheck (m_objectToolbar.IsWindowVisible ());
    //
    // Expected Behavior:
    //   - Always enabled
    //   - Checked if Object toolbar is visible
    //
    // TODO(MFC-Match): Enable and check when Object toolbar exists
    //   For now: Disable menu item (no toolbar to toggle)
    
    event.Enable(false);  // Disabled until Object toolbar is implemented
    event.Check(false);   // Always unchecked (toolbar doesn't exist)
}

void W3DViewFrame::OnViewAnimationBar(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:1830-1850 (OnViewAnimationBar)
    //
    // MFC Implementation:
    //   if (m_animationToolbar.IsWindowVisible () == FALSE)
    //   {
    //       ShowControlBar (&m_animationToolbar, TRUE, FALSE);
    //       m_bShowAnimationBar = TRUE;
    //   }
    //   else
    //   {
    //       ShowControlBar (&m_animationToolbar, FALSE, FALSE);
    //       m_bShowAnimationBar = FALSE;
    //   }
    //
    // Expected Behavior:
    //   - Toggles visibility of Animation toolbar
    //   - Animation toolbar contains: Play, Pause, Stop, Step Forward/Back, Loop, etc.
    //   - MFC: CFancyToolbar with playback controls
    //   - Remembers state in m_bShowAnimationBar for auto-show on animation load
    //
    // TODO(MFC-Match): Implement Animation toolbar infrastructure
    //   Current wxWidgets has animation menu items but no animation toolbar
    //   Need to:
    //   1. Create separate wxToolBar for animation controls
    //   2. Add playback buttons (Play, Pause, Stop)
    //   3. Add step buttons (Step Forward/Back)
    //   4. Add loop/speed controls
    //   5. Implement toggle show/hide functionality
    //   6. Persist toolbar visibility state in wxConfig
    //   7. Auto-show when animation is loaded (see m_bShowAnimationBar)
    //   Until then, this handler does nothing (menu item should be disabled)
    //   See MainFrm.cpp:592-642 for toolbar creation
    //   See Toolbar.cpp for CFancyToolbar implementation
    
    // Placeholder: No action until Animation toolbar is implemented
    wxLogWarning("Animation Toolbar not yet implemented in wxWidgets version");
}

void W3DViewFrame::OnUpdateViewAnimationBar(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:1789-1806 (OnUpdateViewAnimationBar)
    //
    // MFC Implementation:
    //   if ((m_currentAssetType != TypeAnimation) || (m_currentAssetType != TypeCompressedAnimation))
    //   {
    //       pCmdUI->Enable (FALSE);
    //       pCmdUI->SetCheck (FALSE);
    //   }
    //   else
    //   {
    //       pCmdUI->Enable (TRUE);
    //       pCmdUI->SetCheck (m_animationToolbar.IsWindowVisible ());
    //   }
    //
    // Expected Behavior:
    //   - Enabled only when viewing animation asset
    //   - Checked if Animation toolbar is visible
    //   - Uses m_currentAssetType to determine if animation is loaded
    //
    // TODO(MFC-Match): Enable/check based on current asset type
    //   Need to track m_currentAssetType in wxWidgets frame
    //   For now: Always disable (no toolbar to toggle)
    
    event.Enable(false);  // Disabled until Animation toolbar is implemented
    event.Check(false);   // Always unchecked (toolbar doesn't exist)
}

void W3DViewFrame::OnViewFullscreen(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:2258-2271 (OnViewFullscreen)
    //
    // MFC Implementation:
    //   CGraphicView *pCGraphicView = (CGraphicView *)m_wndSplitter.GetPane (0, 1);
    //   if (pCGraphicView->Is_Fullscreen ())
    //   {
    //       RestoreOriginalSize ();
    //   }
    //   pCGraphicView->Set_Fullscreen (!pCGraphicView->Is_Fullscreen ());
    //
    // Expected Behavior:
    //   - Toggles fullscreen mode for GraphicView
    //   - If entering fullscreen: Save original window size
    //   - If exiting fullscreen: Restore original window size
    //   - GraphicView handles actual fullscreen rendering setup
    //
    // TODO(MFC-Match): Implement fullscreen mode in wxWidgets
    //   Need to:
    //   1. Add Is_Fullscreen() and Set_Fullscreen() to GraphicView_wx
    //   2. Implement RestoreOriginalSize() in W3DViewFrame
    //   3. Save/restore window size and position
    //   4. Consider using wxFrame::ShowFullScreen() for true OS fullscreen
    //      or custom implementation matching MFC behavior
    //   5. Handle DirectX fullscreen mode changes (if applicable)
    //   Until then, show placeholder message
    //   See GraphicView.cpp for Is_Fullscreen/Set_Fullscreen implementation
    //   See MainFrm.cpp:2258-2271 for fullscreen toggle logic
    
    // Placeholder: No action until fullscreen mode is implemented
    wxMessageBox(
        "Fullscreen mode not yet implemented in wxWidgets version.\n\n"
        "MFC version toggles fullscreen rendering in GraphicView.\n"
        "This requires GraphicView_wx fullscreen infrastructure.",
        "Fullscreen Not Implemented",
        wxOK | wxICON_INFORMATION,
        this
    );
}

void W3DViewFrame::OnUpdateViewFullscreen(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:2280-2285 (OnUpdateViewFullscreen)
    //
    // MFC Implementation:
    //   CGraphicView *pCGraphicView = (CGraphicView *)m_wndSplitter.GetPane (0, 1);
    //   pCmdUI->SetCheck (pCGraphicView->Is_Fullscreen ());
    //
    // Expected Behavior:
    //   - Checked if GraphicView is in fullscreen mode
    //
    // TODO(MFC-Match): Check GraphicView fullscreen state
    //   Need Is_Fullscreen() in GraphicView_wx
    //   For now: Always unchecked (fullscreen not implemented)
    
    event.Check(false);  // Always unchecked (fullscreen not implemented)
}

// ============================================================================
// View Menu - Toolbars Submenu Handlers
// ============================================================================

void W3DViewFrame::OnViewToolbar(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: Standard MFC ID_VIEW_TOOLBAR (0xE800)
    //
    // MFC Implementation:
    //   Standard MFC framework handler toggles main toolbar visibility
    //   Uses CFrameWnd::ShowControlBar(m_wndToolBar, !m_wndToolBar.IsVisible())
    //
    // Expected Behavior:
    //   - Toggle main toolbar visibility
    //   - Toolbar contains: New, Open, Save, Properties buttons
    //
    // TODO(MFC-Match): Implement main toolbar toggle
    //   Need to:
    //   1. Track main toolbar visibility state
    //   2. Implement Show/Hide with proper layout adjustment
    //   3. Persist toolbar state in wxConfig
    //   Until then: Placeholder (toolbar always visible)

    // Placeholder: No action (main toolbar management not implemented)
    wxMessageBox(
        "Main toolbar toggle not yet implemented.\n\n"
        "MFC version shows/hides the main toolbar with File and Object buttons.\n"
        "This requires toolbar visibility management.",
        "TODO",
        wxOK | wxICON_INFORMATION,
        this
    );
}

void W3DViewFrame::OnUpdateViewToolbar(wxUpdateUIEvent &event)
{
    // MFC Reference: Standard MFC OnUpdateControlBarMenu
    //
    // Expected Behavior:
    //   - Checked if main toolbar is visible
    //   - Always enabled
    //
    // TODO(MFC-Match): Check actual toolbar visibility
    //   For now: Always checked (toolbar always visible)

    event.Enable(true);
    event.Check(true);  // Always checked (toolbar always visible)
}

// ============================================================================
// View Menu - Status Bar Handler
// ============================================================================

void W3DViewFrame::OnViewStatusBar(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: Standard MFC ID_VIEW_STATUS_BAR (0xE801)
    // MFC uses ShowControlBar(m_wndStatusBar, !m_wndStatusBar.IsVisible())
    // Toggles status bar visibility and updates window layout
    
    wxStatusBar *statusBar = GetStatusBar();
    if (statusBar)
    {
        bool isVisible = statusBar->IsShown();
        statusBar->Show(!isVisible);
        Layout();  // Adjust window layout after show/hide
        
        // Persist visibility state to wxConfig
        wxConfigBase *config = wxConfig::Get();
        config->Write("/View/StatusBarVisible", !isVisible);
        config->Flush();
    }
    else
    {
        wxMessageBox(
            "Status bar does not exist.\n\n"
            "InitStatusBar() may not have been called.",
            "Status Bar Missing",
            wxOK | wxICON_WARNING,
            this
        );
    }
}

void W3DViewFrame::OnUpdateViewStatusBar(wxUpdateUIEvent &event)
{
    // MFC Reference: Standard MFC OnUpdateControlBarMenu
    // Shows checkmark when status bar is visible
    
    wxStatusBar *statusBar = GetStatusBar();
    event.Enable(statusBar != nullptr);
    event.Check(statusBar && statusBar->IsShown());
}

// ============================================================================
// View Menu - Slideshow Navigation Handlers
// ============================================================================

void W3DViewFrame::OnSlideshowPrev(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp (IDM_SLIDESHOW_UP = 32849)
    //
    // MFC Implementation:
    //   if (m_slideshowMode)
    //   {
    //       Load_Previous_File();
    //   }
    //
    // Expected Behavior:
    //   - If slideshow mode enabled: Load previous file in directory
    //   - Wraps to last file if at beginning
    //   - Only active when m_slideshowMode is true
    //   - Typically used for batch reviewing W3D models
    //
    // TODO(MFC-Investigate): Implement slideshow mode infrastructure
    //   Need to:
    //   1. Add m_slideshowMode flag to frame
    //   2. Implement directory file enumeration (*.w3d)
    //   3. Track current file index
    //   4. Implement Load_Previous_File() / Load_Next_File()
    //   5. Consider enabling slideshow mode when opening file
    //   6. Handle keyboard shortcuts (PgUp/PgDn)
    //   Until then: Disabled (no slideshow mode)
    //   See MainFrm.cpp for slideshow implementation details

    wxMessageBox(
        "Slideshow navigation not yet implemented.\n\n"
        "MFC version allows navigating through W3D files in a directory.\n"
        "This requires slideshow mode infrastructure.",
        "TODO",
        wxOK | wxICON_INFORMATION,
        this
    );
}

void W3DViewFrame::OnSlideshowNext(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp (IDM_SLIDESHOW_DOWN = 32850)
    //
    // MFC Implementation:
    //   if (m_slideshowMode)
    //   {
    //       Load_Next_File();
    //   }
    //
    // Expected Behavior:
    //   - If slideshow mode enabled: Load next file in directory
    //   - Wraps to first file if at end
    //   - Only active when m_slideshowMode is true
    //
    // TODO(MFC-Investigate): Implement slideshow mode infrastructure
    //   Same requirements as OnSlideshowPrev
    //   Until then: Disabled

    wxMessageBox(
        "Slideshow navigation not yet implemented.\n\n"
        "MFC version allows navigating through W3D files in a directory.\n"
        "This requires slideshow mode infrastructure.",
        "TODO",
        wxOK | wxICON_INFORMATION,
        this
    );
}

// ============================================================================
// View Menu - Device and Resolution Handlers
// ============================================================================

void W3DViewFrame::OnChangeDevice(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp (IDM_DEVICE_CHANGE = 32806)
    //
    // MFC Implementation:
    //   RenderDeviceClass::Reset_Current_Device();
    //   CGraphicView *pCGraphicView = (CGraphicView *)m_wndSplitter.GetPane(0, 1);
    //   pCGraphicView->Change_Device();
    //   // Show device selection dialog
    //   // Reinitialize rendering with new device
    //
    // Expected Behavior:
    //   - Open device selection dialog
    //   - Allow switching between D3D devices (hardware/software)
    //   - Reinitialize GraphicView with new device
    //   - Note: Was GRAYED in MFC menu (disabled)
    //
    // TODO(MFC-Investigate): Implement device change infrastructure
    //   Need to:
    //   1. Add RenderDeviceSelector dialog (already exists as _wx variant)
    //   2. Implement Change_Device() in GraphicView_wx
    //   3. Handle device re-initialization
    //   4. Preserve scene state across device changes
    //   Until then: Show placeholder or reuse existing dialog
    //   Note: May be obsolete (Wine only has one D3D device)

    wxMessageBox(
        "Device change not yet implemented.\n\n"
        "MFC version allows switching between D3D hardware/software devices.\n"
        "This requires device management infrastructure.\n\n"
        "Note: This was GRAYED (disabled) in MFC menu.",
        "TODO",
        wxOK | wxICON_INFORMATION,
        this
    );
}

void W3DViewFrame::OnChangeResolution(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp (IDM_CHANGE_RESOLUTION = 32864)
    //
    // MFC Implementation:
    //   CResolution dlg;
    //   if (dlg.DoModal() == IDOK)
    //   {
    //       // Get selected resolution from dialog
    //       // Resize GraphicView and reinitialize
    //   }
    //
    // Expected Behavior:
    //   - Open resolution selection dialog
    //   - Allow changing rendering resolution
    //   - Resize GraphicView to new resolution
    //   - Note: Was GRAYED in MFC menu (disabled)
    //
    // TODO(MFC-Investigate): Implement resolution change infrastructure
    //   Need to:
    //   1. Add Resolution dialog (already exists as Resolution_wx)
    //   2. Implement resolution change in GraphicView_wx
    //   3. Handle window resizing and layout
    //   Until then: Show placeholder or reuse existing dialog
    //   Note: May be less relevant (windowed mode can be resized directly)

    wxMessageBox(
        "Resolution change not yet implemented.\n\n"
        "MFC version allows changing the rendering resolution.\n"
        "This requires resolution management infrastructure.\n\n"
        "Note: This was GRAYED (disabled) in MFC menu.",
        "TODO",
        wxOK | wxICON_INFORMATION,
        this
    );
}

void W3DViewFrame::OnAnimationPlay(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅ (core complete, toolbar deferred)
    // MFC Reference: MainFrm.cpp:1292-1309 (OnAniStart)
    // Function: Start animation playback
    //
    // Implemented:
    // ✅ Get graphic view from document
    // ✅ Set animation state to AnimPlaying
    // ✅ Animation starts playing
    // ⏸️ Toolbar button updates (deferred - infrastructure pending)
    //
    // MFC Matching: ✅ Core functionality complete
    // Note: Toolbar button state updates will be added when
    //       animation toolbar infrastructure is implemented
    // Ready for runtime testing (animations will play correctly)
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    // Start the animation
    graphicView->SetAnimationState(CGraphicView::AnimPlaying);
    
    // TODO(MFC-Infrastructure): Update toolbar buttons when Animation toolbar is implemented
    //   MFC updates m_animationToolbar button states (Play down, Pause up)
    //   See MainFrm.cpp:1302-1305
    //   Defer until toolbar infrastructure exists
}

void W3DViewFrame::OnAnimationPause(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅ (core complete, toolbar deferred)
    // MFC Reference: MainFrm.cpp:1318-1348 (OnAniPause)
    // Function: Toggle between Playing and Paused animation states
    //
    // Implemented:
    // ✅ Get graphic view from document
    // ✅ Check current animation state
    // ✅ If Playing → Pause (set AnimPaused)
    // ✅ If Paused → Resume (set AnimPlaying)
    // ✅ If Stopped → Do nothing
    // ⏸️ Toolbar button updates (deferred - infrastructure pending)
    //
    // MFC Matching: ✅ Core functionality complete
    // Note: Toolbar button state updates will be added when
    //       animation toolbar infrastructure is implemented
    // Ready for runtime testing (pause/resume works correctly)
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    // Toggle between Playing and Paused
    if (graphicView->GetAnimationState() == CGraphicView::AnimPlaying)
    {
        // Pause the animation
        graphicView->SetAnimationState(CGraphicView::AnimPaused);
        // TODO(MFC-Infrastructure): SetButtonState(IDM_ANI_PAUSE, StateDn)
    }
    else if (graphicView->GetAnimationState() == CGraphicView::AnimPaused)
    {
        // Resume playing
        graphicView->SetAnimationState(CGraphicView::AnimPlaying);
        // TODO(MFC-Infrastructure): SetButtonState(IDM_ANI_PAUSE, StateUp)
    }
    // If stopped, do nothing (toolbar button pops up in MFC)
}

void W3DViewFrame::OnAnimationStop(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅ (core complete, toolbar deferred)
    // MFC Reference: MainFrm.cpp:1268-1283 (OnAniStop)
    // Function: Stop animation playback
    //
    // Implemented:
    // ✅ Get graphic view from document
    // ✅ Set animation state to AnimStopped
    // ✅ Animation stops and resets
    // ⏸️ Toolbar button updates (deferred - infrastructure pending)
    //
    // MFC Matching: ✅ Core functionality complete
    // Note: Toolbar button state updates will be added when
    //       animation toolbar infrastructure is implemented
    // Ready for runtime testing (stop works correctly)
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    // Stop the animation
    graphicView->SetAnimationState(CGraphicView::AnimStopped);
    
    // TODO(MFC-Infrastructure): Update toolbar buttons when Animation toolbar is implemented
    //   MFC pops both Play and Pause buttons
    //   See MainFrm.cpp:1278-1279
    //   Defer until toolbar infrastructure exists
}

void W3DViewFrame::OnAnimationStepBack(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:1902-1913 (OnAniStepBkwd)
    // Function: Step animation backward by one frame
    //
    // Implemented:
    // ✅ Get document
    // ✅ Call StepAnimation(-1) to step backward
    // ✅ Wraps to last frame if at frame 0
    // ✅ Document handles frame update
    //
    // Exact MFC Matching: ✅ Complete
    // Ready for runtime testing
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    // Step animation backward by one frame
    doc->StepAnimation(-1);
}

void W3DViewFrame::OnAnimationStepForward(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:1882-1893 (OnAniStepFwd)
    // Function: Step animation forward by one frame
    //
    // Implemented:
    // ✅ Get document
    // ✅ Call StepAnimation(1) to step forward
    // ✅ Wraps to frame 0 if at last frame
    // ✅ Document handles frame update
    //
    // Exact MFC Matching: ✅ Complete
    // Ready for runtime testing
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    // Step animation forward by one frame
    doc->StepAnimation(1);
}

void W3DViewFrame::OnAnimationSettings(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:990-1002 (OnAniSpeed)
    // MFC Dialog: CAnimationSpeed (AnimationSpeed.cpp:48-243)
    //
    // Implemented (Displayspeed_wx.cpp - 219 lines):
    // ✅ Animation speed slider (1-200%, real-time updates)
    // ✅ OnHscroll: Real-time speed adjustment (0.01-2.00x)
    // ✅ Animation blend checkbox (toggle blend mode)
    // ✅ OnBlend: Toggle animation blending
    // ✅ OnDestroy: Cleanup handler
    // ✅ Constructor: Saves initial speed for cancel restore
    // ✅ OnCancel: Restores initial animation speed
    // ✅ OnOK: Keeps current settings
    //
    // MFC Matching Note: Compression features intentionally NOT implemented
    //   - OnCompressq, On16bit, On8bit are COMMENTED OUT in MFC (AnimationSpeed.cpp:203-243)
    //   - Controls exist in UI but don't function in MFC either
    //   - Exact MFC match: Non-functional compression checkboxes ✓
    //
    // TODO(MFC-Investigation-LOW): Compression features (abandoned in MFC for 20+ years)
    //   Question: Should these be activated?
    //     a) Incomplete/abandoned in MFC? (most likely)
    //     b) Disabled for specific reason?
    //     c) Intended for future implementation?
    //   Impact: VERY LOW (unused for 20+ years)
    //   Recommendation: Leave as-is unless specifically requested
    //
    // Exact MFC Matching: ✅ Complete (including non-functional compression controls)
    // MFC Reference: AnimationSpeed.cpp:48-243
    // Ready for runtime testing
    
    // Get document and view
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* view = doc->GetGraphicView();
    if (!view) return;
    
    // Show animation speed dialog (MFC: AnimationSpeed.cpp:48)
    // Constructor saves initial speed for cancel restore (AnimationSpeed.cpp:124-128)
    Displayspeed dialog(this, doc, view);
    
    // ShowModal handles cancel restore automatically (Displayspeed_wx.cpp:64-72)
    // MFC Reference: MainFrm.cpp:998-1001
    //   if (dlg.DoModal() != IDOK)
    //       pCGraphicView->SetAnimationSpeed(initialSpeed);
    dialog.ShowModal();
    
    // Note: Settings apply in real-time via OnHscroll/OnBlend handlers
    //       No post-dialog processing needed
}

void W3DViewFrame::OnAnimationAdvanced(wxCommandEvent &WXUNUSED(event))
{
    // MFC: MainFrm.cpp (need to investigate OnAdvancedAnim handler)
    // MFC ID: IDM_ADVANCED_ANIM (W3DView.rc:373)
    // Function: Opens advanced animation mixing/management dialog
    // TODO(MFC-Implement): Implement advanced animation dialog
    //   MFC Reference: PropPageAdvanimMixing_wx.cpp, PropPageAdvanimReport_wx.cpp already exist
    //   These appear to be property pages for advanced animation features:
    //   - Animation mixing (blending multiple animations)
    //   - Animation reports (debugging/analysis)
    //   Need to create parent dialog that hosts these property pages
    //   Impact: Medium - advanced user feature for complex animation workflows
    //   Investigation: Check if PropPage files are complete or need work
    wxMessageBox("Advanced Animation dialog not yet implemented.\nSee TODO in OnAnimationAdvanced.\nProperty pages may already exist (PropPageAdvanim*).",
                 "Feature Incomplete", wxOK | wxICON_INFORMATION, this);
}

void W3DViewFrame::OnBackgroundColor(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: BackgroundColorDialog.cpp (CBackgroundColorDialog)
    // MFC: MainFrm.cpp:1580-1586 (OnBackgroundColor)
    //
    // Implemented (BackgroundColor_wx.cpp - 236 lines):
    // ✅ OnInitDialog: Gets current background color from document
    // ✅ Initializes 3 RGB sliders (0-100 range) with current values
    // ✅ Checks grayscale checkbox if R==G==B
    // ✅ OnHScroll: REAL-TIME color updates as sliders move (live preview)
    // ✅ Grayscale mode: All sliders move together when checked
    // ✅ OnCancel: Restores initial color (undoes live preview changes)
    // ✅ OnOK: Just closes (color already set via live preview)
    //
    // Exact MFC Matching: ✅ Complete
    // MFC Reference: BackgroundColorDialog.cpp:42-145
    // Ready for runtime testing
    BackgroundColor dialog(this);
    dialog.ShowModal();
}

void W3DViewFrame::OnBackgroundBmp(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC: MainFrm.cpp (OnBackgroundBmp - shows dialog)
    // Dialog: BackgroundBMPDialog.cpp:38-92 (OnInitDialog, OnOK)
    //
    // Implemented (BackgroundBmp_wx.cpp - 104 lines):
    // ✅ OnInitDialog: Loads background bitmap filename from document
    // ✅ OnBrowse: wxFileDialog for selecting *.bmp files
    // ✅ Filename text control with full path display
    // ✅ OnOK (TransferDataFromWindow): Saves filename to document
    // ✅ Empty filename clears background bitmap
    // ✅ File dialog filter: "Bitmap Files (*.bmp)|*.bmp"
    //
    // Exact MFC Matching: ✅ Complete
    // MFC Reference: BackgroundBMPDialog.cpp:38-92
    // Ready for runtime testing
    BackgroundBmp dialog(this);
    dialog.ShowModal();
}

void W3DViewFrame::OnBackgroundObject(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC: MainFrm.cpp (OnBackgroundObject - shows dialog)
    // Dialog: BackgroundObjectDialog.cpp:44-221 (OnInitDialog, OnItemChangedHierarchyList, OnClear, OnOK)
    //
    // Implemented (BackgroundObject_wx.cpp - 142 lines):
    // ✅ OnInitDialog: Enumerates hierarchies (CLASSID_HMODEL) from asset manager
    // ✅ Populates list control with hierarchy names
    // ✅ Sets selected item to current background object from document
    // ✅ OnItemChangedHierarchyList: Updates selection based on user click
    // ✅ OnClear: Clears background object (sets to nullptr)
    // ✅ OnOK (TransferDataFromWindow): Saves selected hierarchy to document
    // ✅ Integration with WW3DAssetManager for object enumeration
    //
    // Exact MFC Matching: ✅ Complete
    // MFC Reference: BackgroundObjectDialog.cpp:44-221
    // Ready for runtime testing
    BackgroundObject dialog(this);
    dialog.ShowModal();
}

void W3DViewFrame::OnBackgroundFog(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:1649 (OnBackgroundFog)
    // Function: Toggle background fog enable/disable state
    //
    // Implemented:
    // ✅ Get current fog state from document
    // ✅ Toggle fog enable state
    // ✅ Document integration via EnableFog/IsFogEnabled
    //
    // Exact MFC Matching: ✅ Complete
    // Ready for runtime testing
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
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:1397-1408 (OnCameraFront)
    // Function: Position camera to front view
    //
    // Implemented:
    // ✅ Get graphic view from document
    // ✅ Set camera position to CameraFront
    // ✅ View updates automatically
    //
    // Exact MFC Matching: ✅ Complete
    // Ready for runtime testing
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    graphicView->SetCameraPos(CGraphicView::CameraFront);
}

void W3DViewFrame::OnCameraBack(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:1357-1368 (OnCameraBack)
    // Function: Position camera to back view
    //
    // Implemented:
    // ✅ Get graphic view from document
    // ✅ Set camera position to CameraBack
    // ✅ View updates automatically
    //
    // Exact MFC Matching: ✅ Complete
    // Ready for runtime testing
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    graphicView->SetCameraPos(CGraphicView::CameraBack);
}

void W3DViewFrame::OnCameraLeft(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:1417-1428 (OnCameraLeft)
    // Function: Position camera to left view
    //
    // Implemented:
    // ✅ Get graphic view from document
    // ✅ Set camera position to CameraLeft
    // ✅ View updates automatically
    //
    // Exact MFC Matching: ✅ Complete
    // Ready for runtime testing
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    graphicView->SetCameraPos(CGraphicView::CameraLeft);
}

void W3DViewFrame::OnCameraRight(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:1467-1478 (OnCameraRight)
    // Function: Position camera to right view
    //
    // Implemented:
    // ✅ Get graphic view from document
    // ✅ Set camera position to CameraRight
    // ✅ View updates automatically
    //
    // Exact MFC Matching: ✅ Complete
    // Ready for runtime testing
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    graphicView->SetCameraPos(CGraphicView::CameraRight);
}

void W3DViewFrame::OnCameraTop(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:1487-1498 (OnCameraTop)
    // Function: Position camera to top view
    //
    // Implemented:
    // ✅ Get graphic view from document
    // ✅ Set camera position to CameraTop
    // ✅ View updates automatically
    //
    // Exact MFC Matching: ✅ Complete
    // Ready for runtime testing
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    graphicView->SetCameraPos(CGraphicView::CameraTop);
}

void W3DViewFrame::OnCameraBottom(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:1377-1388 (OnCameraBottom)
    // Function: Position camera to bottom view
    //
    // Implemented:
    // ✅ Get graphic view from document
    // ✅ Set camera position to CameraBottom
    // ✅ View updates automatically
    //
    // Exact MFC Matching: ✅ Complete
    // Ready for runtime testing
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    graphicView->SetCameraPos(CGraphicView::CameraBottom);
}

void W3DViewFrame::OnCameraReset(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:1437-1458 (OnCameraReset)
    // Function: Reset camera to optimal viewing position for displayed object
    //
    // Implemented:
    // ✅ Get graphic view from document
    // ✅ Get displayed render object
    // ✅ Check object type (particle emitter vs regular)
    // ✅ Call Reset_Camera_To_Display_Emitter for particle emitters
    // ✅ Call Reset_Camera_To_Display_Object for regular objects
    // ✅ Optimal camera positioning handled by graphic view
    //
    // Exact MFC Matching: ✅ Complete
    // Ready for runtime testing
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    RenderObjClass* renderObj = doc->GetDisplayedObject();
    if (!renderObj) return;
    
    // Reset camera based on object type
    if (renderObj->Class_ID() == RenderObjClass::CLASSID_PARTICLEEMITTER) {
        graphicView->Reset_Camera_To_Display_Emitter(*reinterpret_cast<ParticleEmitterClass*>(renderObj));
    } else {
        graphicView->Reset_Camera_To_Display_Object(*renderObj);
    }
}

void W3DViewFrame::OnCameraSettings(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC: MainFrm.cpp (OnCameraSettings - shows dialog)
    // Dialog: CameraSettingsDialog.cpp:85-197 (OnInitDialog, OnOK)
    // 
    // Implemented (CameraSettings_wx.cpp - 416 lines):
    // ✅ Full camera FOV settings (vertical, horizontal, lens)
    // ✅ Clip plane settings (near, far)
    // ✅ Manual override checkboxes with enable/disable logic
    // ✅ Spin button controls for all numeric fields
    // ✅ Reset button functionality
    // ✅ Integration with GraphicView camera system
    // ✅ Validation and bounds checking
    // ✅ wxConfig persistence
    //
    // Ready for runtime testing
    CameraSettings dialog(this);
    dialog.ShowModal();
}

void W3DViewFrame::OnCameraAllowRotateX(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:1942-1971 (OnCameraAllowRotateX)
    //
    // MFC Implementation:
    //   CGraphicView *pCGraphicView = (CGraphicView *)m_wndSplitter.GetPane (0, 1);
    //   if (pCGraphicView)
    //   {
    //       if (pCGraphicView->GetAllowedCameraRotation () != CGraphicView::OnlyRotateX)
    //       {
    //           pCGraphicView->SetAllowedCameraRotation (CGraphicView::OnlyRotateX);
    //           m_objectToolbar.SetButtonState (IDM_CAMERA_ALLOW_ROTATE_X, CFancyToolbar::StateDn);
    //           m_objectToolbar.SetButtonState (IDM_CAMERA_ALLOW_ROTATE_Y, CFancyToolbar::StateUp);
    //           m_objectToolbar.SetButtonState (IDM_CAMERA_ALLOW_ROTATE_Z, CFancyToolbar::StateUp);
    //       }
    //       else
    //       {
    //           pCGraphicView->SetAllowedCameraRotation (CGraphicView::FreeRotation);
    //           m_objectToolbar.SetButtonState (IDM_CAMERA_ALLOW_ROTATE_X, CFancyToolbar::StateUp);
    //           m_objectToolbar.SetButtonState (IDM_CAMERA_ALLOW_ROTATE_Y, CFancyToolbar::StateUp);
    //           m_objectToolbar.SetButtonState (IDM_CAMERA_ALLOW_ROTATE_Z, CFancyToolbar::StateUp);
    //       }
    //   }
    //
    // Behavior: Toggle camera rotation constraint to X-axis only
    //           If already constrained to X, toggle off (return to FreeRotation)
    //           Menu checkmarks handled by OnUpdateCameraAllowRotateX
    //
    // Menu: Camera → Rotate X Only
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    // Toggle behavior: if already OnlyRotateX, switch to FreeRotation; otherwise set OnlyRotateX
    if (graphicView->GetAllowedCameraRotation() != CGraphicView::OnlyRotateX) {
        graphicView->SetAllowedCameraRotation(CGraphicView::OnlyRotateX);
    } else {
        graphicView->SetAllowedCameraRotation(CGraphicView::FreeRotation);
    }
    
    // TODO(MFC-Match): Update toolbar button states when Object toolbar is implemented
    // MFC syncs m_objectToolbar button states here (IDM_CAMERA_ALLOW_ROTATE_X/Y/Z)
}

void W3DViewFrame::OnUpdateCameraAllowRotateX(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:2055-2067 (OnUpdateCameraAllowRotateX)
    //
    // MFC Implementation:
    //   CGraphicView *pCGraphicView = (CGraphicView *)m_wndSplitter.GetPane (0, 1);
    //   if (pCGraphicView)
    //   {
    //       pCmdUI->SetCheck (pCGraphicView->GetAllowedCameraRotation () == CGraphicView::OnlyRotateX);
    //   }
    //
    // Behavior: Check menu item if camera rotation is constrained to X-axis only
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    event.Check(graphicView->GetAllowedCameraRotation() == CGraphicView::OnlyRotateX);
}

void W3DViewFrame::OnCameraAllowRotateY(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:1980-2009 (OnCameraAllowRotateY)
    //
    // MFC Implementation: Same toggle pattern as OnCameraAllowRotateX but for Y-axis
    //
    // Behavior: Toggle camera rotation constraint to Y-axis only
    //           If already constrained to Y, toggle off (return to FreeRotation)
    //
    // Menu: Camera → Rotate Y Only
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    if (graphicView->GetAllowedCameraRotation() != CGraphicView::OnlyRotateY) {
        graphicView->SetAllowedCameraRotation(CGraphicView::OnlyRotateY);
    } else {
        graphicView->SetAllowedCameraRotation(CGraphicView::FreeRotation);
    }
    
    // TODO(MFC-Match): Update toolbar button states when Object toolbar is implemented
}

void W3DViewFrame::OnUpdateCameraAllowRotateY(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:2075-2087 (OnUpdateCameraAllowRotateY)
    //
    // Behavior: Check menu item if camera rotation is constrained to Y-axis only
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    event.Check(graphicView->GetAllowedCameraRotation() == CGraphicView::OnlyRotateY);
}

void W3DViewFrame::OnCameraAllowRotateZ(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:2018-2047 (OnCameraAllowRotateZ)
    //
    // MFC Implementation: Same toggle pattern as OnCameraAllowRotateX but for Z-axis
    //
    // Behavior: Toggle camera rotation constraint to Z-axis only
    //           If already constrained to Z, toggle off (return to FreeRotation)
    //
    // Menu: Camera → Rotate Z Only
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    if (graphicView->GetAllowedCameraRotation() != CGraphicView::OnlyRotateZ) {
        graphicView->SetAllowedCameraRotation(CGraphicView::OnlyRotateZ);
    } else {
        graphicView->SetAllowedCameraRotation(CGraphicView::FreeRotation);
    }
    
    // TODO(MFC-Match): Update toolbar button states when Object toolbar is implemented
}

void W3DViewFrame::OnUpdateCameraAllowRotateZ(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:2095-2107 (OnUpdateCameraAllowRotateZ)
    //
    // Behavior: Check menu item if camera rotation is constrained to Z-axis only
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    event.Check(graphicView->GetAllowedCameraRotation() == CGraphicView::OnlyRotateZ);
}

void W3DViewFrame::OnCopyScreenSize(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:3398-3432 (OnCopyScreenSize)
    //
    // MFC Implementation:
    //   CGraphicView *graphic_view = (CGraphicView *)m_wndSplitter.GetPane (0, 1);
    //   CameraClass *camera = graphic_view->GetCamera ();
    //   RenderObjClass *render_obj = ::GetCurrentDocument ()->GetDisplayedObject ();
    //   float screen_size = render_obj->Get_Screen_Size (*camera);
    //
    //   CString size_string;
    //   size_string.Format ("MaxScreenSize=%f", screen_size);
    //
    //   [Windows clipboard operations: GlobalAlloc, GlobalLock, OpenClipboard, etc.]
    //
    // Behavior: Calculates the maximum screen size of the displayed object from
    //           the current camera view and copies it to clipboard
    //
    // Output Format: "MaxScreenSize=<float_value>"
    //
    // Menu: Camera → Copy Screen Size To Clipboard (Ctrl+C)
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (!graphicView) return;
    
    // Get the camera from the graphic view
    CameraClass* camera = graphicView->GetCamera();
    if (!camera) return;
    
    // Get the displayed object
    RenderObjClass* renderObj = doc->GetDisplayedObject();
    if (!renderObj) return;
    
    // Calculate the screen size
    float screenSize = renderObj->Get_Screen_Size(*camera);
    
    // Format the string (matching MFC format exactly)
    wxString sizeString = wxString::Format("MaxScreenSize=%f", screenSize);
    
    // Copy to clipboard using wxWidgets API
    if (wxTheClipboard->Open()) {
        wxTheClipboard->SetData(new wxTextDataObject(sizeString));
        wxTheClipboard->Close();
    }
}

void W3DViewFrame::OnSetCameraDistance(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:4059-4064 (OnSetCameraDistance)
    //
    // MFC Implementation:
    //   void CMainFrame::OnSetCameraDistance (void)
    //   {
    //       CameraDistanceDialogClass dialog (this);
    //       dialog.DoModal ();
    //       return ;
    //   }
    //
    // Behavior: Opens camera distance configuration dialog
    //
    // Menu: Camera → Set Distance...
    
    CameraDistance dialog(this);
    dialog.ShowModal();
}

void W3DViewFrame::OnCameraAnimate(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:2514-2520 (OnCameraAnimate)
    //
    // MFC Implementation:
    //   void CMainFrame::OnCameraAnimate (void)
    //   {
    //       bool banimated = ((CW3DViewDoc *)GetActiveDocument ())->Is_Camera_Animated ();
    //       ((CW3DViewDoc *)GetActiveDocument ())->Animate_Camera (banimated == false);
    //       return ;
    //   }
    //
    // Behavior: Toggles camera animation on/off
    //           When disabling, MFC automatically resets camera (via document method)
    //
    // Menu: Camera → Animate Camera (F8) [Checkable]
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    // Toggle the animated state
    bool currentlyAnimated = doc->Is_Camera_Animated();
    doc->Animate_Camera(!currentlyAnimated);
    
    // TODO(MFC-Match): Call OnCameraReset when disabling animation
    // MFC document method sends IDM_CAMERA_RESET command
    // Consider: if (!currentlyAnimated && !doc->Is_Camera_Animated()) OnCameraReset(event);
}

void W3DViewFrame::OnUpdateCameraAnimate(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:2529-2533 (OnUpdateCameraAnimate)
    //
    // MFC Implementation:
    //   void CMainFrame::OnUpdateCameraAnimate (CCmdUI *pCmdUI)
    //   {
    //       pCmdUI->SetCheck (((CW3DViewDoc *)GetActiveDocument ())->Is_Camera_Animated ());
    //       return ;
    //   }
    //
    // Behavior: Updates checkmark state based on document animation flag
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    event.Check(doc && doc->Is_Camera_Animated());
}

void W3DViewFrame::OnCameraBonePosX(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:4231-4237 (OnCameraBonePosX)
    //
    // MFC Implementation:
    //   void CMainFrame::OnCameraBonePosX()
    //   {
    //       CGraphicView *pCGraphicView = (CGraphicView *)m_wndSplitter.GetPane (0, 1);
    //       if (pCGraphicView != nullptr) {
    //           pCGraphicView->Set_Camera_Bone_Pos_X(!pCGraphicView->Is_Camera_Bone_Pos_X());
    //       }
    //   }
    //
    // Behavior: Toggles camera bone position X mode
    //
    // Menu: Camera → +X Camera [Checkable]
    //
    // TODO(MFC-Investigate): Clarify bone position mode behavior
    // May be related to camera attachment to skeletal animation bones
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    CGraphicView* graphicView = doc->GetGraphicView();
    if (graphicView) {
        // Toggle bone position X mode
        graphicView->Set_Camera_Bone_Pos_X(!graphicView->Is_Camera_Bone_Pos_X());
    }
}

void W3DViewFrame::OnUpdateCameraBonePosX(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:4246-4252 (OnUpdateCameraBonePosX)
    //
    // MFC Implementation:
    //   void CMainFrame::OnUpdateCameraBonePosX(CCmdUI* pCmdUI)
    //   {
    //       CGraphicView *pCGraphicView = (CGraphicView *)m_wndSplitter.GetPane (0, 1);
    //       if (pCGraphicView != nullptr) {
    //           pCmdUI->SetCheck(pCGraphicView->Is_Camera_Bone_Pos_X());
    //       }
    //   }
    //
    // Behavior: Updates checkmark state based on GraphicView bone pos flag
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (doc) {
        CGraphicView* graphicView = doc->GetGraphicView();
        event.Check(graphicView && graphicView->Is_Camera_Bone_Pos_X());
    } else {
        event.Check(false);
    }
}

void W3DViewFrame::OnCameraResetOnLoad(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:2564-2574 (OnCameraResetOnLoad)
    //
    // MFC Implementation:
    //   void CMainFrame::OnCameraResetOnLoad (void)
    //   {
    //       // Toggle the auto reset state of the menu option
    //       CW3DViewDoc *pdoc = (CW3DViewDoc *)GetActiveDocument ();
    //       pdoc->Turn_Camera_Auto_Reset_On ((pdoc->Is_Camera_Auto_Reset_On () == false));
    //       return ;
    //   }
    //
    // Behavior: Toggles whether camera automatically resets when loading new objects
    //           State is persisted via Turn_Camera_Auto_Reset_On()
    //
    // Menu: Camera → Reset on Display [Checkable]
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    if (!doc) return;
    
    // Toggle the auto reset state
    doc->Turn_Camera_Auto_Reset_On(!doc->Is_Camera_Auto_Reset_On());
}

void W3DViewFrame::OnUpdateCameraResetOnLoad(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:2579-2588 (OnUpdateCameraResetOnLoad)
    //
    // MFC Implementation:
    //   void CMainFrame::OnUpdateCameraResetOnLoad (CCmdUI *pCmdUI)
    //   {
    //       CW3DViewDoc *pdoc = (CW3DViewDoc *)GetActiveDocument ();
    //       pCmdUI->SetCheck (pdoc->Is_Camera_Auto_Reset_On ());
    //       return ;
    //   }
    //
    // Behavior: Sets checkmark based on current auto reset state
    
    W3DViewDoc* doc = wxStaticCast(GetDocument(), W3DViewDoc);
    event.Check(doc && doc->Is_Camera_Auto_Reset_On());
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
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: AmbientLightDialog.cpp (CAmbientLightDialog)
    // MFC: MainFrm.cpp:1588-1594 (OnLightAmbient)
    //
    // Implemented (LightAmbientDialog_wx.cpp):
    // ✅ OnInitDialog: Gets current ambient light from scene via doc->GetAmbientLight()
    // ✅ Initializes 3 RGB sliders (0-100 range) with current values
    // ✅ Checks grayscale checkbox if R==G==B
    // ✅ OnHScroll: REAL-TIME ambient light updates as sliders move (live preview)
    // ✅ Grayscale mode: All sliders move together when checked
    // ✅ OnCancel: Restores initial ambient light (undoes live preview changes)
    // ✅ OnOK: Just closes (ambient light already set via live preview)
    //
    // Implementation Note: Uses doc->GetAmbientLight()/SetAmbientLight() wrapper
    //   methods to avoid header include issues (ViewerScene.h causes template errors)
    //
    // Exact MFC Matching: ✅ Complete
    // MFC Reference: AmbientLightDialog.cpp:42-145
    // Ready for runtime testing
    LightAmbientDialog dialog(this);
    dialog.ShowModal();
}

void W3DViewFrame::OnLightScene(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:1604-1610 (OnLightScene), SceneLightDialog.cpp:42-577
    // Function: Configure scene directional light properties (diffuse, specular, intensity, attenuation)
    //
    // VERIFIED: LightSceneDialog_wx matches MFC implementation exactly ✓
    //   Verification Details (Session 40):
    //   ✓ OnInitDialog: Saves initial state, sets slider ranges 0-100, loads from scene light
    //   ✓ OnCancel: Restores all initial values (diffuse, specular, intensity, attenuation, distance)
    //   ✓ OnHscroll: Real-time intensity updates via slider (0-100 range, *100.0f conversion)
    //   ✓ RGB Sliders: Real-time color updates with live preview
    //   ✓ Grayscale mode: All RGB sliders linked when checkbox enabled
    //   ✓ Channel selection: Radio buttons for BOTH/DIFFUSE/SPECULAR channels
    //   ✓ Attenuation: Start/End range controls with spin buttons
    //   ✓ Distance control: Light distance from object with spin button
    //   ✓ Update_Light: Applies to diffuse/specular based on channel selection
    //   ✓ All MFC line references present in code (lines 67, 95, 151, 164, 170, 185, 200, 214)
    //
    // Implementation Status: COMPLETE ✅
    //   Dialog: LightSceneDialog_wx.cpp (XRC-based, fully functional)
    //   Features: Real-time light preview, cancel restore, channel switching, attenuation
    //   Note: Runtime testing recommended but code-level verification confirms exact MFC matching
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
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:2795-2815 (OnIncLight)
    // Function: Increase scene light intensity by 0.05
    //
    // Implemented:
    // ✅ Get scene light from document
    // ✅ Read current diffuse and specular colors
    // ✅ Adjust intensity by +0.05 via Adjust_Light_Intensity helper
    // ✅ Set updated colors back to light
    // ✅ Applies to both diffuse and specular
    //
    // Exact MFC Matching: ✅ Complete
    // Ready for runtime testing
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
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:2766-2786 (OnDecLight)
    // Function: Decrease scene light intensity by 0.05
    //
    // Implemented:
    // ✅ Get scene light from document
    // ✅ Read current diffuse and specular colors
    // ✅ Adjust intensity by -0.05 via Adjust_Light_Intensity helper
    // ✅ Set updated colors back to light
    // ✅ Applies to both diffuse and specular
    //
    // Exact MFC Matching: ✅ Complete
    // Ready for runtime testing
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
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:2863-2872 (OnLightingExpose)
    // Function: Toggle exposure of precalculated lighting
    //
    // Implemented:
    // ✅ Read current prelit exposure state
    // ✅ Toggle prelit exposure via WW3D API
    // ✅ Update handled automatically by WW3D
    //
    // Exact MFC Matching: ✅ Complete
    // Ready for runtime testing
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
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:3677-3689 (OnKillSceneLight)
    // Function: Turn off scene light (set to black)
    //
    // Implemented:
    // ✅ Get scene light from document
    // ✅ Set diffuse to black (0,0,0)
    // ✅ Set specular to black (0,0,0)
    // ✅ Effectively turns off the light
    //
    // Exact MFC Matching: ✅ Complete
    // Ready for runtime testing
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
    // MFC Reference: MainFrm.cpp:1650-1654, TexturePathDialog.cpp:42-100
    // Function: Configure primary and secondary texture search paths for W3D asset loading
    //
    // VERIFIED: TexturePaths_wx matches MFC implementation exactly ✓
    //   Verification Details (Session 40):
    //   ✓ OnInitDialog: Loads Path1 and Path2 from doc->Get_Texture_Path1/2()
    //   ✓ OnOK (TransferDataFromWindow): Saves to doc->Set_Texture_Path1/2()
    //   ✓ OnBrowse1/2: wxDirDialog with initial path, updates text control on OK
    //   ✓ MFC match: GetDlgItemText → GetValue(), SetDlgItemText → SetValue()
    //   ✓ Browse_For_Folder → wxDirDialog with wxDD_DIR_MUST_EXIST flag
    //
    // Implementation Status: COMPLETE ✅
    //   Dialog: TexturePaths_wx.cpp (XRC-based, 2 path controls + browse buttons)
    //   Features: Directory browser, path validation, document integration
    //   Note: Simple dialog with exact MFC behavior replication
    TexturePaths dialog(this);
    dialog.ShowModal();
}

void W3DViewFrame::OnDeviceSelection(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅ COMPLETE
    // MFC Reference: MainFrm.cpp:1656-1660, DeviceSelectionDialog.cpp:42-220
    // Function: Select 3D render device (HAL, REF, etc.) and color depth (16/24-bit)
    //
    // Implemented (RenderDeviceSelector_wx.cpp - 223 lines):
    // ✅ ShowModal() override with registry lookup and dialog skip logic (MFC: DoModal)
    // ✅ OnInitDialog: Device enumeration via WW3D::Get_Render_Device_Count/Name
    // ✅ OnInitDialog: Combo population with client data for device indices
    // ✅ OnInitDialog: Select cached device from wxConfig ("Config/DeviceName")
    // ✅ OnInitDialog: Default to 16bpp checkbox
    // ✅ OnSelchangeRenderDeviceCombo: Calls UpdateDeviceDescription on selection change
    // ✅ UpdateDeviceDescription: Populates all 9 device info fields (FIXED!)
    //   - Device Name, Vendor, Platform
    //   - Driver Name, Vendor, Version
    //   - Hardware Name, Vendor, Chipset
    // ✅ TransferDataFromWindow (OnOK): Extract device index from combo client data
    // ✅ TransferDataFromWindow (OnOK): Extract bits per pixel from checkboxes (16/24)
    // ✅ Registry persistence: wxConfig writes "Config/DeviceName" and "Config/DeviceBitsPerPix"
    // ✅ Shift key check: Hold shift to force dialog display even with cached device
    // ✅ Getters: GetDeviceIndex(), GetBitsPerPixel(), GetDriverName() public accessors
    //
    // StringClass Bug Fixed (Session 40 Part 4):
    //   - Modified rddesc.h: Get_*() methods now call .str() to return const char*
    //   - All 9 device info fields now populate correctly
    //   - No limitations remaining!
    //
    // Exact MFC Matching: ✅ Complete
    // MFC Reference: DeviceSelectionDialog.cpp:42-220
    // wxConfig mapping: Registry "Config/*" → wxConfig("/Config/*") with same key names
    // Ready for runtime testing
    RenderDeviceSelector dialog(this);
    dialog.ShowModal();
}

void W3DViewFrame::OnResolutionSettings(wxCommandEvent &WXUNUSED(event))
{
    // MFC: MainFrm.cpp:1565-1576 (OnChangeResolution - shows dialog for DX8 only)
    // Dialog: ResolutionDialog.cpp:84-236 (OnInitDialog, OnOK, OnDblclkResolutionListCtrl)
    // TODO(MFC-Infrastructure): Full resolution enumeration blocked by rddesc.h StringClass conflicts
    //   Dialog structure complete, fullscreen setting functional
    //   Resolution list population requires RenderDeviceDescClass, ResolutionDescClass access
#ifdef WW3D_DX8
    Resolution dialog(this);
    dialog.ShowModal();
#else
    wxMessageBox("Feature removed during conversion to DX8.",
                 "Unsupported Feature", wxOK | wxICON_EXCLAMATION, this);
#endif
}

void W3DViewFrame::OnEnableGammaCorrection(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:4418-4436 (OnEnableGammaCorrection)
    // Function: Toggle gamma correction enable/disable state
    //
    // Implemented:
    // ✅ Read current enable state from wxConfig
    // ✅ Toggle gamma correction enable/disable
    // ✅ Persist state to wxConfig ("/Config/EnableGamma")
    // ✅ Read gamma value from "/Config/Gamma" (default 10 = 1.0x)
    // ✅ Clamp gamma to valid range (1.0-3.0)
    // ✅ Apply gamma via WW3D::Set_Gamma if enabled
    // ✅ Reset to neutral (1.0) if disabled
    //
    // Exact MFC Matching: ✅ Complete
    // Ready for runtime testing
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
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC: MainFrm.cpp:4441-4451 (OnSetGamma - shows dialog if gamma enabled)
    // 
    // Implemented (Session 40 - GammaDialog_wx.cpp):
    // ✅ Check gamma enable state from wxConfig
    // ✅ Show GammaDialog if enabled, warning message if disabled
    // ✅ GammaDialog fully functional:
    //    - OnInitDialog: Loads gamma from wxConfig (range 10-30 = 1.0-3.0)
    //    - Slider (10-30 range) with real-time preview via WW3D::Set_Gamma
    //    - Display text updates with format "%3.2f"
    //    - OnOK: Saves to wxConfig + applies gamma via WW3D::Set_Gamma
    //    - Calibration instructions (exact MFC text)
    // 
    // Note: Uses WW3D::Set_Gamma wrapper to avoid dx8wrapper.h StringClass conflicts
    // MFC Reference: GammaDialog.cpp:42-96 (OnInitDialog, OnOK, OnReleasedcaptureGammaSlider)
    wxConfigBase *config = wxConfigBase::Get();
    long enableGamma = config->Read("/Config/EnableGamma", 0L);
    
    if (enableGamma) {
        GammaDialog dialog(this);
        dialog.ShowModal();
    } else {
        wxMessageBox("Gamma is disabled.\nEnable in Settings Menu.",
                     "Warning", wxOK | wxICON_WARNING, this);
    }
}

// File menu - Export submenu handlers

void W3DViewFrame::OnExportAggregate(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:2687 (OnSaveAggregate)
    // MFC ID: IDM_SAVE_AGGREGATE (32813)
    // Function: Export aggregate model to .w3d file
    //
    // MFC Implementation:
    //   ((CW3DViewDoc *)GetActiveDocument())->Save_Selected_Aggregate();
    //
    // TODO(MFC-BLOCKED): Requires W3DViewDoc::Save_Selected_Aggregate() method
    //   MFC Reference: W3DViewDoc.cpp:2273-2307 (Save_Selected_Aggregate)
    //   MFC Algorithm:
    //     1. Get render object (m_pCRenderObj != nullptr check)
    //     2. Build default filename from DataTreeView->GetCurrentSelectionName() + ".w3d"
    //     3. Show RestrictedFileDialog with:
    //        - Type: Save (FALSE)
    //        - Filter: "Westwood 3D Files (*.w3d)|*.w3d||"
    //        - Title: "Export Aggregate"
    //        - Flags: OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_EXPLORER
    //     4. If dialog OK: Call Save_Current_Aggregate(path)
    //     5. Save_Current_Aggregate (W3DViewDoc.cpp:2315-2380):
    //        a. Get AggregatePrototypeClass from WW3DAssetManager
    //        b. Get AggregateDefClass from prototype
    //        c. Create FileClass for output
    //        d. Call ChunkSaveClass::Save_Aggregate (agg_save.cpp)
    //        e. Close file, return success/failure
    //
    //   Blocking Dependencies:
    //   1. DataTreeView integration (for GetCurrentSelectionName)
    //   2. Port Save_Selected_Aggregate() to w3dviewdoc_wx.cpp
    //   3. Port Save_Current_Aggregate() to w3dviewdoc_wx.cpp
    //   4. Asset manager integration (GetDisplayedObject, WW3DAssetManager)
    //   
    //   Impact: HIGH PRIORITY - Primary export feature for aggregate models
    //   Note: ChunkSaveClass::Save_Aggregate already exists, just need document methods
    wxMessageBox("Export Aggregate requires DataTreeView integration.\n"
                 "See detailed TODO in OnExportAggregate for MFC implementation.\n\n"
                 "MFC: Calls doc->Save_Selected_Aggregate() which uses DataTreeView.",
                 "Feature Blocked", wxOK | wxICON_INFORMATION, this);
}

void W3DViewFrame::OnExportEmitter(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:2699 (OnSaveEmitter)
    // MFC ID: IDM_SAVE_EMITTER (32810)
    // Function: Export particle emitter to .w3d file
    //
    // MFC Implementation:
    //   ((CW3DViewDoc *)GetActiveDocument())->Save_Selected_Emitter();
    //
    // TODO(MFC-BLOCKED): Requires W3DViewDoc::Save_Selected_Emitter() method
    //   MFC Reference: W3DViewDoc.cpp:2052-2087 (Save_Selected_Emitter)
    //   MFC Algorithm:
    //     1. Check if m_pCRenderObj is ParticleEmitter (Class_ID check)
    //     2. Build default filename from DataTreeView->GetCurrentSelectionName() + ".w3d"
    //     3. Show RestrictedFileDialog with:
    //        - Type: Save (FALSE)
    //        - Filter: "Westwood 3D Files (*.w3d)|*.w3d||"
    //        - Title: "Export Emitter"
    //        - Flags: OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_EXPLORER
    //     4. If dialog OK: Call Save_Current_Emitter(path)
    //     5. Save_Current_Emitter (W3DViewDoc.cpp:2095-2136):
    //        a. Get ParticleEmitterPrototypeClass from WW3DAssetManager
    //        b. Get ParticleEmitterDefClass from prototype
    //        c. Create FileClass for output
    //        d. Call ParticleEmitterDefClass::Save_W3D (emitter save method)
    //        e. Close file, return success/failure
    //
    //   Blocking Dependencies:
    //   1. DataTreeView integration (for GetCurrentSelectionName)
    //   2. Port Save_Selected_Emitter() to w3dviewdoc_wx.cpp
    //   3. Port Save_Current_Emitter() to w3dviewdoc_wx.cpp
    //   4. Asset manager integration (m_pCRenderObj, WW3DAssetManager)
    //   
    //   Impact: MEDIUM PRIORITY - Specialized export for particle effects
    //   Note: ParticleEmitterDefClass::Save_W3D already exists, just need document methods
    wxMessageBox("Export Emitter requires DataTreeView integration.\n"
                 "See detailed TODO in OnExportEmitter for MFC implementation.\n\n"
                 "MFC: Calls doc->Save_Selected_Emitter() which uses DataTreeView.",
                 "Feature Blocked", wxOK | wxICON_INFORMATION, this);
}

void W3DViewFrame::OnExportLOD(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:2523 (OnLODSave)
    // MFC ID: IDM_LOD_SAVE (32794)
    // Function: Export hierarchical LOD (HLOD) model to .w3d file
    //
    // MFC Implementation:
    //   CW3DViewDoc *pdoc = (CW3DViewDoc *)GetActiveDocument();
    //   if (pdoc != nullptr) pdoc->Save_Selected_LOD();
    //
    // TODO(MFC-BLOCKED): Requires W3DViewDoc::Save_Selected_LOD() method
    //   MFC Reference: W3DViewDoc.cpp:1724-1759 (Save_Selected_LOD)
    //   MFC Algorithm:
    //     1. Check if m_pCRenderObj is HLOD (Class_ID == CLASSID_HLOD)
    //     2. Build default filename from DataTreeView->GetCurrentSelectionName() + ".w3d"
    //     3. Show RestrictedFileDialog with:
    //        - Type: Save (FALSE)
    //        - Filter: "Westwood 3D Files (*.w3d)|*.w3d||"
    //        - Title: "Export LOD"
    //        - Flags: OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_EXPLORER
    //     4. If dialog OK: Call Save_Current_LOD(path)
    //     5. Save_Current_LOD (W3DViewDoc.cpp:1767-1806):
    //        a. Get HLodPrototypeClass from WW3DAssetManager
    //        b. Get HLodDefClass from prototype
    //        c. Create FileClass for output
    //        d. Call HLodDefClass::Save (ChunkSaveClass) to serialize all LOD levels
    //        e. Close file, return success/failure
    //
    //   Blocking Dependencies:
    //   1. DataTreeView integration (for GetCurrentSelectionName)
    //   2. Port Save_Selected_LOD() to w3dviewdoc_wx.cpp
    //   3. Port Save_Current_LOD() to w3dviewdoc_wx.cpp
    //   4. Asset manager integration (m_pCRenderObj, WW3DAssetManager)
    //   
    //   Impact: HIGH PRIORITY - Critical for LOD workflow
    //   Note: HLodDefClass::Save already exists, just need document methods
    wxMessageBox("Export LOD requires DataTreeView integration.\n"
                 "See detailed TODO in OnExportLOD for MFC implementation.\n\n"
                 "MFC: Calls doc->Save_Selected_LOD() which uses DataTreeView.",
                 "Feature Blocked", wxOK | wxICON_INFORMATION, this);
}

void W3DViewFrame::OnExportPrimitive(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:4073-4078 (OnExportPrimitive), W3DViewDoc.cpp:2510-2636
    // Function: Export selected primitive (sphere/ring) to W3D file
    //
    // TODO(MFC-BLOCKED): Requires Save_Selected_Primitive() + Save_Current_Sphere/Ring()
    //   MFC Algorithm (W3DViewDoc.cpp:2510-2636):
    //   
    //   Frame Handler (MainFrm.cpp:4073-4078):
    //     → doc->Save_Selected_Primitive()
    //   
    //   Save_Selected_Primitive() (W3DViewDoc.cpp:2510-2555):
    //     1. Verify object: (m_pCRenderObj != nullptr) AND
    //        (Class_ID() == CLASSID_SPHERE OR Class_ID() == CLASSID_RING)
    //     2. Build default filename from selection:
    //        - default_filename = GetDataTreeView()->GetCurrentSelectionName() + ".w3d"
    //     3. RestrictedFileDialogClass(FALSE, ".w3d", default_filename,
    //        OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_EXPLORER,
    //        "Westwood 3D Files (*.w3d)|*.~xyzabc||")
    //     4. Set dialog title based on type:
    //        - If CLASSID_SPHERE: lpstrTitle = "Export Sphere"
    //        - If CLASSID_RING: lpstrTitle = "Export Ring"
    //     5. If dialog.DoModal() == IDOK:
    //        - If CLASSID_SPHERE: Save_Current_Sphere(dialog.GetPathName())
    //        - If CLASSID_RING: Save_Current_Ring(dialog.GetPathName())
    //   
    //   Save_Current_Sphere() (W3DViewDoc.cpp:2563-2594):
    //     1. proto = WW3DAssetManager::Get_Instance()->Find_Prototype(m_pCRenderObj->Get_Name())
    //     2. Cast to SpherePrototypeClass*
    //     3. file = _TheFileFactory->Get_File(filename)
    //     4. file->Open(FileClass::WRITE)
    //     5. ChunkSaveClass csave(file)
    //     6. proto->Save(csave)
    //     7. file->Close(), _TheFileFactory->Return_File(file)
    //   
    //   Save_Current_Ring() (W3DViewDoc.cpp:2602-2633):
    //     1. proto = WW3DAssetManager::Get_Instance()->Find_Prototype(m_pCRenderObj->Get_Name())
    //     2. Cast to RingPrototypeClass*
    //     3. file = _TheFileFactory->Get_File(filename)
    //     4. file->Open(FileClass::WRITE)
    //     5. ChunkSaveClass csave(file)
    //     6. proto->Save(csave)
    //     7. file->Close(), _TheFileFactory->Return_File(file)
    //
    //   Common Pattern (Export Primitive):
    //     • Selection → Class_ID check → Default filename from tree
    //     • File dialog (type-specific title) → Save
    //     • Find_Prototype → Get definition → ChunkSaveClass serialization
    //
    //   Blocking Factors:
    //     1. DataTreeView: GetCurrentSelectionName() for default filename
    //     2. W3DViewDoc methods: Save_Selected_Primitive(), Save_Current_Sphere(), Save_Current_Ring()
    //     3. m_pCRenderObj access from W3DViewDoc
    //
    //   Implementation Priority: LOW
    //     - Specialized feature for primitive-only export
    //     - Less common workflow than general export
    //
    //   Related Handlers:
    //     - OnExportEmitter (similar pattern, already documented)
    //     - OnUpdateExportPrimitive: Enable when m_currentAssetType == TypePrimitives
    wxMessageBox("Export Primitive requires Save_Selected_Primitive() method.\n"
                 "See TODO in OnExportPrimitive for implementation details.",
                 "Feature Blocked", wxOK | wxICON_INFORMATION, this);
}

void W3DViewFrame::OnExportSoundObject(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:4157-4162 (OnExportSoundObj), W3DViewDoc.cpp:2641-2722
    // Function: Export selected sound object (3D positioned audio source) to W3D file
    //
    // TODO(MFC-BLOCKED): Requires Save_Selected_Sound_Object() + Save_Current_Sound_Object()
    //   MFC Algorithm (W3DViewDoc.cpp:2641-2722):
    //   
    //   Frame Handler (MainFrm.cpp:4157-4162):
    //     → doc->Save_Selected_Sound_Object()
    //   
    //   Save_Selected_Sound_Object() (W3DViewDoc.cpp:2641-2680):
    //     1. Verify object: (m_pCRenderObj != nullptr) AND
    //        (m_pCRenderObj->Class_ID() == RenderObjClass::CLASSID_SOUND)
    //     2. Build default filename from selection:
    //        - default_filename = GetDataTreeView()->GetCurrentSelectionName() + ".w3d"
    //     3. RestrictedFileDialogClass(FALSE, ".w3d", default_filename,
    //        OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_EXPLORER,
    //        "Westwood 3D Files (*.w3d)|*.~xyzabc||")
    //     4. Set dialog title: lpstrTitle = "Export Sound Object"
    //     5. If dialog.DoModal() == IDOK:
    //        - Save_Current_Sound_Object(dialog.GetPathName())
    //   
    //   Save_Current_Sound_Object() (W3DViewDoc.cpp:2688-2722):
    //     1. proto = WW3DAssetManager::Get_Instance()->Find_Prototype(m_pCRenderObj->Get_Name())
    //     2. Cast to SoundRenderObjPrototypeClass*
    //     3. definition = proto->Peek_Definition()
    //     4. ASSERT(definition != nullptr)
    //     5. file = _TheFileFactory->Get_File(filename)
    //     6. file->Open(FileClass::WRITE)
    //     7. ChunkSaveClass csave(file)
    //     8. definition->Save(csave)  // Note: Saves definition, not prototype
    //     9. file->Close(), _TheFileFactory->Return_File(file)
    //
    //   Difference from Sphere/Ring Export:
    //     • Sound objects save definition->Save() instead of proto->Save()
    //     • Uses Peek_Definition() to get SoundRenderObjDefClass*
    //     • Sound object contains: audio filename, volume, falloff distance,
    //       positional audio flags, 3D spatialization settings
    //
    //   Common Pattern (Export Sound):
    //     • Selection → CLASSID_SOUND check → Default filename from tree
    //     • File dialog ("Export Sound Object") → Save
    //     • Find_Prototype → Peek_Definition → ChunkSaveClass serialization
    //
    //   Blocking Factors:
    //     1. DataTreeView: GetCurrentSelectionName() for default filename
    //     2. W3DViewDoc methods: Save_Selected_Sound_Object(), Save_Current_Sound_Object()
    //     3. m_pCRenderObj access from W3DViewDoc
    //
    //   Implementation Priority: LOW
    //     - Specialized feature for sound object-only export
    //     - Sound objects are less common than meshes/hierarchies
    //     - Useful for exporting 3D positioned audio sources
    //
    //   Related Handlers:
    //     - OnExportPrimitive (similar pattern)
    //     - OnExportEmitter (similar pattern)
    //     - OnUpdateExportSoundObject: Enable when m_currentAssetType == TypeSound
    wxMessageBox("Export Sound Object requires Save_Selected_Sound_Object() method.\n"
                 "See TODO in OnExportSoundObject for implementation details.",
                 "Feature Blocked", wxOK | wxICON_INFORMATION, this);
}

// Object menu handlers

void W3DViewFrame::OnObjectRestrictAnims(wxCommandEvent &event)
{
    // MFC Reference: MainFrm.cpp:4252-4264 (OnRestrictAnims)
    // MFC ID: IDM_RESTRICT_ANIMS (32875)
    // Function: Toggle animation restriction mode (filters animations based on hierarchy)
    // TODO(MFC-BLOCKED): Requires DataTreeView integration
    //   MFC Implementation:
    //     CDataTreeView *data_tree = ::GetCurrentDocument()->GetDataTreeView();
    //     if (data_tree != nullptr) {
    //         bool enabled = data_tree->Are_Anims_Restricted();
    //         data_tree->Restrict_Anims(!enabled);
    //     }
    //   
    //   Blocking Dependencies:
    //   1. Implement DataTreeView widget in wxWidgets
    //      - Port CDataTreeView class from DataTreeView.cpp
    //      - Tree control for browsing W3D assets (meshes, animations, sounds, etc.)
    //      - Handles asset selection and display
    //   2. Add GetDataTreeView() method to W3DViewDoc
    //      - Returns pointer to tree view widget
    //   3. Port Are_Anims_Restricted() and Restrict_Anims() to DataTreeView
    //      - Are_Anims_Restricted(): Returns current restriction state (bool)
    //      - Restrict_Anims(bool): Sets restriction mode
    //      - When enabled, filters animations that don't match current hierarchy
    //   4. Implement OnUpdateObjectRestrictAnims to show checkmark state
    //   
    //   Impact: MEDIUM PRIORITY - Animation workflow feature
    //   Note: This is a complex feature requiring significant UI infrastructure
    wxMessageBox("Restrict Anims requires DataTreeView integration.\n"
                 "See TODO in OnObjectRestrictAnims for implementation details.",
                 "Feature Blocked", wxOK | wxICON_INFORMATION, this);
}

void W3DViewFrame::OnUpdateObjectRestrictAnims(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:4274-4286 (OnUpdateRestrictAnims)
    // TODO(MFC-BLOCKED): Requires DataTreeView integration
    //   MFC Implementation:
    //     bool check = true;
    //     CDataTreeView *data_tree = ::GetCurrentDocument()->GetDataTreeView();
    //     if (data_tree != nullptr) {
    //         check = data_tree->Are_Anims_Restricted();
    //     }
    //     pCmdUI->SetCheck(check);
    //   
    //   Once DataTreeView is ported, update as:
    //     W3DViewDoc *doc = GetDocument();
    //     if (doc && doc->GetDataTreeView()) {
    //         event.Check(doc->GetDataTreeView()->Are_Anims_Restricted());
    //     } else {
    //         event.Check(false);
    //     }
    event.Check(false); // Default to unchecked until DataTreeView implemented
}

// File menu handlers

void W3DViewFrame::OnMungeSortOnLoad(wxCommandEvent &event)
{
    // MFC Reference: MainFrm.cpp:4397-4405 (OnMungeSortOnLoad)
    // MFC ID: IDM_MUNGE_SORT_ON_LOAD (32897)
    // Function: Toggle whether loaded W3D models are automatically munged (sorted)
    // Munging sorts mesh data for optimal rendering performance
    
    // Toggle WW3D munge sort state
    bool currentState = WW3D::Is_Munge_Sort_On_Load_Enabled();
    bool newState = !currentState;
    WW3D::Enable_Munge_Sort_On_Load(newState);
    
    // Persist to wxConfig
    wxConfig::Get()->Write("/Config/MungeSortOnLoad", newState ? 1L : 0L);
    wxConfig::Get()->Flush();
}

void W3DViewFrame::OnUpdateMungeSortOnLoad(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:4407-4411 (OnUpdateMungeSortOnLoad)
    // Show checkmark based on WW3D munge sort state
    event.Check(WW3D::Is_Munge_Sort_On_Load_Enabled());
}

void W3DViewFrame::OnEnableGammaCorrectionFile(wxCommandEvent &event)
{
    // MFC Reference: MainFrm.cpp:4418-4436 (OnEnableGammaCorrection)
    // MFC ID: IDM_ENABLE_GAMMA_CORRECTION (32898)
    // Function: Toggle gamma correction enable/disable
    // When enabled, applies gamma value from config (range 1.0-3.0)
    // When disabled, resets gamma to 1.0 (linear/no correction)
    
    wxConfigBase *config = wxConfig::Get();
    long enableGamma = config->Read("/Config/EnableGamma", 0L);
    bool newState = (enableGamma == 0);
    
    // Save new state
    config->Write("/Config/EnableGamma", newState ? 1L : 0L);
    config->Flush();
    
    // Apply gamma correction via WW3D
    if (newState) {
        // Read gamma value (stored as integer * 10, default 1.0 = 10)
        long gammaInt = config->Read("/Config/Gamma", 10L);
        float gamma = gammaInt / 10.0f;
        
        // Clamp to valid range
        if (gamma < 1.0f) gamma = 1.0f;
        if (gamma > 3.0f) gamma = 3.0f;
        
        // Apply gamma correction (brightness=0, contrast=1)
        WW3D::Set_Gamma(gamma, 0.0f, 1.0f);
    } else {
        // Disable gamma (reset to linear 1.0)
        WW3D::Set_Gamma(1.0f, 0.0f, 1.0f);
    }
}

void W3DViewFrame::OnUpdateEnableGammaCorrectionFile(wxUpdateUIEvent &event)
{
    // MFC Reference: MainFrm.cpp:4438-4442 (OnUpdateEnableGammaCorrection)
    // Show checkmark when gamma correction is enabled
    wxConfigBase *config = wxConfig::Get();
    long enableGamma = config->Read("/Config/EnableGamma", 0L);
    event.Check(enableGamma != 0);
}

void W3DViewFrame::OnSaveSettings(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:3603-3609 (OnSaveSettings)
    // MFC ID: IDM_SAVE_SETTINGS (32796)
    // Function: Save application settings to INI file
    // Dialog: SaveSettings_wx.cpp (XRC-based, converted from MFC)
    //
    // TODO(MFC-Implement): Implement settings save logic
    //   BLOCKED BY: W3DViewDoc::SaveSettings() method not yet implemented
    //
    // MFC Implementation Flow:
    //   1. Show SaveSettings dialog (MainFrm.cpp:3605-3606)
    //   2. Dialog collects user preferences:
    //      - Checkboxes: Lighting, Background, Camera (what to save)
    //      - Filename text box + browse button (.dat file)
    //   3. On OK, dialog calls (SaveSettingsDialog.cpp:209-227):
    //      pCDoc->SaveSettings(filename, dwSettingsMask);
    //
    // Settings Mask Flags (SaveSettingsDialog.cpp):
    //   - SAVE_SETTINGS_LIGHT = 0x1 (save lighting if checked)
    //   - SAVE_SETTINGS_BACK = 0x2 (save background if checked)
    //   - SAVE_SETTINGS_CAMERA = 0x4 (save camera if checked)
    //
    // W3DViewDoc::SaveSettings Implementation (W3DViewDoc.cpp:1793-1910):
    //   Uses INIClass to write settings to file [Settings] section:
    //   - If LIGHT flag: AmbientLightR/G/B, SceneLightR/G/B, orientation, distance, etc.
    //   - If BACK flag: BackgroundColorR/G/B, BackgroundBmp, BackgroundObject
    //   - If CAMERA flag: CameraX/Y/Z, CameraOriginX/Y/Z, CameraUpX/Y/Z
    //
    // REQUIRED INFRASTRUCTURE:
    //   1. SaveSettings_wx dialog needs:
    //      - Browse button handler (wxFileDialog with .dat filter)
    //      - OK handler to extract checkbox states
    //   2. W3DViewDoc::SaveSettings(filename, mask) method
    //   3. INIClass integration (or wxFileConfig as alternative)
    //
    // COMPLEXITY: HIGH
    //   - Dialog button wiring (browse button)
    //   - File I/O with INI format (30+ keys)
    //   - Scene/lighting/camera state extraction
    //
    // Impact: High - important workflow feature for saving work environment
    // Priority: MEDIUM - companion to Load Settings
    
    SaveSettings dialog(this);
    if (dialog.ShowModal() == wxID_OK) {
        // TODO(MFC-Implement): Implement dialog logic
        //   1. Wire up browse button to wxFileDialog
        //   2. Extract checkbox states (lighting, background, camera)
        //   3. Get filename from text control
        //   4. Call W3DViewDoc::SaveSettings(filename, settingsMask)
        //   5. SaveSettings writes INI file with selected sections
        wxMessageBox("Settings save logic not yet implemented.\n\n"
                     "Requires:\n"
                     "- SaveSettings dialog browse button wiring\n"
                     "- W3DViewDoc::SaveSettings(filename, mask) method\n\n"
                     "See comprehensive TODO in code.",
                     "Feature Incomplete", wxOK | wxICON_INFORMATION, this);
    }
}

void W3DViewFrame::OnLoadSettings(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:3616-3636 (OnLoadSettings)
    // MFC ID: IDM_LOAD_SETTINGS (32797)
    // Function: Load application settings from INI file
    //
    // TODO(MFC-Implement): Implement settings load functionality
    //   BLOCKED BY: W3DViewDoc::LoadSettings() method not yet implemented
    //
    // MFC Implementation Flow (MainFrm.cpp:3616-3636):
    //   1. Show file dialog:
    //      - Default extension: ".dat"
    //      - Filter: "Settings data files (*.dat)|*.dat||"
    //      - Flags: OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_EXPLORER
    //   2. Call document method: pCDoc->LoadSettings(openFileDialog.GetPathName())
    //
    // W3DViewDoc::LoadSettings Implementation (W3DViewDoc.cpp:1910-2100+):
    //   Uses INIClass to parse settings file with sections and keys:
    //
    //   [Settings] Section:
    //     - AmbientLightR/G/B (float) - Ambient light color RGB
    //     - SceneLightR/G/B (float) - Scene light color RGB
    //     - SceneLightX/Y/Z/W (float) - Scene light orientation (quaternion)
    //     - SceneLightDistance (float) - Distance from object center
    //     - SceneLightIntensity (float) - Light intensity multiplier
    //     - SceneLightAttenStart/End (float) - Attenuation range
    //     - SceneLightAttenOn (bool) - Enable attenuation
    //     - BackgroundColorR/G/B (float) - Background clear color RGB
    //     - BackgroundBmp (string) - Background bitmap filename
    //     - BackgroundObject (string) - Background object filename
    //     - CameraX/Y/Z (float) - Camera position
    //     - CameraOriginX/Y/Z (float) - Camera look-at point
    //     - CameraUpX/Y/Z (float) - Camera up vector
    //     - And more...
    //
    // REQUIRED INFRASTRUCTURE:
    //   1. W3DViewDoc::LoadSettings(filename) - Main loading method
    //   2. INIClass integration (or wxFileConfig as alternative)
    //   3. Scene/lighting/camera access from document
    //
    // COMPLEXITY: HIGH
    //   - Complex file parsing (30+ settings keys)
    //   - Camera/lighting/background state management
    //   - Coordinate transformations for light positioning
    //
    // Impact: High - important workflow feature for saving/restoring work environment
    // Priority: MEDIUM - requires significant infrastructure
    
    wxFileDialog dialog(this, "Load Settings", "", "",
                       "Settings data files (*.dat)|*.dat|All files (*.*)|*.*",
                       wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    
    if (dialog.ShowModal() == wxID_OK) {
        wxString filename = dialog.GetPath();
        // TODO(MFC-Implement): Implement W3DViewDoc::LoadSettings(filename)
        //   Parse INI file with sections: [Settings]
        //   Apply values to scene (ambient light, scene light, background)
        //   Apply values to camera (position, orientation, up vector)
        //   4. Refresh viewport/UI
        wxMessageBox(wxString::Format("Load Settings not yet implemented.\nSelected file: %s\nFile parsing and apply logic pending.",
                                      filename),
                     "Feature Incomplete", wxOK | wxICON_INFORMATION, this);
    }
}

void W3DViewFrame::OnImportFacialAnims(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:2090-2149 (OnImportFacialAnims)
    // MFC ID: IDM_IMPORT_FACIAL_ANIMS (32874)
    // Function: Import facial animation description files (.txt) for current hierarchy
    //
    // TODO(MFC-Implement): Implement facial animation import
    //   BLOCKED BY: Multiple document/tree methods not yet implemented
    //
    // MFC Implementation Flow (MainFrm.cpp:2090-2149):
    //   1. Get current hierarchy: const HTreeClass *htree = doc->Get_Current_HTree();
    //   2. Show file dialog: 
    //      - Filter: "Animation Description (*.txt)|*.txt||"
    //      - Flags: OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT
    //   3. For each selected file:
    //      - Call: doc->Import_Facial_Animation(htree->Get_Name(), filename);
    //   4. Refresh asset tree:
    //      - CDataTreeView *data_tree = doc->GetDataTreeView();
    //      - data_tree->LoadAssetsIntoTree();
    //
    // REQUIRED INFRASTRUCTURE:
    //   1. W3DViewDoc::Get_Current_HTree() - Returns currently selected hierarchy
    //   2. W3DViewDoc::Import_Facial_Animation(htree_name, filename) - Imports anim file
    //   3. W3DViewDoc::GetDataTreeView() - Returns tree control for refresh
    //   4. W3DViewTreeCtrl::LoadAssetsIntoTree() - Refreshes tree with new assets
    //
    // OnUpdateImportFacialAnims (MainFrm.cpp:2158-2173):
    //   - Enables only if current hierarchy exists: pCmdUI->Enable(htree != nullptr)
    //
    // COMPLEXITY: HIGH
    //   - Needs hierarchy selection tracking (requires DataTreeView)
    //   - Needs facial animation import logic (W3D animation parsing)
    //   - Needs asset tree refresh
    //
    // Impact: Medium - specialized feature for character facial animation
    // Priority: LOW - complex infrastructure dependency
    wxMessageBox("Import Facial Anims not yet implemented.\n\n"
                 "Requires:\n"
                 "- Document methods: Get_Current_HTree(), Import_Facial_Animation()\n"
                 "- DataTreeView integration for asset refresh\n\n"
                 "See comprehensive TODO in code.",
                 "Feature Blocked", wxOK | wxICON_INFORMATION, this);
}

void W3DViewFrame::OnTexturePathFile(wxCommandEvent &WXUNUSED(event))
{
    // MFC: MainFrm.cpp (same as OnTexturePathSettings)
    // MFC ID: IDM_TEXTURE_PATH (in File menu, not Settings)
    // Function: Opens texture path configuration dialog
    // Note: Handler already exists as OnTexturePathSettings, just reusing
    TexturePaths dialog(this);
    dialog.ShowModal();
}

void W3DViewFrame::OnAnimatedSoundOptions(wxCommandEvent &WXUNUSED(event))
{
    // IMPLEMENTATION STATUS: FUNCTIONAL ✅
    // MFC Reference: MainFrm.cpp:OnEditAnimatedSoundsOptions
    // MFC ID: IDM_EDIT_ANIMATED_SOUNDS_OPTIONS (32900)
    //
    // Implemented (AnimatedSoundDialog_wx.cpp - 268 lines):
    // ✅ OnInitDialog: Loads 3 config paths from wxConfig
    // ✅ OnSoundDefinitionLibraryBrowseButton: File dialog for *.ddb files
    // ✅ OnSoundIniBrowseButton: File dialog for *.ini files
    // ✅ OnSoundPathBrowseButton: Directory dialog for sound path
    // ✅ TransferDataFromWindow: Saves all 3 paths to wxConfig
    // ✅ Load_Animated_Sound_Settings(): Engine integration (lines 212-268)
    // ✅ Config keys match MFC exactly:
    //   - Config/SoundDefLibPath (MFC: "Config", "SoundDefLibPath")
    //   - Config/AnimSoundINIPath (MFC: "Config", "AnimSoundINIPath")
    //   - Config/AnimSoundDataPath (MFC: "Config", "AnimSoundDataPath")
    //
    // TODO(MFC-Runtime-Test-LOW): Runtime verification recommended
    //   - Verify dialog displays correctly
    //   - Test file browsing (*.ddb, *.ini, directory)
    //   - Confirm sound library loads with valid files
    //   Priority: LOW (code-level verification complete)
    //
    // Exact MFC Matching: ✅ Complete
    // MFC Reference: MainFrm.cpp, AnimatedSoundDialog.cpp
    // Ready for runtime testing
    AnimatedSoundDialog dialog(this);
    dialog.ShowModal();
}

// Emitters menu handlers

void W3DViewFrame::OnCreateEmitter(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:2179-2198 (OnCreateEmitter)
    // MFC ID: IDM_CREATE_EMITTER (32808)
    // Function: Create a new particle emitter and show property sheet for configuration
    //
    // MFC Implementation:
    //   1. Clear current display: pdoc->DisplayObject((RenderObjClass *)nullptr);
    //   2. Show EmitterPropertySheetClass modal dialog:
    //      - Constructor: EmitterPropertySheetClass(nullptr, IDS_EMITTER_PROP_TITLE, this)
    //      - nullptr = creating new emitter (not editing existing)
    //      - Title resource: IDS_EMITTER_PROP_TITLE
    //   3. Dialog has multiple pages (EmitterPropertySheet.h):
    //      - General properties (EmitterGeneralPropPage)
    //      - Particle properties (EmitterParticlePropPage)
    //      - Physics properties (EmitterPhysicsPropPage)
    //      - Color properties (EmitterColorPropPage)
    //      - Rotation properties (EmitterRotationPropPage)
    //      - Size properties (EmitterSizePropPage)
    //      - Frame properties (EmitterFramePropPage)
    //      - Line properties (EmitterLinePropPage/LineGroupPropPage)
    //      - User properties (EmitterUserPropPage)
    //
    // TODO(MFC-COMPLEX): Implement emitter creation with property sheet
    //   Required Infrastructure:
    //   1. Port EmitterPropertySheet as wxPropertySheetDialog (or notebook-based dialog)
    //   2. Wire up all 9 property pages (already exist in dialogs/PropPageEmitter*.cpp)
    //   3. Implement OK handler to create ParticleEmitterDefClass from property values
    //   4. Add emitter to scene and display it
    //   5. Integrate with document for persistence
    //
    //   Emitter Property Sheet Pages (all exist in dialogs/):
    //   ✓ PropPageEmitterGen_wx.cpp (General: name, type, emission rate)
    //   ✓ PropPageEmitterParticle_wx.cpp (Particle: shader, texture, blend mode)
    //   ✓ PropPageEmitterPhysics_wx.cpp (Physics: velocity, gravity, drag)
    //   ✓ PropPageEmitterColor_wx.cpp (Color: start/end colors, gradients)
    //   ✓ PropPageEmitterRotation_wx.cpp (Rotation: spin, tumble)
    //   ✓ PropPageEmitterSize_wx.cpp (Size: start/end size, scaling)
    //   ✓ PropPageEmitterFrame_wx.cpp (Frame: animation frames)
    //   ✓ PropPageEmitterLineprops_wx.cpp (Line: line rendering properties)
    //   ✓ PropPageEmitterLinegroup_wx.cpp (Line Group: multiple lines)
    //   ✓ PropPageEmitterUser_wx.cpp (User: custom user data)
    //
    //   Impact: HIGH PRIORITY - Core feature for particle effects workflow
    //   Complexity: HIGH - Multi-page dialog with extensive property handling
    //   Note: All individual property pages already converted to wxWidgets
    wxMessageBox("Create Emitter not yet implemented.\n\n"
                 "MFC: Shows EmitterPropertySheet with 9 property pages.\n"
                 "All property pages exist in dialogs/ but parent sheet needs implementation.\n\n"
                 "See detailed TODO in OnCreateEmitter.",
                 "Feature Incomplete", wxOK | wxICON_INFORMATION, this);
}

void W3DViewFrame::OnScaleEmitter(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:2046-2063 (OnScaleEmitter)
    // MFC ID: IDM_SCALE_EMITTER (32884)
    // Function: Scale all properties of selected particle emitter by a single factor
    //
    // TODO(MFC-Implement): Implement emitter scaling
    //   BLOCKED BY: ScaleDialog_wx not yet ported
    //
    // MFC Implementation Flow (MainFrm.cpp:2046-2063):
    //   1. Get document: CW3DViewDoc *pdoc = GetActiveDocument();
    //   2. Show scale dialog:
    //      ScaleDialogClass dlg(1.0, this, "Enter the scaling factor you want to apply to the current particle emitter");
    //      if (dlg.DoModal() == IDCANCEL) return;
    //      float scale = dlg.Get_Scale();
    //   3. Get displayed emitter:
    //      ParticleEmitterClass *emitter = (ParticleEmitterClass *)pdoc->GetDisplayedObject();
    //   4. Scale emitter:
    //      emitter->Scale(scale);
    //
    // REQUIRED INFRASTRUCTURE:
    //   1. ScaleDialog_wx - Simple dialog with:
    //      - Float text input for scale factor (default: 1.0)
    //      - Prompt text (passed to constructor)
    //      - Get_Scale() method to retrieve value
    //      - OK/Cancel buttons
    //   2. W3DViewDoc::GetDisplayedObject() - Returns currently displayed render object
    //
    // COMPLEXITY: LOW
    //   - Simple dialog (single float input)
    //   - Single API call: emitter->Scale(factor)
    //
    // Impact: Medium - useful for quickly adjusting emitter scale
    // Priority: LOW - nice-to-have utility feature
    wxMessageBox("Scale Emitter not yet implemented.\n\n"
                 "Requires:\n"
                 "- ScaleDialog_wx (simple float input dialog)\n"
                 "- Calls ParticleEmitterClass::Scale(factor)\n\n"
                 "See comprehensive TODO in code.",
                 "Feature Incomplete", wxOK | wxICON_INFORMATION, this);
}

void W3DViewFrame::OnEditEmitter(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:2070-2088 (OnEditEmitter)
    // MFC ID: IDM_EDIT_EMITTER (32809)
    // Function: Edit properties of currently displayed particle emitter
    // Note: Keyboard shortcut is Enter (same as Object->Properties)
    //
    // TODO(MFC-Implement): Implement emitter property sheet
    //   BLOCKED BY: EmitterPropertySheet_wx wrapper not yet created
    //
    // MFC Implementation Flow (MainFrm.cpp:2070-2088):
    //   1. Get document: CW3DViewDoc *pdoc = GetActiveDocument();
    //   2. Get displayed emitter:
    //      ParticleEmitterClass *emitter = (ParticleEmitterClass *)pdoc->GetDisplayedObject();
    //   3. Create emitter instance list:
    //      EmitterInstanceListClass *instance_list = new EmitterInstanceListClass;
    //      instance_list->Add_Emitter(emitter);
    //   4. Show property sheet:
    //      EmitterPropertySheetClass prop_sheet(instance_list, IDS_EMITTER_PROP_TITLE, this);
    //      prop_sheet.DoModal();
    //
    // REQUIRED INFRASTRUCTURE:
    //   1. EmitterPropertySheet_wx wrapper - wxPropertySheetDialog containing:
    //      - Multiple property pages (EmitterInstancePropPage_wx already exists!)
    //      - Pages cover: General, Emission, Physics, Appearance, etc.
    //      - Constructor: (EmitterInstanceListClass*, title, parent)
    //   2. EmitterInstanceListClass - Already exists in W3D library
    //   3. W3DViewDoc::GetDisplayedObject() - Returns currently displayed render object
    //
    // COMPLEXITY: MEDIUM
    //   - Property sheet wrapper needed (similar to AdvancedAnimSheet pattern)
    //   - EmitterInstancePropPage_wx already ported!
    //   - Just need wrapper to host the property page
    //
    // Impact: High - primary editing interface for particle emitters
    // Priority: MEDIUM - important feature for emitter workflow
    wxMessageBox("Edit Emitter not yet implemented.\n\n"
                 "Requires:\n"
                 "- EmitterPropertySheet_wx wrapper (wxPropertySheetDialog)\n"
                 "- EmitterInstancePropPage_wx already exists!\n\n"
                 "See comprehensive TODO in code.",
                 "Feature Incomplete", wxOK | wxICON_INFORMATION, this);
}

// Primitives menu handlers

void W3DViewFrame::OnCreateSphere(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:3069-3085 (OnCreateSphere)
    // MFC ID: IDM_CREATE_SPHERE (32866)
    // Function: Create a sphere primitive and show property sheet for configuration
    //
    // MFC Implementation:
    //   1. Clear current display: doc->DisplayObject((RenderObjClass *)nullptr);
    //   2. Show SpherePropertySheetClass modal dialog:
    //      - Constructor: SpherePropertySheetClass(nullptr, IDS_SPHERE_PROP_TITLE, this)
    //      - nullptr = creating new sphere (not editing existing)
    //      - Title resource: IDS_SPHERE_PROP_TITLE
    //   3. Dialog has multiple pages (SpherePropertySheet.h):
    //      - General properties (SphereGeneralPropPage)
    //      - Color properties (SphereColorPropPage)
    //      - Scale properties (SphereScalePropPage)
    //
    // TODO(MFC-COMPLEX): Implement sphere creation with property sheet
    //   Required Infrastructure:
    //   1. Port SpherePropertySheet as wxPropertySheetDialog (or notebook-based dialog)
    //   2. Wire up all 3 property pages:
    //      ✓ PropPageSphereGen_wx.cpp exists (General: radius, segments, name)
    //      ✓ PropPageSphereColor_wx.cpp exists (Color: material, texturing)
    //      ✓ PropPageSphereScale_wx.cpp exists (Scale: uniform/non-uniform scaling)
    //   3. Implement OK handler to generate sphere mesh from property values
    //   4. Add sphere to scene and display it
    //   5. Integrate with document for persistence
    //
    //   Impact: MEDIUM PRIORITY - Useful for placeholder geometry and testing
    //   Complexity: MEDIUM - Multi-page dialog with procedural mesh generation
    //   Note: All 3 property pages already converted to wxWidgets (see dialogs/PropPageSphere*.cpp)
    wxMessageBox("Create Sphere not yet implemented.\n\n"
                 "MFC: Shows SpherePropertySheet with 3 property pages.\n"
                 "All property pages exist in dialogs/ but parent sheet needs implementation.\n\n"
                 "See detailed TODO in OnCreateSphere.",
                 "Feature Incomplete", wxOK | wxICON_INFORMATION, this);
}

void W3DViewFrame::OnCreateRing(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:3095-3111 (OnCreateRing)
    // MFC ID: IDM_CREATE_RING (32867)
    // Function: Create a ring/torus primitive and show property sheet for configuration
    //
    // MFC Implementation:
    //   1. Clear current display: doc->DisplayObject((RenderObjClass *)nullptr);
    //   2. Show RingPropertySheetClass modal dialog:
    //      - Constructor: RingPropertySheetClass(nullptr, IDS_RING_PROP_TITLE, this)
    //      - nullptr = creating new ring (not editing existing)
    //      - Title resource: IDS_RING_PROP_TITLE
    //   3. Dialog has multiple pages (RingPropertySheet.h):
    //      - General properties (RingGeneralPropPage)
    //      - Color properties (RingColorPropPage)
    //      - Scale properties (RingScalePropPage)
    //
    // TODO(MFC-COMPLEX): Implement ring creation with property sheet
    //   Required Infrastructure:
    //   1. Port RingPropertySheet as wxPropertySheetDialog (or notebook-based dialog)
    //   2. Wire up all 3 property pages:
    //      ✓ PropPageRingGen_wx.cpp exists (General: inner/outer radius, segments, name)
    //      ✓ PropPageRingColor_wx.cpp exists (Color: material, texturing)
    //      ✓ PropPageRingScale_wx.cpp exists (Scale: uniform/non-uniform scaling)
    //   3. Implement OK handler to generate ring mesh from property values
    //   4. Add ring to scene and display it
    //   5. Integrate with document for persistence
    //
    //   Impact: MEDIUM PRIORITY - Useful for special effects (halos, shields, portals)
    //   Complexity: MEDIUM - Multi-page dialog with procedural mesh generation
    //   Note: All 3 property pages already converted to wxWidgets (see dialogs/PropPageRing*.cpp)
    wxMessageBox("Create Ring not yet implemented.\n\n"
                 "MFC: Shows RingPropertySheet with 3 property pages.\n"
                 "All property pages exist in dialogs/ but parent sheet needs implementation.\n\n"
                 "See detailed TODO in OnCreateRing.",
                 "Feature Incomplete", wxOK | wxICON_INFORMATION, this);
}

void W3DViewFrame::OnEditPrimitive(wxCommandEvent &WXUNUSED(event))
{
    // MFC Reference: MainFrm.cpp:4055-4091 (OnEditPrimitive), MainFrm.cpp:4093-4106 (OnUpdateEditPrimitive)
    // Function: Edit properties of currently displayed primitive (sphere/ring) via property sheet
    //
    // TODO(MFC-BLOCKED): Requires Property Sheet wrappers + GetDisplayedObject()
    //   MFC Algorithm (MainFrm.cpp:4055-4091):
    //   
    //   1. Get doc = GetActiveDocument()
    //   2. Get render_obj = doc->GetDisplayedObject()
    //   3. If render_obj == nullptr: return (nothing to edit)
    //   4. Check Class_ID:
    //      A. If render_obj->Class_ID() == CLASSID_SPHERE:
    //         - Cast to SphereRenderObjClass*
    //         - SpherePropertySheetClass dialog(sphere_obj, IDS_SPHERE_PROP_TITLE, this)
    //         - dialog.DoModal()
    //      
    //      B. If render_obj->Class_ID() == CLASSID_RING:
    //         - Cast to RingRenderObjClass*
    //         - RingPropertySheetClass dialog(ring_obj, IDS_RING_PROP_TITLE, this)
    //         - dialog.DoModal()
    //   
    //   5. Property sheets modify object properties in-place
    //   
    //   OnUpdateEditPrimitive (MainFrm.cpp:4093-4106):
    //     - data_tree = GetDataTreeView()
    //     - Enable if data_tree->GetCurrentSelectionType() == TypePrimitives
    //     - Otherwise disable
    //
    //   Property Sheet Content (same pages as creation handlers):
    //   
    //   Sphere Property Sheet (3 pages):
    //     1. SphereGeneralPage: Name, segments (horizontal/vertical)
    //     2. SpherePositionPage: Position X/Y/Z, radius
    //     3. SphereColorPage: RGB color values
    //
    //   Ring Property Sheet (3 pages):
    //     1. RingGeneralPage: Name, segments
    //     2. RingPositionPage: Position X/Y/Z, inner/outer radius
    //     3. RingColorPage: RGB color values
    //
    //   Note: Edit uses EXISTING object, Create uses NEW object
    //     - Property sheets take RenderObjClass* instead of nullptr
    //     - Pages populate from object's current values
    //     - OK applies changes directly to render object
    //
    //   Blocking Factors:
    //     1. Property sheet wrappers not implemented:
    //        - SpherePropertySheet_wx (wraps 3 pages)
    //        - RingPropertySheet_wx (wraps 3 pages)
    //     2. W3DViewDoc::GetDisplayedObject() not ported
    //     3. DataTreeView integration for OnUpdate handler
    //
    //   Implementation Priority: MEDIUM-LOW
    //     - Useful for editing existing primitives
    //     - Less critical than creation (can recreate primitives)
    //     - Requires same property sheet infrastructure as OnCreateSphere/Ring
    //
    //   Related Handlers:
    //     - OnCreateSphere: Creates new sphere (property sheet with nullptr)
    //     - OnCreateRing: Creates new ring (property sheet with nullptr)
    //     - All property pages already exist in wxWidgets (verified)
    wxMessageBox("Edit Primitive not yet implemented.\nNeeds primitive properties dialog.",
                 "Feature Incomplete", wxOK | wxICON_INFORMATION, this);
}

// Sound menu handlers

void W3DViewFrame::OnCreateSoundObject(wxCommandEvent &WXUNUSED(event))
{
    // MFC: MainFrm.cpp:OnCreateSoundObject
    // MFC ID: IDM_CREATE_SOUND_OBJECT (32879)
    // Function: Create a new sound object in the scene
    // Dialog: SoundEdit_wx.cpp (XRC-based, converted from MFC SoundEditDialogClass)
    // MFC Implementation: Simply shows SoundEditDialogClass dialog
    // TODO(MFC-Implement): Dialog shows, need to implement object creation logic
    //   Dialog controls (from SoundEdit_wx.h):
    //     - Name, filename (with browse button)
    //     - 2D/3D radio buttons
    //     - Trigger radius, drop-off distance, max volume
    //     - Infinite loops, stop when hidden checkboxes
    //     - Sound effect/music radio, priority/volume sliders
    //     - Play button to preview sound
    //   Need to implement in SoundEdit dialog:
    //     1. Browse button handler for sound file selection
    //     2. Play button handler for sound preview
    //     3. OK handler to create SoundRenderObjClass
    //     4. Add created object to document
    //     5. Update tree view
    //   MFC Reference: SoundEditDialogClass.cpp
    //   Impact: High - core feature for sound designers
    SoundEdit dialog(this);
    if (dialog.ShowModal() == wxID_OK) {
        // TODO(MFC-Implement): Extract values from dialog and create sound object
        //   Get values: dialog.m_idc_name_edit->GetValue(), etc.
        //   Create new SoundRenderObjClass with parameters
        //   Add to document: doc->AddObject(soundObj)
        //   Refresh tree view
        wxMessageBox("Sound object creation logic not yet implemented in dialog.\nDialog shown but object creation pending.",
                     "Feature Incomplete", wxOK | wxICON_INFORMATION, this);
    }
}

void W3DViewFrame::OnEditSoundObject(wxCommandEvent &WXUNUSED(event))
{
    // MFC: MainFrm.cpp:OnEditSoundObject
    // MFC ID: IDM_EDIT_SOUND_OBJECT (32880)
    // Function: Edit properties of the currently displayed sound object
    // Dialog: SoundEdit_wx.cpp (same dialog as Create, but pre-filled with object data)
    // MFC Implementation:
    //   1. Gets current document
    //   2. Gets displayed object (doc->GetDisplayedObject())
    //   3. Casts to SoundRenderObjClass*
    //   4. If valid, shows SoundEditDialogClass with dialog.Set_Sound(sound_obj)
    // TODO(MFC-Implement): Dialog shows, need to implement edit logic
    //   Need to implement in SoundEdit dialog:
    //     1. Set_Sound() method to populate fields from existing object
    //     2. Get_Sound() method to extract modified values
    //     3. Update object when OK clicked
    //   Impact: High - primary editing interface for sound objects
    W3DViewDoc* doc = wxDynamicCast(GetDocument(), W3DViewDoc);
    if (doc != nullptr) {
        RenderObjClass* obj = doc->GetDisplayedObject();
        if (obj != nullptr) {
            // TODO(MFC-Implement): Check if object is SoundRenderObjClass
            //   Need to add type checking: obj->Class_ID() == SoundRenderObjClass::Class_ID()
            //   Or dynamic_cast<SoundRenderObjClass*>(obj)
            SoundEdit dialog(this);
            // TODO(MFC-Implement): dialog.Set_Sound((SoundRenderObjClass*)obj)
            //   Need to implement Set_Sound() method in SoundEdit dialog
            //   Populate all dialog fields from sound object properties
            if (dialog.ShowModal() == wxID_OK) {
                // TODO(MFC-Implement): Update sound object from dialog values
                //   Get values from dialog and apply to object
                //   Refresh viewport if needed
            }
        } else {
            wxMessageBox("No sound object is currently displayed.\nPlease select a sound object in the tree view first.",
                        "No Sound Object Selected", wxOK | wxICON_INFORMATION, this);
        }
    }
}

// Movie menu handlers

void W3DViewFrame::OnMakeMovie(wxCommandEvent &WXUNUSED(event))
{
    // MFC: MainFrm.cpp:OnMakeMovie() → W3DViewDoc.cpp:Make_Movie()
    // MFC ID: IDM_MAKE_MOVIE (32845)
    // Function: Record animation to AVI file
    // MFC Implementation Details:
    //   - Uses FrameGrabClass (framgrab.h/cpp) with Windows VFW (Video for Windows) API
    //   - Creates AVI files using PAVIFILE, PAVISTREAM (vfw.h)
    //   - Loops through animation frames at 30 FPS
    //   - Calls WW3D::Start_Movie_Capture("Grab", 30) to start
    //   - Updates each frame with WW3D::Update_Movie_Capture()
    //   - Stops with WW3D::Stop_Movie_Capture()
    //   - Hides cursor during capture
    //   - Allows ESC key to cancel
    //   - Supports camera animation if enabled
    // TODO(MFC-Implement): LOW PRIORITY - Complex feature, can be left for later/never
    //   Implementation approach:
    //     1. Port FrameGrabClass to use wxWidgets/cross-platform AVI library
    //        * Windows: Can use VFW API (vfw.h) same as MFC
    //        * Linux/Mac: Would need alternative (FFmpeg, OpenCV VideoWriter, etc.)
    //     2. Or: Skip movie recording entirely and only implement screenshot (more useful)
    //   Requirements:
    //     - Access to WW3D rendering buffer
    //     - Animation frame control
    //     - AVI encoding library
    //   Impact: LOW - Nice-to-have feature, screenshot is more important
    //   Recommendation: Mark as "TODO for future" and focus on other features first
    //   Files to review: 
    //     * Generals/Code/Libraries/Source/WWVegas/WW3D2/framgrab.{h,cpp}
    //     * Core/Tools/W3DView/W3DViewDoc.cpp:Make_Movie()
    wxMessageBox("Make Movie not yet implemented.\n\n"
                 "MFC version uses Windows VFW (Video for Windows) API to create AVI files.\n"
                 "This is a complex feature that can be implemented later or left as TODO.\n\n"
                 "Screenshot capture (F7) is higher priority.",
                 "Low Priority Feature", wxOK | wxICON_INFORMATION, this);
}

void W3DViewFrame::OnSaveScreenshot(wxCommandEvent &WXUNUSED(event))
{
    // MFC: MainFrm.cpp:OnSaveScreenshot
    // MFC ID: IDM_SAVE_SCREENSHOT (32846)
    // Function: Capture current viewport to TGA image file
    // Keyboard: F7
    // MFC Implementation (simple):
    //   1. Gets executable directory
    //   2. Hides cursor temporarily
    //   3. Repaints view
    //   4. Calls WW3D::Make_Screen_Shot("ScreenShot")
    //   5. Restores cursor
    // WW3D::Make_Screen_Shot handles everything:
    //   - Auto-numbers files (ScreenShot01.tga, ScreenShot02.tga, etc.)
    //   - Captures D3D surface (back buffer)
    //   - Applies gamma correction
    //   - Writes TGA or BMP format
    //   - Located at: Generals/Code/Libraries/Source/WWVegas/WW3D2/ww3d.cpp:~2350
    
    // Get document and graphic view
    W3DViewDoc* doc = wxDynamicCast(GetDocument(), W3DViewDoc);
    if (doc != nullptr && doc->GetGraphicView() != nullptr) {
        // TODO(MFC-Infrastructure): Implement cursor hide/show for screenshots
        //   BLOCKED BY: ScreenCursorClass not yet ported to wxWidgets
        //   
        //   MFC Implementation (W3DViewDoc.cpp:2562-2582):
        //     Show_Cursor(bool onoff):
        //       - Uses m_pCursor (ScreenCursorClass*)
        //       - Calls m_pCursor->Set_Hidden(!onoff)
        //     Is_Cursor_Shown():
        //       - Returns m_pCursor->Is_Not_Hidden_At_All()
        //   
        //   Required Infrastructure:
        //   1. Port ScreenCursorClass to wxWidgets
        //      - Custom 3D cursor rendering in scene
        //      - MFC: Core/Tools/W3DView/ScreenCursor.h/cpp
        //      - Renders cursor as 3D object in scene
        //   2. Add m_pCursor member to W3DViewDoc
        //      - Type: ScreenCursorClass*
        //      - Initialized in Create_Cursor() (W3DViewDoc.cpp:2409-2470)
        //   3. Add m_pCursorScene member
        //      - Type: SceneClass*
        //      - Separate scene for cursor rendering
        //   4. Implement Show_Cursor(bool) and Is_Cursor_Shown()
        //   
        //   Usage in Screenshot (MainFrm.cpp:2419-2420, 2505):
        //     bool restore_cursor = Is_Cursor_Shown();
        //     Show_Cursor(false);  // Hide before screenshot
        //     WW3D::Make_Screen_Shot(...);
        //     Show_Cursor(restore_cursor);  // Restore after
        //   
        //   Impact: LOW - Screenshots work without cursor hiding
        //   Priority: LOW - Nice-to-have, not essential
        //   Complexity: MEDIUM-HIGH - Requires ScreenCursorClass port
        //   
        //   Current Behavior: Cursor may appear in screenshots if visible
        //   MFC Behavior: Cursor always hidden during screenshot capture
        
        // Repaint view to ensure latest frame is captured
        doc->GetGraphicView()->RepaintView();
        
        // Get executable directory for screenshot location
        wxStandardPaths &paths = wxStandardPaths::Get();
        wxString exePath = wxPathOnly(wxStandardPaths::Get().GetExecutablePath());
        wxString screenshotBase = exePath + wxFILE_SEP_PATH + "ScreenShot";
        
        // Call WW3D screenshot function (handles numbering, capture, and file writing)
        WW3D::Make_Screen_Shot(screenshotBase.mb_str(), 1.3f, WW3D::TGA);
        
        // TODO(MFC-Infrastructure): Restore cursor visibility
        //   (Same infrastructure as above TODO)
        
        // Show confirmation (optional - MFC doesn't show this)
        // wxMessageBox(wxString::Format("Screenshot saved to:\n%s##.tga", screenshotBase),
        //             "Screenshot Saved", wxOK | wxICON_INFORMATION, this);
    } else {
        wxMessageBox("Cannot capture screenshot:\nNo document or graphic view available.",
                    "Screenshot Failed", wxOK | wxICON_ERROR, this);
    }
}
