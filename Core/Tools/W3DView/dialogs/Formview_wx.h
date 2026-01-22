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
#include <wx/stattext.h>
#include <wx/xrc/xmlres.h>

// Base class that loads from XRC
class FormviewBase : public wxDialog
{
public:
    FormviewBase() {}
    FormviewBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_FORMVIEW")) {
            return false;
        }

        // Get references to controls
        m_idc_static = XRCCTRL(*this, "IDC_STATIC", wxStaticText);

        return true;
    }

protected:
    wxStaticText *m_idc_static;
};

// Derived class for event handlers and custom logic
class Formview : public FormviewBase
{
public:
    Formview(wxWindow *parent);

protected:
    // Override for data transfer if needed
    // bool TransferDataToWindow() override;
    // bool TransferDataFromWindow() override;

private:
    void OnOK(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
};
