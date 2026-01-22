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
#include <wx/spinbutt.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/xrc/xmlres.h>

// Base class that loads from XRC
class ColorFormBase : public wxDialog
{
public:
    ColorFormBase() {}
    ColorFormBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_COLOR_FORM")) {
            return false;
        }

        // Get references to controls
        m_idc_hue_picker = XRCCTRL(*this, "IDC_HUE_PICKER", wxPanel);
        m_idc_whiteness_bar = XRCCTRL(*this, "IDC_WHITENESS_BAR", wxPanel);
        m_idc_static_1 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_red_bar = XRCCTRL(*this, "IDC_RED_BAR", wxPanel);
        m_1005 = XRCCTRL(*this, "1005", wxTextCtrl);
        m_1008 = XRCCTRL(*this, "1008", wxSpinButton);
        m_idc_static_2 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_green_bar = XRCCTRL(*this, "IDC_GREEN_BAR", wxPanel);
        m_1006 = XRCCTRL(*this, "1006", wxTextCtrl);
        m_1009 = XRCCTRL(*this, "1009", wxSpinButton);
        m_idc_static_3 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_blue_bar = XRCCTRL(*this, "IDC_BLUE_BAR", wxPanel);
        m_1007 = XRCCTRL(*this, "1007", wxTextCtrl);
        m_1010 = XRCCTRL(*this, "1010", wxSpinButton);
        m_idc_orig_color_bar = XRCCTRL(*this, "IDC_ORIG_COLOR_BAR", wxPanel);
        m_idc_current_color_bar = XRCCTRL(*this, "IDC_CURRENT_COLOR_BAR", wxPanel);
        m_idc_static_4 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_5 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_reset = XRCCTRL(*this, "IDC_RESET", wxButton);

        return true;
    }

protected:
    wxPanel *m_idc_hue_picker;
    wxPanel *m_idc_whiteness_bar;
    wxStaticText *m_idc_static_1;
    wxPanel *m_idc_red_bar;
    wxTextCtrl *m_1005;
    wxSpinButton *m_1008;
    wxStaticText *m_idc_static_2;
    wxPanel *m_idc_green_bar;
    wxTextCtrl *m_1006;
    wxSpinButton *m_1009;
    wxStaticText *m_idc_static_3;
    wxPanel *m_idc_blue_bar;
    wxTextCtrl *m_1007;
    wxSpinButton *m_1010;
    wxPanel *m_idc_orig_color_bar;
    wxPanel *m_idc_current_color_bar;
    wxStaticText *m_idc_static_4;
    wxStaticText *m_idc_static_5;
    wxButton *m_idc_reset;
};

// Derived class for event handlers and custom logic
class ColorForm : public ColorFormBase
{
public:
    ColorForm(wxWindow *parent);

protected:
    // Override for data transfer if needed
    // bool TransferDataToWindow() override;
    // bool TransferDataFromWindow() override;

private:
    void OnOK(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
};
