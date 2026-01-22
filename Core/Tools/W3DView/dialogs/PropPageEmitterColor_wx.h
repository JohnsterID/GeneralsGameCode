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

#include <wx/dialog.h>
#include <wx/panel.h>
#include <wx/spinbutt.h>
#include <wx/statbmp.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/xrc/xmlres.h>

// Base class that loads from XRC
class PropPageEmitterColorBase : public wxDialog
{
public:
    PropPageEmitterColorBase() {}
    PropPageEmitterColorBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_PROP_PAGE_EMITTER_COLOR")) {
            return false;
        }

        // Get references to controls
        m_idc_static_1 = XRCCTRL(*this, "IDC_STATIC", wxStaticBitmap);
        m_idc_static_2 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_3 = XRCCTRL(*this, "IDC_STATIC", wxPanel);
        m_idc_static_4 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_color_bar = XRCCTRL(*this, "IDC_COLOR_BAR", wxPanel);
        m_idc_static_5 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_6 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_red_random_edit = XRCCTRL(*this, "IDC_RED_RANDOM_EDIT", wxTextCtrl);
        m_idc_red_random_spin = XRCCTRL(*this, "IDC_RED_RANDOM_SPIN", wxSpinButton);
        m_idc_static_7 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_green_random_edit = XRCCTRL(*this, "IDC_GREEN_RANDOM_EDIT", wxTextCtrl);
        m_idc_green_random_spin = XRCCTRL(*this, "IDC_GREEN_RANDOM_SPIN", wxSpinButton);
        m_idc_static_8 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_blue_random_edit = XRCCTRL(*this, "IDC_BLUE_RANDOM_EDIT", wxTextCtrl);
        m_idc_blue_random_spin = XRCCTRL(*this, "IDC_BLUE_RANDOM_SPIN", wxSpinButton);
        m_idc_static_9 = XRCCTRL(*this, "IDC_STATIC", wxPanel);
        m_idc_static_10 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_opacity_bar = XRCCTRL(*this, "IDC_OPACITY_BAR", wxPanel);
        m_idc_static_11 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_opacity_random_edit = XRCCTRL(*this, "IDC_OPACITY_RANDOM_EDIT", wxTextCtrl);
        m_idc_opacity_random_spin = XRCCTRL(*this, "IDC_OPACITY_RANDOM_SPIN", wxSpinButton);
        m_idc_static_12 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);

        return true;
    }

protected:
    wxStaticBitmap *m_idc_static_1;
    wxStaticText *m_idc_static_2;
    wxPanel *m_idc_static_3;
    wxStaticText *m_idc_static_4;
    wxPanel *m_idc_color_bar;
    wxStaticText *m_idc_static_5;
    wxStaticText *m_idc_static_6;
    wxTextCtrl *m_idc_red_random_edit;
    wxSpinButton *m_idc_red_random_spin;
    wxStaticText *m_idc_static_7;
    wxTextCtrl *m_idc_green_random_edit;
    wxSpinButton *m_idc_green_random_spin;
    wxStaticText *m_idc_static_8;
    wxTextCtrl *m_idc_blue_random_edit;
    wxSpinButton *m_idc_blue_random_spin;
    wxPanel *m_idc_static_9;
    wxStaticText *m_idc_static_10;
    wxPanel *m_idc_opacity_bar;
    wxStaticText *m_idc_static_11;
    wxTextCtrl *m_idc_opacity_random_edit;
    wxSpinButton *m_idc_opacity_random_spin;
    wxStaticText *m_idc_static_12;
};

// Derived class for event handlers and custom logic
class PropPageEmitterColor : public PropPageEmitterColorBase
{
public:
    PropPageEmitterColor(wxWindow *parent);

protected:
    // Override for data transfer if needed
    // bool TransferDataToWindow() override;
    // bool TransferDataFromWindow() override;

private:
    void OnOK(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
};
