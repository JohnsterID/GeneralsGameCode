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
#include <wx/dialog.h>
#include <wx/statbmp.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/xrc/xmlres.h>

// Base class that loads from XRC
class PlaySoundEffectBase : public wxDialog
{
public:
    PlaySoundEffectBase() {}
    PlaySoundEffectBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_PLAY_SOUND_EFFECT")) {
            return false;
        }

        // Get references to controls
        m_idc_static_1 = XRCCTRL(*this, "IDC_STATIC", wxStaticBitmap);
        m_idc_static_2 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_play_sound_effect = XRCCTRL(*this, "IDC_PLAY_SOUND_EFFECT", wxButton);
        m_idcancel = XRCCTRL(*this, "IDCANCEL", wxButton);
        m_idc_static_3 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_stop_sound_effect = XRCCTRL(*this, "IDC_STOP_SOUND_EFFECT", wxButton);
        m_idc_filename = XRCCTRL(*this, "IDC_FILENAME", wxTextCtrl);

        return true;
    }

protected:
    wxStaticBitmap *m_idc_static_1;
    wxStaticText *m_idc_static_2;
    wxButton *m_idc_play_sound_effect;
    wxButton *m_idcancel;
    wxStaticText *m_idc_static_3;
    wxButton *m_idc_stop_sound_effect;
    wxTextCtrl *m_idc_filename;
};

// Derived class for event handlers and custom logic
class PlaySoundEffect : public PlaySoundEffectBase
{
public:
    PlaySoundEffect(wxWindow *parent);

protected:
    // Override for data transfer if needed
    // bool TransferDataToWindow() override;
    // bool TransferDataFromWindow() override;

private:
    void OnOK(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
};
