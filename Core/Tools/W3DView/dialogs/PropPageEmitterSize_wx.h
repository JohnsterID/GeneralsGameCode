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
class PropPageEmitterSizeBase : public wxDialog
{
public:
    PropPageEmitterSizeBase() {}
    PropPageEmitterSizeBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_PROP_PAGE_EMITTER_SIZE")) {
            return false;
        }

        // Get references to controls
        m_idc_size_bar = XRCCTRL(*this, "IDC_SIZE_BAR", wxPanel);
        m_idc_size_random_edit = XRCCTRL(*this, "IDC_SIZE_RANDOM_EDIT", wxTextCtrl);
        m_idc_size_random_spin = XRCCTRL(*this, "IDC_SIZE_RANDOM_SPIN", wxSpinButton);

        return true;
    }

protected:
    wxPanel *m_idc_size_bar;
    wxTextCtrl *m_idc_size_random_edit;
    wxSpinButton *m_idc_size_random_spin;
};

// Derived class for event handlers and custom logic
class PropPageEmitterSize : public PropPageEmitterSizeBase
{
public:
    PropPageEmitterSize(wxWindow *parent);

protected:
    // Override for data transfer if needed
    // bool TransferDataToWindow() override;
    // bool TransferDataFromWindow() override;

private:
    void OnOK(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
};
