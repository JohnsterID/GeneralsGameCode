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
#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/spinbutt.h>
#include <wx/statbmp.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/xrc/xmlres.h>
#include "w3dcompat_wx.h"

// Base class that loads from XRC
class VolumeRandomizerBase : public wxDialog
{
public:
    VolumeRandomizerBase() {}
    VolumeRandomizerBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_VOLUME_RANDOMIZER")) {
            return false;
        }

        // Get references to controls
        m_idc_static_1 = XRCCTRL(*this, "IDC_STATIC", wxStaticBitmap);
        m_idc_static_2 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_3 = XRCCTRL(*this, "IDC_STATIC", wxStaticBox);
        m_idc_static_4 = XRCCTRL(*this, "IDC_STATIC", wxStaticBox);
        m_idc_static_5 = XRCCTRL(*this, "IDC_STATIC", wxStaticBox);
        m_idc_box_radio = XRCCTRL(*this, "IDC_BOX_RADIO", wxCheckBox);
        m_idc_sphere_radio = XRCCTRL(*this, "IDC_SPHERE_RADIO", wxCheckBox);
        m_idc_cylinder_radio = XRCCTRL(*this, "IDC_CYLINDER_RADIO", wxCheckBox);
        m_idc_static_6 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_box_x_edit = XRCCTRL(*this, "IDC_BOX_X_EDIT", wxTextCtrl);
        m_idc_box_x_spin = XRCCTRL(*this, "IDC_BOX_X_SPIN", wxSpinButton);
        m_idc_static_7 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_box_y_edit = XRCCTRL(*this, "IDC_BOX_Y_EDIT", wxTextCtrl);
        m_idc_box_y_spin = XRCCTRL(*this, "IDC_BOX_Y_SPIN", wxSpinButton);
        m_idc_static_8 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_box_z_edit = XRCCTRL(*this, "IDC_BOX_Z_EDIT", wxTextCtrl);
        m_idc_box_z_spin = XRCCTRL(*this, "IDC_BOX_Z_SPIN", wxSpinButton);
        m_idc_static_9 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_sphere_radius_edit = XRCCTRL(*this, "IDC_SPHERE_RADIUS_EDIT", wxTextCtrl);
        m_idc_sphere_radius_spin = XRCCTRL(*this, "IDC_SPHERE_RADIUS_SPIN", wxSpinButton);
        m_idc_sphere_hollow_check = XRCCTRL(*this, "IDC_SPHERE_HOLLOW_CHECK", wxCheckBox);
        m_idc_static_10 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_cylinder_radius_edit = XRCCTRL(*this, "IDC_CYLINDER_RADIUS_EDIT", wxTextCtrl);
        m_idc_cylinder_radius_spin = XRCCTRL(*this, "IDC_CYLINDER_RADIUS_SPIN", wxSpinButton);
        m_idc_static_11 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_cylinder_height_edit = XRCCTRL(*this, "IDC_CYLINDER_HEIGHT_EDIT", wxTextCtrl);
        m_idc_cylinder_height_spin = XRCCTRL(*this, "IDC_CYLINDER_HEIGHT_SPIN", wxSpinButton);
        m_idok = XRCCTRL(*this, "IDOK", wxButton);
        m_idcancel = XRCCTRL(*this, "IDCANCEL", wxButton);

        return true;
    }

protected:
    wxStaticBitmap *m_idc_static_1;
    wxStaticText *m_idc_static_2;
    wxStaticBox *m_idc_static_3;
    wxStaticBox *m_idc_static_4;
    wxStaticBox *m_idc_static_5;
    wxCheckBox *m_idc_box_radio;
    wxCheckBox *m_idc_sphere_radio;
    wxCheckBox *m_idc_cylinder_radio;
    wxStaticText *m_idc_static_6;
    wxTextCtrl *m_idc_box_x_edit;
    wxSpinButton *m_idc_box_x_spin;
    wxStaticText *m_idc_static_7;
    wxTextCtrl *m_idc_box_y_edit;
    wxSpinButton *m_idc_box_y_spin;
    wxStaticText *m_idc_static_8;
    wxTextCtrl *m_idc_box_z_edit;
    wxSpinButton *m_idc_box_z_spin;
    wxStaticText *m_idc_static_9;
    wxTextCtrl *m_idc_sphere_radius_edit;
    wxSpinButton *m_idc_sphere_radius_spin;
    wxCheckBox *m_idc_sphere_hollow_check;
    wxStaticText *m_idc_static_10;
    wxTextCtrl *m_idc_cylinder_radius_edit;
    wxSpinButton *m_idc_cylinder_radius_spin;
    wxStaticText *m_idc_static_11;
    wxTextCtrl *m_idc_cylinder_height_edit;
    wxSpinButton *m_idc_cylinder_height_spin;
    wxButton *m_idok;
    wxButton *m_idcancel;
};

// Derived class for event handlers and custom logic
class VolumeRandomizer : public VolumeRandomizerBase
{
public:
    VolumeRandomizer(wxWindow *parent);

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
void OnBoxRadio(wxCommandEvent &event);  // Button/Checkbox click
    void OnCylinderRadio(wxCommandEvent &event);  // Button/Checkbox click
    void OnSphereRadio(wxCommandEvent &event);  // Button/Checkbox click

    // Phase 2.5: Member variables
    Vector3 initial_box;
    float initial_sphere_radius;
    bool initial_sphere_hollow;
    float initial_cylinder_radius;
    float initial_cylinder_height;
    int m_initial_type;
};
