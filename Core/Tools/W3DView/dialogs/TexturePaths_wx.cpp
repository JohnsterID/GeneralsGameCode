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

#include "TexturePaths_wx.h"
#include <wx/xrc/xmlres.h>

wxBEGIN_EVENT_TABLE(TexturePaths, TexturePathsBase)
EVT_BUTTON(XRCID("IDC_BROWSE1"), TexturePaths::OnBrowse1)  // Button/Checkbox click
    EVT_BUTTON(XRCID("IDC_BROWSE2"), TexturePaths::OnBrowse2)  // Button/Checkbox click
    EVT_INIT_DIALOG(TexturePaths::OnInitDialog)
wxEND_EVENT_TABLE()

TexturePaths::TexturePaths(wxWindow *parent)
    : TexturePathsBase(parent)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void TexturePaths::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void TexturePaths::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}

// ============================================================================
// Event Handlers (Phase 2 - Auto-integrated)
// ============================================================================

void TexturePaths::OnBrowse1(wxCommandEvent &event)
{
    // TODO: Implement OnBrowse1
    // Control ID: IDC_BROWSE1
}

void TexturePaths::OnBrowse2(wxCommandEvent &event)
{
    // TODO: Implement OnBrowse2
    // Control ID: IDC_BROWSE2
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void TexturePaths::OnInitDialog(wxInitDialogEvent& event)
{
    // Initialize controls after they're created
    // TODO: Convert: CW3DViewDoc *doc = ::GetCurrentDocument ();
    if (m_idc_path1) {
        m_idc_path1->SetValue(doc->Get_Texture_Path1 ();
    }
    if (m_idc_path2) {
        m_idc_path2->SetValue(doc->Get_Texture_Path2 ();
    }
    // TODO: Convert: return TRUE;

    event.Skip();
}

bool TexturePaths::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool TexturePaths::TransferDataFromWindow()
{
    // Extract data from controls and apply to business logic

    // TODO: Convert: CString path1;
    // TODO: Convert: CString path2;
    // TODO: Convert: GetDlgItemText (IDC_PATH1, path1);
    // TODO: Convert: GetDlgItemText (IDC_PATH2, path2);
    // TODO: Convert: CW3DViewDoc *doc = ::GetCurrentDocument ();
    // TODO: Convert: doc->Set_Texture_Path1 (path1);
    // TODO: Convert: doc->Set_Texture_Path2 (path2);
    // TODO: Convert: return ;

    return true;
}
