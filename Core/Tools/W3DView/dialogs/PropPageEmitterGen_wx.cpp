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
#include <wx/filedlg.h>

wxBEGIN_EVENT_TABLE(PropPageEmitterGen, PropPageEmitterGenBase)
    EVT_BUTTON(XRCID("IDC_BROWSE_BUTTON"), PropPageEmitterGen::OnBrowseButton)
    EVT_TEXT(XRCID("IDC_FILENAME_EDIT"), PropPageEmitterGen::OnChangeFilenameEdit)
    EVT_TEXT(XRCID("IDC_NAME_EDIT"), PropPageEmitterGen::OnChangeNameEdit)
    EVT_TEXT(XRCID("IDC_PARTICLE_LIFETIME_EDIT"), PropPageEmitterGen::OnChangeParticleLifetimeEdit)
    EVT_COMBOBOX(XRCID("IDC_SHADER_COMBO"), PropPageEmitterGen::OnSelchangeShaderCombo)
    EVT_CHECKBOX(XRCID("IDC_PARTICLE_LIFETIME_CHECK"), PropPageEmitterGen::OnParticleLifetimeCheck)
    EVT_SPIN(XRCID("IDC_PARTICLE_LIFETIME_SPIN"), PropPageEmitterGen::OnParticleLifetimeSpin)
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
    wxFileDialog openFileDialog(
        this,
        "Select Texture File",
        "",  // Default directory
        "",  // Default filename
        "Texture files (*.tga)|*.tga",
        wxFD_OPEN | wxFD_FILE_MUST_EXIST
    );

    if (openFileDialog.ShowModal() == wxID_OK)
    {
        // MFC: SetDlgItemText(IDC_FILENAME_EDIT, openFileDialog.GetPathName());
        if (m_idc_filename_edit)
        {
            m_idc_filename_edit->SetValue(openFileDialog.GetPath());
        }
        // TODO(Phase 3 - Property Page Tracking): SetModified()
        // MFC calls SetModified() to enable Apply button in property sheet
    }
}

void PropPageEmitterGen::OnChangeFilenameEdit(wxCommandEvent &event)
{
    // MFC Reference: EmitterGeneralPropPage.cpp (OnChangeFilenameEdit)
    // Function: Mark property page as modified when filename changes
    //
    // MFC Implementation:
    //   SetModified();
    
    // TODO(Phase 3 - Property Page Tracking): SetModified()
    //   MFC calls SetModified() to enable Apply button in property sheet
    //   wxWidgets requires property sheet tracking infrastructure
    //   Workaround: No-op for now, changes applied immediately on OK
    //   Priority: LOW - functional but no Apply button state tracking
}

void PropPageEmitterGen::OnChangeNameEdit(wxCommandEvent &event)
{
    // MFC Reference: EmitterGeneralPropPage.cpp (OnChangeNameEdit)
    // Function: Mark property page as modified when name changes
    //
    // MFC Implementation:
    //   SetModified();
    
    // TODO(Phase 3 - Property Page Tracking): SetModified()
    //   MFC calls SetModified() to enable Apply button in property sheet
    //   wxWidgets requires property sheet tracking infrastructure
    //   Workaround: No-op for now, changes applied immediately on OK
    //   Priority: LOW - functional but no Apply button state tracking
}

void PropPageEmitterGen::OnChangeParticleLifetimeEdit(wxCommandEvent &event)
{
    // MFC Reference: EmitterGeneralPropPage.cpp (OnChangeParticleLifetimeEdit)
    // Function: Mark property page as modified when particle lifetime changes
    //
    // MFC Implementation:
    //   SetModified();
    
    // TODO(Phase 3 - Property Page Tracking): SetModified()
    //   MFC calls SetModified() to enable Apply button in property sheet
    //   wxWidgets requires property sheet tracking infrastructure
    //   Workaround: No-op for now, changes applied immediately on OK
    //   Priority: LOW - functional but no Apply button state tracking
}

void PropPageEmitterGen::OnSelchangeShaderCombo(wxCommandEvent &event)
{
    // MFC Reference: EmitterGeneralPropPage.cpp (OnSelchangeShaderCombo)
    // Function: Mark property page as modified when shader selection changes
    //
    // MFC Implementation:
    //   SetModified();
    
    // TODO(Phase 3 - Property Page Tracking): SetModified()
    //   MFC calls SetModified() to enable Apply button in property sheet
    //   wxWidgets requires property sheet tracking infrastructure
    //   Workaround: No-op for now, changes applied immediately on OK
    //   Priority: LOW - functional but no Apply button state tracking
}

void PropPageEmitterGen::OnParticleLifetimeCheck(wxCommandEvent &event)
{
    // MFC Reference: EmitterGeneralPropPage.cpp (OnParticleLifetimeCheck)
    // Function: Enable/disable particle lifetime controls based on checkbox state
    //
    // MFC Implementation:
    //   bool enable = (SendDlgItemMessage(IDC_PARTICLE_LIFETIME_CHECK, BM_GETCHECK) == 1);
    //   EnableWindow(GetDlgItem(IDC_PARTICLE_LIFETIME_EDIT), enable);
    //   EnableWindow(GetDlgItem(IDC_PARTICLE_LIFETIME_SPIN), enable);
    //   if (enable == false) {
    //       m_Lifetime = 0;
    //       SetDlgItemFloat(IDC_PARTICLE_LIFETIME_EDIT, 0);
    //   }
    //   SetModified();
    
    bool enable = false;
    if (m_idc_particle_lifetime_check)
    {
        enable = m_idc_particle_lifetime_check->GetValue();
    }
    
    // Enable/disable lifetime controls based on checkbox
    if (m_idc_particle_lifetime_edit) m_idc_particle_lifetime_edit->Enable(enable);
    if (m_idc_particle_lifetime_spin) m_idc_particle_lifetime_spin->Enable(enable);
    
    // If disabled, clear the lifetime value
    if (!enable && m_idc_particle_lifetime_edit)
    {
        m_idc_particle_lifetime_edit->SetValue("0");
    }
    
    // NOTE(MFC-Match): SetModified() not needed - wxWidgets uses standalone dialogs
    // MFC property pages use SetModified() to enable Apply button in CPropertySheet.
    // Our wxWidgets implementation uses standalone wxDialog, not wxPropertySheetDialog,
    // so Apply button state management is not applicable.
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
        // MFC: SendDlgItemMessage(IDC_PARTICLE_LIFETIME_CHECK, BM_SETCHECK, (WPARAM)(m_Lifetime < 100));
        m_idc_particle_lifetime_check->SetValue(m_Lifetime < 100);
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
	// MFC: return TRUE;

    event.Skip();
}

bool PropPageEmitterGen::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool PropPageEmitterGen::TransferDataFromWindow()
{
    // Extract data from controls to member variables
    // MFC: GetDlgItemText(IDC_NAME_EDIT, m_EmitterName);
    if (m_idc_name_edit)
    {
        m_EmitterName = m_idc_name_edit->GetValue();
    }

    // MFC: GetDlgItemText(IDC_FILENAME_EDIT, m_TextureFilename);
    if (m_idc_filename_edit)
    {
        m_TextureFilename = m_idc_filename_edit->GetValue();
    }

    // MFC: m_Lifetime = GetDlgItemFloat(IDC_PARTICLE_LIFETIME_EDIT);
    if (m_idc_particle_lifetime_edit)
    {
        double val;
        if (m_idc_particle_lifetime_edit->GetValue().ToDouble(&val))
        {
            m_Lifetime = static_cast<float>(val);
        }
    }

    // TODO(Phase 4): Apply extracted data to emitter object
    // MFC: m_pEmitterList->Set_Name(m_EmitterName);
    // MFC: m_pEmitterList->Set_Texture_Filename(m_TextureFilename);
    // MFC: m_pEmitterList->Set_Lifetime(m_Lifetime);
    return true;
}


// ============================================================================
// Spin Button Handlers (MFC: OnNotify with Update_Spinner_Buddy)
// ============================================================================

void PropPageEmitterGen::UpdateSpinnerBuddy(wxTextCtrl* edit, int delta, float minVal, float maxVal)
{
    // MFC Reference: Utils.cpp Update_Spinner_Buddy
    if (!edit) return;
    
    double currentValue = 0.0;
    edit->GetValue().ToDouble(&currentValue);
    
    currentValue += delta * 0.01f;  // Match MFC: delta / 100.0
    
    if (currentValue < minVal) currentValue = minVal;
    if (currentValue > maxVal) currentValue = maxVal;
    
    edit->SetValue(wxString::Format("%.2f", currentValue));
}

void PropPageEmitterGen::OnParticleLifetimeSpin(wxSpinEvent &event)
{
    UpdateSpinnerBuddy(m_idc_particle_lifetime_edit, event.GetPosition(), 0.0f, 1000.0f);
    // TODO(Phase 3 - Emitter): m_pEmitterList->Set_Lifetime(value)
}
