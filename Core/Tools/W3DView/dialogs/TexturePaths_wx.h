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
class TexturePathsBase : public wxDialog
{
public:
    TexturePathsBase() {}
    TexturePathsBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_TEXTURE_PATHS")) {
            return false;
        }

        // Get references to controls
        m_idc_static_1 = XRCCTRL(*this, "IDC_STATIC", wxStaticBitmap);
        m_idc_static_2 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_3 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_path1 = XRCCTRL(*this, "IDC_PATH1", wxTextCtrl);
        m_idc_browse1 = XRCCTRL(*this, "IDC_BROWSE1", wxButton);
        m_idc_static_4 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_path2 = XRCCTRL(*this, "IDC_PATH2", wxTextCtrl);
        m_idc_browse2 = XRCCTRL(*this, "IDC_BROWSE2", wxButton);
        m_idok = XRCCTRL(*this, "IDOK", wxButton);
        m_idcancel = XRCCTRL(*this, "IDCANCEL", wxButton);

        return true;
    }

protected:
    wxStaticBitmap *m_idc_static_1;
    wxStaticText *m_idc_static_2;
    wxStaticText *m_idc_static_3;
    wxTextCtrl *m_idc_path1;
    wxButton *m_idc_browse1;
    wxStaticText *m_idc_static_4;
    wxTextCtrl *m_idc_path2;
    wxButton *m_idc_browse2;
    wxButton *m_idok;
    wxButton *m_idcancel;
};

// Derived class for event handlers and custom logic
class TexturePaths : public TexturePathsBase
{
public:
    TexturePaths(wxWindow *parent);

protected:
    // Override for data transfer if needed
    // bool TransferDataToWindow() override;
    // bool TransferDataFromWindow() override;

private:
    void OnOK(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
private:
    // Phase 2.5: Dialog infrastructure
    void OnInitDialog(wxInitDialogEvent& event);
    bool TransferDataToWindow() override;
    bool TransferDataFromWindow() override;

    // Event handlers (Phase 2)
    void OnBrowse1(wxCommandEvent &event);  // Button/Checkbox click
    void OnBrowse2(wxCommandEvent &event);  // Button/Checkbox click
    
    // NOTE: No member variables needed - document obtained via GetCurrentDocument_wx() on-demand
    // MFC Reference: TexturePathDialog.cpp (no member variables used)
};
