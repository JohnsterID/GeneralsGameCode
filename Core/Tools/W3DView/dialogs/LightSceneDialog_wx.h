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
#include <wx/panel.h>
#include <wx/slider.h>
#include <wx/spinbutt.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/xrc/xmlres.h>

// Base class that loads from XRC
class LightSceneDialogBase : public wxDialog
{
public:
    LightSceneDialogBase() {}
    LightSceneDialogBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_LIGHT_SCENE_DIALOG")) {
            return false;
        }

        // Get references to controls
        m_idc_static_1 = XRCCTRL(*this, "IDC_STATIC", wxStaticBox);
        m_idc_channel_diffuse_radio = XRCCTRL(*this, "IDC_CHANNEL_DIFFUSE_RADIO", wxCheckBox);
        m_idc_channel_specular_radio = XRCCTRL(*this, "IDC_CHANNEL_SPECULAR_RADIO", wxCheckBox);
        m_idc_channel_both_radio = XRCCTRL(*this, "IDC_CHANNEL_BOTH_RADIO", wxCheckBox);
        m_idc_red_gradient = XRCCTRL(*this, "IDC_RED_GRADIENT", wxPanel);
        m_idc_static_2 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_slider_red = XRCCTRL(*this, "IDC_SLIDER_RED", wxSlider);
        m_idc_green_gradient = XRCCTRL(*this, "IDC_GREEN_GRADIENT", wxPanel);
        m_idc_static_3 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_slider_green = XRCCTRL(*this, "IDC_SLIDER_GREEN", wxSlider);
        m_idc_blue_gradient = XRCCTRL(*this, "IDC_BLUE_GRADIENT", wxPanel);
        m_idc_static_4 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_slider_blue = XRCCTRL(*this, "IDC_SLIDER_BLUE", wxSlider);
        m_idc_grayscale_check = XRCCTRL(*this, "IDC_GRAYSCALE_CHECK", wxCheckBox);
        m_idc_static_5 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_intensity_slider = XRCCTRL(*this, "IDC_INTENSITY_SLIDER", wxSlider);
        m_idc_static_6 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_distance_edit = XRCCTRL(*this, "IDC_DISTANCE_EDIT", wxTextCtrl);
        m_idc_distance_spin = XRCCTRL(*this, "IDC_DISTANCE_SPIN", wxSpinButton);
        m_idc_static_7 = XRCCTRL(*this, "IDC_STATIC", wxStaticBox);
        m_idc_attenuation_check = XRCCTRL(*this, "IDC_ATTENUATION_CHECK", wxCheckBox);
        m_idc_static_8 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_start_attenuation_edit = XRCCTRL(*this, "IDC_START_ATTENUATION_EDIT", wxTextCtrl);
        m_idc_start_attenuation_spin = XRCCTRL(*this, "IDC_START_ATTENUATION_SPIN", wxSpinButton);
        m_idc_static_9 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_end_attenuation_edit = XRCCTRL(*this, "IDC_END_ATTENUATION_EDIT", wxTextCtrl);
        m_idc_end_attenuation_spin = XRCCTRL(*this, "IDC_END_ATTENUATION_SPIN", wxSpinButton);
        m_idc_static_10 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idok = XRCCTRL(*this, "IDOK", wxButton);
        m_idcancel = XRCCTRL(*this, "IDCANCEL", wxButton);

        return true;
    }

protected:
    wxStaticBox *m_idc_static_1;
    wxCheckBox *m_idc_channel_diffuse_radio;
    wxCheckBox *m_idc_channel_specular_radio;
    wxCheckBox *m_idc_channel_both_radio;
    wxPanel *m_idc_red_gradient;
    wxStaticText *m_idc_static_2;
    wxSlider *m_idc_slider_red;
    wxPanel *m_idc_green_gradient;
    wxStaticText *m_idc_static_3;
    wxSlider *m_idc_slider_green;
    wxPanel *m_idc_blue_gradient;
    wxStaticText *m_idc_static_4;
    wxSlider *m_idc_slider_blue;
    wxCheckBox *m_idc_grayscale_check;
    wxStaticText *m_idc_static_5;
    wxSlider *m_idc_intensity_slider;
    wxStaticText *m_idc_static_6;
    wxTextCtrl *m_idc_distance_edit;
    wxSpinButton *m_idc_distance_spin;
    wxStaticBox *m_idc_static_7;
    wxCheckBox *m_idc_attenuation_check;
    wxStaticText *m_idc_static_8;
    wxTextCtrl *m_idc_start_attenuation_edit;
    wxSpinButton *m_idc_start_attenuation_spin;
    wxStaticText *m_idc_static_9;
    wxTextCtrl *m_idc_end_attenuation_edit;
    wxSpinButton *m_idc_end_attenuation_spin;
    wxStaticText *m_idc_static_10;
    wxButton *m_idok;
    wxButton *m_idcancel;
};

// Derived class for event handlers and custom logic
class LightSceneDialog : public LightSceneDialogBase
{
public:
    LightSceneDialog(wxWindow *parent);

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
    bool TransferDataToWindow() override;
    bool TransferDataFromWindow() override;

    // Event handlers
    void OnHscroll(wxCommandEvent &event);  // Intensity slider
    void OnSliderRed(wxCommandEvent &event);  // RGB slider
    void OnSliderGreen(wxCommandEvent &event);  // RGB slider
    void OnSliderBlue(wxCommandEvent &event);  // RGB slider
    void OnGrayscaleCheck(wxCommandEvent &event);
    void OnChannelBothRadio(wxCommandEvent &event);
    void OnChannelDiffuseRadio(wxCommandEvent &event);
    void OnChannelSpecularRadio(wxCommandEvent &event);
    void OnAttenuationCheck(wxCommandEvent &event);
    void OnDistanceSpin(wxSpinEvent &event);
    void OnStartAttenSpin(wxSpinEvent &event);
    void OnEndAttenSpin(wxSpinEvent &event);
    void OnInitDialog(wxInitDialogEvent &event);
    
    // Helper methods (MFC: SceneLightDialog.cpp)
    void Update_Light(const class Vector3 &color);
    void Set_Color_Control_State(const class Vector3 &color);
    void Update_Attenuation();
    void Update_Distance(float distance);
    void Update_Attenuation_Controls();
    
    // Channel selection enum (MFC: SceneLightDialog.h:104)
    enum CHANNEL {
        DIFFUSE = 2,
        SPECULAR = 4,
        BOTH = DIFFUSE | SPECULAR
    };
    
    // Initial values for cancel restore (MFC: SceneLightDialog.h:108-115)
    int m_InitialRedDiffuse;
    int m_InitialGreenDiffuse;
    int m_InitialBlueDiffuse;
    int m_InitialRedSpecular;
    int m_InitialGreenSpecular;
    int m_InitialBlueSpecular;
    CHANNEL m_CurrentChannel;
    
    // Initial light settings (MFC: SceneLightDialog.h:116)
    float m_InitialStartAtten;
    float m_InitialEndAtten;
    float m_InitialDistance;
    float m_InitialIntensity;
    bool m_InitialAttenOn;
    
};
// NOTE: All methods declared above are implemented in LightSceneDialog_wx.cpp
// MFC Reference: SceneLightDialog.cpp (563 lines)
