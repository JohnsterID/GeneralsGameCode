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
#include <wx/listctrl.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/xrc/xmlres.h>

// Base class that loads from XRC
class PropPageAdvanimReportBase : public wxDialog
{
public:
    PropPageAdvanimReportBase() {}
    PropPageAdvanimReportBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_PROP_PAGE_ADVANIM_REPORT")) {
            return false;
        }

        // Get references to controls
        m_idc_anim_report = XRCCTRL(*this, "IDC_ANIM_REPORT", wxListCtrl);
        m_idc_static_1 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_2 = XRCCTRL(*this, "IDC_STATIC", wxStaticBox);
        m_idc_static_3 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_4 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_5 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_6 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_7 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);

        return true;
    }

protected:
    wxListCtrl *m_idc_anim_report;
    wxStaticText *m_idc_static_1;
    wxStaticBox *m_idc_static_2;
    wxStaticText *m_idc_static_3;
    wxStaticText *m_idc_static_4;
    wxStaticText *m_idc_static_5;
    wxStaticText *m_idc_static_6;
    wxStaticText *m_idc_static_7;
};

// Derived class for event handlers and custom logic
class PropPageAdvanimReport : public PropPageAdvanimReportBase
{
public:
    PropPageAdvanimReport(wxWindow *parent);

protected:
    // Override for data transfer if needed
    // bool TransferDataToWindow() override;
    // bool TransferDataFromWindow() override;

private:
    void OnOK(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
};
