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
#include <wx/listctrl.h>
#include <wx/spinbutt.h>
#include <wx/statbmp.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/xrc/xmlres.h>

// Base class that loads from XRC
class EditLodBase : public wxDialog
{
public:
    EditLodBase() {}
    EditLodBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_EDIT_LOD")) {
            return false;
        }

        // Get references to controls
        m_idc_static_1 = XRCCTRL(*this, "IDC_STATIC", wxStaticBitmap);
        m_idc_static_2 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_3 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_hierarchy_list = XRCCTRL(*this, "IDC_HIERARCHY_LIST", wxListCtrl);
        m_idc_settings_group = XRCCTRL(*this, "IDC_SETTINGS_GROUP", wxStaticBox);
        m_idc_static_4 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_switch_up_edit = XRCCTRL(*this, "IDC_SWITCH_UP_EDIT", wxTextCtrl);
        m_idc_switch_up_spin = XRCCTRL(*this, "IDC_SWITCH_UP_SPIN", wxSpinButton);
        m_idc_check1 = XRCCTRL(*this, "IDC_CHECK1", wxCheckBox);
        m_idok = XRCCTRL(*this, "IDOK", wxButton);
        m_idcancel = XRCCTRL(*this, "IDCANCEL", wxButton);

        return true;
    }

protected:
    wxStaticBitmap *m_idc_static_1;
    wxStaticText *m_idc_static_2;
    wxStaticText *m_idc_static_3;
    wxListCtrl *m_idc_hierarchy_list;
    wxStaticBox *m_idc_settings_group;
    wxStaticText *m_idc_static_4;
    wxTextCtrl *m_idc_switch_up_edit;
    wxSpinButton *m_idc_switch_up_spin;
    wxCheckBox *m_idc_check1;
    wxButton *m_idok;
    wxButton *m_idcancel;
};

// Derived class for event handlers and custom logic
class EditLod : public EditLodBase
{
public:
    EditLod(wxWindow *parent);

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
void OnDeltaposSwitchUpSpin(various &event);  // Notification message (needs analysis)
    void OnDeltaposSwitchDnSpin(various &event);  // Notification message (needs analysis)
    void OnItemChangedHierarchyList(various &event);  // Notification message (needs analysis)
    void OnRecalc(wxCommandEvent &event);  // Button/Checkbox click
};
