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
    : PropPageEmitterGenBase(parent),
      m_EmitterName(wxEmptyString),
      m_TextureFilename(wxEmptyString),
      m_Lifetime(0.0f)
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
    // MFC: CFileDialog openFileDialog(TRUE, ".tga", nullptr, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_EXPLORER,
    //                                  "Textures files (*.tga)|*.tga||", ::AfxGetMainWnd());
    // MFC: if (openFileDialog.DoModal() == IDOK) {
    // MFC:     SetDlgItemText(IDC_FILENAME_EDIT, openFileDialog.GetPathName());
    // MFC:     SetModified();
    // MFC: }
    
    // TODO: BLOCKER - Requires EmitterInstanceListClass* pointer (constructor dependency)
    // TODO: BLOCKER - File dialog result needs SetModified() for property page architecture
    // TODO: BLOCKER - Texture filename applied to emitter object in TransferDataFromWindow
    // TODO: Can implement wxFileDialog for .tga files (simple)
    // TODO: But cannot complete handler without engine integration (Phase 4)
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
    
    // TODO: BLOCKER - Requires ShaderClass static instances from rendering engine (Phase 4)
    // MFC: Add_Shader_To_Combo (ShaderClass::_PresetAdditiveSpriteShader, "Additive");
    // MFC: Add_Shader_To_Combo (ShaderClass::_PresetAlphaSpriteShader, "Alpha");
    // MFC: Add_Shader_To_Combo (ShaderClass::_PresetATestSpriteShader, "Alpha-Test");
    // MFC: Add_Shader_To_Combo (ShaderClass::_PresetATestBlendSpriteShader, "Alpha-Test-Blend");
    // MFC: Add_Shader_To_Combo (ShaderClass::_PresetScreenSpriteShader, "Screen");
    // MFC: Add_Shader_To_Combo (ShaderClass::_PresetMultiplicativeSpriteShader, "Multiplicative");
    // MFC: Add_Shader_To_Combo (ShaderClass::_PresetOpaqueSpriteShader, "Opaque");
    // TODO: ShaderClass instances cannot be created without rendering engine
    // TODO: Add_Shader_To_Combo stores ShaderClass* as combo item data for later retrieval
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
    // TODO: Phase 3 - Initialize from emitter list when available
    // if (m_idc_render_mode_combo && m_pEmitterList) {
    //     m_idc_render_mode_combo->SetSelection(m_pEmitterList->Get_Render_Mode());
    // }
    if (m_idc_render_mode_combo) {
        m_idc_render_mode_combo->SetSelection(0);  // Default selection
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
