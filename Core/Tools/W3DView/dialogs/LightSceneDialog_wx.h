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

    // Event handlers (Phase 2)
void OnHscroll(wxCommandEvent &event);  // Horizontal scroll (slider)
    void OnGrayscaleCheck(wxCommandEvent &event);  // Button/Checkbox click
    void OnChannelBothRadio(wxCommandEvent &event);  // Button/Checkbox click
    void OnChannelDiffuseRadio(wxCommandEvent &event);  // Button/Checkbox click
    void OnChannelSpecularRadio(wxCommandEvent &event);  // Button/Checkbox click
    void OnAttenuationCheck(wxCommandEvent &event);  // Button/Checkbox click
    
    // ============================================================================
    // Phase 4: Additional Event Handlers and Methods Needed
    // ============================================================================
    
    // TODO: Phase 4 - Add OnInitDialog event handler (MFC: SceneLightDialog.cpp lines 96-180)
    // void OnInitDialog(wxInitDialogEvent& event);
    // Required for loading initial values from scene light
    
    // TODO: Phase 4 - Add slider event handlers (MFC: OnHScroll lines 188-242)
    // Need separate handlers or unified handler for:
    // - m_idc_slider_red (RGB color control)
    // - m_idc_slider_green (RGB color control)
    // - m_idc_slider_blue (RGB color control)
    // - m_idc_intensity_slider (already has OnHscroll, but needs proper implementation)
    
    // TODO: Phase 4 - Add spinner event handlers (MFC: WindowProc lines 289-360)
    // void OnDistanceSpin(wxSpinEvent& event);
    // void OnStartAttenSpin(wxSpinEvent& event);
    // void OnEndAttenSpin(wxSpinEvent& event);
    
    // TODO: Phase 4 - Add helper methods (MFC: SceneLightDialog.cpp lines 432-545)
    // void Update_Light(const Vector3 &color);  // Lines 432-451
    // void Set_Color_Control_State(const Vector3 &color);  // Lines 459-474
    // void Update_Attenuation();  // Lines 482-496
    // void Update_Distance(float distance);  // Lines 504-528
    // void Update_Attenuation_Controls();  // Lines 536-545
    
    // ============================================================================
    // Phase 4: Member Variables Needed for State Tracking
    // ============================================================================
    
    // TODO: Phase 4 - Add member variables for state tracking (MFC: SceneLightDialog.h lines 104-116)
    // Required for OnCancel restoration:
    //
    // // Channel selection enum
    // enum CHANNEL {
    //     DIFFUSE = 2,
    //     SPECULAR = 4,
    //     BOTH = DIFFUSE | SPECULAR
    // };
    //
    // // Initial color values (saved on OnInitDialog, restored on OnCancel)
    // int m_InitialRedDiffuse;
    // int m_InitialGreenDiffuse;
    // int m_InitialBlueDiffuse;
    // int m_InitialRedSpecular;
    // int m_InitialGreenSpecular;
    // int m_InitialBlueSpecular;
    // CHANNEL m_CurrentChannel;
    //
    // // Initial light settings
    // float m_InitialStartAtten;
    // float m_InitialEndAtten;
    // float m_InitialDistance;
    // float m_InitialIntensity;
    // bool m_InitialAttenOn;
    
    // ============================================================================
    // Phase 4: BLOCKER - Missing W3DViewDoc Method
    // ============================================================================
    
    // TODO: Phase 4 - BLOCKER: GetSceneLight() doesn't exist in W3DViewDoc_wx yet!
    //   Must add to W3DViewDoc_wx before this dialog can work:
    //   1. w3dviewdoc_wx.h: Add forward declaration: class LightClass;
    //   2. w3dviewdoc_wx.h: Add member variable: LightClass* m_sceneLight;
    //   3. w3dviewdoc_wx.h: Add accessor: LightClass* GetSceneLight() { return m_sceneLight; }
    //   4. w3dviewdoc_wx.cpp: Initialize m_sceneLight in constructor
    //   5. w3dviewdoc_wx.cpp: Clean up in destructor if needed
    //   See MFC reference: W3DViewDoc.h line 118 (GetSceneLight)
    //                      W3DViewDoc.h member variable m_pCSceneLight
};
