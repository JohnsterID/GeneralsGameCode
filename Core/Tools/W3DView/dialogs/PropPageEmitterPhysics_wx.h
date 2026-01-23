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

#pragma once

#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/panel.h>
#include "../w3dcompat_wx.h"  // For Vector3
#include <wx/spinbutt.h>
#include <wx/statbmp.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/xrc/xmlres.h>

// Base class that loads from XRC
class PropPageEmitterPhysicsBase : public wxDialog
{
public:
    PropPageEmitterPhysicsBase() {}
    PropPageEmitterPhysicsBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_PROP_PAGE_EMITTER_PHYSICS")) {
            return false;
        }

        // Get references to controls
        m_idc_static_1 = XRCCTRL(*this, "IDC_STATIC", wxStaticBitmap);
        m_idc_static_2 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_3 = XRCCTRL(*this, "IDC_STATIC", wxPanel);
        m_idc_static_4 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_5 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_velocity_x_edit = XRCCTRL(*this, "IDC_VELOCITY_X_EDIT", wxTextCtrl);
        m_idc_velocity_x_spin = XRCCTRL(*this, "IDC_VELOCITY_X_SPIN", wxSpinButton);
        m_idc_static_6 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_velocity_y_edit = XRCCTRL(*this, "IDC_VELOCITY_Y_EDIT", wxTextCtrl);
        m_idc_velocity_y_spin = XRCCTRL(*this, "IDC_VELOCITY_Y_SPIN", wxSpinButton);
        m_idc_static_7 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_velocity_z_edit = XRCCTRL(*this, "IDC_VELOCITY_Z_EDIT", wxTextCtrl);
        m_idc_velocity_z_spin = XRCCTRL(*this, "IDC_VELOCITY_Z_SPIN", wxSpinButton);
        m_idc_specify_velocity_random = XRCCTRL(*this, "IDC_SPECIFY_VELOCITY_RANDOM", wxButton);
        m_idc_static_8 = XRCCTRL(*this, "IDC_STATIC", wxPanel);
        m_idc_static_9 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_10 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_out_factor_edit = XRCCTRL(*this, "IDC_OUT_FACTOR_EDIT", wxTextCtrl);
        m_idc_out_factor_spin = XRCCTRL(*this, "IDC_OUT_FACTOR_SPIN", wxSpinButton);
        m_idc_static_11 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_inheritance_factor_edit = XRCCTRL(*this, "IDC_INHERITANCE_FACTOR_EDIT", wxTextCtrl);
        m_idc_inheritance_factor_spin = XRCCTRL(*this, "IDC_INHERITANCE_FACTOR_SPIN", wxSpinButton);
        m_idc_static_12 = XRCCTRL(*this, "IDC_STATIC", wxPanel);
        m_idc_static_13 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_14 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_acceleration_x_edit = XRCCTRL(*this, "IDC_ACCELERATION_X_EDIT", wxTextCtrl);
        m_idc_acceleration_x_spin = XRCCTRL(*this, "IDC_ACCELERATION_X_SPIN", wxSpinButton);
        m_idc_static_15 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_acceleration_y_edit = XRCCTRL(*this, "IDC_ACCELERATION_Y_EDIT", wxTextCtrl);
        m_idc_acceleration_y_spin = XRCCTRL(*this, "IDC_ACCELERATION_Y_SPIN", wxSpinButton);
        m_idc_static_16 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_acceleration_z_edit = XRCCTRL(*this, "IDC_ACCELERATION_Z_EDIT", wxTextCtrl);
        m_idc_acceleration_z_spin = XRCCTRL(*this, "IDC_ACCELERATION_Z_SPIN", wxSpinButton);

        return true;
    }

protected:
    wxStaticBitmap *m_idc_static_1;
    wxStaticText *m_idc_static_2;
    wxPanel *m_idc_static_3;
    wxStaticText *m_idc_static_4;
    wxStaticText *m_idc_static_5;
    wxTextCtrl *m_idc_velocity_x_edit;
    wxSpinButton *m_idc_velocity_x_spin;
    wxStaticText *m_idc_static_6;
    wxTextCtrl *m_idc_velocity_y_edit;
    wxSpinButton *m_idc_velocity_y_spin;
    wxStaticText *m_idc_static_7;
    wxTextCtrl *m_idc_velocity_z_edit;
    wxSpinButton *m_idc_velocity_z_spin;
    wxButton *m_idc_specify_velocity_random;
    wxPanel *m_idc_static_8;
    wxStaticText *m_idc_static_9;
    wxStaticText *m_idc_static_10;
    wxTextCtrl *m_idc_out_factor_edit;
    wxSpinButton *m_idc_out_factor_spin;
    wxStaticText *m_idc_static_11;
    wxTextCtrl *m_idc_inheritance_factor_edit;
    wxSpinButton *m_idc_inheritance_factor_spin;
    wxPanel *m_idc_static_12;
    wxStaticText *m_idc_static_13;
    wxStaticText *m_idc_static_14;
    wxTextCtrl *m_idc_acceleration_x_edit;
    wxSpinButton *m_idc_acceleration_x_spin;
    wxStaticText *m_idc_static_15;
    wxTextCtrl *m_idc_acceleration_y_edit;
    wxSpinButton *m_idc_acceleration_y_spin;
    wxStaticText *m_idc_static_16;
    wxTextCtrl *m_idc_acceleration_z_edit;
    wxSpinButton *m_idc_acceleration_z_spin;
};

// Derived class for event handlers and custom logic
class PropPageEmitterPhysics : public PropPageEmitterPhysicsBase
{
public:
    PropPageEmitterPhysics(wxWindow *parent);
    
    // Dialog data (MFC compatibility)
    float m_OutFactor;             // Outward velocity factor
    float m_InheritanceFactor;     // Velocity inheritance factor
    Vector3 m_Velocity;            // Particle velocity vector
    Vector3 m_Acceleration;        // Particle acceleration vector

protected:
    // Override for data transfer if needed
    // bool TransferDataToWindow() override;
    // bool TransferDataFromWindow() override;

private:
    void OnOK(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
private:
    // Phase 2.5: Dialog infrastructure
    void OnInitDialog(wxInitDialogEvent& event);
    bool TransferDataToWindow() override;
    bool TransferDataFromWindow() override;

    // Event handlers (Phase 2)
void OnSpecifyVelocityRandom(wxCommandEvent &event);  // Button/Checkbox click
};
