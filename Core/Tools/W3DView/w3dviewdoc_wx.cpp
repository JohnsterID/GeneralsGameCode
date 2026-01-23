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

// Phase 3A.2: Include real engine headers in .cpp
// CRITICAL: Undefine CString macro before including MFC-dependent engine headers
#ifdef CString
#undef CString
#endif

#include "vector3.h"
// TODO: ViewerScene.h, ViewerAssetMgr.h and AssetInfo.h have MFC CString dependencies
// or require complete RenderObjClass types. These will be fixed in Phase 3A.3 
// or when actually needed by specific dialogs.
// #include "ViewerScene.h"
// #include "ViewerAssetMgr.h"
// #include "AssetInfo.h"

// Redefine CString for wxWidgets compatibility (if needed later)
#define CString wxString

extern ViewerAssetMgrClass *_TheAssetMgr;

wxIMPLEMENT_DYNAMIC_CLASS(W3DViewDoc, wxDocument);

W3DViewDoc::W3DViewDoc()
    : m_scene(nullptr)
    , m_currentObject(nullptr)
    , m_backgroundColor(0.0f, 0.0f, 0.0f)  // Black by default
    , m_manualFOV(false)
    , m_manualClipPlanes(false)
{
}

W3DViewDoc::~W3DViewDoc()
{
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

    // TODO: Phase 3A.2 - ViewerSceneClass requires complete RenderObjClass
    // m_scene = new ViewerSceneClass();
    m_scene = nullptr;
    return true;
}

bool W3DViewDoc::OnOpenDocument(const wxString &filename)
{
    if (!wxDocument::OnOpenDocument(filename))
        return false;

    // TODO: Phase 3A.2 - ViewerSceneClass requires complete RenderObjClass
    // Create scene if not already created
    // if (!m_scene)
    // {
    //     m_scene = new ViewerSceneClass();
    // }

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
