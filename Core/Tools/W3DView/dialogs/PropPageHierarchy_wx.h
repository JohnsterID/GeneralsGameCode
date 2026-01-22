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
#include <wx/stattext.h>
#include <wx/xrc/xmlres.h>

// Base class that loads from XRC
class PropPageHierarchyBase : public wxDialog
{
public:
    PropPageHierarchyBase() {}
    PropPageHierarchyBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_PROP_PAGE_HIERARCHY")) {
            return false;
        }

        // Get references to controls
        m_idc_description = XRCCTRL(*this, "IDC_DESCRIPTION", wxStaticText);
        m_idc_subobject_list = XRCCTRL(*this, "IDC_SUBOBJECT_LIST", wxListCtrl);
        m_idc_total_polygons = XRCCTRL(*this, "IDC_TOTAL_POLYGONS", wxStaticText);
        m_idc_subobjects = XRCCTRL(*this, "IDC_SUBOBJECTS", wxStaticText);

        return true;
    }

protected:
    wxStaticText *m_idc_description;
    wxListCtrl *m_idc_subobject_list;
    wxStaticText *m_idc_total_polygons;
    wxStaticText *m_idc_subobjects;
};

// Derived class for event handlers and custom logic
class PropPageHierarchy : public PropPageHierarchyBase
{
public:
    PropPageHierarchy(wxWindow *parent);

protected:
    // Override for data transfer if needed
    // bool TransferDataToWindow() override;
    // bool TransferDataFromWindow() override;

private:
    void OnOK(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
};
