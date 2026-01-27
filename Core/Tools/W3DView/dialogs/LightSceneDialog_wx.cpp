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

#include "LightSceneDialog_wx.h"
#include "../w3dcompat_wx.h"
#include "../w3dviewdoc_wx.h"
#include "light.h"
#include "rendobj.h"
#include <wx/xrc/xmlres.h>

wxBEGIN_EVENT_TABLE(LightSceneDialog, LightSceneDialogBase)
    EVT_INIT_DIALOG(LightSceneDialog::OnInitDialog)
    EVT_SLIDER(XRCID("IDC_INTENSITY_SLIDER"), LightSceneDialog::OnHscroll)
    EVT_SLIDER(XRCID("IDC_SLIDER_RED"), LightSceneDialog::OnSliderRed)
    EVT_SLIDER(XRCID("IDC_SLIDER_GREEN"), LightSceneDialog::OnSliderGreen)
    EVT_SLIDER(XRCID("IDC_SLIDER_BLUE"), LightSceneDialog::OnSliderBlue)
    EVT_CHECKBOX(XRCID("IDC_GRAYSCALE_CHECK"), LightSceneDialog::OnGrayscaleCheck)
    EVT_CHECKBOX(XRCID("IDC_CHANNEL_BOTH_RADIO"), LightSceneDialog::OnChannelBothRadio)
    EVT_CHECKBOX(XRCID("IDC_CHANNEL_DIFFUSE_RADIO"), LightSceneDialog::OnChannelDiffuseRadio)
    EVT_CHECKBOX(XRCID("IDC_CHANNEL_SPECULAR_RADIO"), LightSceneDialog::OnChannelSpecularRadio)
    EVT_CHECKBOX(XRCID("IDC_ATTENUATION_CHECK"), LightSceneDialog::OnAttenuationCheck)
    EVT_SPIN(XRCID("IDC_DISTANCE_SPIN"), LightSceneDialog::OnDistanceSpin)
    EVT_SPIN(XRCID("IDC_START_ATTENUATION_SPIN"), LightSceneDialog::OnStartAttenSpin)
    EVT_SPIN(XRCID("IDC_END_ATTENUATION_SPIN"), LightSceneDialog::OnEndAttenSpin)
wxEND_EVENT_TABLE()

LightSceneDialog::LightSceneDialog(wxWindow *parent)
    : LightSceneDialogBase(parent),
      m_CurrentChannel(BOTH),
      m_InitialRedDiffuse(0),
      m_InitialGreenDiffuse(0),
      m_InitialBlueDiffuse(0),
      m_InitialRedSpecular(0),
      m_InitialGreenSpecular(0),
      m_InitialBlueSpecular(0),
      m_InitialStartAtten(0.0f),
      m_InitialEndAtten(0.0f),
      m_InitialDistance(0.0f),
      m_InitialIntensity(0.0f),
      m_InitialAttenOn(false)
{
    Centre();
}

void LightSceneDialog::OnOK(wxCommandEvent &event)
{
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

// MFC: SceneLightDialog.cpp lines 250-281
void LightSceneDialog::OnCancel(wxCommandEvent &event)
{
    W3DViewDoc *pCDoc = GetCurrentDocument_wx();
    if (pCDoc && pCDoc->GetScene()) {
        LightClass *light = pCDoc->GetSceneLight();
        if (light) {
            Vector3 diffuse;
            diffuse.X = float(m_InitialRedDiffuse) / 100.0f;
            diffuse.Y = float(m_InitialGreenDiffuse) / 100.0f;
            diffuse.Z = float(m_InitialBlueDiffuse) / 100.0f;
            
            Vector3 specular;
            specular.X = float(m_InitialRedSpecular) / 100.0f;
            specular.Y = float(m_InitialGreenSpecular) / 100.0f;
            specular.Z = float(m_InitialBlueSpecular) / 100.0f;
            
            light->Set_Diffuse(diffuse);
            light->Set_Specular(specular);
            light->Set_Intensity(m_InitialIntensity);
            light->Set_Far_Attenuation_Range(m_InitialStartAtten, m_InitialEndAtten);
            light->Set_Flag(LightClass::FAR_ATTENUATION, m_InitialAttenOn);
            Update_Distance(m_InitialDistance);
        }
    }
    EndModal(wxID_CANCEL);
}

// MFC: SceneLightDialog.cpp lines 188-242 (intensity slider)
void LightSceneDialog::OnHscroll(wxCommandEvent &event)
{
    W3DViewDoc *pCDoc = GetCurrentDocument_wx();
    if (pCDoc && pCDoc->GetScene()) {
        LightClass *light = pCDoc->GetSceneLight();
        if (light) {
            float intensity = float(m_idc_intensity_slider->GetValue()) / 100.0f;
            light->Set_Intensity(intensity);
        }
    }
}

// RGB slider handlers (MFC: OnHScroll lines 188-242)
void LightSceneDialog::OnSliderRed(wxCommandEvent &event)
{
    if (m_idc_grayscale_check->GetValue()) {
        int pos = m_idc_slider_red->GetValue();
        m_idc_slider_green->SetValue(pos);
        m_idc_slider_blue->SetValue(pos);
    }
    Vector3 color;
    color.X = float(m_idc_slider_red->GetValue()) / 100.0f;
    color.Y = float(m_idc_slider_green->GetValue()) / 100.0f;
    color.Z = float(m_idc_slider_blue->GetValue()) / 100.0f;
    Update_Light(color);
}

void LightSceneDialog::OnSliderGreen(wxCommandEvent &event)
{
    if (m_idc_grayscale_check->GetValue()) {
        int pos = m_idc_slider_green->GetValue();
        m_idc_slider_red->SetValue(pos);
        m_idc_slider_blue->SetValue(pos);
    }
    Vector3 color;
    color.X = float(m_idc_slider_red->GetValue()) / 100.0f;
    color.Y = float(m_idc_slider_green->GetValue()) / 100.0f;
    color.Z = float(m_idc_slider_blue->GetValue()) / 100.0f;
    Update_Light(color);
}

void LightSceneDialog::OnSliderBlue(wxCommandEvent &event)
{
    if (m_idc_grayscale_check->GetValue()) {
        int pos = m_idc_slider_blue->GetValue();
        m_idc_slider_red->SetValue(pos);
        m_idc_slider_green->SetValue(pos);
    }
    Vector3 color;
    color.X = float(m_idc_slider_red->GetValue()) / 100.0f;
    color.Y = float(m_idc_slider_green->GetValue()) / 100.0f;
    color.Z = float(m_idc_slider_blue->GetValue()) / 100.0f;
    Update_Light(color);
}

// MFC: SceneLightDialog.cpp lines 364-380
void LightSceneDialog::OnGrayscaleCheck(wxCommandEvent &event)
{
    if (m_idc_grayscale_check->GetValue()) {
        int red_pos = m_idc_slider_red->GetValue();
        m_idc_slider_green->SetValue(red_pos);
        m_idc_slider_blue->SetValue(red_pos);
        Vector3 color;
        color.X = color.Y = color.Z = float(red_pos) / 100.0f;
        Update_Light(color);
    }
}

// MFC: SceneLightDialog.cpp lines 388-392
void LightSceneDialog::OnChannelBothRadio(wxCommandEvent &event)
{
    m_CurrentChannel = BOTH;
}

// MFC: SceneLightDialog.cpp lines 400-408
void LightSceneDialog::OnChannelDiffuseRadio(wxCommandEvent &event)
{
    W3DViewDoc *pCDoc = GetCurrentDocument_wx();
    if (pCDoc && pCDoc->GetScene()) {
        LightClass *light = pCDoc->GetSceneLight();
        if (light) {
            Vector3 color;
            light->Get_Diffuse(&color);
            Set_Color_Control_State(color);
            m_CurrentChannel = DIFFUSE;
        }
    }
}

// MFC: SceneLightDialog.cpp lines 416-424
void LightSceneDialog::OnChannelSpecularRadio(wxCommandEvent &event)
{
    W3DViewDoc *pCDoc = GetCurrentDocument_wx();
    if (pCDoc && pCDoc->GetScene()) {
        LightClass *light = pCDoc->GetSceneLight();
        if (light) {
            Vector3 color;
            light->Get_Specular(&color);
            Set_Color_Control_State(color);
            m_CurrentChannel = SPECULAR;
        }
    }
}

// MFC: SceneLightDialog.cpp lines 553-563
void LightSceneDialog::OnAttenuationCheck(wxCommandEvent &event)
{
    W3DViewDoc *pCDoc = GetCurrentDocument_wx();
    if (pCDoc && pCDoc->GetScene()) {
        LightClass *light = pCDoc->GetSceneLight();
        if (light) {
            bool enable = m_idc_attenuation_check->GetValue();
            light->Set_Flag(LightClass::FAR_ATTENUATION, enable);
            Update_Attenuation_Controls();
        }
    }
}

// MFC: WindowProc lines 289-360
void LightSceneDialog::OnDistanceSpin(wxSpinEvent &event)
{
    wxString value_str = m_idc_distance_edit->GetValue();
    double distance;
    if (value_str.ToDouble(&distance)) {
        distance += (event.GetPosition() > 0) ? 0.01 : -0.01;
        if (distance < 0.0) distance = 0.0;
        m_idc_distance_edit->SetValue(wxString::Format("%.2f", distance));
        Update_Distance(float(distance));
    }
}

void LightSceneDialog::OnStartAttenSpin(wxSpinEvent &event)
{
    wxString value_str = m_idc_start_attenuation_edit->GetValue();
    double value;
    if (value_str.ToDouble(&value)) {
        value += (event.GetPosition() > 0) ? 0.01 : -0.01;
        if (value < 0.0) value = 0.0;
        m_idc_start_attenuation_edit->SetValue(wxString::Format("%.2f", value));
        Update_Attenuation();
    }
}

void LightSceneDialog::OnEndAttenSpin(wxSpinEvent &event)
{
    wxString value_str = m_idc_end_attenuation_edit->GetValue();
    double value;
    if (value_str.ToDouble(&value)) {
        value += (event.GetPosition() > 0) ? 0.01 : -0.01;
        if (value < 0.0) value = 0.0;
        m_idc_end_attenuation_edit->SetValue(wxString::Format("%.2f", value));
        Update_Attenuation();
    }
}

// MFC: SceneLightDialog.cpp lines 96-180
void LightSceneDialog::OnInitDialog(wxInitDialogEvent &event)
{
    m_idc_slider_red->SetRange(0, 100);
    m_idc_slider_green->SetRange(0, 100);
    m_idc_slider_blue->SetRange(0, 100);
    
    W3DViewDoc *pCDoc = GetCurrentDocument_wx();
    if (pCDoc && pCDoc->GetScene()) {
        LightClass *light = pCDoc->GetSceneLight();
        if (light) {
            Vector3 diffuse;
            Vector3 specular;
            light->Get_Diffuse(&diffuse);
            light->Get_Specular(&specular);
            
            m_InitialRedDiffuse = int(diffuse.X * 100.0f);
            m_InitialGreenDiffuse = int(diffuse.Y * 100.0f);
            m_InitialBlueDiffuse = int(diffuse.Z * 100.0f);
            m_InitialRedSpecular = int(specular.X * 100.0f);
            m_InitialGreenSpecular = int(specular.Y * 100.0f);
            m_InitialBlueSpecular = int(specular.Z * 100.0f);
            Set_Color_Control_State(diffuse);
            
            double start = 0;
            double end = 0;
            light->Get_Far_Attenuation_Range(start, end);
            bool atten_on = light->Get_Flag(LightClass::FAR_ATTENUATION);
            m_idc_attenuation_check->SetValue(atten_on);
            
            float intensity = light->Get_Intensity();
            float distance = 0;
            if (pCDoc->GetDisplayedObject() != nullptr) {
                Vector3 light_pos = light->Get_Position();
                Vector3 obj_pos = pCDoc->GetDisplayedObject()->Get_Position();
                distance = (light_pos - obj_pos).Length();
            }
            
            m_idc_start_attenuation_edit->SetValue(wxString::Format("%.2f", start));
            m_idc_end_attenuation_edit->SetValue(wxString::Format("%.2f", end));
            m_idc_distance_edit->SetValue(wxString::Format("%.2f", distance));
            m_idc_intensity_slider->SetRange(0, 100);
            m_idc_intensity_slider->SetValue(int(intensity * 100.0f));
            
            m_InitialStartAtten = float(start);
            m_InitialEndAtten = float(end);
            m_InitialDistance = distance;
            m_InitialIntensity = intensity;
            m_InitialAttenOn = atten_on;
        }
    }
    
    m_idc_channel_diffuse_radio->SetValue(true);
    m_CurrentChannel = DIFFUSE;
    Update_Attenuation_Controls();
    event.Skip();
}

bool LightSceneDialog::TransferDataToWindow()
{
    return true;
}

bool LightSceneDialog::TransferDataFromWindow()
{
    return true;
}

// MFC: SceneLightDialog.cpp lines 432-451
void LightSceneDialog::Update_Light(const Vector3 &color)
{
    W3DViewDoc *pCDoc = GetCurrentDocument_wx();
    if (pCDoc && pCDoc->GetScene()) {
        LightClass *light = pCDoc->GetSceneLight();
        if (light) {
            if (m_CurrentChannel & DIFFUSE) {
                light->Set_Diffuse(color);
            }
            if (m_CurrentChannel & SPECULAR) {
                light->Set_Specular(color);
            }
        }
    }
}

// MFC: SceneLightDialog.cpp lines 459-474
void LightSceneDialog::Set_Color_Control_State(const Vector3 &color)
{
    if (color.X == color.Y && color.X == color.Z) {
        m_idc_grayscale_check->SetValue(true);
    } else {
        m_idc_grayscale_check->SetValue(false);
    }
    m_idc_slider_red->SetValue(int(color.X * 100.0f));
    m_idc_slider_green->SetValue(int(color.Y * 100.0f));
    m_idc_slider_blue->SetValue(int(color.Z * 100.0f));
}

// MFC: SceneLightDialog.cpp lines 482-496
void LightSceneDialog::Update_Attenuation()
{
    W3DViewDoc *pCDoc = GetCurrentDocument_wx();
    if (pCDoc && pCDoc->GetScene()) {
        LightClass *light = pCDoc->GetSceneLight();
        if (light) {
            wxString start_str = m_idc_start_attenuation_edit->GetValue();
            wxString end_str = m_idc_end_attenuation_edit->GetValue();
            double start, end;
            if (start_str.ToDouble(&start) && end_str.ToDouble(&end)) {
                light->Set_Far_Attenuation_Range(start, end);
            }
        }
    }
}

// MFC: SceneLightDialog.cpp lines 504-528
void LightSceneDialog::Update_Distance(float distance)
{
    W3DViewDoc *pCDoc = GetCurrentDocument_wx();
    if (pCDoc && pCDoc->GetScene()) {
        LightClass *light = pCDoc->GetSceneLight();
        RenderObjClass *render_obj = pCDoc->GetDisplayedObject();
        if (light) {
            Vector3 obj_pos(0, 0, 0);
            if (render_obj != nullptr) {
                obj_pos = render_obj->Get_Position();
            }
            Vector3 light_pos = light->Get_Position();
            Vector3 direction = light_pos - obj_pos;
            direction.Normalize();
            Vector3 new_pos = obj_pos + (direction * distance);
            light->Set_Position(new_pos);
        }
    }
}

// MFC: SceneLightDialog.cpp lines 536-545
void LightSceneDialog::Update_Attenuation_Controls()
{
    bool enable = m_idc_attenuation_check->GetValue();
    m_idc_start_attenuation_edit->Enable(enable);
    m_idc_start_attenuation_spin->Enable(enable);
    m_idc_end_attenuation_edit->Enable(enable);
    m_idc_end_attenuation_spin->Enable(enable);
}
