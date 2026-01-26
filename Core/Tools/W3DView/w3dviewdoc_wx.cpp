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

// TheSuperHackers: wxWidgets document implementation for W3DView

#include "w3dviewdoc_wx.h"
#include "w3dcompat_wx.h"
#include "GraphicView_wx.h"

#include <wx/msgdlg.h>
#include <wx/config.h>

// Phase 3A.3: Include real engine headers in .cpp
// CRITICAL: Undefine CString macro before including engine headers
// EngineString typedef + wwstring.h fix allows these to work with wxWidgets
#ifdef CString
#undef CString
#endif

#include "vector3.h"
#include "ViewerScene.h"
#include "ViewerAssetMgr.h"
#include "AssetInfo.h"
#include "camera.h"
#include "light.h"
#include "hanimmgr.h"  // For HAnimManagerClass
#include "hrawanim.h"  // For HAnimClass (HRawAnimClass)
#include "hmorphanim.h"  // For HMorphAnimClass
// Note: HAnimComboClass appears to be defined in one of the above headers

// Redefine CString for wxWidgets compatibility
#define CString wxString

extern ViewerAssetMgrClass *_TheAssetMgr;

wxIMPLEMENT_DYNAMIC_CLASS(W3DViewDoc, wxDocument);

W3DViewDoc::W3DViewDoc()
    : m_scene(nullptr)
    , m_currentObject(nullptr)
    , m_sceneLight(nullptr)  // Phase 4: Initialize scene light
    , m_backgroundColor(0.0f, 0.0f, 0.0f)  // Black by default
    , m_manualFOV(false)
    , m_manualClipPlanes(false)
    , m_animation(nullptr)     // Animation state
    , m_animCombo(nullptr)
    , m_currentFrame(0.0f)
    , m_animTime(0.0f)
    , m_bAnimateCamera(false)  // Camera animation disabled by default
    , m_bAutoCameraReset(true)  // Auto reset enabled by default (MFC: W3DViewDoc.cpp:108)
    , m_bAnimBlend(true)  // Animation blending enabled by default (MFC: W3DViewDoc.cpp:106)
    , m_bCompress_channel_Q(false)  // Channel Q compression disabled by default (MFC: W3DViewDoc.cpp)
    , m_nChannelQnBytes(2)  // Q bytes default to 2 (16-bit) (MFC: W3DViewDoc.cpp)
    , m_backgroundBMP(nullptr)  // Background bitmap (MFC: m_pCBackgroundBMP)
{
    // MFC Reference: W3DViewDoc.cpp:121
    // Loads auto reset setting from registry: GetProfileInt("Config", "ResetCamera", 1)
    // wxWidgets equivalent: Use wxConfig
    wxConfigBase *config = wxConfigBase::Get();
    if (config)
    {
        m_bAutoCameraReset = config->ReadBool("/Config/ResetCamera", true);
    }
}

W3DViewDoc::~W3DViewDoc()
{
    // Phase 4: Clean up scene light (MFC: deletes light in scene destructor)
    // Note: Light is added to scene via Add_Render_Object, so scene owns it
    // We just need to null our pointer
    m_sceneLight = nullptr;
    
    if (m_scene)
    {
        delete m_scene;
        m_scene = nullptr;
    }
}

bool W3DViewDoc::OnNewDocument()
{
    if (!wxDocument::OnNewDocument())
        return false;

    // Phase 3A.3: Create scene (EngineString + wwstring.h fix enables this)
    m_scene = new ViewerSceneClass();
    
    // Phase 4: Create and initialize scene light (MFC: W3DViewDoc.cpp lines 374-390)
    m_sceneLight = new LightClass;
    
    if (m_sceneLight != nullptr) {
        // Create default light settings matching MFC
        m_sceneLight->Set_Position(Vector3(0, 5000, 3000));
        m_sceneLight->Set_Intensity(1.0F);
        m_sceneLight->Set_Force_Visible(true);
        m_sceneLight->Set_Flag(LightClass::NEAR_ATTENUATION, false);
        m_sceneLight->Set_Far_Attenuation_Range(1000000, 1000000);
        m_sceneLight->Set_Ambient(Vector3(0, 0, 0));
        m_sceneLight->Set_Diffuse(Vector3(1, 1, 1));
        m_sceneLight->Set_Specular(Vector3(1, 1, 1));
        
        // Add this light to the scene
        m_scene->Add_Render_Object(m_sceneLight);
    }
    
    return true;
}

bool W3DViewDoc::OnOpenDocument(const wxString &filename)
{
    if (!wxDocument::OnOpenDocument(filename))
        return false;

    // Phase 3A.3: Create scene if not already created
    if (!m_scene)
    {
        m_scene = new ViewerSceneClass();
    }

    // Load the W3D file
    wxString ext = filename.AfterLast('.').Lower();
    
    if (ext == "w3d" || ext == "w3x")
    {
        // TODO: Phase 3A.2 - Asset loading functionality to be implemented
        // Currently blocked by MFC/wxWidgets CString conflicts in ViewerAssetMgr.h
        // Will be fixed in Phase 3A.3 or when actually needed by dialogs
        
        // Temporary: Just set filename and mark success
        SetFilename(filename, true);
        Modify(false);
        UpdateAllViews();
        return true;
        
        /*
        // Real implementation (commented until CString issues resolved):
        if (_TheAssetMgr)
        {
            AssetInfoClass *info = _TheAssetMgr->Load_W3D_Asset(filename.utf8_str());
            if (info)
            {
                m_currentObject = info->Get_Render_Obj();
                if (m_currentObject)
                {
                    m_scene->Add_Render_Object(m_currentObject);
                }
                SetFilename(filename, true);
                Modify(false);
                UpdateAllViews();
                return true;
            }
        }
        */
    }

    wxMessageBox("Failed to load file: " + filename,
                 "Error", wxOK | wxICON_ERROR);
    return false;
}

bool W3DViewDoc::OnSaveDocument(const wxString &filename)
{
    // TODO: Implement save functionality
    return wxDocument::OnSaveDocument(filename);
}

bool W3DViewDoc::OnCloseDocument()
{
    if (m_scene)
    {
        delete m_scene;
        m_scene = nullptr;
    }
    m_currentObject = nullptr;
    m_sceneLight = nullptr;  // Phase 4: Clear scene light pointer (owned by scene)

    return wxDocument::OnCloseDocument();
}

AssetInfoClass *W3DViewDoc::GetAssetInfo(int index)
{
    // TODO: Phase 3A.2 - Implement when CString conflicts resolved
    // Method exists in ViewerAssetMgrClass but inaccessible due to header conflicts
    return nullptr;
}

int W3DViewDoc::GetAssetCount() const
{
    // TODO: Phase 3A.2 - Implement when CString conflicts resolved
    // Method exists in ViewerAssetMgrClass but inaccessible due to header conflicts
    return 0;
}

// ============================================================================
// Phase 3A: Dialog Infrastructure Method Implementations
// ============================================================================

void W3DViewDoc::SetBackgroundColor(const Vector3& color)
{
    m_backgroundColor = color;
    
    // Update the scene's background color if scene exists
    if (m_scene)
    {
        // TODO: Apply to actual scene rendering
        // m_scene->Set_Background_Color(color);
    }
    
    // Notify all views that document has changed
    UpdateAllViews();
    Modify(true);
}

Vector3 W3DViewDoc::GetAmbientLight() const
{
    // MFC: AmbientLightDialog.cpp:69 (pCDoc->GetScene()->Get_Ambient_Light())
    // Returns current ambient light from scene, or default if no scene
    if (m_scene)
    {
        return m_scene->Get_Ambient_Light();
    }
    
    // Default ambient light (black - no ambient light)
    return Vector3(0.0f, 0.0f, 0.0f);
}

void W3DViewDoc::SetAmbientLight(const Vector3& light)
{
    // MFC: AmbientLightDialog.cpp:117 (pCDoc->GetScene()->Set_Ambient_Light(lightSettings))
    // Sets ambient light for scene (real-time update for dialog preview)
    if (m_scene)
    {
        m_scene->Set_Ambient_Light(light);
    }
    
    // Notify all views that document has changed
    UpdateAllViews();
    Modify(true);
}

bool W3DViewDoc::IsFogEnabled() const
{
    // MFC: W3DViewDoc.cpp (CW3DViewDoc::IsFogEnabled)
    // Returns fog enable state from scene
    if (m_scene)
    {
        return m_scene->Get_Fog_Enable();
    }
    return false;
}

void W3DViewDoc::EnableFog(bool enable)
{
    // MFC: W3DViewDoc.cpp (CW3DViewDoc::EnableFog)
    // Sets fog enable state in scene
    if (m_scene)
    {
        m_scene->Set_Fog_Enable(enable);
    }
}

CGraphicView* W3DViewDoc::GetGraphicView()
{
    // Get the first view that's a CGraphicView
    wxList& views = GetViews();
    for (wxList::iterator it = views.begin(); it != views.end(); ++it)
    {
        wxView* view = static_cast<wxView*>(*it);
        CGraphicView* graphicView = dynamic_cast<CGraphicView*>(view);
        if (graphicView)
        {
            return graphicView;
        }
    }
    return nullptr;
}

// ============================================================================
// Phase 4: Save_Camera_Settings
// MFC: CW3DViewDoc::Save_Camera_Settings() (W3DViewDoc.cpp lines 3001-3037)
// ============================================================================

void W3DViewDoc::Save_Camera_Settings()
{
    // MFC: theApp.WriteProfileInt("Config", "UseManualFOV", m_ManualFOV);
    // MFC: theApp.WriteProfileInt("Config", "UseManualClipPlanes", m_ManualClipPlanes);
    
    wxConfigBase* config = wxConfig::Get();
    config->Write("Config/UseManualFOV", m_manualFOV);
    config->Write("Config/UseManualClipPlanes", m_manualClipPlanes);
    
    // MFC: CGraphicView *graphic_view = ::Get_Graphic_View();
    // MFC: CameraClass *camera = graphic_view->GetCamera();
    CGraphicView *graphic_view = GetGraphicView();
    if (graphic_view == nullptr) {
        config->Flush();
        return;
    }
    
    CameraClass *camera = graphic_view->GetCamera();
    if (camera != nullptr) {
        // MFC: double hfov = camera->Get_Horizontal_FOV();
        // MFC: double vfov = camera->Get_Vertical_FOV();
        double hfov = camera->Get_Horizontal_FOV();
        double vfov = camera->Get_Vertical_FOV();
        
        // MFC: float znear = 0;
        // MFC: float zfar = 0;
        // MFC: camera->Get_Clip_Planes(znear, zfar);
        float znear = 0;
        float zfar = 0;
        camera->Get_Clip_Planes(znear, zfar);
        
        // MFC: CString hfov_string;
        // MFC: hfov_string.Format("%f", hfov);
        // MFC: theApp.WriteProfileString("Config", "hfov", hfov_string);
        // wxWidgets: Can write doubles directly to wxConfig
        config->Write("Config/hfov", hfov);
        config->Write("Config/vfov", vfov);
        config->Write("Config/znear", (double)znear);
        config->Write("Config/zfar", (double)zfar);
    }
    
    // Ensure config is written to disk
    config->Flush();
}

void W3DViewDoc::StepAnimation(int frameIncrement)
{
    // MFC Reference: W3DViewDoc.cpp:802-846 (StepAnimation)
    //
    // MFC Implementation:
    //   if (m_pCRenderObj && m_pCAnimation) {
    //       int iTotalFrames = m_pCAnimation->Get_Num_Frames ();
    //       m_CurrentFrame += iFrameInc;
    //       // Wrap around...
    //       if (m_pCAnimCombo) {
    //           for (int i = 0; i < m_pCAnimCombo->Get_Num_Anims(); i++)
    //               m_pCAnimCombo->Set_Frame(i, m_CurrentFrame);
    //           m_pCRenderObj->Set_Animation (m_pCAnimCombo);
    //       } else {
    //           m_pCRenderObj->Set_Animation (m_pCAnimation, m_CurrentFrame);
    //       }
    //       ((CMainFrame *)::AfxGetMainWnd ())->UpdateFrameCount (...);
    //       Update_Camera ();
    //   }
    //
    // Behavior: Steps animation forward/backward by frameIncrement frames
    //           Handles frame wrapping at boundaries
    //           Updates status bar and camera position
    
    if (!m_currentObject || !m_animation) {
        // No object or animation loaded
        return;
    }
    
    int totalFrames = m_animation->Get_Num_Frames();
    if (totalFrames <= 0) {
        // Invalid animation
        return;
    }
    
    // Increment the frame
    m_currentFrame += frameIncrement;
    
    // Wrap the animation
    if (m_currentFrame >= totalFrames) {
        // Forward wrap: go to frame 0
        m_currentFrame = 0.0f;
        m_animTime = 0.0f;
    }
    else if (m_currentFrame < 0) {
        // Backward wrap: go to last frame
        m_currentFrame = static_cast<float>(totalFrames - 1);
    }
    
    // Update the animation frame
    if (m_animCombo) {
        // Combo animation: set frame for all sub-animations
        for (int i = 0; i < m_animCombo->Get_Num_Anims(); i++) {
            m_animCombo->Set_Frame(i, static_cast<int>(m_currentFrame));
        }
        m_currentObject->Set_Animation(m_animCombo);
    } else {
        // Single animation: set frame directly
        m_currentObject->Set_Animation(m_animation, static_cast<int>(m_currentFrame));
    }
    
    // TODO(MFC-Defer): Update status bar with frame count
    // MFC: ((CMainFrame *)::AfxGetMainWnd ())->UpdateFrameCount(m_CurrentFrame, iTotalFrames - 1, frame_rate * anim_speed);
    // Status bar implementation deferred - will add when status bar infrastructure is complete
    
    // TODO(MFC-Investigate): Call Update_Camera() for camera animations
    // MFC: Update_Camera();
    // Need to verify if Update_Camera() method exists and what it does for animated cameras
}

void W3DViewDoc::Animate_Camera(bool animate)
{
    // MFC Reference: W3DViewDoc.cpp:2397-2407 (Animate_Camera)
    //
    // MFC Implementation:
    //   void CW3DViewDoc::Animate_Camera (bool banimate)
    //   {
    //       m_bAnimateCamera = banimate;
    //
    //       // Restore the camera if we are done animating it
    //       if (m_bAnimateCamera == false) {
    //           ::AfxGetMainWnd ()->SendMessage (WM_COMMAND, MAKEWPARAM (IDM_CAMERA_RESET, 0));
    //       }
    //       return ;
    //   }
    //
    // Behavior: Enables/disables camera animation
    //           When disabling, automatically resets camera to default position
    
    m_bAnimateCamera = animate;
    
    // TODO(MFC-Match): Trigger camera reset when disabling animation
    // MFC sends WM_COMMAND with IDM_CAMERA_RESET to reset camera on disable
    // wxWidgets approach: Frame handler should check state and reset camera
    // Alternative: Add camera reset logic here directly
    
    // TODO(MFC-Investigate): Implement actual camera animation logic
    // MFC may animate camera during idle processing or timer updates
    // Current implementation: Just sets flag, actual animation logic TBD
    // May need to investigate GraphicView camera animation methods or timer-based updates
}

void W3DViewDoc::Reload_Displayed_Object()
{
    // TODO(MFC-Infrastructure): Implement object reloading for prelit mode changes
    // MFC Reference: W3DViewDoc.cpp:579-593
    //
    // Current status: STUB - Does nothing
    //
    // MFC implementation:
    //   void CW3DViewDoc::Reload_Displayed_Object(void) {
    //       GetDataTreeView()->Display_Asset();
    //       // Commented out in MFC:
    //       //SAFE_ADD_REF(m_pCRenderObj);
    //       //DisplayObject(m_pCRenderObj, false, false);
    //       //SAFE_RELEASE_REF(m_pCRenderObj);
    //   }
    //
    // Full implementation requires:
    //   1. GetDataTreeView() method to access tree control from document
    //   2. W3DViewTreeCtrl::Display_Asset() method
    //   3. Document → Frame → Tree control connection
    //
    // Purpose: Refreshes the currently displayed 3D object from the tree view selection.
    //          When prelit lighting mode changes, loaded models need to be reloaded
    //          to show the new lighting. This method triggers that reload.
    //
    // Called by: OnPrelitVertex, OnPrelitMultipass, OnPrelitMultitex
    // Impact: Without this, prelit mode changes apply to new loads but not current objects
    // Priority: Medium - mode changes work, but current display may not update
    
    // STUB: Currently does nothing - prelit mode is set but current object isn't reloaded
    return;
}

// MFC: W3DViewDoc.cpp:3008-3059 (SetBackgroundBMP)
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
    Modify(true);  // Mark document as modified
}
