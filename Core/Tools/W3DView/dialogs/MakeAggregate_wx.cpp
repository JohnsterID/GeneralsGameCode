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

#include "MakeAggregate_wx.h"
#include <wx/xrc/xmlres.h>
#include "w3d_file.h"  // For W3D_NAME_LEN

wxBEGIN_EVENT_TABLE(MakeAggregate, MakeAggregateBase)
    EVT_INIT_DIALOG(MakeAggregate::OnInitDialog)
wxEND_EVENT_TABLE()

MakeAggregate::MakeAggregate(wxWindow *parent)
    : MakeAggregateBase(parent)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void MakeAggregate::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void MakeAggregate::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void MakeAggregate::OnInitDialog(wxInitDialogEvent& event)
{
    // Initialize controls after they're created
    // Restrict the amount of text a user can type into the control
    // W3D_NAME_LEN is defined in w3d_file.h as 16 characters
    if (m_idc_aggregate_name) {
        m_idc_aggregate_name->SetMaxLength(W3D_NAME_LEN - 1);
        m_idc_aggregate_name->SetValue(m_Name);
    }

    event.Skip();
}

bool MakeAggregate::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool MakeAggregate::TransferDataFromWindow()
{
    // Extract data from controls and apply to business logic
    if (m_idc_aggregate_name) {
        m_Name = m_idc_aggregate_name->GetValue();
    }

    return true;
}
