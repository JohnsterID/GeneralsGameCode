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

#include <wx/checkbox.h>
#include <wx/combobox.h>
#include <wx/dialog.h>
#include <wx/panel.h>
#include <wx/spinbutt.h>
#include <wx/statbmp.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/xrc/xmlres.h>

// Base class that loads from XRC
class PropPageEmitterLinepropsBase : public wxDialog
{
public:
    PropPageEmitterLinepropsBase() {}
    PropPageEmitterLinepropsBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_PROP_PAGE_EMITTER_LINEPROPS")) {
            return false;
        }

        // Get references to controls
        m_idc_static_1 = XRCCTRL(*this, "IDC_STATIC", wxStaticBitmap);
        m_idc_static_2 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_3 = XRCCTRL(*this, "IDC_STATIC", wxPanel);
        m_idc_static_4 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_5 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_subdivision_level_edit = XRCCTRL(*this, "IDC_SUBDIVISION_LEVEL_EDIT", wxTextCtrl);
        m_idc_subdivision_level_spin = XRCCTRL(*this, "IDC_SUBDIVISION_LEVEL_SPIN", wxSpinButton);
        m_idc_static_6 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_noise_amplitude_edit = XRCCTRL(*this, "IDC_NOISE_AMPLITUDE_EDIT", wxTextCtrl);
        m_idc_noise_amplitude_spin = XRCCTRL(*this, "IDC_NOISE_AMPLITUDE_SPIN", wxSpinButton);
        m_idc_static_7 = XRCCTRL(*this, "IDC_STATIC", wxPanel);
        m_idc_static_8 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_merge_intersections_check = XRCCTRL(*this, "IDC_MERGE_INTERSECTIONS_CHECK", wxCheckBox);
        m_idc_end_caps_check = XRCCTRL(*this, "IDC_END_CAPS_CHECK", wxCheckBox);
        m_idc_disable_sorting_check = XRCCTRL(*this, "IDC_DISABLE_SORTING_CHECK", wxCheckBox);
        m_idc_static_9 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_mapmode_combo = XRCCTRL(*this, "IDC_MAPMODE_COMBO", wxComboBox);
        m_idc_static_10 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_merge_abort_factor_edit = XRCCTRL(*this, "IDC_MERGE_ABORT_FACTOR_EDIT", wxTextCtrl);
        m_idc_merge_abort_factor_spin = XRCCTRL(*this, "IDC_MERGE_ABORT_FACTOR_SPIN", wxSpinButton);
        m_idc_static_11 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_uvtiling_edit = XRCCTRL(*this, "IDC_UVTILING_EDIT", wxTextCtrl);
        m_idc_uvtiling_spin = XRCCTRL(*this, "IDC_UVTILING_SPIN", wxSpinButton);
        m_idc_static_12 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_upersec_edit = XRCCTRL(*this, "IDC_UPERSEC_EDIT", wxTextCtrl);
        m_idc_upersec_spin = XRCCTRL(*this, "IDC_UPERSEC_SPIN", wxSpinButton);
        m_idc_static_13 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_vpersec_edit = XRCCTRL(*this, "IDC_VPERSEC_EDIT", wxTextCtrl);
        m_idc_vpersec_spin = XRCCTRL(*this, "IDC_VPERSEC_SPIN", wxSpinButton);

        return true;
    }

protected:
    wxStaticBitmap *m_idc_static_1;
    wxStaticText *m_idc_static_2;
    wxPanel *m_idc_static_3;
    wxStaticText *m_idc_static_4;
    wxStaticText *m_idc_static_5;
    wxTextCtrl *m_idc_subdivision_level_edit;
    wxSpinButton *m_idc_subdivision_level_spin;
    wxStaticText *m_idc_static_6;
    wxTextCtrl *m_idc_noise_amplitude_edit;
    wxSpinButton *m_idc_noise_amplitude_spin;
    wxPanel *m_idc_static_7;
    wxStaticText *m_idc_static_8;
    wxCheckBox *m_idc_merge_intersections_check;
    wxCheckBox *m_idc_end_caps_check;
    wxCheckBox *m_idc_disable_sorting_check;
    wxStaticText *m_idc_static_9;
    wxComboBox *m_idc_mapmode_combo;
    wxStaticText *m_idc_static_10;
    wxTextCtrl *m_idc_merge_abort_factor_edit;
    wxSpinButton *m_idc_merge_abort_factor_spin;
    wxStaticText *m_idc_static_11;
    wxTextCtrl *m_idc_uvtiling_edit;
    wxSpinButton *m_idc_uvtiling_spin;
    wxStaticText *m_idc_static_12;
    wxTextCtrl *m_idc_upersec_edit;
    wxSpinButton *m_idc_upersec_spin;
    wxStaticText *m_idc_static_13;
    wxTextCtrl *m_idc_vpersec_edit;
    wxSpinButton *m_idc_vpersec_spin;
};

// Derived class for event handlers and custom logic
class PropPageEmitterLineprops : public PropPageEmitterLinepropsBase
{
public:
    PropPageEmitterLineprops(wxWindow *parent);

protected:
    // Override for data transfer if needed
    // bool TransferDataToWindow() override;
    // bool TransferDataFromWindow() override;

private:
    void OnOK(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
};
