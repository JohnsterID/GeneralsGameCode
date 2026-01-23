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

#include <wx/dialog.h>
#include <wx/panel.h>
#include <wx/spinbutt.h>
#include <wx/statbmp.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/xrc/xmlres.h>

// Base class that loads from XRC
class PropPageSphereScaleBase : public wxDialog
{
public:
    PropPageSphereScaleBase() {}
    PropPageSphereScaleBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_PROP_PAGE_SPHERE_SCALE")) {
            return false;
        }

        // Get references to controls
        m_idc_static_1 = XRCCTRL(*this, "IDC_STATIC", wxStaticBitmap);
        m_idc_static_2 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_3 = XRCCTRL(*this, "IDC_STATIC", wxPanel);
        m_idc_static_4 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_5 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_size_x_edit = XRCCTRL(*this, "IDC_SIZE_X_EDIT", wxTextCtrl);
        m_idc_size_x_spin = XRCCTRL(*this, "IDC_SIZE_X_SPIN", wxSpinButton);
        m_idc_static_6 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_size_y_edit = XRCCTRL(*this, "IDC_SIZE_Y_EDIT", wxTextCtrl);
        m_idc_size_y_spin = XRCCTRL(*this, "IDC_SIZE_Y_SPIN", wxSpinButton);
        m_idc_static_7 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_size_z_edit = XRCCTRL(*this, "IDC_SIZE_Z_EDIT", wxTextCtrl);
        m_idc_size_z_spin = XRCCTRL(*this, "IDC_SIZE_Z_SPIN", wxSpinButton);
        m_idc_static_8 = XRCCTRL(*this, "IDC_STATIC", wxPanel);
        m_idc_static_9 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_10 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_scale_bar_x = XRCCTRL(*this, "IDC_SCALE_BAR_X", wxPanel);
        m_idc_static_11 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_scale_bar_y = XRCCTRL(*this, "IDC_SCALE_BAR_Y", wxPanel);
        m_idc_static_12 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_scale_bar_z = XRCCTRL(*this, "IDC_SCALE_BAR_Z", wxPanel);

        return true;
    }

protected:
    wxStaticBitmap *m_idc_static_1;
    wxStaticText *m_idc_static_2;
    wxPanel *m_idc_static_3;
    wxStaticText *m_idc_static_4;
    wxStaticText *m_idc_static_5;
    wxTextCtrl *m_idc_size_x_edit;
    wxSpinButton *m_idc_size_x_spin;
    wxStaticText *m_idc_static_6;
    wxTextCtrl *m_idc_size_y_edit;
    wxSpinButton *m_idc_size_y_spin;
    wxStaticText *m_idc_static_7;
    wxTextCtrl *m_idc_size_z_edit;
    wxSpinButton *m_idc_size_z_spin;
    wxPanel *m_idc_static_8;
    wxStaticText *m_idc_static_9;
    wxStaticText *m_idc_static_10;
    wxPanel *m_idc_scale_bar_x;
    wxStaticText *m_idc_static_11;
    wxPanel *m_idc_scale_bar_y;
    wxStaticText *m_idc_static_12;
    wxPanel *m_idc_scale_bar_z;
};

// Derived class for event handlers and custom logic
class PropPageSphereScale : public PropPageSphereScaleBase
{
public:
    PropPageSphereScale(wxWindow *parent);

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
void OnDestroy(wxWindowDestroyEvent &event);  // Window destruction
};
