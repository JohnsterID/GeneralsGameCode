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
#include <wx/listctrl.h>
#include <wx/statbmp.h>
#include <wx/stattext.h>
#include <wx/xrc/xmlres.h>

// Base class that loads from XRC
class BackgroundObjectBase : public wxDialog
{
public:
    BackgroundObjectBase() {}
    BackgroundObjectBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_BACKGROUND_OBJECT")) {
            return false;
        }

        // Get references to controls
        m_idc_static_1 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_2 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_hierarchy_list = XRCCTRL(*this, "IDC_HIERARCHY_LIST", wxListCtrl);
        m_idok = XRCCTRL(*this, "IDOK", wxButton);
        m_idcancel = XRCCTRL(*this, "IDCANCEL", wxButton);
        m_idc_static_3 = XRCCTRL(*this, "IDC_STATIC", wxStaticBitmap);
        m_idc_clear = XRCCTRL(*this, "IDC_CLEAR", wxButton);
        m_idc_static_4 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_curr_obj = XRCCTRL(*this, "IDC_CURR_OBJ", wxStaticText);

        return true;
    }

protected:
    wxStaticText *m_idc_static_1;
    wxStaticText *m_idc_static_2;
    wxListCtrl *m_idc_hierarchy_list;
    wxButton *m_idok;
    wxButton *m_idcancel;
    wxStaticBitmap *m_idc_static_3;
    wxButton *m_idc_clear;
    wxStaticText *m_idc_static_4;
    wxStaticText *m_idc_curr_obj;
};

// Derived class for event handlers and custom logic
class BackgroundObject : public BackgroundObjectBase
{
public:
    BackgroundObject(wxWindow *parent);

protected:
    // Override for data transfer if needed
    // bool TransferDataToWindow() override;
    // bool TransferDataFromWindow() override;

private:
    void OnOK(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
};
