/*
**	Command & Conquer Renegade(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// TheSuperHackers: wxWidgets Display Speed Dialog for W3DView

#pragma once

#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/slider.h>
#include <wx/checkbox.h>
#include <wx/stattext.h>

// Base class that loads from XRC
class DisplaySpeedDialogBase : public wxDialog
{
public:
    DisplaySpeedDialogBase() {}
    DisplaySpeedDialogBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_DISPLAYSPEED")) {
            return false;
        }

        // Get references to controls
        m_speedSlider = XRCCTRL(*this, "IDC_SPEED_SLIDER", wxSlider);
        m_blendCheckbox = XRCCTRL(*this, "IDC_BLEND", wxCheckBox);
        m_compressQCheckbox = XRCCTRL(*this, "IDC_COMPRESSQ", wxCheckBox);
        m_16bitCheckbox = XRCCTRL(*this, "IDC_16BIT", wxCheckBox);
        m_8bitCheckbox = XRCCTRL(*this, "IDC_8BIT", wxCheckBox);
        m_okButton = XRCCTRL(*this, "IDOK", wxButton);
        m_cancelButton = XRCCTRL(*this, "IDCANCEL", wxButton);

        return true;
    }

protected:
    wxSlider *m_speedSlider;
    wxCheckBox *m_blendCheckbox;
    wxCheckBox *m_compressQCheckbox;
    wxCheckBox *m_16bitCheckbox;
    wxCheckBox *m_8bitCheckbox;
    wxButton *m_okButton;
    wxButton *m_cancelButton;
};

// Actual dialog class with data and event handlers
class DisplaySpeedDialog : public DisplaySpeedDialogBase
{
public:
    DisplaySpeedDialog(wxWindow *parent);

    // Data members (equivalent to MFC dialog data)
    int m_speed;
    bool m_blendFrames;
    bool m_compressQ;
    bool m_16bit;
    bool m_8bit;

protected:
    // Override data transfer functions
    bool TransferDataToWindow() override;
    bool TransferDataFromWindow() override;

private:
    void OnOK(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
};
