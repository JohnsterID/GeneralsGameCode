/*
**Command & Conquer Renegade(tm)
**Copyright 2026 TheSuperHackers
**
**This program is free software: you can redistribute it and/or modify
**it under the terms of the GNU General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.
**
**This program is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**GNU General Public License for more details.
**
**You should have received a copy of the GNU General Public License
**along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Auto-generated from XRC by xrc2cpp.py

#include "TextureManagment_wx.h"
#include <wx/xrc/xmlres.h>

wxBEGIN_EVENT_TABLE(TextureManagment, TextureManagmentBase)
    EVT_LIST_ITEM_ACTIVATED(XRCID("IDC_MESH_TEXTURE_LIST_CTRL"), TextureManagment::OnDblclkMeshTextureListCtrl)
    EVT_LIST_KEY_DOWN(XRCID("IDC_MESH_TEXTURE_LIST_CTRL"), TextureManagment::OnKeydownMeshTextureListCtrl)
    EVT_WINDOW_DESTROY(TextureManagment::OnDestroy)
    // Toolbar button commands (MFC ON_COMMAND equivalents)
    EVT_BUTTON(XRCID("IDC_BACK"), TextureManagment::OnBack)
    EVT_BUTTON(XRCID("IDC_DETAILS"), TextureManagment::OnDetails)
    EVT_BUTTON(XRCID("IDC_LARGE"), TextureManagment::OnLarge)
    EVT_BUTTON(XRCID("IDC_LIST"), TextureManagment::OnList)
    EVT_BUTTON(XRCID("IDC_SMALL"), TextureManagment::OnSmall)
    EVT_BUTTON(XRCID("IDC_PROPAGATE"), TextureManagment::OnPropagate)
    EVT_INIT_DIALOG(TextureManagment::OnInitDialog)
wxEND_EVENT_TABLE()

TextureManagment::TextureManagment(wxWindow *parent)
    : TextureManagmentBase(parent)
    , m_bContainsMeshes(true)  // MFC: Starts showing mesh list
{
    Centre();
}

void TextureManagment::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void TextureManagment::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}

// ============================================================================
// Event Handlers (Phase 2 - Auto-integrated)
// ============================================================================

void TextureManagment::OnDblclkMeshTextureListCtrl(wxListEvent &event)
{
    // MFC: TextureMgrDialogClass::OnDblclkMeshTextureListCtrl
    // Double-click on list item:
    // - If mesh: Fill_List_Ctrl_With_Textures() to show that mesh's textures
    // - If texture: Open TextureSettingsDialog if it's an IndirectTexture

    // TODO(Phase 3 - List Control Integration): Implement double-click handler
    // Requires:
    // 1. TextureListNodeClass to get node type and data
    // 2. Fill_List_Ctrl_With_Textures() helper function
    // 3. TextureSettingsDialog integration for texture editing
    // 4. WW3DAssetManager access for original texture lookup
    // MFC flow:
    //   int index = m_ListCtrl.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
    //   TextureListNodeClass* pnode = (TextureListNodeClass*)m_ListCtrl.GetItemData(index);
    //   if (pnode->Get_Type() == TYPE_MESH) Fill_List_Ctrl_With_Textures(*pnode);
    //   else if (ptexture->getClassID() == ID_INDIRECT_TEXTURE_CLASS) show TextureSettingsDialog

    event.Skip();
}

void TextureManagment::OnKeydownMeshTextureListCtrl(wxListEvent &event)
{
    // MFC: TextureMgrDialogClass::OnKeydownMeshTextureListCtrl
    // Handle backspace key to return to mesh list from texture view

    // Check if backspace was pressed (VK_BACK = 0x08 = WXK_BACK)
    if (event.GetKeyCode() == WXK_BACK)
    {
        // Return to mesh list if currently showing textures
        if (!m_bContainsMeshes)
        {
            // TODO(Phase 3 - List Control Integration): Fill_List_Ctrl_With_Meshes()
            // MFC repopulates list control with mesh nodes
            m_bContainsMeshes = true;
        }
    }

    event.Skip();
}

void TextureManagment::OnDestroy(wxWindowDestroyEvent &event)
{
    // MFC Reference: TextureMgrDialog.cpp (OnDestroy)
    // Function: Cleanup image lists and texture names
    //
    // MFC Implementation:
    //   m_ListCtrl.SetImageList(nullptr, LVSIL_NORMAL);
    //   m_ListCtrl.SetImageList(nullptr, LVSIL_SMALL);
    //   SAFE_DELETE(m_pImageList);
    //   SAFE_DELETE(m_pImageListSmall);
    //   SAFE_DELETE(m_pTextureImageList);
    //   SAFE_DELETE(m_pTextureImageListSmall);
    //   m_TextureNames.Delete_All();
    //   CDialog::OnDestroy();
    
    // TODO(Phase 3 - List Control Integration): Image lists and texture data cleanup
    //   When OnInitDialog creates image lists for m_idc_mesh_texture_list_ctrl:
    //   1. Store image list pointers as member variables:
    //      - m_pImageList (normal icons)
    //      - m_pImageListSmall (small icons)
    //      - m_pTextureImageList (texture preview normal)
    //      - m_pTextureImageListSmall (texture preview small)
    //   2. Store texture names collection (m_TextureNames)
    //   3. OnDestroy: Detach from list control and delete all
    //   wxWidgets pattern:
    //     if (m_idc_mesh_texture_list_ctrl) {
    //         m_idc_mesh_texture_list_ctrl->SetImageList(nullptr, wxIMAGE_LIST_NORMAL);
    //         m_idc_mesh_texture_list_ctrl->SetImageList(nullptr, wxIMAGE_LIST_SMALL);
    //     }
    //     delete m_pImageList; m_pImageList = nullptr;
    //     delete m_pImageListSmall; m_pImageListSmall = nullptr;
    //     delete m_pTextureImageList; m_pTextureImageList = nullptr;
    //     delete m_pTextureImageListSmall; m_pTextureImageListSmall = nullptr;
    //     m_TextureNames.clear();  // Or appropriate cleanup
    //   Priority: LOW - wxWidgets may auto-cleanup, but explicit is safer
    //   Note: Only needed if OnInitDialog creates image lists
    
    // Allow base class processing
    event.Skip();
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void TextureManagment::OnInitDialog(wxInitDialogEvent& event)
{
    // Initialize controls after they're created
    // TODO: Convert: CWaitCursor wait_cursor;
    // Allow the base class to process this message
    // TODO: Convert: m_ListCtrl.SetExtendedStyle (LVS_EX_FULLROWSELECT);
    // TODO: Convert: m_Toolbar.CreateEx (this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP, CRect(0, 0, 0, 0), 101);
    // TODO: Convert: m_Toolbar.SetOwner (this);
    // TODO: Convert: m_Toolbar.LoadToolBar (IDR_INSTANCES_TOOLBAR);
    // TODO: Convert: m_Toolbar.SetBarStyle (m_Toolbar.GetBarStyle () | CBRS_TOOLTIPS | CBRS_FLYBY);
    // Get the bounding rectangle of the form window
    // TODO: Convert: CRect rect;
    // TODO: Convert: ::GetWindowRect (::GetDlgItem (m_hWnd, IDC_TOOLBAR_SLOT), &rect);
    // TODO: Convert: ScreenToClient (&rect);
    // TODO: Convert: m_Toolbar.SetWindowPos (nullptr, rect.left, rect.top, rect.Width (), rect.Height (), SWP_NOZORDER);
    // TODO: Convert: ASSERT (m_pBaseModel != nullptr);
    // Create an icon imagelist for the tree control
    // TODO: Convert: m_pImageList = new CImageList;
    // TODO: Convert: m_pImageListSmall = new CImageList;
    // TODO: Convert: m_pTextureImageList = new CImageList;
    // TODO: Convert: m_pTextureImageListSmall = new CImageList;
    // TODO: Convert: m_pImageList->Create (32, 32, ILC_COLOR | ILC_MASK, 1, 2);
    // TODO: Convert: m_pImageListSmall->Create (16, 16, ILC_COLOR | ILC_MASK, 1, 2);
    // TODO: Convert: m_pTextureImageList->Create (TEXTURE_THUMB_X, TEXTURE_THUMB_Y, ILC_COLOR24, 10, 20);
    // TODO: Convert: m_pTextureImageListSmall->Create (TEXTURE_THUMBSMALL_X, TEXTURE_THUMBSMALL_Y, ILC_COLOR24, 10, 20);
    // Load this icon and add it to our imagelist
    // TODO: Convert: m_pImageList->Add ((HICON)::LoadImage (::AfxGetResourceHandle (),
    // TODO: Convert: MAKEINTRESOURCE (IDI_MESH_FOLDER),
    // TODO: Convert: IMAGE_ICON,
    // TODO: Convert: 32,
    // TODO: Convert: 32,
    // TODO: Convert: LR_SHARED));
    // Load this icon and add it to our imagelist
    // TODO: Convert: m_pImageListSmall->Add ((HICON)::LoadImage (::AfxGetResourceHandle (),
    // TODO: Convert: MAKEINTRESOURCE (IDI_MESH_FOLDER),
    // TODO: Convert: IMAGE_ICON,
    // TODO: Convert: 16,
    // TODO: Convert: 16,
    // TODO: Convert: LR_SHARED));
    // Add the name column to the list control
    // TODO: Convert: m_ListCtrl.GetClientRect (&rect);
    // TODO: Convert: m_ListCtrl.InsertColumn (COL_NAME, "Name", LVCFMT_LEFT, (rect.Width () / 2) - 20);
    // Build a list of mesh's and textures
    // TODO: Convert: Add_Subobjs_To_List (m_pBaseModel);
    // TODO: Convert: Fill_List_Ctrl_With_Meshes ();
    
    // MFC: return TRUE;
    event.Skip();
}

bool TextureManagment::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool TextureManagment::TransferDataFromWindow()
{
    // MFC: No data extraction in TransferDataFromWindow
    // Dialog is view-only (texture manager/browser)
    return true;
}

// ============================================================================
// Toolbar Command Handlers (MFC ON_COMMAND implementations)
// ============================================================================

void TextureManagment::OnBack(wxCommandEvent &event)
{
    // MFC: TextureMgrDialogClass::OnBack
    // Display the mesh list when viewing textures
    if (!m_bContainsMeshes)
    {
        // TODO(Phase 3 - List Control Integration): Fill_List_Ctrl_With_Meshes()
        // MFC repopulates list control with mesh nodes when user clicks Back
        // For now, just update state flag - list population requires m_NodeList
        m_bContainsMeshes = true;
    }
}

void TextureManagment::OnDetails(wxCommandEvent &event)
{
    // MFC: TextureMgrDialogClass::OnDetails
    // Set list control to report (details) view
    // MFC: SetWindowLong(m_ListCtrl, GWL_STYLE, (style & (~LVS_TYPEMASK)) | LVS_REPORT)
    if (m_idc_mesh_texture_list_ctrl)
    {
        m_idc_mesh_texture_list_ctrl->SetWindowStyleFlag(
            (m_idc_mesh_texture_list_ctrl->GetWindowStyleFlag() & ~wxLC_MASK_TYPE) | wxLC_REPORT);
    }
}

void TextureManagment::OnLarge(wxCommandEvent &event)
{
    // MFC: TextureMgrDialogClass::OnLarge
    // Set list control to large icon view
    // MFC: SetWindowLong(m_ListCtrl, GWL_STYLE, (style & (~LVS_TYPEMASK)) | LVS_ICON)
    if (m_idc_mesh_texture_list_ctrl)
    {
        m_idc_mesh_texture_list_ctrl->SetWindowStyleFlag(
            (m_idc_mesh_texture_list_ctrl->GetWindowStyleFlag() & ~wxLC_MASK_TYPE) | wxLC_ICON);
    }
}

void TextureManagment::OnList(wxCommandEvent &event)
{
    // MFC: TextureMgrDialogClass::OnList
    // Set list control to list view
    // MFC: SetWindowLong(m_ListCtrl, GWL_STYLE, (style & (~LVS_TYPEMASK)) | LVS_LIST)
    if (m_idc_mesh_texture_list_ctrl)
    {
        m_idc_mesh_texture_list_ctrl->SetWindowStyleFlag(
            (m_idc_mesh_texture_list_ctrl->GetWindowStyleFlag() & ~wxLC_MASK_TYPE) | wxLC_LIST);
    }
}

void TextureManagment::OnSmall(wxCommandEvent &event)
{
    // MFC: TextureMgrDialogClass::OnSmall
    // Set list control to small icon view
    // MFC: SetWindowLong(m_ListCtrl, GWL_STYLE, (style & (~LVS_TYPEMASK)) | LVS_SMALLICON)
    if (m_idc_mesh_texture_list_ctrl)
    {
        m_idc_mesh_texture_list_ctrl->SetWindowStyleFlag(
            (m_idc_mesh_texture_list_ctrl->GetWindowStyleFlag() & ~wxLC_MASK_TYPE) | wxLC_SMALL_ICON);
    }
}

void TextureManagment::OnPropagate(wxCommandEvent &event)
{
    // MFC: TextureMgrDialogClass::OnPropagate
    // Propagate texture settings from selected mesh to all meshes with same texture count
    // This is a complex operation requiring mesh/texture data structures

    // Only valid when showing meshes
    if (!m_bContainsMeshes)
    {
        return;
    }

    // TODO(Phase 3 - List Control Integration): Implement texture propagation
    // MFC implementation:
    // 1. Get selected item: int sel_index = m_ListCtrl.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED)
    // 2. Show warning message: MessageBox("Warning, this operation will copy...")
    // 3. Get source node: TextureListNodeClass* src_node = (TextureListNodeClass*)m_ListCtrl.GetItemData(sel_index)
    // 4. Loop all other meshes with same texture count
    // 5. Copy IndirectTextureClass textures between meshes
    // Requires: m_NodeList, TextureListNodeClass, IndirectTextureClass access
}
