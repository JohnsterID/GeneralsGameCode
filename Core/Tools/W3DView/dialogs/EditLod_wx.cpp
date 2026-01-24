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

#include "EditLod_wx.h"
#include <wx/xrc/xmlres.h>

wxBEGIN_EVENT_TABLE(EditLod, EditLodBase)
EVT_SPIN(XRCID("IDC_SWITCH_UP_SPIN"), EditLod::OnDeltaposSwitchUpSpin)  // Spin button change
    EVT_SPIN(XRCID("IDC_SWITCH_DN_SPIN"), EditLod::OnDeltaposSwitchDnSpin)  // Spin button change
    EVT_LIST_ITEM_SELECTED(XRCID("IDC_HIERARCHY_LIST"), EditLod::OnItemChangedHierarchyList)  // List item selection changed
    // ON_EN_UPDATE not needed - wxTextCtrl handles text updates automatically
    EVT_BUTTON(XRCID("IDC_RECALC"), EditLod::OnRecalc)  // Button/Checkbox click
wxEND_EVENT_TABLE()

EditLod::EditLod(wxWindow *parent)
    : EditLodBase(parent)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void EditLod::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void EditLod::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}

// ============================================================================
// Event Handlers (Phase 2 - Auto-integrated)
// ============================================================================

void EditLod::OnDeltaposSwitchUpSpin(wxSpinEvent &event)
{
    // Switch up spin control changed - update LOD switch distance
}

void EditLod::OnDeltaposSwitchDnSpin(wxSpinEvent &event)
{
    // Switch down spin control changed - update LOD switch distance
}

void EditLod::OnItemChangedHierarchyList(wxListEvent &event)
{
    // Hierarchy list selection changed - update LOD info display
}

void EditLod::OnRecalc(wxCommandEvent &event)
{
    // Recalculate LOD values button clicked
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

bool EditLod::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool EditLod::TransferDataFromWindow()
{
    // LOD switch distances are managed by spin controls and text controls
    // Calling code retrieves values from controls directly
    return true;
}
