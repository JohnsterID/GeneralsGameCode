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

#include <wx/msgdlg.h>

extern ViewerAssetMgrClass *_TheAssetMgr;

wxIMPLEMENT_DYNAMIC_CLASS(W3DViewDoc, wxDocument);

W3DViewDoc::W3DViewDoc()
    : m_scene(nullptr)
    , m_currentObject(nullptr)
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

    m_scene = new ViewerSceneClass();
    return true;
}

bool W3DViewDoc::OnOpenDocument(const wxString &filename)
{
    if (!wxDocument::OnOpenDocument(filename))
        return false;

    // Create scene if not already created
    if (!m_scene)
    {
        m_scene = new ViewerSceneClass();
    }

    // Load the W3D file
    wxString ext = filename.AfterLast('.').Lower();
    
    if (ext == "w3d" || ext == "w3x")
    {
        // Load asset through asset manager
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
    if (_TheAssetMgr)
    {
        return _TheAssetMgr->Get_Asset_Info(index);
    }
    return nullptr;
}

int W3DViewDoc::GetAssetCount() const
{
    if (_TheAssetMgr)
    {
        return _TheAssetMgr->Get_Asset_Count();
    }
    return 0;
}
