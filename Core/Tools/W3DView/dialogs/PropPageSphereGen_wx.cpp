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

#include "PropPageSphereGen_wx.h"
#include <wx/xrc/xmlres.h>
#include <wx/spinbutt.h>

wxBEGIN_EVENT_TABLE(PropPageSphereGen, PropPageSphereGenBase)
EVT_BUTTON(XRCID("IDC_BROWSE_BUTTON"), PropPageSphereGen::OnBrowseButton)  // Button/Checkbox click
    EVT_TEXT(XRCID("IDC_FILENAME_EDIT"), PropPageSphereGen::OnChangeFilenameEdit)  // Text control change
    EVT_TEXT(XRCID("IDC_NAME_EDIT"), PropPageSphereGen::OnChangeNameEdit)  // Text control change
    EVT_TEXT(XRCID("IDC_LIFETIME_EDIT"), PropPageSphereGen::OnChangeLifetimeEdit)  // Text control change
    EVT_COMBOBOX(XRCID("IDC_SHADER_COMBO"), PropPageSphereGen::OnSelchangeShaderCombo)  // Combobox selection change
wxEND_EVENT_TABLE()

PropPageSphereGen::PropPageSphereGen(wxWindow *parent)
    : PropPageSphereGenBase(parent)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void PropPageSphereGen::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void PropPageSphereGen::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}

// ============================================================================
// Event Handlers (Phase 2 - Auto-integrated)
// ============================================================================

void PropPageSphereGen::OnBrowseButton(wxCommandEvent &event)
{
    // TODO: Implement OnBrowseButton
    // Control ID: IDC_BROWSE_BUTTON
}

void PropPageSphereGen::OnChangeFilenameEdit(wxCommandEvent &event)
{
    // TODO: Implement OnChangeFilenameEdit
    // Control ID: IDC_FILENAME_EDIT
}

void PropPageSphereGen::OnChangeNameEdit(wxCommandEvent &event)
{
    // TODO: Implement OnChangeNameEdit
    // Control ID: IDC_NAME_EDIT
}

void PropPageSphereGen::OnChangeLifetimeEdit(wxCommandEvent &event)
{
    // TODO: Implement OnChangeLifetimeEdit
    // Control ID: IDC_LIFETIME_EDIT
}

void PropPageSphereGen::OnSelchangeShaderCombo(wxCommandEvent &event)
{
    // TODO: Implement OnSelchangeShaderCombo
    // Control ID: IDC_SHADER_COMBO

// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void PropPageSphereGenBase::OnInitDialog(wxInitDialogEvent& event)
{
    // Initialize controls after they're created
    // Allow the base class to process this message
    //
    //	Add the known shaders to the combobox
    //
    // TODO: Convert: Add_Shader_To_Combo (ShaderClass::_PresetAdditiveShader, "Additive");
    // TODO: Convert: Add_Shader_To_Combo (ShaderClass::_PresetAlphaShader, "Alpha");
    // TODO: Convert: Add_Shader_To_Combo (ShaderClass::_PresetOpaqueShader, "Opaque");
    // TODO: Convert: Add_Shader_To_Combo (ShaderClass::_PresetMultiplicativeShader, "Multiplicative");
    // TODO: Convert: CheckDlgButton (IDC_CAMERA_ALIGNED_CHECK, (m_RenderObj->Get_Flags () & SphereRenderObjClass::USE_CAMERA_ALIGN) != 0);
    // TODO: Convert: CheckDlgButton (IDC_LOOPING_CHECK, (m_RenderObj->Get_Flags () & SphereRenderObjClass::USE_ANIMATION_LOOP) != 0);
    //
    // Fill the edit controls with the default values
    //
    if (m_idc_name_edit) {
        m_idc_name_edit->SetValue(m_Name);
    }
    if (m_idc_filename_edit) {
        m_idc_filename_edit->SetValue(m_TextureFilename);
    }
    //
    // Initialize the lifetime control
    //
    if (m_idc_lifetime_spin) {
        m_idc_lifetime_spin->SetRange(0, 1000);
        m_idc_lifetime_spin->SetValue(static_cast<int>(m_Lifetime));
    }
    // TODO: Convert: return TRUE;

    event.Skip();
}

bool PropPageSphereGenBase::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool PropPageSphereGenBase::TransferDataFromWindow()
{
    // Extract data from controls and apply to business logic

    // TODO: Extract data from controls

    return true;
}

}
