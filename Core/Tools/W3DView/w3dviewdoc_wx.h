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

    wxDECLARE_DYNAMIC_CLASS(W3DViewDoc);
};
