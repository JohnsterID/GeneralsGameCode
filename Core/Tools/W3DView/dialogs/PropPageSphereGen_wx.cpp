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
#include <wx/filedlg.h>

wxBEGIN_EVENT_TABLE(PropPageSphereGen, PropPageSphereGenBase)
    EVT_BUTTON(XRCID("IDC_BROWSE_BUTTON"), PropPageSphereGen::OnBrowseButton)
    EVT_TEXT(XRCID("IDC_FILENAME_EDIT"), PropPageSphereGen::OnChangeFilenameEdit)
    EVT_TEXT(XRCID("IDC_NAME_EDIT"), PropPageSphereGen::OnChangeNameEdit)
    EVT_TEXT(XRCID("IDC_LIFETIME_EDIT"), PropPageSphereGen::OnChangeLifetimeEdit)
    EVT_COMBOBOX(XRCID("IDC_SHADER_COMBO"), PropPageSphereGen::OnSelchangeShaderCombo)
    EVT_SPIN(XRCID("IDC_LIFETIME_SPIN"), PropPageSphereGen::OnLifetimeSpin)
    EVT_INIT_DIALOG(PropPageSphereGen::OnInitDialog)
wxEND_EVENT_TABLE()

PropPageSphereGen::PropPageSphereGen(wxWindow *parent)
    : PropPageSphereGenBase(parent),
      m_Name(wxEmptyString),
      m_TextureFilename(wxEmptyString),
      m_Lifetime(1.0f)
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
    // MFC Reference: SphereGeneralPropPage.cpp (OnBrowseButton)
    // Function: Browse for texture file (.tga) and populate filename edit control
    //
    // MFC Implementation:
    //   CFileDialog(TRUE, ".tga", nullptr, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_EXPLORER,
    //               "Textures files (*.tga)|*.tga||", ::AfxGetMainWnd());
    //   if (dialog.DoModal() == IDOK) {
    //       SetDlgItemText(IDC_FILENAME_EDIT, dialog.GetPathName());
    //       SetModified();
    //   }
    
    wxFileDialog fileDialog(
        this,
        "Select Texture File",  // Title
        "",  // Default directory (empty = current)
        "",  // Default filename (empty = none)
        "Texture files (*.tga)|*.tga",  // Wildcard filter
        wxFD_OPEN | wxFD_FILE_MUST_EXIST  // Flags (Open mode, file must exist)
    );
    
    if (fileDialog.ShowModal() == wxID_OK)
    {
        // Get selected file path and set it in the filename edit control
        wxString filepath = fileDialog.GetPath();
        if (m_idc_filename_edit)
        {
            m_idc_filename_edit->SetValue(filepath);
            // Note: SetModified() equivalent would be needed if this were in a property sheet book
            // For standalone dialog, change tracking happens through TransferDataFromWindow
        }
    }
}

void PropPageSphereGen::OnChangeFilenameEdit(wxCommandEvent &event)
{
    // MFC Reference: SphereGeneralPropPage.cpp (OnChangeFilenameEdit)
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

void PropPageSphereGen::OnChangeNameEdit(wxCommandEvent &event)
{
    // MFC Reference: SphereGeneralPropPage.cpp (OnChangeNameEdit)
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

void PropPageSphereGen::OnChangeLifetimeEdit(wxCommandEvent &event)
{
    // MFC Reference: SphereGeneralPropPage.cpp (OnChangeLifetimeEdit)
    // Function: Mark property page as modified when lifetime changes
    //
    // MFC Implementation:
    //   SetModified();
    
    // TODO(Phase 3 - Property Page Tracking): SetModified()
    //   MFC calls SetModified() to enable Apply button in property sheet
    //   wxWidgets requires property sheet tracking infrastructure
    //   Workaround: No-op for now, changes applied immediately on OK
    //   Priority: LOW - functional but no Apply button state tracking
}

void PropPageSphereGen::OnSelchangeShaderCombo(wxCommandEvent &event)
{
    // MFC Reference: SphereGeneralPropPage.cpp (OnSelchangeShaderCombo)
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


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void PropPageSphereGen::OnInitDialog(wxInitDialogEvent& event)
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
	// MFC: return TRUE;

    event.Skip();
}

bool PropPageSphereGen::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool PropPageSphereGen::TransferDataFromWindow()
{
    // Extract data from controls to member variables
    if (m_idc_name_edit)
    {
        m_Name = m_idc_name_edit->GetValue();
    }
    
    if (m_idc_filename_edit)
    {
        m_TextureFilename = m_idc_filename_edit->GetValue();
    }
    
    if (m_idc_lifetime_edit)
    {
        double val;
        if (m_idc_lifetime_edit->GetValue().ToDouble(&val))
        {
            m_Lifetime = static_cast<float>(val);
        }
    }

    return true;
}


// ============================================================================
// Spin Button Handlers (MFC: OnNotify with Update_Spinner_Buddy)
// ============================================================================

void PropPageSphereGen::UpdateSpinnerBuddy(wxTextCtrl* edit, int delta, float minVal, float maxVal)
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

void PropPageSphereGen::OnLifetimeSpin(wxSpinEvent &event)
{
    UpdateSpinnerBuddy(m_idc_lifetime_edit, event.GetPosition(), 0.0f, 1000.0f);
    // TODO(Phase 3 - Sphere): m_RenderObj->Set_Lifetime(value)
}

