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
#include <wx/combobox.h>
#include <wx/dialog.h>
#include <wx/spinbutt.h>
#include <wx/statbmp.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/xrc/xmlres.h>

// Base class that loads from XRC
class PropPageSphereGenBase : public wxDialog
{
public:
    PropPageSphereGenBase() {}
    PropPageSphereGenBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_PROP_PAGE_SPHERE_GEN")) {
            return false;
        }

        // Get references to controls
        m_idc_static_1 = XRCCTRL(*this, "IDC_STATIC", wxStaticBitmap);
        m_idc_static_2 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_3 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_name_edit = XRCCTRL(*this, "IDC_NAME_EDIT", wxTextCtrl);
        m_idc_static_4 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_lifetime_edit = XRCCTRL(*this, "IDC_LIFETIME_EDIT", wxTextCtrl);
        m_idc_lifetime_spin = XRCCTRL(*this, "IDC_LIFETIME_SPIN", wxSpinButton);
        m_idc_static_5 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_camera_aligned_check = XRCCTRL(*this, "IDC_CAMERA_ALIGNED_CHECK", wxCheckBox);
        m_idc_looping_check = XRCCTRL(*this, "IDC_LOOPING_CHECK", wxCheckBox);
        m_idc_static_6 = XRCCTRL(*this, "IDC_STATIC", wxStaticBox);
        m_idc_static_7 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_shader_combo = XRCCTRL(*this, "IDC_SHADER_COMBO", wxComboBox);
        m_idc_static_8 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_filename_edit = XRCCTRL(*this, "IDC_FILENAME_EDIT", wxTextCtrl);
        m_idc_browse_button = XRCCTRL(*this, "IDC_BROWSE_BUTTON", wxButton);

        return true;
    }

protected:
    wxStaticBitmap *m_idc_static_1;
    wxStaticText *m_idc_static_2;
    wxStaticText *m_idc_static_3;
    wxTextCtrl *m_idc_name_edit;
    wxStaticText *m_idc_static_4;
    wxTextCtrl *m_idc_lifetime_edit;
    wxSpinButton *m_idc_lifetime_spin;
    wxStaticText *m_idc_static_5;
    wxCheckBox *m_idc_camera_aligned_check;
    wxCheckBox *m_idc_looping_check;
    wxStaticBox *m_idc_static_6;
    wxStaticText *m_idc_static_7;
    wxComboBox *m_idc_shader_combo;
    wxStaticText *m_idc_static_8;
    wxTextCtrl *m_idc_filename_edit;
    wxButton *m_idc_browse_button;
};

// Derived class for event handlers and custom logic
class PropPageSphereGen : public PropPageSphereGenBase
{
public:
    PropPageSphereGen(wxWindow *parent);

protected:
    // Override for data transfer if needed
    // bool TransferDataToWindow() override;
    // bool TransferDataFromWindow() override;

private:
    void OnOK(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
private:
    // Event handlers (Phase 2)
void OnBrowseButton(wxCommandEvent &event);  // Button/Checkbox click
    void OnChangeFilenameEdit(wxCommandEvent &event);  // Text control change
    void OnChangeNameEdit(wxCommandEvent &event);  // Text control change
    void OnChangeLifetimeEdit(wxCommandEvent &event);  // Text control change
    void OnSelchangeShaderCombo(wxCommandEvent &event);  // Combobox selection change
};
