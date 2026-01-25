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
{
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
