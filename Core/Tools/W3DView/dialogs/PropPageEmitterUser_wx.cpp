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
wxEND_EVENT_TABLE()

PropPageEmitterUser::PropPageEmitterUser(wxWindow *parent)
    : PropPageEmitterUserBase(parent)
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
