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

#pragma once

#include <wx/docview.h>

// Phase 3A.2: Include engine types needed for member variables
// CRITICAL: Undefine CString before including engine headers
#ifdef CString
#undef CString
#endif

#include "vector3.h"

// Redefine CString for wxWidgets compatibility
#define CString wxString

#include "w3dcompat_wx.h"

// Forward declarations for other engine types
class ViewerSceneClass;
class RenderObjClass;
class AssetInfoClass;
class CGraphicView;
class LightClass;
class HAnimClass;
class HAnimComboClass;
class Bitmap2DObjClass;

class W3DViewDoc : public wxDocument
{
public:
    W3DViewDoc();
    virtual ~W3DViewDoc();

    // Document overrides
    virtual bool OnOpenDocument(const wxString &filename) override;
    virtual bool OnSaveDocument(const wxString &filename) override;
    virtual bool OnNewDocument() override;
    virtual bool OnCloseDocument() override;

    // Scene and object accessors
    ViewerSceneClass *GetScene() { return m_scene; }
    RenderObjClass *GetCurrentObject() { return m_currentObject; }
    RenderObjClass *GetDisplayedObject() { return m_currentObject; }  // Alias for MFC compatibility
    void SetCurrentObject(RenderObjClass *obj) { m_currentObject = obj; }
    
    // Phase 4: Scene light accessor (MFC: GetSceneLight)
    LightClass *GetSceneLight() { return m_sceneLight; }

    AssetInfoClass *GetAssetInfo(int index);
    int GetAssetCount() const;

    // ============================================================================
    // Phase 3A: Dialog Infrastructure Methods
    // ============================================================================

    // Background color methods
    const Vector3& GetBackgroundColor() const { return m_backgroundColor; }
    void SetBackgroundColor(const Vector3& color);

    // Ambient light methods (MFC: AmbientLightDialog.cpp:69,117)
    // Wrapper methods to avoid header include issues in dialog files
    // Access scene ambient light without requiring ViewerScene.h in dialogs
    Vector3 GetAmbientLight() const;
    void SetAmbientLight(const Vector3& light);

    // Background fog methods (MFC: IsFogEnabled, EnableFog)
    bool IsFogEnabled() const;
    void EnableFog(bool enable);

    // Camera settings methods
    bool Is_FOV_Manual() const { return m_manualFOV; }
    void Set_Manual_FOV(bool manual) { m_manualFOV = manual; }
    
    bool Are_Clip_Planes_Manual() const { return m_manualClipPlanes; }
    void Set_Manul_Clip_Planes(bool manual) { m_manualClipPlanes = manual; }  // Note: typo matches MFC
    
    // View access
    CGraphicView* GetGraphicView();
    
    // Texture path methods
    const wxString& Get_Texture_Path1() const { return m_texturePath1; }
    const wxString& Get_Texture_Path2() const { return m_texturePath2; }
    void Set_Texture_Path1(const wxString& path) { m_texturePath1 = path; }
    void Set_Texture_Path2(const wxString& path) { m_texturePath2 = path; }
    
    // Camera settings persistence
    void Save_Camera_Settings();
    
    // Animation accessors (MFC compatibility)
    HAnimClass* GetCurrentAnimation() const { return m_animation; }
    HAnimComboClass* GetAnimationCombo() const { return m_animCombo; }
    float GetCurrentFrame() const { return m_currentFrame; }
    float GetAnimationTime() const { return m_animTime; }
    
    // Animation control
    void StepAnimation(int frameIncrement);
    
    // Camera animation control (MFC: W3DViewDoc.h:156, W3DViewDoc.cpp:2397-2407)
    void Animate_Camera(bool animate);
    bool Is_Camera_Animated() const { return m_bAnimateCamera; }
    
    // Animation blend control (MFC: W3DViewDoc.h:151,155)
    // Controls whether animation blending is enabled for smooth transitions
    void SetAnimationBlend(bool blend) { m_bAnimBlend = blend; }
    bool GetAnimationBlend() const { return m_bAnimBlend; }
    
    // Channel Q compression settings (MFC: W3DViewDoc.h:108,152-154)
    // NOTE: These methods exist in MFC but are NOT USED in AnimationSpeed dialog
    //       (OnCompressq, On16bit, On8bit are commented out in AnimationSpeed.cpp)
    // TODO(MFC-Match): Investigate if these are used elsewhere in codebase
    //   If compression features are never used, consider removing UI controls
    //   If used elsewhere, implement compression logic when needed
    void SetChannelQCompression(bool compress) { m_bCompress_channel_Q = compress; }
    bool GetChannelQCompression() const { return m_bCompress_channel_Q; }
    int GetChannelQnBytes() const { return m_nChannelQnBytes; }
    void SetChannelQnBytes(int n_bytes) { m_nChannelQnBytes = n_bytes; }
    
    // Camera auto reset control (MFC: W3DViewDoc.h:164-165, MainFrm.cpp:2564-2588)
    // Controls whether camera resets automatically when loading new objects
    // TODO(MFC-Implementation): Use m_bAutoCameraReset in DisplayObject/Display_Emitter methods
    //   MFC Reference: W3DViewDoc.cpp:637,714,751,895,994
    //   Logic: if ((use_global_reset_flag && m_bAutoCameraReset) || ...) 
    //          then call pCGraphicView->Reset_Camera_To_Display_Object()/Reset_Camera_To_Display_Emitter()
    //   Required when: Object loading/display infrastructure is implemented
    bool Is_Camera_Auto_Reset_On() const { return m_bAutoCameraReset; }
    void Turn_Camera_Auto_Reset_On(bool onoff) { m_bAutoCameraReset = onoff; }
    
    // TODO(MFC-Infrastructure): Implement Reload_Displayed_Object() for prelit mode changes
    // MFC Reference: W3DViewDoc.cpp:579-593
    // Required for: OnPrelitVertex, OnPrelitMultipass, OnPrelitMultitex
    //
    // MFC implementation:
    //   void CW3DViewDoc::Reload_Displayed_Object(void) {
    //       GetDataTreeView()->Display_Asset();
    //   }
    //
    // Purpose: Refreshes the currently displayed object from the tree view selection.
    //          Essential for showing prelit mode changes on loaded models.
    //
    // Full implementation requires:
    //   - GetDataTreeView() method to access tree control
    //   - Tree control's Display_Asset() method
    //   - Document → Tree → View connections
    void Reload_Displayed_Object();
    
    // Background BMP accessors (MFC: W3DViewDoc.h:231,244, W3DViewDoc.cpp:3008-3059)
    const wxString& GetBackgroundBMP() const { return m_backgroundBMPFilename; }
    void SetBackgroundBMP(const wxString& filename);

private:
    // Scene and object data
    ViewerSceneClass *m_scene;
    RenderObjClass *m_currentObject;
    LightClass *m_sceneLight;  // Phase 4: Scene light (MFC: m_pCSceneLight)

    // Phase 3A: Dialog settings storage
    Vector3 m_backgroundColor;
    bool m_manualFOV;
    bool m_manualClipPlanes;
    
    // Texture paths
    wxString m_texturePath1;
    wxString m_texturePath2;
    
    // Animation state (MFC compatibility)
    HAnimClass *m_animation;         // Current animation (MFC: m_pCAnimation)
    HAnimComboClass *m_animCombo;    // Combo animation (MFC: m_pCAnimCombo)
    float m_currentFrame;            // Current animation frame (MFC: m_CurrentFrame)
    float m_animTime;                // Current animation time (MFC: m_animTime)
    
    // Camera animation state (MFC: m_bAnimateCamera)
    bool m_bAnimateCamera;           // Camera animation enabled flag
    
    // Camera auto reset state (MFC: m_bAutoCameraReset, W3DViewDoc.h:316)
    bool m_bAutoCameraReset;         // Auto reset camera on object load
    
    // Animation blend state (MFC: m_bAnimBlend, W3DViewDoc.h:314)
    bool m_bAnimBlend;               // Animation blending enabled (default: true)
    
    // Channel Q compression state (MFC: m_bCompress_channel_Q, m_nChannelQnBytes)
    // NOTE: These exist in MFC but are unused in AnimationSpeed dialog
    bool m_bCompress_channel_Q;      // Channel Q compression enabled
    int m_nChannelQnBytes;           // Q bytes (1 or 2)
    
    // Background BMP state (MFC: m_pCBackgroundBMP, m_stringBackgroundBMP)
    Bitmap2DObjClass *m_backgroundBMP;    // Background bitmap texture object
    wxString m_backgroundBMPFilename;     // Background bitmap filename

    wxDECLARE_DYNAMIC_CLASS(W3DViewDoc);
};
