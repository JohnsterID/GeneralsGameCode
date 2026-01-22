/*
**Command & Conquer Renegade(tm)
**Copyright 2025 Electronic Arts Inc.
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

#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/panel.h>
#include <wx/statbmp.h>
#include <wx/stattext.h>
#include <wx/xrc/xmlres.h>

// Base class that loads from XRC
class PropPageSphereColorBase : public wxDialog
{
public:
    PropPageSphereColorBase() {}
    PropPageSphereColorBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_PROP_PAGE_SPHERE_COLOR")) {
            return false;
        }

        // Get references to controls
        m_idc_static_1 = XRCCTRL(*this, "IDC_STATIC", wxStaticBitmap);
        m_idc_static_2 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_3 = XRCCTRL(*this, "IDC_STATIC", wxPanel);
        m_idc_static_4 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_color_bar = XRCCTRL(*this, "IDC_COLOR_BAR", wxPanel);
        m_idc_static_5 = XRCCTRL(*this, "IDC_STATIC", wxPanel);
        m_idc_static_6 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_opacity_bar = XRCCTRL(*this, "IDC_OPACITY_BAR", wxPanel);
        m_idc_static_7 = XRCCTRL(*this, "IDC_STATIC", wxPanel);
        m_idc_opacity_vector_check = XRCCTRL(*this, "IDC_OPACITY_VECTOR_CHECK", wxCheckBox);
        m_idc_invert_vector_check = XRCCTRL(*this, "IDC_INVERT_VECTOR_CHECK", wxCheckBox);
        m_idc_vector_bar = XRCCTRL(*this, "IDC_VECTOR_BAR", wxPanel);

        return true;
    }

protected:
    wxStaticBitmap *m_idc_static_1;
    wxStaticText *m_idc_static_2;
    wxPanel *m_idc_static_3;
    wxStaticText *m_idc_static_4;
    wxPanel *m_idc_color_bar;
    wxPanel *m_idc_static_5;
    wxStaticText *m_idc_static_6;
    wxPanel *m_idc_opacity_bar;
    wxPanel *m_idc_static_7;
    wxCheckBox *m_idc_opacity_vector_check;
    wxCheckBox *m_idc_invert_vector_check;
    wxPanel *m_idc_vector_bar;
};

// Derived class for event handlers and custom logic
class PropPageSphereColor : public PropPageSphereColorBase
{
public:
    PropPageSphereColor(wxWindow *parent);

protected:
    // Override for data transfer if needed
    // bool TransferDataToWindow() override;
    // bool TransferDataFromWindow() override;

private:
    void OnOK(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
};
