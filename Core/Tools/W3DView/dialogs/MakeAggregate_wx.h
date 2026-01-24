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
#include <wx/statbmp.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/xrc/xmlres.h>

// Base class that loads from XRC
class MakeAggregateBase : public wxDialog
{
public:
    MakeAggregateBase() {}
    MakeAggregateBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_MAKE_AGGREGATE")) {
            return false;
        }

        // Get references to controls
        m_idc_static_1 = XRCCTRL(*this, "IDC_STATIC", wxStaticBitmap);
        m_idc_static_2 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_3 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_aggregate_name = XRCCTRL(*this, "IDC_AGGREGATE_NAME", wxTextCtrl);
        m_idok = XRCCTRL(*this, "IDOK", wxButton);
        m_idcancel = XRCCTRL(*this, "IDCANCEL", wxButton);

        return true;
    }

protected:
    wxStaticBitmap *m_idc_static_1;
    wxStaticText *m_idc_static_2;
    wxStaticText *m_idc_static_3;
    wxTextCtrl *m_idc_aggregate_name;
    wxButton *m_idok;
    wxButton *m_idcancel;
};

// Derived class for event handlers and custom logic
class MakeAggregate : public MakeAggregateBase
{
public:
    // MFC: AggregateNameDialogClass(CWnd* pParent = nullptr);
    MakeAggregate(wxWindow *parent);
    
    // MFC: AggregateNameDialogClass(UINT resource_id, const CString &def_name, CWnd* pParent = nullptr);
    MakeAggregate(const wxString& def_name, wxWindow *parent);
    
    // Dialog data (MFC compatibility)
    wxString m_Name;  // Aggregate name from user input
    
    // MFC: Public accessors
    const wxString& Get_Name() const { return m_Name; }
    void Set_Name(const wxString& name) { m_Name = name; }

protected:
    // Override for data transfer if needed
    // bool TransferDataToWindow() override;
    // bool TransferDataFromWindow() override;

private:
    // Phase 2.5: Dialog infrastructure
    void OnInitDialog(wxInitDialogEvent& event);
    bool TransferDataToWindow() override;
    bool TransferDataFromWindow() override;

    void OnOK(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
};
