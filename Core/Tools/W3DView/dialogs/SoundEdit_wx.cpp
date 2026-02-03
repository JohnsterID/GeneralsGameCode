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

#include "SoundEdit_wx.h"
#include "PlaySoundEffect_wx.h"
#include <wx/xrc/xmlres.h>
#include <wx/filedlg.h>
#include <wx/filename.h>

wxBEGIN_EVENT_TABLE(SoundEdit, SoundEditBase)
EVT_BUTTON(XRCID("IDC_BROWSE"), SoundEdit::OnBrowse)  // Button/Checkbox click
    EVT_CHECKBOX(XRCID("IDC_2D_RADIO"), SoundEdit::On2DRadio)  // Button/Checkbox click
    EVT_CHECKBOX(XRCID("IDC_3D_RADIO"), SoundEdit::On3DRadio)  // Button/Checkbox click
    EVT_BUTTON(XRCID("IDC_PLAY"), SoundEdit::OnPlay)  // Button/Checkbox click
    EVT_SLIDER(XRCID("IDC_VOLUME_SLIDER"), SoundEdit::OnHscroll)  // Horizontal scroll (slider)
    EVT_INIT_DIALOG(SoundEdit::OnInitDialog)
wxEND_EVENT_TABLE()

SoundEdit::SoundEdit(wxWindow *parent)
    : SoundEditBase(parent)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void SoundEdit::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void SoundEdit::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}

// ============================================================================
// Event Handlers (Phase 2 - Auto-integrated)
// ============================================================================

void SoundEdit::OnBrowse(wxCommandEvent &event)
{
    // MFC Reference: SoundEditDialog.cpp (OnBrowse)
    // Function: Browse for sound file (.wav or .mp3), store filename only in control
    //
    // MFC Implementation:
    //   1. Get current filename from control
    //   2. Extract path from filename using Strip_Filename_From_Path
    //   3. Show CFileDialog with .wav/.mp3 filters, set initial directory to extracted path
    //   4. On OK: Extract just filename using Get_Filename_From_Path and store in control
    //   Note: Unlike TextureSettings, this stores ONLY the filename, not the full path
    
    wxString defaultFilename;
    wxString initialDir;
    
    // Get current filename from control
    if (m_idc_filename_edit)
    {
        defaultFilename = m_idc_filename_edit->GetValue();
        
        // Extract directory path if filename contains path separator
        if (!defaultFilename.IsEmpty())
        {
            wxFileName fn(defaultFilename);
            if (fn.HasVolume() || fn.HasName())  // Has path or just filename
            {
                initialDir = fn.GetPath();  // wxWidgets equivalent of Strip_Filename_From_Path
            }
        }
    }
    
    wxFileDialog fileDialog(
        this,
        "Select Sound File",  // Title
        initialDir,  // Initial directory (MFC: dialog.m_ofn.lpstrInitialDir)
        defaultFilename,  // Default filename
        "All Sound Files|*.wav;*.mp3|WAV File (*.wav)|*.wav|MP3 File (*.mp3)|*.mp3",  // Wildcard
        wxFD_OPEN | wxFD_FILE_MUST_EXIST  // Flags
    );
    
    if (fileDialog.ShowModal() == wxID_OK)
    {
        wxString fullPath = fileDialog.GetPath();
        wxFileName fn(fullPath);
        wxString filenameOnly = fn.GetFullName();  // wxWidgets equivalent of Get_Filename_From_Path
        
        // Store only the filename (not full path) in control
        // MFC: SetDlgItemText(IDC_FILENAME_EDIT, Get_Filename_From_Path(dialog.GetPathName()))
        if (m_idc_filename_edit)
        {
            m_idc_filename_edit->SetValue(filenameOnly);
        }
    }
}

void SoundEdit::On2DRadio(wxCommandEvent &event)
{
    // MFC Reference: SoundEditDialog.cpp (On2DRadio)
    // Function: Update control enable states when 2D radio selected
    //
    // MFC Implementation:
    //   Update_Enable_State();
    
    Update_Enable_State();
}

void SoundEdit::On3DRadio(wxCommandEvent &event)
{
    // MFC Reference: SoundEditDialog.cpp (On3DRadio)
    // Function: Update control enable states when 3D radio selected
    //
    // MFC Implementation:
    //   Update_Enable_State();
    
    Update_Enable_State();
}

void SoundEdit::OnPlay(wxCommandEvent &event)
{
    // MFC: SoundEditDialogClass::OnPlay
    // Get the current filename and show the play sound dialog

    wxString filename;
    if (m_idc_filename_edit)
    {
        filename = m_idc_filename_edit->GetValue();
    }

    // Show the play sound dialog (MFC: PlaySoundDialogClass)
    PlaySoundEffect dialog(this, filename);
    dialog.ShowModal();
}

void SoundEdit::OnHscroll(wxCommandEvent &event)
{
    // MFC: ON_WM_HSCROLL - No custom handler in MFC SoundEditDialog
    // MFC uses DDX to bind slider values to member variables automatically
    // wxWidgets: Slider value changes are captured via EVT_SLIDER
    // If we need to update UI based on slider (e.g. show percentage), add here
    // For now, let default processing handle it
    event.Skip();
}

// ============================================================================
// Helper Functions
// ============================================================================

void SoundEdit::Update_Enable_State()
{
    // MFC Reference: SoundEditDialog.cpp (Update_Enable_State)
    // Function: Enable/disable controls based on 2D/3D radio button state
    //
    // MFC Implementation:
    //   bool enable_3d = (SendDlgItemMessage(IDC_3D_RADIO, BM_GETCHECK) == 1);
    //   EnableWindow(GetDlgItem(IDC_MAX_VOL_EDIT), enable_3d);
    //   EnableWindow(GetDlgItem(IDC_DROP_OFF_EDIT), enable_3d);
    //   EnableWindow(GetDlgItem(IDC_TRIGGER_RADIUS_EDIT), !enable_3d);
    
    bool enable_3d = false;
    if (m_idc_3d_radio)
    {
        enable_3d = m_idc_3d_radio->GetValue();  // Check if 3D radio is checked
    }
    
    // Enable 3D-specific controls when 3D mode is selected
    if (m_idc_max_vol_edit) m_idc_max_vol_edit->Enable(enable_3d);
    if (m_idc_drop_off_edit) m_idc_drop_off_edit->Enable(enable_3d);
    
    // Enable 2D-specific controls when 2D mode is selected (opposite of 3D)
    if (m_idc_trigger_radius_edit) m_idc_trigger_radius_edit->Enable(!enable_3d);
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void SoundEdit::OnInitDialog(wxInitDialogEvent& event)
{
    // Initialize controls after they're created
    //
    //	Create the reneder object if we don't already have one
    //
    // TODO: Convert: SoundRObj = new SoundRenderObjClass;
    //
    //	Choose default settings
    //
    // TODO: Convert: OldName						= SoundRObj->Get_Name ();
    // TODO: Declare: bool stop_on_hide			= SoundRObj->Get_Flag (SoundRenderObjClass::FLAG_STOP_WHEN_HIDDEN);
    // TODO: Convert: StringClass filename;
    // TODO: Declare: float drop_off_radius	= 100;
    // TODO: Declare: float max_vol_radius		= 10;
    // TODO: Declare: float priority				= 0.5F;
    // TODO: Declare: bool is_3d					= true;
    // TODO: Declare: bool is_music				= false;
    // TODO: Declare: float loop_count			= 1;
    // TODO: Declare: float volume				= 1.0F;
    //
    // Get the real settings from the sound object (if we have one)
    //
    // TODO: Convert: AudibleSoundClass *sound = SoundRObj->Peek_Sound ();
    // TODO: Convert: Sound3DClass *sound_3d = sound->As_Sound3DClass ();
    // TODO: Convert: filename				= sound->Get_Filename ();
    // TODO: Convert: drop_off_radius	= sound->Get_DropOff_Radius ();
    // TODO: Convert: priority				= sound->Peek_Priority ();
    // TODO: Convert: is_3d					= (sound_3d != nullptr);
    // TODO: Convert: is_music				= (sound->Get_Type () == AudibleSoundClass::TYPE_MUSIC);
    // TODO: Convert: loop_count			= sound->Get_Loop_Count ();
    // TODO: Convert: volume				= sound->Get_Volume ();
    // TODO: Convert: max_vol_radius	= sound_3d->Get_Max_Vol_Radius ();
    //
    // Fill the edit controls
    //
    if (m_idc_name_edit) {
        m_idc_name_edit->SetValue(OldName);
    }
    if (m_idc_filename_edit) {
        m_idc_filename_edit->SetValue(filename);
    }
    //
    // Check the appropriate controls
    //
    // MFC: SendDlgItemMessage(IDC_INFINITE_LOOPS_CHECK, BM_SETCHECK, (WPARAM)(loop_count == 0));
    // MFC: SendDlgItemMessage(IDC_3D_RADIO, BM_SETCHECK, (WPARAM)is_3d);
    // MFC: SendDlgItemMessage(IDC_2D_RADIO, BM_SETCHECK, (WPARAM)(is_3d == false));
    // MFC: SendDlgItemMessage(IDC_MUSIC_RADIO, BM_SETCHECK, (WPARAM)is_music);
    // MFC: SendDlgItemMessage(IDC_SOUNDEFFECT_RADIO, BM_SETCHECK, (WPARAM)(is_music == false));
    // MFC: SendDlgItemMessage(IDC_STOP_WHEN_HIDDEN_CHECK, BM_SETCHECK, (WPARAM)(stop_on_hide));
    if (m_idc_infinite_loops_check) {
        m_idc_infinite_loops_check->SetValue(loop_count == 0);
    }
    if (m_idc_3d_radio) {
        m_idc_3d_radio->SetValue(is_3d);
    }
    if (m_idc_2d_radio) {
        m_idc_2d_radio->SetValue(is_3d == false);
    }
    if (m_idc_music_radio) {
        m_idc_music_radio->SetValue(is_music);
    }
    if (m_idc_soundeffect_radio) {
        m_idc_soundeffect_radio->SetValue(is_music == false);
    }
    if (m_idc_stop_when_hidden_check) {
        m_idc_stop_when_hidden_check->SetValue(stop_on_hide);
    }
    //
    // Set up the sliders
    //
    // MFC: VolumeSlider.SetRange (0, 100);
    if (m_idc_volume_slider) {
        m_idc_volume_slider->SetRange(0, 100);
    }
    // MFC: PrioritySlider.SetRange (0, 100);
    if (m_idc_priority_slider) {
        m_idc_priority_slider->SetRange(0, 100);
    }
    // TODO: Convert: VolumeSlider.SetPos (int(volume * 100.00F));
    // TODO: Convert: PrioritySlider.SetPos (int(priority * 100.00F));
    //
    // Put the attenuation factors into the edit fields
    //
    if (m_idc_drop_off_edit) {
        m_idc_drop_off_edit->SetValue(wxString::Format("%.2f", drop_off_radius));
    }
    if (m_idc_max_vol_edit) {
        m_idc_max_vol_edit->SetValue(wxString::Format("%.2f", max_vol_radius));
    }
    if (m_idc_trigger_radius_edit) {
        m_idc_trigger_radius_edit->SetValue(wxString::Format("%.2f", drop_off_radius));
    }
    //
    //	Make sure the appropriate controls are enabled/disabled
    //
    // MFC: Update_Enable_State();
    Update_Enable_State();
    
    // MFC: return TRUE;
    event.Skip();
}

bool SoundEdit::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool SoundEdit::TransferDataFromWindow()
{
    // Extract data from controls and apply to business logic

    // TODO: Convert: CString name;
    // TODO: Convert: GetDlgItemText (IDC_NAME_EDIT, name);
    // TODO: Convert: //
    // TODO: Convert: //	Early exit if the name isn't valid
    // TODO: Convert: //
    // TODO: Convert: if (name.GetLength () == 0) {
    // TODO: Convert: ::MessageBox (m_hWnd, "Invalid object name.  Please enter a new name.", "Invalid settings", MB_ICONEXCLAMATION | MB_OK);
    // TODO: Convert: return ;
    // TODO: Convert: }
    // TODO: Convert: //
    // TODO: Convert: //	Create a sound definition from the settings on the dialog
    // TODO: Convert: //
    // TODO: Convert: AudibleSoundClass *sound = Create_Sound_Object ();
    // TODO: Convert: AudibleSoundDefinitionClass definition;
    // TODO: Convert: definition.Initialize_From_Sound (sound);
    // TODO: Convert: REF_PTR_RELEASE (sound);
    // TODO: Convert: //
    // TODO: Convert: //	Pass the sound definition onto the render object
    // TODO: Convert: //
    // TODO: Convert: SoundRObj->Set_Sound (&definition);
    // TODO: Convert: //
    // TODO: Convert: //	Pass the flags onto the render object
    // TODO: Convert: //
    // TODO: Convert: if (SendDlgItemMessage (IDC_STOP_WHEN_HIDDEN_CHECK, BM_GETCHECK) == 1) {
    // TODO: Convert: SoundRObj->Set_Flags (SoundRenderObjClass::FLAG_STOP_WHEN_HIDDEN);
    // TODO: Convert: } else {
    // TODO: Convert: SoundRObj->Set_Flags (0);
    // TODO: Convert: }
    // TODO: Convert: //
    // TODO: Convert: //	Name the render object
    // TODO: Convert: //
    // TODO: Convert: SoundRObj->Set_Name (name);
    // TODO: Convert: //
    // TODO: Convert: //	Add this sound object to the viewer
    // TODO: Convert: //
    // TODO: Convert: CW3DViewDoc *doc = ::GetCurrentDocument ();
    // TODO: Convert: if (doc != nullptr) {
    // TODO: Convert: //
    // TODO: Convert: // Create a new prototype for this emitter and add it to the asset manager
    // TODO: Convert: //
    // TODO: Convert: SoundRenderObjDefClass *definition			= new SoundRenderObjDefClass (*SoundRObj);
    // TODO: Convert: SoundRenderObjPrototypeClass *prototype	= new SoundRenderObjPrototypeClass (definition);
    // TODO: Convert: //
    // TODO: Convert: // Update the asset manager with the new prototype
    // TODO: Convert: //
    // TODO: Convert: if (!OldName.Is_Empty()) {
    // TODO: Convert: WW3DAssetManager::Get_Instance()->Remove_Prototype (OldName);
    // TODO: Convert: }
    // TODO: Convert: WW3DAssetManager::Get_Instance()->Add_Prototype (prototype);
    // TODO: Convert: //
    // TODO: Convert: // Add the new object to the data tree
    // TODO: Convert: //
    // TODO: Convert: CDataTreeView *data_tree = doc->GetDataTreeView ();
    // TODO: Convert: data_tree->Refresh_Asset (name, OldName, TypeSound);
    // TODO: Convert: //
    // TODO: Convert: // Display the emitter
    // TODO: Convert: //
    // TODO: Convert: doc->Reload_Displayed_Object ();
    // TODO: Convert: OldName = name;
    // TODO: Convert: }
    // TODO: Convert: return ;

    return true;
}
