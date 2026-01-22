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
#include <wx/panel.h>
#include <wx/slider.h>
#include <wx/stattext.h>
#include <wx/xrc/xmlres.h>

// Base class that loads from XRC
class LightAmbientDialogBase : public wxDialog
{
public:
    LightAmbientDialogBase() {}
    LightAmbientDialogBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_LIGHT_AMBIENT_DIALOG")) {
            return false;
        }

        // Get references to controls
        m_idc_red_gradient = XRCCTRL(*this, "IDC_RED_GRADIENT", wxPanel);
        m_idc_slider_red = XRCCTRL(*this, "IDC_SLIDER_RED", wxSlider);
        m_idc_green_gradient = XRCCTRL(*this, "IDC_GREEN_GRADIENT", wxPanel);
        m_idc_slider_green = XRCCTRL(*this, "IDC_SLIDER_GREEN", wxSlider);
        m_idc_blue_gradient = XRCCTRL(*this, "IDC_BLUE_GRADIENT", wxPanel);
        m_idc_slider_blue = XRCCTRL(*this, "IDC_SLIDER_BLUE", wxSlider);
        m_idc_grayscale_check = XRCCTRL(*this, "IDC_GRAYSCALE_CHECK", wxCheckBox);
        m_idok = XRCCTRL(*this, "IDOK", wxButton);
        m_idcancel = XRCCTRL(*this, "IDCANCEL", wxButton);
        m_idc_static_1 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_2 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_3 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);

        return true;
    }

protected:
    wxPanel *m_idc_red_gradient;
    wxSlider *m_idc_slider_red;
    wxPanel *m_idc_green_gradient;
    wxSlider *m_idc_slider_green;
    wxPanel *m_idc_blue_gradient;
    wxSlider *m_idc_slider_blue;
    wxCheckBox *m_idc_grayscale_check;
    wxButton *m_idok;
    wxButton *m_idcancel;
    wxStaticText *m_idc_static_1;
    wxStaticText *m_idc_static_2;
    wxStaticText *m_idc_static_3;
};

// Derived class for event handlers and custom logic
class LightAmbientDialog : public LightAmbientDialogBase
{
public:
    LightAmbientDialog(wxWindow *parent);

protected:
    // Override for data transfer if needed
    // bool TransferDataToWindow() override;
    // bool TransferDataFromWindow() override;

private:
    void OnOK(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
};
