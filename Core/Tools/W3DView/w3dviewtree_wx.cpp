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

#include "w3dviewtree_wx.h"
#include "w3dcompat_wx.h"

#include <wx/menu.h>

extern ViewerAssetMgrClass *_TheAssetMgr;

// Custom tree item data to store asset index
class TreeItemDataInt : public wxTreeItemData
{
public:
    TreeItemDataInt(int value) : m_value(value) {}
    int GetValue() const { return m_value; }
private:
    int m_value;
};

wxBEGIN_EVENT_TABLE(W3DViewTreeCtrl, wxTreeCtrl)
    EVT_TREE_SEL_CHANGED(wxID_ANY, W3DViewTreeCtrl::OnSelectionChanged)
    EVT_TREE_ITEM_ACTIVATED(wxID_ANY, W3DViewTreeCtrl::OnItemActivated)
    EVT_TREE_ITEM_RIGHT_CLICK(wxID_ANY, W3DViewTreeCtrl::OnRightClick)
wxEND_EVENT_TABLE()

W3DViewTreeCtrl::W3DViewTreeCtrl(wxWindow *parent, wxWindowID id,
                                 const wxPoint &pos, const wxSize &size,
                                 long style)
    : wxTreeCtrl(parent, id, pos, size, style | wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT)
{
    BuildTree();
}

W3DViewTreeCtrl::~W3DViewTreeCtrl()
{
}

void W3DViewTreeCtrl::BuildTree()
{
    DeleteAllItems();

    wxTreeItemId root = AddRoot("Assets");

    // TODO: Phase 3A.2 - AssetMgr has MFC CString dependencies
    // Tree population will be enabled when CString issues are resolved
    if (_TheAssetMgr)
    {
        // int assetCount = _TheAssetMgr->Get_Asset_Count();
        // for (int i = 0; i < assetCount; i++)
        // {
        //     AssetInfoClass *info = _TheAssetMgr->Get_Asset_Info(i);
        //     if (info)
        //     {
        //         wxString assetName = info->Get_Name();
        //         wxTreeItemId item = AppendItem(root, assetName);
        //         SetItemData(item, new TreeItemDataInt(i));
        //     }
        // }
    }

    Expand(root);
}

void W3DViewTreeCtrl::RefreshTree()
{
    BuildTree();
}

void W3DViewTreeCtrl::Clear()
{
    DeleteAllItems();
}

void W3DViewTreeCtrl::OnSelectionChanged(wxTreeEvent &event)
{
    wxTreeItemId item = event.GetItem();
    if (!item.IsOk())
        return;

    TreeItemDataInt *data = dynamic_cast<TreeItemDataInt*>(GetItemData(item));
    if (data)
    {
        // TODO: Update the current selection in the document
        int assetIndex = data->GetValue();
        // Notify views to update
    }
}

void W3DViewTreeCtrl::OnItemActivated(wxTreeEvent &event)
{
    wxTreeItemId item = event.GetItem();
    if (!item.IsOk())
        return;

    // TODO: Handle double-click on asset
}

void W3DViewTreeCtrl::OnRightClick(wxTreeEvent &event)
{
    wxTreeItemId item = event.GetItem();
    if (!item.IsOk())
        return;

    SelectItem(item);

    wxMenu menu;
    menu.Append(wxID_ANY, "Properties...");
    menu.Append(wxID_ANY, "Delete");

    PopupMenu(&menu);
}

void W3DViewTreeCtrl::Reload_Lightmap_Models()
{
    // TODO(MFC-Infrastructure): Implement lightmap model reloading
    // MFC Reference: DataTreeView.cpp:1426-1436
    //
    // Current status: STUB - Does nothing
    //
    // Full implementation requires:
    //   1. Tree structure with mesh roots (m_hMeshCollectionRoot, m_hHierarchyRoot, m_hMeshRoot)
    //   2. AssetInfoClass* attached to tree items (not TreeItemDataInt)
    //   3. WW3DAssetManager integration for Remove_Prototype()
    //
    // MFC implementation:
    //   void CDataTreeView::Reload_Lightmap_Models(void) {
    //       Free_Child_Models(m_hMeshCollectionRoot);
    //       Free_Child_Models(m_hHierarchyRoot);
    //       Free_Child_Models(m_hMeshRoot);
    //   }
    //
    //   void Free_Child_Models(HTREEITEM parent_item) {
    //       for (HTREEITEM tree_item = GetTreeCtrl().GetChildItem(parent_item); ...) {
    //           AssetInfoClass *asset_info = (AssetInfoClass*)GetTreeCtrl().GetItemData(tree_item);
    //           if (asset_info != nullptr) {
    //               WW3DAssetManager::Get_Instance()->Remove_Prototype(asset_info->Get_Name());
    //           }
    //       }
    //   }
    //
    // When implementing:
    //   - Traverse mesh collection, hierarchy, and mesh tree roots
    //   - For each child item, get AssetInfoClass from item data
    //   - Call WW3DAssetManager::Get_Instance()->Remove_Prototype(name)
    //   - This forces models to reload from disk with new prelit settings
    //
    // Called by: OnPrelitVertex, OnPrelitMultipass, OnPrelitMultitex
    // Impact: Without this, prelit mode changes may not fully take effect on loaded models
    // Priority: Medium - prelit handlers work but may need reload for full effect
    
    // STUB: Currently does nothing - prelit mode is set but models aren't reloaded
    return;
}
