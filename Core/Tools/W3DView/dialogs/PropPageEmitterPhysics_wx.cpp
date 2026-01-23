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

#include "PropPageEmitterPhysics_wx.h"
#include <wx/xrc/xmlres.h>
#include <wx/spinbutt.h>

wxBEGIN_EVENT_TABLE(PropPageEmitterPhysics, PropPageEmitterPhysicsBase)
EVT_BUTTON(XRCID("IDC_SPECIFY_VELOCITY_RANDOM"), PropPageEmitterPhysics::OnSpecifyVelocityRandom)  // Button/Checkbox click
    EVT_INIT_DIALOG(PropPageEmitterPhysics::OnInitDialog)
wxEND_EVENT_TABLE()

PropPageEmitterPhysics::PropPageEmitterPhysics(wxWindow *parent)
    : PropPageEmitterPhysicsBase(parent),
      m_OutFactor(0.0f),
      m_InheritanceFactor(0.0f),
      m_Velocity(0.0f, 0.0f, 0.0f),
      m_Acceleration(0.0f, 0.0f, 0.0f)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void PropPageEmitterPhysics::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void PropPageEmitterPhysics::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}

// ============================================================================
// Event Handlers (Phase 2 - Auto-integrated)
// ============================================================================

void PropPageEmitterPhysics::OnSpecifyVelocityRandom(wxCommandEvent &event)
{
    // TODO: Implement OnSpecifyVelocityRandom
    // Control ID: IDC_SPECIFY_VELOCITY_RANDOM
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void PropPageEmitterPhysics::OnInitDialog(wxInitDialogEvent& event)
{
    // Initialize controls after they're created
    // Allow the base class to process this message
    //
    //	Setup the velocity controls
    //
    if (m_idc_out_factor_spin) {
        m_idc_out_factor_spin->SetRange(-10000, 10000);
        m_idc_out_factor_spin->SetValue(static_cast<int>(m_OutFactor));
    }
    if (m_idc_inheritance_factor_spin) {
        m_idc_inheritance_factor_spin->SetRange(-10000, 10000);
        m_idc_inheritance_factor_spin->SetValue(static_cast<int>(m_InheritanceFactor));
    }
    if (m_idc_velocity_x_spin) {
        m_idc_velocity_x_spin->SetRange(-10000, 10000);
        m_idc_velocity_x_spin->SetValue(static_cast<int>(m_Velocity.X));
    }
    if (m_idc_velocity_y_spin) {
        m_idc_velocity_y_spin->SetRange(-10000, 10000);
        m_idc_velocity_y_spin->SetValue(static_cast<int>(m_Velocity.Y));
    }
    if (m_idc_velocity_z_spin) {
        m_idc_velocity_z_spin->SetRange(-10000, 10000);
        m_idc_velocity_z_spin->SetValue(static_cast<int>(m_Velocity.Z));
    }
    //
    //	Setup the acceleration controls
    //
    if (m_idc_acceleration_x_spin) {
        m_idc_acceleration_x_spin->SetRange(-10000, 10000);
        m_idc_acceleration_x_spin->SetValue(static_cast<int>(m_Acceleration.X));
    }
    if (m_idc_acceleration_y_spin) {
        m_idc_acceleration_y_spin->SetRange(-10000, 10000);
        m_idc_acceleration_y_spin->SetValue(static_cast<int>(m_Acceleration.Y));
    }
    if (m_idc_acceleration_z_spin) {
        m_idc_acceleration_z_spin->SetRange(-10000, 10000);
        m_idc_acceleration_z_spin->SetValue(static_cast<int>(m_Acceleration.Z));
    }
    // TODO: Convert: return TRUE;

    event.Skip();
}

bool PropPageEmitterPhysics::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool PropPageEmitterPhysics::TransferDataFromWindow()
{
    // Extract data from controls and apply to business logic

    // TODO: Extract data from controls

    return true;
}
