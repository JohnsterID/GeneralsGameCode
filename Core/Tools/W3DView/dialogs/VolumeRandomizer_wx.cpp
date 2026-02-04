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

#include "VolumeRandomizer_wx.h"
#include <wx/xrc/xmlres.h>
#include <wx/spinbutt.h>
#include <wx/msgdlg.h>

wxBEGIN_EVENT_TABLE(VolumeRandomizer, VolumeRandomizerBase)
EVT_CHECKBOX(XRCID("IDC_BOX_RADIO"), VolumeRandomizer::OnBoxRadio)  // Button/Checkbox click
    EVT_CHECKBOX(XRCID("IDC_CYLINDER_RADIO"), VolumeRandomizer::OnCylinderRadio)  // Button/Checkbox click
    EVT_CHECKBOX(XRCID("IDC_SPHERE_RADIO"), VolumeRandomizer::OnSphereRadio)  // Button/Checkbox click
    EVT_INIT_DIALOG(VolumeRandomizer::OnInitDialog)
wxEND_EVENT_TABLE()

VolumeRandomizer::VolumeRandomizer(wxWindow *parent)
    : VolumeRandomizerBase(parent)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void VolumeRandomizer::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void VolumeRandomizer::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}

// ============================================================================
// Event Handlers (Phase 2 - Auto-integrated)
// ============================================================================

void VolumeRandomizer::OnBoxRadio(wxCommandEvent &event)
{
    // MFC Reference: VolumeRandomDialog.cpp (OnBoxRadio)
    // Function: Update control enable states when box radio selected
    //
    // MFC Implementation:
    //   Update_Enable_State();
    
    Update_Enable_State();
}

void VolumeRandomizer::OnCylinderRadio(wxCommandEvent &event)
{
    // MFC Reference: VolumeRandomDialog.cpp (OnCylinderRadio)
    // Function: Update control enable states when cylinder radio selected
    //
    // MFC Implementation:
    //   Update_Enable_State();
    
    Update_Enable_State();
}

void VolumeRandomizer::OnSphereRadio(wxCommandEvent &event)
{
    // MFC Reference: VolumeRandomDialog.cpp (OnSphereRadio)
    // Function: Update control enable states when sphere radio selected
    //
    // MFC Implementation:
    //   Update_Enable_State();
    
    Update_Enable_State();
}

// ============================================================================
// Helper Functions
// ============================================================================

void VolumeRandomizer::Update_Enable_State()
{
    // MFC Reference: VolumeRandomDialog.cpp (Update_Enable_State)
    // Function: Enable/disable controls based on which shape type is selected
    //
    // MFC Implementation:
    //   bool enable_box_ctrls = (SendDlgItemMessage(IDC_BOX_RADIO, BM_GETCHECK) == 1);
    //   bool enable_sphere_ctrls = (SendDlgItemMessage(IDC_SPHERE_RADIO, BM_GETCHECK) == 1);
    //   bool enable_cylinder_ctrls = (SendDlgItemMessage(IDC_CYLINDER_RADIO, BM_GETCHECK) == 1);
    //   EnableWindow(GetDlgItem(IDC_BOX_X_EDIT), enable_box_ctrls);
    //   ... (same for all box/sphere/cylinder controls)
    
    bool enable_box_ctrls = false;
    bool enable_sphere_ctrls = false;
    bool enable_cylinder_ctrls = false;
    
    // Check which radio button is selected
    if (m_idc_box_radio) enable_box_ctrls = m_idc_box_radio->GetValue();
    if (m_idc_sphere_radio) enable_sphere_ctrls = m_idc_sphere_radio->GetValue();
    if (m_idc_cylinder_radio) enable_cylinder_ctrls = m_idc_cylinder_radio->GetValue();
    
    // Update box controls
    if (m_idc_box_x_edit) m_idc_box_x_edit->Enable(enable_box_ctrls);
    if (m_idc_box_y_edit) m_idc_box_y_edit->Enable(enable_box_ctrls);
    if (m_idc_box_z_edit) m_idc_box_z_edit->Enable(enable_box_ctrls);
    if (m_idc_box_x_spin) m_idc_box_x_spin->Enable(enable_box_ctrls);
    if (m_idc_box_y_spin) m_idc_box_y_spin->Enable(enable_box_ctrls);
    if (m_idc_box_z_spin) m_idc_box_z_spin->Enable(enable_box_ctrls);
    
    // Update sphere controls
    if (m_idc_sphere_radius_edit) m_idc_sphere_radius_edit->Enable(enable_sphere_ctrls);
    if (m_idc_sphere_radius_spin) m_idc_sphere_radius_spin->Enable(enable_sphere_ctrls);
    if (m_idc_sphere_hollow_check) m_idc_sphere_hollow_check->Enable(enable_sphere_ctrls);
    
    // Update cylinder controls
    if (m_idc_cylinder_radius_edit) m_idc_cylinder_radius_edit->Enable(enable_cylinder_ctrls);
    if (m_idc_cylinder_radius_spin) m_idc_cylinder_radius_spin->Enable(enable_cylinder_ctrls);
    if (m_idc_cylinder_height_edit) m_idc_cylinder_height_edit->Enable(enable_cylinder_ctrls);
    if (m_idc_cylinder_height_spin) m_idc_cylinder_height_spin->Enable(enable_cylinder_ctrls);
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void VolumeRandomizer::OnInitDialog(wxInitDialogEvent& event)
{
    // Initialize controls after they're created
    //
    //	Start with some default values
    //   MFC defaults: initial_type = IDC_BOX_RADIO
    //
    Vector3 initial_box(1, 1, 1);
    float initial_sphere_radius = 1.0F;
    bool initial_sphere_hollow = false;
    float initial_cylinder_radius = 1.0F;
    float initial_cylinder_height = 1.0F;
    m_initial_type = SHAPE_BOX;  // Default to box (matches MFC IDC_BOX_RADIO)
    //
    //	Initialize from the provided randomizer (if any)
    //
    // TODO(Phase 4 - Vector3Randomizer): Initialize from m_Randomizer
    //   When Vector3Randomizer is available, check Class_ID() to determine type:
    //   - CLASSID_SOLIDBOX: m_initial_type = SHAPE_BOX, get extents
    //   - CLASSID_SOLIDSPHERE: m_initial_type = SHAPE_SPHERE, initial_sphere_hollow = false
    //   - CLASSID_HOLLOWSPHERE: m_initial_type = SHAPE_SPHERE, initial_sphere_hollow = true
    //   - CLASSID_SOLIDCYLINDER: m_initial_type = SHAPE_CYLINDER
    //
    //	Initialize the box controls
    //
    if (m_idc_box_x_spin) {
        m_idc_box_x_spin->SetRange(-10000, 10000);
        m_idc_box_x_spin->SetValue(static_cast<int>(initial_box.X));
    }
    if (m_idc_box_y_spin) {
        m_idc_box_y_spin->SetRange(-10000, 10000);
        m_idc_box_y_spin->SetValue(static_cast<int>(initial_box.Y));
    }
    if (m_idc_box_z_spin) {
        m_idc_box_z_spin->SetRange(-10000, 10000);
        m_idc_box_z_spin->SetValue(static_cast<int>(initial_box.Z));
    }
    //
    //	Initialize the sphere controls
    //
    if (m_idc_sphere_radius_spin) {
        m_idc_sphere_radius_spin->SetRange(0, 10000);
        m_idc_sphere_radius_spin->SetValue(static_cast<int>(initial_sphere_radius));
    }
    if (m_idc_sphere_hollow_check) {
        // MFC: SendDlgItemMessage(IDC_SPHERE_HOLLOW_CHECK, BM_SETCHECK, (WPARAM)initial_sphere_hollow);
        m_idc_sphere_hollow_check->SetValue(initial_sphere_hollow);
    }
    //
    //	Initialize the cylinder controls
    //
    if (m_idc_cylinder_radius_spin) {
        m_idc_cylinder_radius_spin->SetRange(0, 10000);
        m_idc_cylinder_radius_spin->SetValue(static_cast<int>(initial_cylinder_radius));
    }
    if (m_idc_cylinder_height_spin) {
        m_idc_cylinder_height_spin->SetRange(0, 10000);
        m_idc_cylinder_height_spin->SetValue(static_cast<int>(initial_cylinder_height));
    }
    //
    //	Check the appropriate radio
    //   MFC: SendDlgItemMessage(initial_type, BM_SETCHECK, (WPARAM)TRUE);
    //
    switch (m_initial_type) {
        case SHAPE_BOX:
            if (m_idc_box_radio) m_idc_box_radio->SetValue(true);
            break;
        case SHAPE_SPHERE:
            if (m_idc_sphere_radio) m_idc_sphere_radio->SetValue(true);
            break;
        case SHAPE_CYLINDER:
            if (m_idc_cylinder_radio) m_idc_cylinder_radio->SetValue(true);
            break;
    }
    
    // MFC: Update_Enable_State();
    Update_Enable_State();
    
    // MFC: return TRUE;
    event.Skip();
}

bool VolumeRandomizer::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool VolumeRandomizer::TransferDataFromWindow()
{
    // MFC Reference: VolumeRandomDialog.cpp (OnOK)
    // Creates appropriate Vector3Randomizer based on selected radio button
    
    double value;
    
    // Check which radio button is selected
    bool is_box = m_idc_box_radio && m_idc_box_radio->GetValue();
    bool is_sphere = m_idc_sphere_radio && m_idc_sphere_radio->GetValue();
    bool is_cylinder = m_idc_cylinder_radio && m_idc_cylinder_radio->GetValue();
    
    if (is_box) {
        // Create a box randomizer
        Vector3 extents(0, 0, 0);
        if (m_idc_box_x_edit && m_idc_box_x_edit->GetValue().ToDouble(&value)) {
            extents.X = static_cast<float>(value);
        } else {
            wxMessageBox("Please enter a valid numeric value for Box X", "Invalid Input", 
                         wxOK | wxICON_ERROR, this);
            return false;
        }
        if (m_idc_box_y_edit && m_idc_box_y_edit->GetValue().ToDouble(&value)) {
            extents.Y = static_cast<float>(value);
        } else {
            wxMessageBox("Please enter a valid numeric value for Box Y", "Invalid Input", 
                         wxOK | wxICON_ERROR, this);
            return false;
        }
        if (m_idc_box_z_edit && m_idc_box_z_edit->GetValue().ToDouble(&value)) {
            extents.Z = static_cast<float>(value);
        } else {
            wxMessageBox("Please enter a valid numeric value for Box Z", "Invalid Input", 
                         wxOK | wxICON_ERROR, this);
            return false;
        }
        // TODO(Phase 4 - Vector3Randomizer): Create Vector3SolidBoxRandomizer
        //   m_Randomizer = new Vector3SolidBoxRandomizer(extents);
        
    } else if (is_sphere) {
        // Create a sphere randomizer (hollow or solid)
        float radius = 0.0f;
        if (m_idc_sphere_radius_edit && m_idc_sphere_radius_edit->GetValue().ToDouble(&value)) {
            radius = static_cast<float>(value);
        } else {
            wxMessageBox("Please enter a valid numeric value for Sphere Radius", "Invalid Input", 
                         wxOK | wxICON_ERROR, this);
            return false;
        }
        bool is_hollow = m_idc_sphere_hollow_check && m_idc_sphere_hollow_check->GetValue();
        // TODO(Phase 4 - Vector3Randomizer): Create sphere randomizer
        //   if (is_hollow) {
        //       m_Randomizer = new Vector3HollowSphereRandomizer(radius);
        //   } else {
        //       m_Randomizer = new Vector3SolidSphereRandomizer(radius);
        //   }
        (void)radius;
        (void)is_hollow;
        
    } else if (is_cylinder) {
        // Create a cylinder randomizer
        float radius = 0.0f;
        float height = 0.0f;
        if (m_idc_cylinder_radius_edit && m_idc_cylinder_radius_edit->GetValue().ToDouble(&value)) {
            radius = static_cast<float>(value);
        } else {
            wxMessageBox("Please enter a valid numeric value for Cylinder Radius", "Invalid Input", 
                         wxOK | wxICON_ERROR, this);
            return false;
        }
        if (m_idc_cylinder_height_edit && m_idc_cylinder_height_edit->GetValue().ToDouble(&value)) {
            height = static_cast<float>(value);
        } else {
            wxMessageBox("Please enter a valid numeric value for Cylinder Height", "Invalid Input", 
                         wxOK | wxICON_ERROR, this);
            return false;
        }
        // TODO(Phase 4 - Vector3Randomizer): Create Vector3SolidCylinderRandomizer
        //   m_Randomizer = new Vector3SolidCylinderRandomizer(height, radius);
        (void)radius;
        (void)height;
    }
    
    return true;
}
