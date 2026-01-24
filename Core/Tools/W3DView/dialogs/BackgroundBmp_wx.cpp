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

#include "BackgroundBmp_wx.h"
#include <wx/xrc/xmlres.h>
#include <wx/filedlg.h>

wxBEGIN_EVENT_TABLE(BackgroundBmp, BackgroundBmpBase)
EVT_BUTTON(XRCID("IDC_BROWSE"), BackgroundBmp::OnBrowse)  // Button/Checkbox click
wxEND_EVENT_TABLE()

BackgroundBmp::BackgroundBmp(wxWindow *parent)
    : BackgroundBmpBase(parent)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void BackgroundBmp::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void BackgroundBmp::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}

// ============================================================================
// Event Handlers (Phase 2 - Auto-integrated)
// ============================================================================

void BackgroundBmp::OnBrowse(wxCommandEvent &event)
{
    // Browse for bitmap file
    wxFileDialog fileDlg(this, "Select Background Bitmap", "", "",
                         "Bitmap Files (*.bmp)|*.bmp|All Files (*.*)|*.*",
                         wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    
    if (fileDlg.ShowModal() == wxID_OK) {
        m_idc_filename_edit->SetValue(fileDlg.GetPath());
    }
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

bool BackgroundBmp::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool BackgroundBmp::TransferDataFromWindow()
{
    // Filename is already in the text control, no additional extraction needed
    // The calling code can retrieve it via the text control
    return true;
}
