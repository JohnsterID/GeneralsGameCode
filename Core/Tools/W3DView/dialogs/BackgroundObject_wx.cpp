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

#include "BackgroundObject_wx.h"
#include <wx/xrc/xmlres.h>
#include "../w3dcompat_wx.h"
#include "../w3dviewdoc_wx.h"
#include "assetmgr.h"
#include "rendobj.h"

wxBEGIN_EVENT_TABLE(BackgroundObject, BackgroundObjectBase)
    EVT_LIST_ITEM_SELECTED(XRCID("IDC_HIERARCHY_LIST"), BackgroundObject::OnItemChangedHierarchyList)  // List item selection changed
    EVT_BUTTON(XRCID("IDC_CLEAR"), BackgroundObject::OnClear)  // Button/Checkbox click
    EVT_INIT_DIALOG(BackgroundObject::OnInitDialog)
wxEND_EVENT_TABLE()

BackgroundObject::BackgroundObject(wxWindow *parent)
    : BackgroundObjectBase(parent)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void BackgroundObject::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void BackgroundObject::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}

// ============================================================================
// Event Handlers (Phase 2 - Auto-integrated)
// ============================================================================

void BackgroundObject::OnInitDialog(wxInitDialogEvent& event)
{
    // MFC: BackgroundObjectDialog.cpp:44-96 (OnInitDialog)
    
    // Setup list columns
    m_idc_hierarchy_list->InsertColumn(0, "Name", wxLIST_FORMAT_LEFT, 200);
    
    // Enumerate hierarchies from asset manager
    RenderObjIterator *objEnum = WW3DAssetManager::Get_Instance()->Create_Render_Obj_Iterator();
    if (objEnum) {
        for (objEnum->First(); !objEnum->Is_Done(); objEnum->Next()) {
            const char *itemName = objEnum->Current_Item_Name();
            
            // Check if this is a hierarchy (CLASSID_HMODEL)
            if (WW3DAssetManager::Get_Instance()->Render_Obj_Exists(itemName) &&
                objEnum->Current_Item_Class_ID() == RenderObjClass::CLASSID_HMODEL) {
                // Add hierarchy to list
                long index = m_idc_hierarchy_list->InsertItem(0, wxString::FromUTF8(itemName));
            }
        }
        delete objEnum;
    }
    
    // Show current background object
    W3DViewDoc *doc = GetCurrentDocument_wx();
    if (doc) {
        m_idc_curr_obj->SetLabel(doc->GetBackgroundObjectName());
    }
    
    event.Skip();
}

void BackgroundObject::OnItemChangedHierarchyList(wxListEvent &event)
{
    // MFC: BackgroundObjectDialog.cpp:157-176 (OnItemChangedHierarchyList)
    // Update current object label with selected item
    long index = event.GetIndex();
    if (index != -1) {
        wxString itemName = m_idc_hierarchy_list->GetItemText(index);
        m_idc_curr_obj->SetLabel(itemName);
    }
}

void BackgroundObject::OnClear(wxCommandEvent &event)
{
    // MFC: BackgroundObjectDialog.cpp:181-194 (OnClear)
    // Clear the selection
    long index = m_idc_hierarchy_list->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (index != -1) {
        m_idc_hierarchy_list->SetItemState(index, 0, wxLIST_STATE_SELECTED);
    }
    m_idc_curr_obj->SetLabel("");
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

bool BackgroundObject::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool BackgroundObject::TransferDataFromWindow()
{
    // MFC: BackgroundObjectDialog.cpp:199-221 (OnOK)
    W3DViewDoc *doc = GetCurrentDocument_wx();
    if (doc) {
        // Get selected item index
        long index = m_idc_hierarchy_list->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
        if (index != -1) {
            // Get item name and set as background object
            wxString itemName = m_idc_hierarchy_list->GetItemText(index);
            doc->SetBackgroundObject(itemName);
        } else {
            // No selection - clear background object
            doc->SetBackgroundObject(wxEmptyString);
        }
    }
    return true;
}
