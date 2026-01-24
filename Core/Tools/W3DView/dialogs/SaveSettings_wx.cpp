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

#include "SaveSettings_wx.h"
#include <wx/xrc/xmlres.h>
#include <wx/filedlg.h>

wxBEGIN_EVENT_TABLE(SaveSettings, SaveSettingsBase)
EVT_BUTTON(XRCID("IDC_BROWSE_BUTTON"), SaveSettings::OnBrowseButton)  // Button/Checkbox click
    // ON_EN_UPDATE not needed - wxTextCtrl handles text updates automatically
wxEND_EVENT_TABLE()

SaveSettings::SaveSettings(wxWindow *parent)
    : SaveSettingsBase(parent)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void SaveSettings::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void SaveSettings::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}

// ============================================================================
// Event Handlers (Phase 2 - Auto-integrated)
// ============================================================================

void SaveSettings::OnBrowseButton(wxCommandEvent &event)
{
    // Browse for save file location
    wxFileDialog fileDlg(this, "Save Settings", "", "",
                         "Settings Files (*.ini)|*.ini|All Files (*.*)|*.*",
                         wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    
    if (fileDlg.ShowModal() == wxID_OK) {
        m_idc_filename_edit->SetValue(fileDlg.GetPath());
    }
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

bool SaveSettings::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool SaveSettings::TransferDataFromWindow()
{
    // Filename is in the text control, calling code retrieves it directly
    return true;
}
