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

// MFC Reference: CameraSettingsDialog.cpp
// Auto-generated from XRC by xrc2cpp.py

#include "CameraSettings_wx.h"
#include <wx/xrc/xmlres.h>
#include <wx/spinbutt.h>
#include <wx/msgdlg.h>
#include <cmath>

// Phase 4: Engine integration includes
#include "../w3dcompat_wx.h"
#include "../w3dviewdoc_wx.h"
#include "../GraphicView_wx.h"
#include "camera.h"
#include "ViewerScene.h"
#include "rendobj.h"
#include "wwmath.h"

wxBEGIN_EVENT_TABLE(CameraSettings, CameraSettingsBase)
    EVT_CHECKBOX(XRCID("IDC_FOV_CHECK"), CameraSettings::OnFovCheck)
    EVT_CHECKBOX(XRCID("IDC_CLIP_PLANE_CHECK"), CameraSettings::OnClipPlaneCheck)
    EVT_BUTTON(XRCID("IDC_RESET"), CameraSettings::OnReset)
    EVT_INIT_DIALOG(CameraSettings::OnInitDialog)
    // Spin button handlers (MFC OnNotify UDN_DELTAPOS)
    EVT_SPIN(XRCID("IDC_NEAR_CLIP_SPIN"), CameraSettings::OnNearClipSpin)
    EVT_SPIN(XRCID("IDC_FAR_CLIP_SPIN"), CameraSettings::OnFarClipSpin)
    EVT_SPIN(XRCID("IDC_LENS_SPIN"), CameraSettings::OnLensSpin)
    EVT_SPIN(XRCID("IDC_HFOV_SPIN"), CameraSettings::OnHfovSpin)
    EVT_SPIN(XRCID("IDC_VFOV_SPIN"), CameraSettings::OnVfovSpin)
    // Edit box change handlers (MFC OnCommand EN_UPDATE)
    EVT_TEXT(XRCID("IDC_LENS_EDIT"), CameraSettings::OnLensEditChange)
    EVT_TEXT(XRCID("IDC_HFOV_EDIT"), CameraSettings::OnHfovEditChange)
wxEND_EVENT_TABLE()

CameraSettings::CameraSettings(wxWindow *parent)
    : CameraSettingsBase(parent)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void CameraSettings::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void CameraSettings::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}

// ============================================================================
// Event Handlers (Phase 2 - Auto-integrated)
// ============================================================================

void CameraSettings::OnFovCheck(wxCommandEvent &event)
{
    
    bool manual_fov = m_idc_fov_check->GetValue();
    
    m_idc_vfov_spin->Enable(manual_fov);
    m_idc_hfov_spin->Enable(manual_fov);
    m_idc_lens_spin->Enable(manual_fov);
    m_idc_vfov_edit->Enable(manual_fov);
    m_idc_hfov_edit->Enable(manual_fov);
    m_idc_lens_edit->Enable(manual_fov);
}

void CameraSettings::OnClipPlaneCheck(wxCommandEvent &event)
{
    
    bool manual_planes = m_idc_clip_plane_check->GetValue();
    
    m_idc_near_clip_spin->Enable(manual_planes);
    m_idc_far_clip_spin->Enable(manual_planes);
    m_idc_near_clip_edit->Enable(manual_planes);
    m_idc_far_clip_edit->Enable(manual_planes);
}

void CameraSettings::OnReset(wxCommandEvent &event)
{
    
    W3DViewDoc *doc = GetCurrentDocument_wx();
    if (!doc)
    {
        wxLogError("Cannot reset camera: No document available");
        return;
    }
    
    CGraphicView *graphic_view = doc->GetGraphicView();
    if (!graphic_view)
    {
        wxLogError("Cannot reset camera: No graphic view available");
        return;
    }
    
    CameraClass *camera = graphic_view->GetCamera();
    if (!camera)
    {
        wxLogError("Cannot reset camera: No camera available");
        return;
    }
    
    doc->Set_Manual_FOV(false);
    doc->Set_Manul_Clip_Planes(false);  // Note: MFC has typo "Manul" - we match it
    
    graphic_view->Reset_FOV();
    
    RenderObjClass *render_obj = doc->GetDisplayedObject();
    if (render_obj != nullptr)
    {
        graphic_view->Reset_Camera_To_Display_Object(*render_obj);
    }
    
    
    float znear = 0;
    float zfar = 0;
    camera->Get_Clip_Planes(znear, zfar);
    SetDlgItemFloat(m_idc_near_clip_edit, znear);
    SetDlgItemFloat(m_idc_far_clip_edit, zfar);
    
    
    int hfov_deg = (int)RAD_TO_DEG(camera->Get_Horizontal_FOV());
    int vfov_deg = (int)RAD_TO_DEG(camera->Get_Vertical_FOV());
    SetDlgItemFloat(m_idc_hfov_edit, (float)hfov_deg);
    SetDlgItemFloat(m_idc_vfov_edit, (float)vfov_deg);
    
    
    float vfov = camera->Get_Vertical_FOV();
    float lens = ((::atan((18.0F / 1000.0F)) / vfov) * 2.0F) * 1000.0F;
    SetDlgItemFloat(m_idc_lens_edit, lens);
    
    // Update checkboxes to unchecked state
    m_idc_fov_check->SetValue(false);
    m_idc_clip_plane_check->SetValue(false);
    
    // Update the enable/disable state of controls
    wxCommandEvent dummy;
    OnFovCheck(dummy);
    OnClipPlaneCheck(dummy);
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void CameraSettings::OnInitDialog(wxInitDialogEvent& event)
{
    
    W3DViewDoc *doc = GetCurrentDocument_wx();
    if (!doc)
    {
        wxLogError("Cannot initialize camera settings: No document available");
        return;
    }
    
    CGraphicView *graphic_view = doc->GetGraphicView();
    if (!graphic_view)
    {
        wxLogError("Cannot initialize camera settings: No graphic view available");
        return;
    }
    
    CameraClass *camera = graphic_view->GetCamera();
    if (!camera)
    {
        wxLogError("Cannot initialize camera settings: No camera available");
        return;
    }
    
    
    bool manual_fov = doc->Is_FOV_Manual();
    bool manual_planes = doc->Are_Clip_Planes_Manual();
    m_idc_fov_check->SetValue(manual_fov);
    m_idc_clip_plane_check->SetValue(manual_planes);
    
    
    float znear = 0;
    float zfar = 0;
    camera->Get_Clip_Planes(znear, zfar);
    SetDlgItemFloat(m_idc_near_clip_edit, znear);
    SetDlgItemFloat(m_idc_far_clip_edit, zfar);
    
    // Note: Spinner range setup - wxSpinButton doesn't have float range like MFC
    // We'll handle this through validation if needed
    
    
    int hfov_deg = (int)RAD_TO_DEG(camera->Get_Horizontal_FOV());
    int vfov_deg = (int)RAD_TO_DEG(camera->Get_Vertical_FOV());
    SetDlgItemFloat(m_idc_hfov_edit, (float)hfov_deg);
    SetDlgItemFloat(m_idc_vfov_edit, (float)vfov_deg);
    
    
    float hfov = camera->Get_Horizontal_FOV();
    const float constant = (18.0F / 1000.0F);
    float lens = (constant / (::tan(hfov / 2))) * 1000.0F;
    SetDlgItemFloat(m_idc_lens_edit, lens);
    
    
    // Call handlers to set initial enable/disable state
    wxCommandEvent dummy_event;
    OnFovCheck(dummy_event);
    OnClipPlaneCheck(dummy_event);
    
    event.Skip();
}

bool CameraSettings::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool CameraSettings::TransferDataFromWindow()
{
    
    W3DViewDoc *doc = GetCurrentDocument_wx();
    if (!doc)
    {
        wxLogError("Cannot apply camera settings: No document available");
        return false;
    }
    
    CGraphicView *graphic_view = doc->GetGraphicView();
    if (!graphic_view)
    {
        wxLogError("Cannot apply camera settings: No graphic view available");
        return false;
    }
    
    CameraClass *camera = graphic_view->GetCamera();
    if (!camera)
    {
        wxLogError("Cannot apply camera settings: No camera available");
        return false;
    }
    
    
    bool manual_fov = m_idc_fov_check->GetValue();
    bool manual_planes = m_idc_clip_plane_check->GetValue();
    
    doc->Set_Manual_FOV(manual_fov);
    doc->Set_Manul_Clip_Planes(manual_planes);  // Note: MFC typo preserved
    
    
    if (manual_fov == false)
    {
        graphic_view->Reset_FOV();
    }
    else
    {
        // Update the camera's FOV from manual values
        float hfov_deg = GetDlgItemFloat(m_idc_hfov_edit);
        float vfov_deg = GetDlgItemFloat(m_idc_vfov_edit);
        camera->Set_View_Plane(DEG_TO_RAD(hfov_deg), DEG_TO_RAD(vfov_deg));
    }
    
    
    float znear = GetDlgItemFloat(m_idc_near_clip_edit);
    float zfar = GetDlgItemFloat(m_idc_far_clip_edit);
    camera->Set_Clip_Planes(znear, zfar);
    
    // Save camera settings to wxConfig (registry/config file)
    doc->Save_Camera_Settings();
    
    
    ViewerSceneClass *scene = doc->GetScene();
    if (scene)
    {
        float fog_near, fog_far;
        scene->Get_Fog_Range(&fog_near, &fog_far);
        scene->Set_Fog_Range(znear, fog_far);  // Update near clip to match camera
        scene->Recalculate_Fog_Planes();
    }
    
    
    RenderObjClass *render_obj = doc->GetDisplayedObject();
    if (render_obj != nullptr)
    {
        graphic_view->Reset_Camera_To_Display_Object(*render_obj);
    }
    
    
    return true;  // Success
}

// ============================================================================
// Spin Button Handlers (MFC OnNotify UDN_DELTAPOS)
// ============================================================================
// MFC Reference: CameraSettingsDialog.cpp:280-307 (OnNotify)
// Behavior: Increment/decrement edit box values by 0.01 per spin click

void CameraSettings::OnNearClipSpin(wxSpinEvent &event)
{
    UpdateSpinnerBuddy(m_idc_near_clip_edit, m_idc_near_clip_spin, event.GetPosition(), 0.01f);
}

void CameraSettings::OnFarClipSpin(wxSpinEvent &event)
{
    UpdateSpinnerBuddy(m_idc_far_clip_edit, m_idc_far_clip_spin, event.GetPosition(), 0.01f);
}

void CameraSettings::OnLensSpin(wxSpinEvent &event)
{
    UpdateSpinnerBuddy(m_idc_lens_edit, m_idc_lens_spin, event.GetPosition(), 0.01f);
    Update_FOV();  // Lens and FOV are interdependent
}

void CameraSettings::OnHfovSpin(wxSpinEvent &event)
{
    UpdateSpinnerBuddy(m_idc_hfov_edit, m_idc_hfov_spin, event.GetPosition(), 0.01f);
    Update_Camera_Lens();  // FOV and Lens are interdependent
}

void CameraSettings::OnVfovSpin(wxSpinEvent &event)
{
    UpdateSpinnerBuddy(m_idc_vfov_edit, m_idc_vfov_spin, event.GetPosition(), 0.01f);
}

// ============================================================================
// Edit Box Change Handlers (MFC OnCommand EN_UPDATE)
// ============================================================================
// MFC Reference: CameraSettingsDialog.cpp:373-402 (OnCommand)
// Behavior: When lens edit changes, update FOV; when HFOV changes, update lens

void CameraSettings::OnLensEditChange(wxCommandEvent &event)
{
    if (!m_updatingControls) {
        m_updatingControls = true;
        Update_FOV();
        m_updatingControls = false;
    }
}

void CameraSettings::OnHfovEditChange(wxCommandEvent &event)
{
    if (!m_updatingControls) {
        m_updatingControls = true;
        Update_Camera_Lens();
        m_updatingControls = false;
    }
}

// ============================================================================
// Helper Methods (MFC CameraSettingsDialog.cpp:317-365)
// ============================================================================

void CameraSettings::Update_Camera_Lens()
{
    // Get the current horizontal FOV setting
    float hfov = GetDlgItemFloat(m_idc_hfov_edit);

    // Convert the horizontal FOV to a camera lens setting
    if (hfov > 0) {
        const float constant = (18.0f / 1000.0f);
        float lens = (constant / (::tan(DEG_TO_RAD(hfov) / 2))) * 1000.0f;
        SetDlgItemFloat(m_idc_lens_edit, lens);
    }
}

void CameraSettings::Update_FOV()
{
    // Get the current camera lens setting
    float lens = (GetDlgItemFloat(m_idc_lens_edit) / 1000.0f);

    // Convert the camera lens to a FOV
    if (lens > 0) {
        const float constant = (18.0f / 1000.0f);
        float hfov = (::atan(constant / lens) * 2.0f);
        float vfov = (3 * hfov / 4);  // 4:3 aspect ratio

        // Pass the new FOV settings onto the dialog
        SetDlgItemFloat(m_idc_hfov_edit, RAD_TO_DEG(hfov));
        SetDlgItemFloat(m_idc_vfov_edit, RAD_TO_DEG(vfov));
    }
}

void CameraSettings::UpdateSpinnerBuddy(wxTextCtrl *edit, wxSpinButton *spin, int delta, float increment)
{
    // Get current value from edit box
    float value = GetDlgItemFloat(edit);
    
    // Increment by delta (MFC uses delta/100.0 but wxWidgets delta is simpler)
    // wxSpinButton delta is typically +1 or -1 per click
    value += delta * increment;
    
    // Clamp to minimum of 0
    if (value < 0.0f) {
        value = 0.0f;
    }
    
    // Update the edit box
    SetDlgItemFloat(edit, value);
}
