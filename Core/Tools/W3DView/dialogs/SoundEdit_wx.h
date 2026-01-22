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
#include <wx/dialog.h>
#include <wx/slider.h>
#include <wx/statbmp.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/xrc/xmlres.h>

// Base class that loads from XRC
class SoundEditBase : public wxDialog
{
public:
    SoundEditBase() {}
    SoundEditBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_SOUND_EDIT")) {
            return false;
        }

        // Get references to controls
        m_idc_static_1 = XRCCTRL(*this, "IDC_STATIC", wxStaticBitmap);
        m_idc_static_2 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_3 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_name_edit = XRCCTRL(*this, "IDC_NAME_EDIT", wxTextCtrl);
        m_idc_static_4 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_filename_edit = XRCCTRL(*this, "IDC_FILENAME_EDIT", wxTextCtrl);
        m_idc_browse = XRCCTRL(*this, "IDC_BROWSE", wxButton);
        m_idc_static_5 = XRCCTRL(*this, "IDC_STATIC", wxStaticBox);
        m_idc_2d_radio = XRCCTRL(*this, "IDC_2D_RADIO", wxCheckBox);
        m_idc_static_6 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_trigger_radius_edit = XRCCTRL(*this, "IDC_TRIGGER_RADIUS_EDIT", wxTextCtrl);
        m_idc_static_7 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_8 = XRCCTRL(*this, "IDC_STATIC", wxStaticBox);
        m_idc_3d_radio = XRCCTRL(*this, "IDC_3D_RADIO", wxCheckBox);
        m_idc_static_9 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_drop_off_edit = XRCCTRL(*this, "IDC_DROP_OFF_EDIT", wxTextCtrl);
        m_idc_static_10 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_11 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_max_vol_edit = XRCCTRL(*this, "IDC_MAX_VOL_EDIT", wxTextCtrl);
        m_idc_static_12 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_infinite_loops_check = XRCCTRL(*this, "IDC_INFINITE_LOOPS_CHECK", wxCheckBox);
        m_idc_stop_when_hidden_check = XRCCTRL(*this, "IDC_STOP_WHEN_HIDDEN_CHECK", wxCheckBox);
        m_idc_soundeffect_radio = XRCCTRL(*this, "IDC_SOUNDEFFECT_RADIO", wxCheckBox);
        m_idc_music_radio = XRCCTRL(*this, "IDC_MUSIC_RADIO", wxCheckBox);
        m_idc_static_13 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_priority_slider = XRCCTRL(*this, "IDC_PRIORITY_SLIDER", wxSlider);
        m_idc_static_14 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_volume_slider = XRCCTRL(*this, "IDC_VOLUME_SLIDER", wxSlider);
        m_idc_play = XRCCTRL(*this, "IDC_PLAY", wxButton);
        m_idok = XRCCTRL(*this, "IDOK", wxButton);
        m_idcancel = XRCCTRL(*this, "IDCANCEL", wxButton);

        return true;
    }

protected:
    wxStaticBitmap *m_idc_static_1;
    wxStaticText *m_idc_static_2;
    wxStaticText *m_idc_static_3;
    wxTextCtrl *m_idc_name_edit;
    wxStaticText *m_idc_static_4;
    wxTextCtrl *m_idc_filename_edit;
    wxButton *m_idc_browse;
    wxStaticBox *m_idc_static_5;
    wxCheckBox *m_idc_2d_radio;
    wxStaticText *m_idc_static_6;
    wxTextCtrl *m_idc_trigger_radius_edit;
    wxStaticText *m_idc_static_7;
    wxStaticBox *m_idc_static_8;
    wxCheckBox *m_idc_3d_radio;
    wxStaticText *m_idc_static_9;
    wxTextCtrl *m_idc_drop_off_edit;
    wxStaticText *m_idc_static_10;
    wxStaticText *m_idc_static_11;
    wxTextCtrl *m_idc_max_vol_edit;
    wxStaticText *m_idc_static_12;
    wxCheckBox *m_idc_infinite_loops_check;
    wxCheckBox *m_idc_stop_when_hidden_check;
    wxCheckBox *m_idc_soundeffect_radio;
    wxCheckBox *m_idc_music_radio;
    wxStaticText *m_idc_static_13;
    wxSlider *m_idc_priority_slider;
    wxStaticText *m_idc_static_14;
    wxSlider *m_idc_volume_slider;
    wxButton *m_idc_play;
    wxButton *m_idok;
    wxButton *m_idcancel;
};

// Derived class for event handlers and custom logic
class SoundEdit : public SoundEditBase
{
public:
    SoundEdit(wxWindow *parent);

protected:
    // Override for data transfer if needed
    // bool TransferDataToWindow() override;
    // bool TransferDataFromWindow() override;

private:
    void OnOK(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
private:
    // Event handlers (Phase 2)
void OnBrowse(wxCommandEvent &event);  // Button/Checkbox click
    void On2DRadio(wxCommandEvent &event);  // Button/Checkbox click
    void On3DRadio(wxCommandEvent &event);  // Button/Checkbox click
    void OnPlay(wxCommandEvent &event);  // Button/Checkbox click
    void OnHscroll(wxScrollEvent &event);  // Horizontal scroll (slider)
};
