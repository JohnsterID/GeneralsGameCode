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

#include "PropPageEmitterGen_wx.h"
#include <wx/xrc/xmlres.h>
#include <wx/spinbutt.h>

wxBEGIN_EVENT_TABLE(PropPageEmitterGen, PropPageEmitterGenBase)
EVT_BUTTON(XRCID("IDC_BROWSE_BUTTON"), PropPageEmitterGen::OnBrowseButton)  // Button/Checkbox click
    EVT_TEXT(XRCID("IDC_FILENAME_EDIT"), PropPageEmitterGen::OnChangeFilenameEdit)  // Text control change
    EVT_TEXT(XRCID("IDC_NAME_EDIT"), PropPageEmitterGen::OnChangeNameEdit)  // Text control change
    EVT_TEXT(XRCID("IDC_PARTICLE_LIFETIME_EDIT"), PropPageEmitterGen::OnChangeParticleLifetimeEdit)  // Text control change
    EVT_COMBOBOX(XRCID("IDC_SHADER_COMBO"), PropPageEmitterGen::OnSelchangeShaderCombo)  // Combobox selection change
    EVT_CHECKBOX(XRCID("IDC_PARTICLE_LIFETIME_CHECK"), PropPageEmitterGen::OnParticleLifetimeCheck)  // Button/Checkbox click
    EVT_INIT_DIALOG(PropPageEmitterGen::OnInitDialog)
wxEND_EVENT_TABLE()

PropPageEmitterGen::PropPageEmitterGen(wxWindow *parent)
    : PropPageEmitterGenBase(parent)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void PropPageEmitterGen::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void PropPageEmitterGen::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}

// ============================================================================
// Event Handlers (Phase 2 - Auto-integrated)
// ============================================================================

void PropPageEmitterGen::OnBrowseButton(wxCommandEvent &event)
{
    // TODO: Implement OnBrowseButton
    // Control ID: IDC_BROWSE_BUTTON
}

void PropPageEmitterGen::OnChangeFilenameEdit(wxCommandEvent &event)
{
    // TODO: Implement OnChangeFilenameEdit
    // Control ID: IDC_FILENAME_EDIT
}

void PropPageEmitterGen::OnChangeNameEdit(wxCommandEvent &event)
{
    // TODO: Implement OnChangeNameEdit
    // Control ID: IDC_NAME_EDIT
}

void PropPageEmitterGen::OnChangeParticleLifetimeEdit(wxCommandEvent &event)
{
    // TODO: Implement OnChangeParticleLifetimeEdit
    // Control ID: IDC_PARTICLE_LIFETIME_EDIT
}

void PropPageEmitterGen::OnSelchangeShaderCombo(wxCommandEvent &event)
{
    // TODO: Implement OnSelchangeShaderCombo
    // Control ID: IDC_SHADER_COMBO
}

void PropPageEmitterGen::OnParticleLifetimeCheck(wxCommandEvent &event)
{
    // TODO: Implement OnParticleLifetimeCheck
    // Control ID: IDC_PARTICLE_LIFETIME_CHECK
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void PropPageEmitterGen::OnInitDialog(wxInitDialogEvent& event)
{
    // Initialize controls after they're created
    // Allow the base class to process this message
    //
    //	Add the known shaders to the combobox
    //
    // TODO: Convert: Add_Shader_To_Combo (ShaderClass::_PresetAdditiveSpriteShader, "Additive");
    // TODO: Convert: Add_Shader_To_Combo (ShaderClass::_PresetAlphaSpriteShader, "Alpha");
    // TODO: Convert: Add_Shader_To_Combo (ShaderClass::_PresetATestSpriteShader, "Alpha-Test");
    // TODO: Convert: Add_Shader_To_Combo (ShaderClass::_PresetATestBlendSpriteShader, "Alpha-Test-Blend");
    // TODO: Convert: Add_Shader_To_Combo (ShaderClass::_PresetScreenSpriteShader, "Screen");
    // TODO: Convert: Add_Shader_To_Combo (ShaderClass::_PresetMultiplicativeSpriteShader, "Multiplicative");
    // TODO: Convert: Add_Shader_To_Combo (ShaderClass::_PresetOpaqueSpriteShader, "Opaque");
    //
    // Fill the edit controls with the default values
    //
    if (m_idc_name_edit) {
        m_idc_name_edit->SetValue(m_EmitterName);
    }
    if (m_idc_filename_edit) {
        m_idc_filename_edit->SetValue(m_TextureFilename);
    }
    //
    // Initialize the lifetime control
    //
    if (m_idc_particle_lifetime_check) {
        m_idc_particle_lifetime_check->SetValue(m_Lifetime < 100 != 0);  // TODO: Verify boolean logic
    }
    // TODO: Convert: m_Lifetime = 0;
    if (m_idc_particle_lifetime_spin) {
        m_idc_particle_lifetime_spin->SetRange(0, 1000);
        m_idc_particle_lifetime_spin->SetValue(static_cast<int>(m_Lifetime));
    }
    // TODO: Convert: OnParticleLifetimeCheck ();
    //
    // Initialize the render mode combo
    //
    if (m_idc_render_mode_combo) {
        m_idc_render_mode_combo->SetSelection(m_pEmitterList->Get_Render_Mode();
    }
    // TODO: Convert: return TRUE;

    event.Skip();
}

bool PropPageEmitterGen::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool PropPageEmitterGen::TransferDataFromWindow()
{
    // Extract data from controls and apply to business logic

    // TODO: Extract data from controls

    return true;
}
