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
#include <wx/textctrl.h>
#include <wx/xrc/xmlres.h>

// Base class that loads from XRC
class PropPageRingScaleBase : public wxDialog
{
public:
    PropPageRingScaleBase() {}
    PropPageRingScaleBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_PROP_PAGE_RING_SCALE")) {
            return false;
        }

        // Get references to controls
        m_idc_inner_size_x_edit = XRCCTRL(*this, "IDC_INNER_SIZE_X_EDIT", wxTextCtrl);
        m_idc_inner_size_x_spin = XRCCTRL(*this, "IDC_INNER_SIZE_X_SPIN", wxSpinButton);
        m_idc_inner_size_y_edit = XRCCTRL(*this, "IDC_INNER_SIZE_Y_EDIT", wxTextCtrl);
        m_idc_inner_size_y_spin = XRCCTRL(*this, "IDC_INNER_SIZE_Y_SPIN", wxSpinButton);
        m_idc_inner_scale_bar_x = XRCCTRL(*this, "IDC_INNER_SCALE_BAR_X", wxPanel);
        m_idc_inner_scale_bar_y = XRCCTRL(*this, "IDC_INNER_SCALE_BAR_Y", wxPanel);
        m_idc_outer_size_x_edit = XRCCTRL(*this, "IDC_OUTER_SIZE_X_EDIT", wxTextCtrl);
        m_idc_outer_size_x_spin = XRCCTRL(*this, "IDC_OUTER_SIZE_X_SPIN", wxSpinButton);
        m_idc_outer_size_y_edit = XRCCTRL(*this, "IDC_OUTER_SIZE_Y_EDIT", wxTextCtrl);
        m_idc_outer_size_y_spin = XRCCTRL(*this, "IDC_OUTER_SIZE_Y_SPIN", wxSpinButton);
        m_idc_outer_scale_bar_x = XRCCTRL(*this, "IDC_OUTER_SCALE_BAR_X", wxPanel);
        m_idc_outer_scale_bar_y = XRCCTRL(*this, "IDC_OUTER_SCALE_BAR_Y", wxPanel);

        return true;
    }

protected:
    wxTextCtrl *m_idc_inner_size_x_edit;
    wxSpinButton *m_idc_inner_size_x_spin;
    wxTextCtrl *m_idc_inner_size_y_edit;
    wxSpinButton *m_idc_inner_size_y_spin;
    wxPanel *m_idc_inner_scale_bar_x;
    wxPanel *m_idc_inner_scale_bar_y;
    wxTextCtrl *m_idc_outer_size_x_edit;
    wxSpinButton *m_idc_outer_size_x_spin;
    wxTextCtrl *m_idc_outer_size_y_edit;
    wxSpinButton *m_idc_outer_size_y_spin;
    wxPanel *m_idc_outer_scale_bar_x;
    wxPanel *m_idc_outer_scale_bar_y;
};

// Derived class for event handlers and custom logic
class PropPageRingScale : public PropPageRingScaleBase
{
public:
    PropPageRingScale(wxWindow *parent);

protected:
    // Override for data transfer if needed
    // bool TransferDataToWindow() override;
    // bool TransferDataFromWindow() override;

private:
    void OnOK(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
};
