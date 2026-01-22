/*
**	Command & Conquer Renegade(tm)
**	Copyright 2026 TheSuperHackers
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

// TheSuperHackers: wxWidgets About Dialog for W3DView

#pragma once

#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/statbmp.h>

// Base class that loads from XRC
class AboutDialogBase : public wxDialog
{
public:
    AboutDialogBase() {}
    AboutDialogBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_ABOUTBOX")) {
            return false;
        }

        // Get references to controls (optional for read-only dialogs)
        m_iconBitmap = XRCCTRL(*this, "IDC_STATIC", wxStaticBitmap);
        m_versionText = XRCCTRL(*this, "IDC_VERSION", wxStaticText);
        m_okButton = XRCCTRL(*this, "IDOK", wxButton);

        return true;
    }

protected:
    wxStaticBitmap *m_iconBitmap;
    wxStaticText *m_versionText;
    wxButton *m_okButton;
};

// Actual dialog class with event handlers
class AboutDialog : public AboutDialogBase
{
public:
    AboutDialog(wxWindow *parent);

private:
    void OnOK(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
};
