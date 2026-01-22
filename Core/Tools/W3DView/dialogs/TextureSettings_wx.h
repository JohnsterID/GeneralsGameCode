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
#include <wx/checkbox.h>
#include <wx/combobox.h>
#include <wx/dialog.h>
#include <wx/panel.h>
#include <wx/spinbutt.h>
#include <wx/statbmp.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/xrc/xmlres.h>

// Base class that loads from XRC
class TextureSettingsBase : public wxDialog
{
public:
    TextureSettingsBase() {}
    TextureSettingsBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_TEXTURE_SETTINGS")) {
            return false;
        }

        // Get references to controls
        m_idc_static_1 = XRCCTRL(*this, "IDC_STATIC", wxStaticBitmap);
        m_idc_static_2 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_3 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_filename_edit = XRCCTRL(*this, "IDC_FILENAME_EDIT", wxTextCtrl);
        m_idc_browse_button = XRCCTRL(*this, "IDC_BROWSE_BUTTON", wxButton);
        m_idc_resizeable_check = XRCCTRL(*this, "IDC_RESIZEABLE_CHECK", wxCheckBox);
        m_idc_mipmap_off_check = XRCCTRL(*this, "IDC_MIPMAP_OFF_CHECK", wxCheckBox);
        m_idc_alpha_check = XRCCTRL(*this, "IDC_ALPHA_CHECK", wxCheckBox);
        m_idc_clampu_check = XRCCTRL(*this, "IDC_CLAMPU_CHECK", wxCheckBox);
        m_idc_clampv_check = XRCCTRL(*this, "IDC_CLAMPV_CHECK", wxCheckBox);
        m_idc_restore = XRCCTRL(*this, "IDC_RESTORE", wxButton);
        m_idc_texture_thumbnail = XRCCTRL(*this, "IDC_TEXTURE_THUMBNAIL", wxPanel);
        m_idc_static_4 = XRCCTRL(*this, "IDC_STATIC", wxStaticBox);
        m_idc_animation_check = XRCCTRL(*this, "IDC_ANIMATION_CHECK", wxCheckBox);
        m_idc_static_5 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_frame_count_edit = XRCCTRL(*this, "IDC_FRAME_COUNT_EDIT", wxTextCtrl);
        m_idc_frame_count_spin = XRCCTRL(*this, "IDC_FRAME_COUNT_SPIN", wxSpinButton);
        m_idc_static_6 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_fps_edit = XRCCTRL(*this, "IDC_FPS_EDIT", wxTextCtrl);
        m_idc_fps_spin = XRCCTRL(*this, "IDC_FPS_SPIN", wxSpinButton);
        m_idc_static_7 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_type_combo = XRCCTRL(*this, "IDC_TYPE_COMBO", wxComboBox);
        m_idok = XRCCTRL(*this, "IDOK", wxButton);
        m_idcancel = XRCCTRL(*this, "IDCANCEL", wxButton);
        m_idc_static_8 = XRCCTRL(*this, "IDC_STATIC", wxStaticBox);
        m_idc_apply = XRCCTRL(*this, "IDC_APPLY", wxButton);

        return true;
    }

protected:
    wxStaticBitmap *m_idc_static_1;
    wxStaticText *m_idc_static_2;
    wxStaticText *m_idc_static_3;
    wxTextCtrl *m_idc_filename_edit;
    wxButton *m_idc_browse_button;
    wxCheckBox *m_idc_resizeable_check;
    wxCheckBox *m_idc_mipmap_off_check;
    wxCheckBox *m_idc_alpha_check;
    wxCheckBox *m_idc_clampu_check;
    wxCheckBox *m_idc_clampv_check;
    wxButton *m_idc_restore;
    wxPanel *m_idc_texture_thumbnail;
    wxStaticBox *m_idc_static_4;
    wxCheckBox *m_idc_animation_check;
    wxStaticText *m_idc_static_5;
    wxTextCtrl *m_idc_frame_count_edit;
    wxSpinButton *m_idc_frame_count_spin;
    wxStaticText *m_idc_static_6;
    wxTextCtrl *m_idc_fps_edit;
    wxSpinButton *m_idc_fps_spin;
    wxStaticText *m_idc_static_7;
    wxComboBox *m_idc_type_combo;
    wxButton *m_idok;
    wxButton *m_idcancel;
    wxStaticBox *m_idc_static_8;
    wxButton *m_idc_apply;
};

// Derived class for event handlers and custom logic
class TextureSettings : public TextureSettingsBase
{
public:
    TextureSettings(wxWindow *parent);

protected:
    // Override for data transfer if needed
    // bool TransferDataToWindow() override;
    // bool TransferDataFromWindow() override;

private:
    void OnOK(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
};
