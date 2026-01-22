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

class ViewerSceneClass;
class RenderObjClass;
class AssetInfoClass;

class W3DViewDoc : public wxDocument
{
public:
    W3DViewDoc();
    virtual ~W3DViewDoc();

    virtual bool OnOpenDocument(const wxString &filename) override;
    virtual bool OnSaveDocument(const wxString &filename) override;
    virtual bool OnNewDocument() override;
    virtual bool OnCloseDocument() override;

    ViewerSceneClass *GetScene() { return m_scene; }
    RenderObjClass *GetCurrentObject() { return m_currentObject; }
    void SetCurrentObject(RenderObjClass *obj) { m_currentObject = obj; }

    AssetInfoClass *GetAssetInfo(int index);
    int GetAssetCount() const;

private:
    ViewerSceneClass *m_scene;
    RenderObjClass *m_currentObject;

    wxDECLARE_DYNAMIC_CLASS(W3DViewDoc);
};
