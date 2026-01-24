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
#include <wx/dirdlg.h>

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
    // MFC: CString initial_path; GetDlgItemText(IDC_PATH1, initial_path);
    // MFC: if (::Browse_For_Folder(m_hWnd, initial_path, path)) { SetDlgItemText(IDC_PATH1, path); }
    
    // Get initial path from text control
    wxString initial_path = m_idc_path1->GetValue();
    
    // Show directory selection dialog
    wxDirDialog dialog(this, "Select Texture Path", initial_path, 
                       wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
    
    if (dialog.ShowModal() == wxID_OK) {
        wxString path = dialog.GetPath();
        m_idc_path1->SetValue(path);
    }
}

void TexturePaths::OnBrowse2(wxCommandEvent &event)
{
    // MFC: CString initial_path; GetDlgItemText(IDC_PATH2, initial_path);
    // MFC: if (::Browse_For_Folder(m_hWnd, initial_path, path)) { SetDlgItemText(IDC_PATH2, path); }
    
    // Get initial path from text control
    wxString initial_path = m_idc_path2->GetValue();
    
    // Show directory selection dialog
    wxDirDialog dialog(this, "Select Texture Path", initial_path,
                       wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
    
    if (dialog.ShowModal() == wxID_OK) {
        wxString path = dialog.GetPath();
        m_idc_path2->SetValue(path);
    }
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void TexturePaths::OnInitDialog(wxInitDialogEvent& event)
{
    // Initialize controls after they're created
    // MFC: CW3DViewDoc *doc = ::GetCurrentDocument ();
    // TODO: BLOCKER - Requires document access mechanism in wxWidgets
    // TODO: MFC uses GetCurrentDocument() to access CW3DViewDoc
    // TODO: Need to implement wxWidgets equivalent (pass doc pointer in constructor?)
    // TODO: Once available: m_idc_path1->SetValue(doc->Get_Texture_Path1());
    // TODO: Once available: m_idc_path2->SetValue(doc->Get_Texture_Path2());

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
    // MFC: GetDlgItemText(IDC_PATH1, path1); GetDlgItemText(IDC_PATH2, path2);
    // MFC: CW3DViewDoc *doc = ::GetCurrentDocument();
    // MFC: doc->Set_Texture_Path1(path1); doc->Set_Texture_Path2(path2);
    
    // TODO: BLOCKER - Requires document access mechanism in wxWidgets
    // TODO: Get path1 = m_idc_path1->GetValue()
    // TODO: Get path2 = m_idc_path2->GetValue()
    // TODO: Once doc available: doc->Set_Texture_Path1(path1)
    // TODO: Once doc available: doc->Set_Texture_Path2(path2)

    return true;
}
