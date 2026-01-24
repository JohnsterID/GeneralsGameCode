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
#include <wx/slider.h>
#include <wx/statbmp.h>
#include <wx/stattext.h>
#include <wx/xrc/xmlres.h>

// Base class that loads from XRC
class GammaDialogBase : public wxDialog
{
public:
    GammaDialogBase() {}
    GammaDialogBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_GAMMA_DIALOG")) {
            return false;
        }

        // Get references to controls
        m_idok = XRCCTRL(*this, "IDOK", wxButton);
        m_idc_gamma_slider = XRCCTRL(*this, "IDC_GAMMA_SLIDER", wxSlider);
        m_idc_static_1 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_2 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_3 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_gamma_display = XRCCTRL(*this, "IDC_GAMMA_DISPLAY", wxStaticText);
        m_idc_static_4 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_5 = XRCCTRL(*this, "IDC_STATIC", wxStaticBitmap);
        m_idc_instructions = XRCCTRL(*this, "IDC_INSTRUCTIONS", wxStaticText);

        return true;
    }

protected:
    wxButton *m_idok;
    wxSlider *m_idc_gamma_slider;
    wxStaticText *m_idc_static_1;
    wxStaticText *m_idc_static_2;
    wxStaticText *m_idc_static_3;
    wxStaticText *m_idc_gamma_display;
    wxStaticText *m_idc_static_4;
    wxStaticBitmap *m_idc_static_5;
    wxStaticText *m_idc_instructions;
};

// Derived class for event handlers and custom logic
class GammaDialog : public GammaDialogBase
{
public:
    GammaDialog(wxWindow *parent);

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
    void OnReleasedcaptureGammaSlider(wxCommandEvent &event);  // Slider value changed

    // Member data (matches MFC m_gamma)
    int m_gamma;
};
