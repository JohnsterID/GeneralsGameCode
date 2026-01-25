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

// TheSuperHackers: wxWidgets tree view implementation for W3DView

#pragma once

#include <wx/treectrl.h>

class W3DViewTreeCtrl : public wxTreeCtrl
{
public:
    W3DViewTreeCtrl(wxWindow *parent, wxWindowID id,
                    const wxPoint &pos = wxDefaultPosition,
                    const wxSize &size = wxDefaultSize,
                    long style = wxTR_DEFAULT_STYLE);

    virtual ~W3DViewTreeCtrl();

    void RefreshTree();
    void Clear();
    
    // TODO(MFC-Infrastructure): Implement Reload_Lightmap_Models() for prelit mode changes
    // MFC Reference: DataTreeView.cpp:1426-1436
    // Required for: OnPrelitVertex, OnPrelitMultipass, OnPrelitMultitex
    //
    // Full implementation requires:
    //   - Tree structure with mesh collection, hierarchy, and mesh roots
    //   - AssetInfoClass data attached to tree items
    //   - Free_Child_Models() helper method
    //   - Integration with WW3DAssetManager::Remove_Prototype()
    //
    // MFC logic:
    //   Free_Child_Models(m_hMeshCollectionRoot);
    //   Free_Child_Models(m_hHierarchyRoot);
    //   Free_Child_Models(m_hMeshRoot);
    //
    // Purpose: Removes cached lightmap model prototypes from asset manager,
    //          forcing reload from disk when models are next displayed.
    //          Essential for prelit mode changes to take effect.
    void Reload_Lightmap_Models();

private:
    void OnSelectionChanged(wxTreeEvent &event);
    void OnItemActivated(wxTreeEvent &event);
    void OnRightClick(wxTreeEvent &event);

    void BuildTree();

    wxDECLARE_EVENT_TABLE();
};
