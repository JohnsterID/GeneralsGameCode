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

#include "TextureSettings_wx.h"
#include <wx/xrc/xmlres.h>
#include <wx/filedlg.h>

wxBEGIN_EVENT_TABLE(TextureSettings, TextureSettingsBase)
EVT_CHECKBOX(XRCID("IDC_ANIMATION_CHECK"), TextureSettings::OnAnimationCheck)  // Button/Checkbox click
    EVT_WINDOW_DESTROY(TextureSettings::OnDestroy)  // Window destruction
    EVT_BUTTON(XRCID("IDC_BROWSE_BUTTON"), TextureSettings::OnBrowseButton)  // Button/Checkbox click
    EVT_BUTTON(XRCID("IDC_RESTORE"), TextureSettings::OnRestore)  // Button/Checkbox click
    EVT_BUTTON(XRCID("IDC_APPLY"), TextureSettings::OnApply)  // Button/Checkbox click
    EVT_INIT_DIALOG(TextureSettings::OnInitDialog)
wxEND_EVENT_TABLE()

TextureSettings::TextureSettings(wxWindow *parent)
    : TextureSettingsBase(parent)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void TextureSettings::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void TextureSettings::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}

// ============================================================================
// Event Handlers (Phase 2 - Auto-integrated)
// ============================================================================

void TextureSettings::OnAnimationCheck(wxCommandEvent &event)
{
    // MFC Reference: TextureSettingsDialog.cpp (OnAnimationCheck)
    // Function: Enable/disable animation-related controls based on checkbox state
    //
    // MFC Implementation:
    //   bool benable = (SendDlgItemMessage(IDC_ANIMATION_CHECK, BM_GETCHECK) == 1);
    //   EnableWindow(GetDlgItem(IDC_FRAME_COUNT_EDIT), benable);
    //   EnableWindow(GetDlgItem(IDC_FPS_EDIT), benable);
    //   EnableWindow(m_TypeCombo, benable);
    //   EnableWindow(m_FrameRateSpin, benable);
    //   EnableWindow(m_FrameCountSpin, benable);
    
    bool enable = false;
    if (m_idc_animation_check)
    {
        enable = m_idc_animation_check->GetValue();  // Checkbox state
    }
    
    // Enable/disable animation controls based on checkbox state
    if (m_idc_frame_count_edit) m_idc_frame_count_edit->Enable(enable);
    if (m_idc_fps_edit) m_idc_fps_edit->Enable(enable);
    if (m_idc_type_combo) m_idc_type_combo->Enable(enable);
    if (m_idc_fps_spin) m_idc_fps_spin->Enable(enable);
    if (m_idc_frame_count_spin) m_idc_frame_count_spin->Enable(enable);
}

void TextureSettings::OnDestroy(wxWindowDestroyEvent &event)
{
    // MFC Reference: TextureSettingsDialog.cpp (OnDestroy)
    // Function: Cleanup dialog resources
    //
    // MFC Implementation:
    //   if (m_hThumbnail != nullptr) {
    //       DeleteObject(m_hThumbnail);
    //       m_hThumbnail = nullptr;
    //   }
    //   CDialog::OnDestroy();
    //
    // wxWidgets: 
    //   Bitmap cleanup is automatic (no manual DeleteObject needed)
    //   wxWidgets uses smart pointers/automatic memory management
    //   Just call event.Skip() to allow base class processing
    
    event.Skip();  // Allow base class to process destruction
}

void TextureSettings::OnBrowseButton(wxCommandEvent &event)
{
    // MFC Reference: TextureSettingsDialog.cpp (OnBrowseButton)
    // Function: Browse for .tga texture file, update filename control, enable apply button
    //
    // MFC Implementation:
    //   1. Get current filename from control as default
    //   2. Show CFileDialog with .tga filter
    //   3. On OK:
    //      - WW3D::Add_Search_Path(Strip_Filename_From_Path(dialog.GetFileName()))
    //      - SetDlgItemText(IDC_FILENAME_EDIT, dialog.GetFileName())
    //      - Select all text in control (EM_SETSEL)
    //      - Enable apply button
    
    // Get current filename to use as default
    wxString currentFilename;
    if (m_idc_filename_edit)
    {
        currentFilename = m_idc_filename_edit->GetValue();
    }
    
    wxFileDialog fileDialog(
        this,
        "Select Texture File",  // Title
        "",  // Default directory (empty = use current)
        currentFilename,  // Default filename
        "Targa files (*.tga)|*.tga",  // Wildcard filter (MFC: "Targa files (*.tga)|*.tga||")
        wxFD_OPEN | wxFD_FILE_MUST_EXIST  // Flags
    );
    
    if (fileDialog.ShowModal() == wxID_OK)
    {
        wxString filepath = fileDialog.GetPath();  // Full path (matches MFC GetFileName())
        
        // TODO(MFC-Match): Add search path for texture loading
        //   MFC calls: WW3D::Add_Search_Path(Strip_Filename_From_Path(filepath))
        //   This adds the directory containing the texture to WW3D's search paths
        //   Need to verify if WW3D::Add_Search_Path() is available in wxWidgets build
        //   and if Strip_Filename_From_Path is in Utils_wx.cpp
        //   Priority: MEDIUM - texture loading may fail without correct search path
        
        // Set filename in control
        if (m_idc_filename_edit)
        {
            m_idc_filename_edit->SetValue(filepath);
            m_idc_filename_edit->SelectAll();  // MFC: SendDlgItemMessage(EM_SETSEL, 0, -1)
        }
        
        // Enable apply button (MFC: EnableWindow(GetDlgItem(IDC_APPLY), TRUE))
        if (m_idc_apply)
        {
            m_idc_apply->Enable(true);
        }
    }
}

void TextureSettings::OnRestore(wxCommandEvent &event)
{
    // TODO: Implement OnRestore
    // Control ID: IDC_RESTORE
}

void TextureSettings::OnApply(wxCommandEvent &event)
{
    // TODO: Implement OnApply
    // Control ID: IDC_APPLY
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void TextureSettings::OnInitDialog(wxInitDialogEvent& event)
{
    // Initialize controls after they're created
    // Allow the base class to process this message
    // TODO: Convert: ASSERT (m_pTexture != nullptr);
    // TODO: Convert: ASSERT (m_pTexture->getClassID () == ID_INDIRECT_TEXTURE_CLASS);
    // Determine what the starting texture was so we can restore on cancel (if necessary)
    // TODO: Convert: m_pStartingTexture = m_pTexture->Get_Texture ();
    //m_pStartingTexture->addReference ();
    // Set the range of the spin controls
    // TODO: Convert: m_FrameCountSpin.SetRange (1, 10000);
    // TODO: Convert: m_FrameRateSpin.SetRange (1, 10000);
    // Remove the border from around our child window
    // TODO: Convert: HWND hchild_wnd = ::GetDlgItem (m_hWnd, IDC_TEXTURE_THUMBNAIL);
    // TODO: Convert: LONG style = ::GetWindowLong (hchild_wnd, GWL_STYLE);
    // TODO: Convert: ::SetWindowLong (hchild_wnd, GWL_STYLE, style & (~WS_BORDER));
    // Enable or disable the 'restore' button based on whether or not we
    // have an original texture to switch to...
    // TODO: Convert: ::EnableWindow (::GetDlgItem (m_hWnd, IDC_RESTORE), (m_pOriginalTexture != nullptr));
    // TODO: Convert: ::EnableWindow (::GetDlgItem (m_hWnd, IDC_APPLY), FALSE);
    // Fill the dialog controls with data from the texture
    // TODO: Convert: Load_Texture_Settings ();
    // TODO: Convert: return TRUE;

    event.Skip();
}

bool TextureSettings::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool TextureSettings::TransferDataFromWindow()
{
    // Extract data from controls and apply to business logic

    // TODO: Convert: // Force the new settings to take effect
    // TODO: Convert: OnApply ();
    // TODO: Convert: // Allow the base class to process this message
    // TODO: Convert: return ;

    return true;
}
