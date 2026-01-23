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
class AnimatedSoundDialogBase : public wxDialog
{
public:
    AnimatedSoundDialogBase() {}
    AnimatedSoundDialogBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_ANIMATED_SOUND_DIALOG")) {
            return false;
        }

        // Get references to controls
        m_idc_static_1 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_sound_definition_library_edit = XRCCTRL(*this, "IDC_SOUND_DEFINITION_LIBRARY_EDIT", wxTextCtrl);
        m_idc_sound_definition_library_browse_button = XRCCTRL(*this, "IDC_SOUND_DEFINITION_LIBRARY_BROWSE_BUTTON", wxButton);
        m_idc_static_2 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_sound_ini_edit = XRCCTRL(*this, "IDC_SOUND_INI_EDIT", wxTextCtrl);
        m_idc_sound_ini_browse_button = XRCCTRL(*this, "IDC_SOUND_INI_BROWSE_BUTTON", wxButton);
        m_idc_static_3 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_sound_file_path_edit = XRCCTRL(*this, "IDC_SOUND_FILE_PATH_EDIT", wxTextCtrl);
        m_idc_sound_path_browse_button = XRCCTRL(*this, "IDC_SOUND_PATH_BROWSE_BUTTON", wxButton);
        m_idok = XRCCTRL(*this, "IDOK", wxButton);
        m_idcancel = XRCCTRL(*this, "IDCANCEL", wxButton);
        m_idc_static_4 = XRCCTRL(*this, "IDC_STATIC", wxStaticBitmap);
        m_idc_static_5 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);

        return true;
    }

protected:
    wxStaticText *m_idc_static_1;
    wxTextCtrl *m_idc_sound_definition_library_edit;
    wxButton *m_idc_sound_definition_library_browse_button;
    wxStaticText *m_idc_static_2;
    wxTextCtrl *m_idc_sound_ini_edit;
    wxButton *m_idc_sound_ini_browse_button;
    wxStaticText *m_idc_static_3;
    wxTextCtrl *m_idc_sound_file_path_edit;
    wxButton *m_idc_sound_path_browse_button;
    wxButton *m_idok;
    wxButton *m_idcancel;
    wxStaticBitmap *m_idc_static_4;
    wxStaticText *m_idc_static_5;
};

// Derived class for event handlers and custom logic
class AnimatedSoundDialog : public AnimatedSoundDialogBase
{
public:
    AnimatedSoundDialog(wxWindow *parent);

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
void OnSoundDefinitionLibraryBrowseButton(wxCommandEvent &event);  // Button/Checkbox click
    void OnSoundIniBrowseButton(wxCommandEvent &event);  // Button/Checkbox click
    void OnSoundPathBrowseButton(wxCommandEvent &event);  // Button/Checkbox click
};
