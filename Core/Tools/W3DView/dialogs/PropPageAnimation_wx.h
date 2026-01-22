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
#include <wx/statbmp.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/xrc/xmlres.h>

// Base class that loads from XRC
class PropPageAnimationBase : public wxDialog
{
public:
    PropPageAnimationBase() {}
    PropPageAnimationBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_PROP_PAGE_ANIMATION")) {
            return false;
        }

        // Get references to controls
        m_idc_static_1 = XRCCTRL(*this, "IDC_STATIC", wxStaticBitmap);
        m_idc_description = XRCCTRL(*this, "IDC_DESCRIPTION", wxStaticText);
        m_idc_static_2 = XRCCTRL(*this, "IDC_STATIC", wxPanel);
        m_idc_static_3 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_frame_count = XRCCTRL(*this, "IDC_FRAME_COUNT", wxStaticText);
        m_idc_static_4 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_frame_rate = XRCCTRL(*this, "IDC_FRAME_RATE", wxStaticText);
        m_idc_static_5 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_hierarchy_name = XRCCTRL(*this, "IDC_HIERARCHY_NAME", wxTextCtrl);
        m_idc_static_6 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_total_time = XRCCTRL(*this, "IDC_TOTAL_TIME", wxStaticText);

        return true;
    }

protected:
    wxStaticBitmap *m_idc_static_1;
    wxStaticText *m_idc_description;
    wxPanel *m_idc_static_2;
    wxStaticText *m_idc_static_3;
    wxStaticText *m_idc_frame_count;
    wxStaticText *m_idc_static_4;
    wxStaticText *m_idc_frame_rate;
    wxStaticText *m_idc_static_5;
    wxTextCtrl *m_idc_hierarchy_name;
    wxStaticText *m_idc_static_6;
    wxStaticText *m_idc_total_time;
};

// Derived class for event handlers and custom logic
class PropPageAnimation : public PropPageAnimationBase
{
public:
    PropPageAnimation(wxWindow *parent);

protected:
    // Override for data transfer if needed
    // bool TransferDataToWindow() override;
    // bool TransferDataFromWindow() override;

private:
    void OnOK(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
};
