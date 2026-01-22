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

#include <wx/button.h>
#include <wx/combobox.h>
#include <wx/dialog.h>
#include <wx/listbox.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/xrc/xmlres.h>

// Base class that loads from XRC
class XxxBrowseDirectoryBase : public wxDialog
{
public:
    XxxBrowseDirectoryBase() {}
    XxxBrowseDirectoryBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_XXX_BROWSE_DIRECTORY")) {
            return false;
        }

        // Get references to controls
        m_20627,7,7,92 = XRCCTRL(*this, "20627,7,7,92", wxStaticText);
        m_20626 = XRCCTRL(*this, "20626", wxTextCtrl);
        m_1121 = XRCCTRL(*this, "1121", wxListBox);
        m_-1,7,107,92 = XRCCTRL(*this, "-1,7,107,92", wxStaticText);
        m_1137 = XRCCTRL(*this, "1137", wxComboBox);
        m_1 = XRCCTRL(*this, "1", wxButton);
        m_2 = XRCCTRL(*this, "2", wxButton);
        m_1090 = XRCCTRL(*this, "1090", wxStaticText);
        m_1152 = XRCCTRL(*this, "1152", wxTextCtrl);
        m_1088 = XRCCTRL(*this, "1088", wxStaticText);
        m_1120 = XRCCTRL(*this, "1120", wxListBox);
        m_1089 = XRCCTRL(*this, "1089", wxStaticText);
        m_1136 = XRCCTRL(*this, "1136", wxComboBox);
        m_1037 = XRCCTRL(*this, "1037", wxButton);
        m_21251 = XRCCTRL(*this, "21251", wxStaticText);

        return true;
    }

protected:
    wxStaticText *m_20627,7,7,92;
    wxTextCtrl *m_20626;
    wxListBox *m_1121;
    wxStaticText *m_-1,7,107,92;
    wxComboBox *m_1137;
    wxButton *m_1;
    wxButton *m_2;
    wxStaticText *m_1090;
    wxTextCtrl *m_1152;
    wxStaticText *m_1088;
    wxListBox *m_1120;
    wxStaticText *m_1089;
    wxComboBox *m_1136;
    wxButton *m_1037;
    wxStaticText *m_21251;
};

// Derived class for event handlers and custom logic
class XxxBrowseDirectory : public XxxBrowseDirectoryBase
{
public:
    XxxBrowseDirectory(wxWindow *parent);

protected:
    // Override for data transfer if needed
    // bool TransferDataToWindow() override;
    // bool TransferDataFromWindow() override;

private:
    void OnOK(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
};
