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

#include "AnimatedSoundDialog_wx.h"
#include <wx/xrc/xmlres.h>
#include <wx/config.h>
#include <wx/filedlg.h>
#include <wx/dirdlg.h>

wxBEGIN_EVENT_TABLE(AnimatedSoundDialog, AnimatedSoundDialogBase)
EVT_BUTTON(XRCID("IDC_SOUND_DEFINITION_LIBRARY_BROWSE_BUTTON"), AnimatedSoundDialog::OnSoundDefinitionLibraryBrowseButton)  // Button/Checkbox click
    EVT_BUTTON(XRCID("IDC_SOUND_INI_BROWSE_BUTTON"), AnimatedSoundDialog::OnSoundIniBrowseButton)  // Button/Checkbox click
    EVT_BUTTON(XRCID("IDC_SOUND_PATH_BROWSE_BUTTON"), AnimatedSoundDialog::OnSoundPathBrowseButton)  // Button/Checkbox click
    EVT_INIT_DIALOG(AnimatedSoundDialog::OnInitDialog)
wxEND_EVENT_TABLE()

AnimatedSoundDialog::AnimatedSoundDialog(wxWindow *parent)
    : AnimatedSoundDialogBase(parent)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void AnimatedSoundDialog::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void AnimatedSoundDialog::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}

// ============================================================================
// Event Handlers (Phase 2 - Auto-integrated)
// ============================================================================

void AnimatedSoundDialog::OnSoundDefinitionLibraryBrowseButton(wxCommandEvent &event)
{
    // MFC: CFileDialog dialog(TRUE, ".ddb", "20480.ddb", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_EXPLORER,
    //                         "Definition Database Files(*.ddb)|*.ddb||", this);
    // MFC: if (dialog.DoModal() == IDOK) { SetDlgItemText(IDC_SOUND_DEFINITION_LIBRARY_EDIT, dialog.GetPathName()); }
    
    wxString currentPath = m_idc_sound_definition_library_edit->GetValue();
    
    wxFileDialog dialog(this, "Select Sound Definition Library", 
                        wxEmptyString, "20480.ddb",
                        "Definition Database Files (*.ddb)|*.ddb",
                        wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    
    if (!currentPath.IsEmpty()) {
        dialog.SetPath(currentPath);
    }
    
    if (dialog.ShowModal() == wxID_OK) {
        m_idc_sound_definition_library_edit->SetValue(dialog.GetPath());
    }
}

void AnimatedSoundDialog::OnSoundIniBrowseButton(wxCommandEvent &event)
{
    // MFC: CFileDialog dialog(TRUE, ".ini", "w3danimsound.ini", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_EXPLORER,
    //                         "INI Files (*.ini)|*.ini||", this);
    // MFC: if (dialog.DoModal() == IDOK) { SetDlgItemText(IDC_SOUND_INI_EDIT, dialog.GetPathName()); }
    
    wxString currentPath = m_idc_sound_ini_edit->GetValue();
    
    wxFileDialog dialog(this, "Select Sound INI File",
                        wxEmptyString, "w3danimsound.ini",
                        "INI Files (*.ini)|*.ini",
                        wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    
    if (!currentPath.IsEmpty()) {
        dialog.SetPath(currentPath);
    }
    
    if (dialog.ShowModal() == wxID_OK) {
        m_idc_sound_ini_edit->SetValue(dialog.GetPath());
    }
}

void AnimatedSoundDialog::OnSoundPathBrowseButton(wxCommandEvent &event)
{
    // MFC: RestrictedFileDialogClass dialog(TRUE, ".wav", "test.wav", OFN_HIDEREADONLY | OFN_EXPLORER,
    //                                        "Directories|*.wav||", AfxGetMainWnd());
    // MFC: dialog.m_ofn.lpstrTitle = "Pick Sound Path";
    // MFC: if (dialog.DoModal() == IDOK) {
    // MFC:     CString path = ::Strip_Filename_From_Path(dialog.GetPathName());
    // MFC:     SetDlgItemText(IDC_SOUND_FILE_PATH_EDIT, path);
    // MFC: }
    
    // Note: MFC uses file dialog to pick directory (extracts path from selected file)
    // wxWidgets: Use wxDirDialog directly for better UX
    wxString currentPath = m_idc_sound_file_path_edit->GetValue();
    
    wxDirDialog dialog(this, "Pick Sound Path", currentPath,
                       wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
    
    if (dialog.ShowModal() == wxID_OK) {
        m_idc_sound_file_path_edit->SetValue(dialog.GetPath());
    }
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void AnimatedSoundDialog::OnInitDialog(wxInitDialogEvent& event)
{
    // Initialize controls after they're created
    // Load configuration values from wxConfig
    wxConfigBase* config = wxConfig::Get();
    wxString sound_def_lib_path = config->Read("Config/SoundDefLibPath", "");
    wxString sound_ini_path = config->Read("Config/AnimSoundINIPath", "");
    wxString sound_data_path = config->Read("Config/AnimSoundDataPath", "");
    
    //
    //	Fill in the default values
    //
    if (m_idc_sound_definition_library_edit) {
        m_idc_sound_definition_library_edit->SetValue(sound_def_lib_path);
    }
    if (m_idc_sound_ini_edit) {
        m_idc_sound_ini_edit->SetValue(sound_ini_path);
    }
    if (m_idc_sound_file_path_edit) {
        m_idc_sound_file_path_edit->SetValue(sound_data_path);
    }

    event.Skip();
}

bool AnimatedSoundDialog::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool AnimatedSoundDialog::TransferDataFromWindow()
{
    // Extract data from controls and apply to business logic
    
    // Get the user's response
    wxString sound_def_lib_path = m_idc_sound_definition_library_edit->GetValue();
    wxString sound_ini_path = m_idc_sound_ini_edit->GetValue();
    wxString sound_data_path = m_idc_sound_file_path_edit->GetValue();
    
    // Store this information in wxConfig (registry/config file)
    wxConfigBase* config = wxConfig::Get();
    config->Write("Config/SoundDefLibPath", sound_def_lib_path);
    config->Write("Config/AnimSoundINIPath", sound_ini_path);
    config->Write("Config/AnimSoundDataPath", sound_data_path);
    config->Flush(); // Ensure written to disk
    
    // TODO: BLOCKER - Requires engine integration (Phase 4)
    // MFC calls: Load_Animated_Sound_Settings();
    // This function:
    //   - Calls DefinitionMgrClass::Free_Definitions()
    //   - Loads sound definition files with FileFactory
    //   - Initializes AnimatedSoundMgrClass
    //   - Configures file search paths
    // Cannot implement until Phase 4 engine integration
    
    return true;
}
