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

#include "PropPageEmitterUser_wx.h"
#include <wx/xrc/xmlres.h>

wxBEGIN_EVENT_TABLE(PropPageEmitterUser, PropPageEmitterUserBase)
EVT_TEXT(XRCID("IDC_PROGRAMMER_SETTINGS_EDIT"), PropPageEmitterUser::OnChangeProgrammerSettingsEdit)  // Text control change
    EVT_COMBOBOX(XRCID("IDC_TYPE_COMBO"), PropPageEmitterUser::OnSelchangeTypeCombo)  // Combobox selection change
    EVT_INIT_DIALOG(PropPageEmitterUser::OnInitDialog)
wxEND_EVENT_TABLE()

PropPageEmitterUser::PropPageEmitterUser(wxWindow *parent)
    : PropPageEmitterUserBase(parent),
      m_iType(0),
      m_UserString(wxEmptyString)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void PropPageEmitterUser::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void PropPageEmitterUser::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}

// ============================================================================
// Event Handlers (Phase 2 - Auto-integrated)
// ============================================================================

void PropPageEmitterUser::OnChangeProgrammerSettingsEdit(wxCommandEvent &event)
{
    // TODO: Implement OnChangeProgrammerSettingsEdit
    // Control ID: IDC_PROGRAMMER_SETTINGS_EDIT
}

void PropPageEmitterUser::OnSelchangeTypeCombo(wxCommandEvent &event)
{
    // TODO: Implement OnSelchangeTypeCombo
    // Control ID: IDC_TYPE_COMBO
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void PropPageEmitterUser::OnInitDialog(wxInitDialogEvent& event)
{
    // Initialize controls after they're created
    // Allow the base class to process this message
    // Add the list of user-types to the combobox
    // TODO: Convert: m_TypeCombo.AddString (EMITTER_TYPE_NAMES[index]);
    // Select the correct entry in the combobox
    if (m_idc_type_combo) {
        m_idc_type_combo->SetSelection(m_iType);
    }
    // Fill in the user-box
    if (m_idc_programmer_settings_edit) {
        m_idc_programmer_settings_edit->SetValue(m_UserString);
    }
    // TODO: Convert: return TRUE;

    event.Skip();
}

bool PropPageEmitterUser::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool PropPageEmitterUser::TransferDataFromWindow()
{
    // Extract data from controls and apply to business logic

    // TODO: Extract data from controls

    return true;
}
