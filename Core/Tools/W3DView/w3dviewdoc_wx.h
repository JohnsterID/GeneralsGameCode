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

    AssetInfoClass *GetAssetInfo(int index);
    int GetAssetCount() const;

    // ============================================================================
    // Phase 3A: Dialog Infrastructure Methods
    // ============================================================================

    // Background color methods
    const Vector3& GetBackgroundColor() const { return m_backgroundColor; }
    void SetBackgroundColor(const Vector3& color);

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

private:
    // Scene and object data
    ViewerSceneClass *m_scene;
    RenderObjClass *m_currentObject;

    // Phase 3A: Dialog settings storage
    Vector3 m_backgroundColor;
    bool m_manualFOV;
    bool m_manualClipPlanes;
    
    // Texture paths
    wxString m_texturePath1;
    wxString m_texturePath2;

    wxDECLARE_DYNAMIC_CLASS(W3DViewDoc);
};
