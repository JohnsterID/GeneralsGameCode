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
#include <wx/spinbutt.h>
#include <wx/statbmp.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/xrc/xmlres.h>

// Base class that loads from XRC
class CameraSettingsBase : public wxDialog
{
public:
    CameraSettingsBase() {}
    CameraSettingsBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_CAMERA_SETTINGS")) {
            return false;
        }

        // Get references to controls
        m_idc_static_1 = XRCCTRL(*this, "IDC_STATIC", wxStaticBitmap);
        m_idc_static_2 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_3 = XRCCTRL(*this, "IDC_STATIC", wxStaticBox);
        m_idc_clip_plane_check = XRCCTRL(*this, "IDC_CLIP_PLANE_CHECK", wxCheckBox);
        m_idc_static_4 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_near_clip_edit = XRCCTRL(*this, "IDC_NEAR_CLIP_EDIT", wxTextCtrl);
        m_idc_near_clip_spin = XRCCTRL(*this, "IDC_NEAR_CLIP_SPIN", wxSpinButton);
        m_idc_static_5 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_far_clip_edit = XRCCTRL(*this, "IDC_FAR_CLIP_EDIT", wxTextCtrl);
        m_idc_far_clip_spin = XRCCTRL(*this, "IDC_FAR_CLIP_SPIN", wxSpinButton);
        m_idc_static_6 = XRCCTRL(*this, "IDC_STATIC", wxStaticBox);
        m_idc_fov_check = XRCCTRL(*this, "IDC_FOV_CHECK", wxCheckBox);
        m_idc_static_7 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_lens_edit = XRCCTRL(*this, "IDC_LENS_EDIT", wxTextCtrl);
        m_idc_lens_spin = XRCCTRL(*this, "IDC_LENS_SPIN", wxSpinButton);
        m_idc_static_8 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_9 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_hfov_edit = XRCCTRL(*this, "IDC_HFOV_EDIT", wxTextCtrl);
        m_idc_hfov_spin = XRCCTRL(*this, "IDC_HFOV_SPIN", wxSpinButton);
        m_idc_static_10 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_vfov_edit = XRCCTRL(*this, "IDC_VFOV_EDIT", wxTextCtrl);
        m_idc_vfov_spin = XRCCTRL(*this, "IDC_VFOV_SPIN", wxSpinButton);
        m_idok = XRCCTRL(*this, "IDOK", wxButton);
        m_idcancel = XRCCTRL(*this, "IDCANCEL", wxButton);
        m_idc_reset = XRCCTRL(*this, "IDC_RESET", wxButton);
        m_idc_static_11 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_12 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);

        return true;
    }

protected:
    wxStaticBitmap *m_idc_static_1;
    wxStaticText *m_idc_static_2;
    wxStaticBox *m_idc_static_3;
    wxCheckBox *m_idc_clip_plane_check;
    wxStaticText *m_idc_static_4;
    wxTextCtrl *m_idc_near_clip_edit;
    wxSpinButton *m_idc_near_clip_spin;
    wxStaticText *m_idc_static_5;
    wxTextCtrl *m_idc_far_clip_edit;
    wxSpinButton *m_idc_far_clip_spin;
    wxStaticBox *m_idc_static_6;
    wxCheckBox *m_idc_fov_check;
    wxStaticText *m_idc_static_7;
    wxTextCtrl *m_idc_lens_edit;
    wxSpinButton *m_idc_lens_spin;
    wxStaticText *m_idc_static_8;
    wxStaticText *m_idc_static_9;
    wxTextCtrl *m_idc_hfov_edit;
    wxSpinButton *m_idc_hfov_spin;
    wxStaticText *m_idc_static_10;
    wxTextCtrl *m_idc_vfov_edit;
    wxSpinButton *m_idc_vfov_spin;
    wxButton *m_idok;
    wxButton *m_idcancel;
    wxButton *m_idc_reset;
    wxStaticText *m_idc_static_11;
    wxStaticText *m_idc_static_12;
};

// Derived class for event handlers and custom logic
class CameraSettings : public CameraSettingsBase
{
public:
    CameraSettings(wxWindow *parent);

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
void OnFovCheck(wxCommandEvent &event);  // Button/Checkbox click
    void OnClipPlaneCheck(wxCommandEvent &event);  // Button/Checkbox click
    void OnReset(wxCommandEvent &event);  // Button/Checkbox click
};
