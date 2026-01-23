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
#include <wx/xrc/xmlres.h>

wxBEGIN_EVENT_TABLE(SoundEdit, SoundEditBase)
EVT_BUTTON(XRCID("IDC_BROWSE"), SoundEdit::OnBrowse)  // Button/Checkbox click
    EVT_CHECKBOX(XRCID("IDC_2D_RADIO"), SoundEdit::On2DRadio)  // Button/Checkbox click
    EVT_CHECKBOX(XRCID("IDC_3D_RADIO"), SoundEdit::On3DRadio)  // Button/Checkbox click
    EVT_BUTTON(XRCID("IDC_PLAY"), SoundEdit::OnPlay)  // Button/Checkbox click
    EVT_SLIDER(XRCID("IDC_VOLUME_SLIDER"), SoundEdit::OnHscroll)  // Horizontal scroll (slider)
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
    // TODO: Implement OnBrowse
    // Control ID: IDC_BROWSE
}

void SoundEdit::On2DRadio(wxCommandEvent &event)
{
    // TODO: Implement On2DRadio
    // Control ID: IDC_2D_RADIO
}

void SoundEdit::On3DRadio(wxCommandEvent &event)
{
    // TODO: Implement On3DRadio
    // Control ID: IDC_3D_RADIO
}

void SoundEdit::OnPlay(wxCommandEvent &event)
{
    // TODO: Implement OnPlay
    // Control ID: IDC_PLAY
}

void SoundEdit::OnHscroll(wxCommandEvent &event)
{
    // TODO: Implement OnHscroll

// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void SoundEditBase::OnInitDialog(wxInitDialogEvent& event)
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
    if (m_idc_infinite_loops_check) {
        m_idc_infinite_loops_check->SetValue(loop_count == 0 != 0);  // TODO: Verify boolean logic
    }
    if (m_idc_3d_radio) {
        m_idc_3d_radio->SetValue(is_3d != 0);  // TODO: Verify boolean logic
    }
    if (m_idc_2d_radio) {
        m_idc_2d_radio->SetValue(is_3d == false != 0);  // TODO: Verify boolean logic
    }
    if (m_idc_music_radio) {
        m_idc_music_radio->SetValue(is_music != 0);  // TODO: Verify boolean logic
    }
    if (m_idc_soundeffect_radio) {
        m_idc_soundeffect_radio->SetValue(is_music == false != 0);  // TODO: Verify boolean logic
    }
    if (m_idc_stop_when_hidden_check) {
        m_idc_stop_when_hidden_check->SetValue(stop_on_hide != 0);  // TODO: Verify boolean logic
    }
    //
    // Set up the sliders
    //
    // TODO: Convert: VolumeSlider.SetRange (0, 100);
    // TODO: Convert: PrioritySlider.SetRange (0, 100);
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
    // TODO: Convert: Update_Enable_State ();
    // TODO: Convert: return TRUE;

    event.Skip();
}

bool SoundEditBase::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool SoundEditBase::TransferDataFromWindow()
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

}
