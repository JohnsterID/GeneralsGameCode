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

#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/slider.h>
#include <wx/statbmp.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/xrc/xmlres.h>

// Base class that loads from XRC
class DisplayspeedBase : public wxDialog
{
public:
    DisplayspeedBase() {}
    DisplayspeedBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_DISPLAYSPEED")) {
            return false;
        }

        // Get references to controls
        m_idc_static_1 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_speed_slider = XRCCTRL(*this, "IDC_SPEED_SLIDER", wxSlider);
        m_idc_blend = XRCCTRL(*this, "IDC_BLEND", wxCheckBox);
        m_idok = XRCCTRL(*this, "IDOK", wxButton);
        m_idcancel = XRCCTRL(*this, "IDCANCEL", wxButton);
        m_idc_static_2 = XRCCTRL(*this, "IDC_STATIC", wxStaticBitmap);
        m_idc_static_3 = XRCCTRL(*this, "IDC_STATIC", wxStaticBox);
        m_idc_compressq = XRCCTRL(*this, "IDC_COMPRESSQ", wxCheckBox);
        m_idc_16bit = XRCCTRL(*this, "IDC_16BIT", wxCheckBox);
        m_idc_8bit = XRCCTRL(*this, "IDC_8BIT", wxCheckBox);

        return true;
    }

protected:
    wxStaticText *m_idc_static_1;
    wxSlider *m_idc_speed_slider;
    wxCheckBox *m_idc_blend;
    wxButton *m_idok;
    wxButton *m_idcancel;
    wxStaticBitmap *m_idc_static_2;
    wxStaticBox *m_idc_static_3;
    wxCheckBox *m_idc_compressq;
    wxCheckBox *m_idc_16bit;
    wxCheckBox *m_idc_8bit;
};

// Derived class for event handlers and custom logic
class Displayspeed : public DisplayspeedBase
{
public:
    Displayspeed(wxWindow *parent);

protected:
    // Override for data transfer if needed
    // bool TransferDataToWindow() override;
    // bool TransferDataFromWindow() override;

private:
    void OnOK(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
};
