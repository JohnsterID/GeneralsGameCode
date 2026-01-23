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
    // TODO: Implement OnBoxRadio
    // Control ID: IDC_BOX_RADIO
}

void VolumeRandomizer::OnCylinderRadio(wxCommandEvent &event)
{
    // TODO: Implement OnCylinderRadio
    // Control ID: IDC_CYLINDER_RADIO
}

void VolumeRandomizer::OnSphereRadio(wxCommandEvent &event)
{
    // TODO: Implement OnSphereRadio
    // Control ID: IDC_SPHERE_RADIO
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void VolumeRandomizer::OnInitDialog(wxInitDialogEvent& event)
{
    // Initialize controls after they're created
    //
    //	Start with some default values
    //
    // TODO: Convert: Vector3 initial_box (1, 1, 1);
    // TODO: Declare: float initial_sphere_radius = 1.0F;
    // TODO: Declare: bool initial_sphere_hollow = false;
    // TODO: Declare: float initial_cylinder_radius = 1.0F;
    // TODO: Declare: float initial_cylinder_height = 1.0F;
    // TODO: Convert: UINT initial_type = IDC_BOX_RADIO;
    //
    //	Initialize from the provided randomizer
    //
    // What type of randomizer is this?
    // TODO: Convert: switch (m_Randomizer->Class_ID ())
    // TODO: Convert: case Vector3Randomizer::CLASSID_SOLIDBOX:
    // TODO: Convert: initial_type = IDC_BOX_RADIO;
    // TODO: Convert: initial_box = ((Vector3SolidBoxRandomizer *)m_Randomizer)->Get_Extents ();
    // TODO: Convert: break;
    // TODO: Convert: case Vector3Randomizer::CLASSID_SOLIDSPHERE:
    // TODO: Convert: initial_type = IDC_SPHERE_RADIO;
    // TODO: Convert: initial_sphere_radius = ((Vector3SolidSphereRandomizer *)m_Randomizer)->Get_Radius();
    // TODO: Convert: initial_sphere_hollow = false;
    // TODO: Convert: break;
    // TODO: Convert: case Vector3Randomizer::CLASSID_HOLLOWSPHERE:
    // TODO: Convert: initial_type = IDC_SPHERE_RADIO;
    // TODO: Convert: initial_sphere_radius = ((Vector3HollowSphereRandomizer *)m_Randomizer)->Get_Radius ();
    // TODO: Convert: initial_sphere_hollow = true;
    // TODO: Convert: break;
    // TODO: Convert: case Vector3Randomizer::CLASSID_SOLIDCYLINDER:
    // TODO: Convert: initial_type = IDC_CYLINDER_RADIO;
    // TODO: Convert: initial_cylinder_radius = ((Vector3SolidCylinderRandomizer *)m_Randomizer)->Get_Radius ();
    // TODO: Convert: initial_cylinder_height = ((Vector3SolidCylinderRandomizer *)m_Randomizer)->Get_Height ();
    // TODO: Convert: break;
    // TODO: Convert: default:
    // TODO: Convert: ASSERT (0);
    // TODO: Convert: break;
    //
    //	Initialize the box controls
    //
    if (m_idc_box_x_spin) {
        m_idc_box_x_spin->SetRange(-10000, 10000);
        m_idc_box_x_spin->SetValue(static_cast<int>(initial_box.x));
    }
    if (m_idc_box_y_spin) {
        m_idc_box_y_spin->SetRange(-10000, 10000);
        m_idc_box_y_spin->SetValue(static_cast<int>(initial_box.y));
    }
    if (m_idc_box_z_spin) {
        m_idc_box_z_spin->SetRange(-10000, 10000);
        m_idc_box_z_spin->SetValue(static_cast<int>(initial_box.z));
    }
    //
    //	Initialize the sphere controls
    //
    if (m_idc_sphere_radius_spin) {
        m_idc_sphere_radius_spin->SetRange(0, 10000);
        m_idc_sphere_radius_spin->SetValue(static_cast<int>(initial_sphere_radius));
    }
    if (m_idc_sphere_hollow_check) {
        m_idc_sphere_hollow_check->SetValue(initial_sphere_hollow != 0);  // TODO: Verify boolean logic
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
    //
    // TODO: Phase 2.5: Set the appropriate radio button based on m_initial_type
    // if (m_initial_type == BOX_TYPE && m_idc_box_radio) {
    //     m_idc_box_radio->SetValue(true);
    // } else if (m_initial_type == SPHERE_TYPE && m_idc_sphere_radio) {
    //     m_idc_sphere_radio->SetValue(true);
    // } else if (m_initial_type == CYLINDER_TYPE && m_idc_cylinder_radio) {
    //     m_idc_cylinder_radio->SetValue(true);
    // }
    // TODO: Convert: Update_Enable_State ();
    // TODO: Convert: return TRUE;

    event.Skip();
}

bool VolumeRandomizer::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool VolumeRandomizer::TransferDataFromWindow()
{
    // Extract data from controls and apply to business logic

    // TODO: Convert: if (SendDlgItemMessage (IDC_BOX_RADIO, BM_GETCHECK) == 1) {
    // TODO: Convert: //
    // TODO: Convert: //	Create a box randomizer
    // TODO: Convert: //
    // TODO: Convert: Vector3 extents (0, 0, 0);
    double value;
    if (m_idc_box_x_edit && m_idc_box_x_edit->GetValue().ToDouble(&value)) {
        // Use value (cast to float if needed)
    } else {
        wxMessageBox("Please enter a valid numeric value", "Invalid Input", 
                     wxOK | wxICON_ERROR, this);
        return false;
    }
    if (m_idc_box_y_edit && m_idc_box_y_edit->GetValue().ToDouble(&value)) {
        // Use value (cast to float if needed)
    } else {
        wxMessageBox("Please enter a valid numeric value", "Invalid Input", 
                     wxOK | wxICON_ERROR, this);
        return false;
    }
    if (m_idc_box_z_edit && m_idc_box_z_edit->GetValue().ToDouble(&value)) {
        // Use value (cast to float if needed)
    } else {
        wxMessageBox("Please enter a valid numeric value", "Invalid Input", 
                     wxOK | wxICON_ERROR, this);
        return false;
    }
    // TODO: Convert: m_Randomizer = new Vector3SolidBoxRandomizer (extents);
    // TODO: Convert: } else if (SendDlgItemMessage (IDC_SPHERE_RADIO, BM_GETCHECK) == 1) {
    // TODO: Convert: //
    // TODO: Convert: //	What type of sphere is this, hollow or solid?
    // TODO: Convert: //
    if (m_idc_sphere_radius_edit && m_idc_sphere_radius_edit->GetValue().ToDouble(&value)) {
        // Use value (cast to float if needed)
    } else {
        wxMessageBox("Please enter a valid numeric value", "Invalid Input", 
                     wxOK | wxICON_ERROR, this);
        return false;
    }
    // TODO: Convert: if (SendDlgItemMessage (IDC_SPHERE_HOLLOW_CHECK, BM_GETCHECK) == 1) {
    // TODO: Convert: m_Randomizer = new Vector3HollowSphereRandomizer (radius);
    // TODO: Convert: } else {
    // TODO: Convert: m_Randomizer = new Vector3SolidSphereRandomizer (radius);
    // TODO: Convert: }
    // TODO: Convert: } else if (SendDlgItemMessage (IDC_CYLINDER_RADIO, BM_GETCHECK) == 1) {
    // TODO: Convert: //
    // TODO: Convert: //	Create a cylinder randomizer
    // TODO: Convert: //
    if (m_idc_cylinder_radius_edit && m_idc_cylinder_radius_edit->GetValue().ToDouble(&value)) {
        // Use value (cast to float if needed)
    } else {
        wxMessageBox("Please enter a valid numeric value", "Invalid Input", 
                     wxOK | wxICON_ERROR, this);
        return false;
    }
    if (m_idc_cylinder_height_edit && m_idc_cylinder_height_edit->GetValue().ToDouble(&value)) {
        // Use value (cast to float if needed)
    } else {
        wxMessageBox("Please enter a valid numeric value", "Invalid Input", 
                     wxOK | wxICON_ERROR, this);
        return false;
    }
    // TODO: Convert: m_Randomizer = new Vector3SolidCylinderRandomizer (height, radius);
    // TODO: Convert: }
    // TODO: Convert: return ;

    return true;
}
