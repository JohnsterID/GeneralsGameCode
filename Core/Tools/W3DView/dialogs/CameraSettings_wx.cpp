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
EVT_CHECKBOX(XRCID("IDC_FOV_CHECK"), CameraSettings::OnFovCheck)  // Button/Checkbox click
    EVT_CHECKBOX(XRCID("IDC_CLIP_PLANE_CHECK"), CameraSettings::OnClipPlaneCheck)  // Button/Checkbox click
    EVT_BUTTON(XRCID("IDC_RESET"), CameraSettings::OnReset)  // Button/Checkbox click
    EVT_INIT_DIALOG(CameraSettings::OnInitDialog)
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
    // MFC: bool manual_fov = (SendDlgItemMessage (IDC_FOV_CHECK, BM_GETCHECK) == 1);
    // MFC: ::EnableWindow (m_VFOVSpin, manual_fov);
    // MFC: ::EnableWindow (m_HFOVSpin, manual_fov);
    // MFC: ::EnableWindow (m_LensSpin, manual_fov);
    // MFC: ::EnableWindow (::GetDlgItem (m_hWnd, IDC_VFOV_EDIT), manual_fov);
    // MFC: ::EnableWindow (::GetDlgItem (m_hWnd, IDC_HFOV_EDIT), manual_fov);
    // MFC: ::EnableWindow (::GetDlgItem (m_hWnd, IDC_LENS_EDIT), manual_fov);
    
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
    // MFC: bool manual_planes = (SendDlgItemMessage (IDC_CLIP_PLANE_CHECK, BM_GETCHECK) == 1);
    // MFC: ::EnableWindow (m_NearClipSpin, manual_planes);
    // MFC: ::EnableWindow (m_FarClipSpin, manual_planes);
    // MFC: ::EnableWindow (::GetDlgItem (m_hWnd, IDC_NEAR_CLIP_EDIT), manual_planes);
    // MFC: ::EnableWindow (::GetDlgItem (m_hWnd, IDC_FAR_CLIP_EDIT), manual_planes);
    
    bool manual_planes = m_idc_clip_plane_check->GetValue();
    
    m_idc_near_clip_spin->Enable(manual_planes);
    m_idc_far_clip_spin->Enable(manual_planes);
    m_idc_near_clip_edit->Enable(manual_planes);
    m_idc_far_clip_edit->Enable(manual_planes);
}

void CameraSettings::OnReset(wxCommandEvent &event)
{
    // MFC: CW3DViewDoc *doc                             = ::GetCurrentDocument ();
    // MFC: CGraphicView *graphic_view = doc->GetGraphicView ();
    // MFC: CameraClass *camera                  = graphic_view->GetCamera ();
    
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
    
    // MFC: doc->Set_Manual_FOV (false);
    // MFC: doc->Set_Manul_Clip_Planes (false);
    doc->Set_Manual_FOV(false);
    doc->Set_Manul_Clip_Planes(false);  // Note: MFC has typo "Manul" - we match it
    
    // MFC: graphic_view->Reset_FOV ();
    graphic_view->Reset_FOV();
    
    // MFC: RenderObjClass *render_obj = doc->GetDisplayedObject ();
    // MFC: if (render_obj != nullptr) {
    // MFC:     graphic_view->Reset_Camera_To_Display_Object (*render_obj);
    // MFC: }
    RenderObjClass *render_obj = doc->GetDisplayedObject();
    if (render_obj != nullptr)
    {
        graphic_view->Reset_Camera_To_Display_Object(*render_obj);
    }
    
    // MFC: //
    // MFC: //      Update the clip plane controls
    // MFC: //
    // MFC: float znear = 0;
    // MFC: float zfar = 0;
    // MFC: camera->Get_Clip_Planes (znear, zfar);
    // MFC: ::SetDlgItemFloat (m_hWnd, IDC_NEAR_CLIP_EDIT, znear);
    // MFC: ::SetDlgItemFloat (m_hWnd, IDC_FAR_CLIP_EDIT, zfar);
    
    float znear = 0;
    float zfar = 0;
    camera->Get_Clip_Planes(znear, zfar);
    SetDlgItemFloat(m_idc_near_clip_edit, znear);
    SetDlgItemFloat(m_idc_far_clip_edit, zfar);
    
    // MFC: //
    // MFC: //      Update the FOV controls
    // MFC: //
    // MFC: int hfov_deg = (int)RAD_TO_DEG (camera->Get_Horizontal_FOV ());
    // MFC: int vfov_deg = (int)RAD_TO_DEG (camera->Get_Vertical_FOV ());
    // MFC: ::SetDlgItemFloat (m_hWnd, IDC_HFOV_EDIT, hfov_deg);
    // MFC: ::SetDlgItemFloat (m_hWnd, IDC_VFOV_EDIT, vfov_deg);
    
    int hfov_deg = (int)RAD_TO_DEG(camera->Get_Horizontal_FOV());
    int vfov_deg = (int)RAD_TO_DEG(camera->Get_Vertical_FOV());
    SetDlgItemFloat(m_idc_hfov_edit, (float)hfov_deg);
    SetDlgItemFloat(m_idc_vfov_edit, (float)vfov_deg);
    
    // MFC: //
    // MFC: //      Setup the camera lens controls
    // MFC: //
    // MFC: float vfov = camera->Get_Vertical_FOV ();
    // MFC: float lens = ((::atan ((18.0F / 1000.0F)) / vfov) * 2.0F) * 1000.0F;
    // MFC: ::SetDlgItemFloat (m_hWnd, IDC_LENS_EDIT, lens);
    
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
    // MFC: CDialog::OnInitDialog ();
    // MFC: CW3DViewDoc *doc                             = ::GetCurrentDocument ();
    // MFC: CGraphicView *graphic_view = doc->GetGraphicView ();
    // MFC: CameraClass *camera                  = graphic_view->GetCamera ();
    
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
    
    // MFC: //
    // MFC: //      Enable/disable the group boxes
    // MFC: //
    // MFC: SendDlgItemMessage (IDC_FOV_CHECK, BM_SETCHECK, (WPARAM)doc->Is_FOV_Manual ());
    // MFC: SendDlgItemMessage (IDC_CLIP_PLANE_CHECK, BM_SETCHECK, (WPARAM)doc->Are_Clip_Planes_Manual ());
    
    bool manual_fov = doc->Is_FOV_Manual();
    bool manual_planes = doc->Are_Clip_Planes_Manual();
    m_idc_fov_check->SetValue(manual_fov);
    m_idc_clip_plane_check->SetValue(manual_planes);
    
    // MFC: float znear = 0;
    // MFC: float zfar = 0;
    // MFC: camera->Get_Clip_Planes (znear, zfar);
    // MFC: ::Initialize_Spinner (m_NearClipSpin, znear, 0.0F, 999999.0F);
    // MFC: ::Initialize_Spinner (m_FarClipSpin, zfar, 1.0F, 999999.0F);
    
    float znear = 0;
    float zfar = 0;
    camera->Get_Clip_Planes(znear, zfar);
    SetDlgItemFloat(m_idc_near_clip_edit, znear);
    SetDlgItemFloat(m_idc_far_clip_edit, zfar);
    
    // Note: Spinner range setup - wxSpinButton doesn't have float range like MFC
    // We'll handle this through validation if needed
    
    // MFC: //
    // MFC: //      Setup the FOV controls
    // MFC: //
    // MFC: int hfov_deg = (int)RAD_TO_DEG (camera->Get_Horizontal_FOV ());
    // MFC: int vfov_deg = (int)RAD_TO_DEG (camera->Get_Vertical_FOV ());
    // MFC: ::Initialize_Spinner (m_HFOVSpin, hfov_deg, 0.0F, 180.0F);
    // MFC: ::Initialize_Spinner (m_VFOVSpin, vfov_deg, 0.0F, 180.0F);
    
    int hfov_deg = (int)RAD_TO_DEG(camera->Get_Horizontal_FOV());
    int vfov_deg = (int)RAD_TO_DEG(camera->Get_Vertical_FOV());
    SetDlgItemFloat(m_idc_hfov_edit, (float)hfov_deg);
    SetDlgItemFloat(m_idc_vfov_edit, (float)vfov_deg);
    
    // MFC: //
    // MFC: //      Setup the camera lens controls
    // MFC: //
    // MFC: float hfov = camera->Get_Horizontal_FOV ();
    // MFC: const float constant    = (18.0F / 1000.0F);
    // MFC: float lens                              = (constant / (::tan (hfov / 2))) * 1000.0F;
    // MFC: ::Initialize_Spinner (m_LensSpin, lens, 1.0F, 200.0F);
    
    float hfov = camera->Get_Horizontal_FOV();
    const float constant = (18.0F / 1000.0F);
    float lens = (constant / (::tan(hfov / 2))) * 1000.0F;
    SetDlgItemFloat(m_idc_lens_edit, lens);
    
    // MFC: OnFovCheck ();
    // MFC: OnClipPlaneCheck ();
    // MFC: return TRUE;
    
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
    // MFC: CW3DViewDoc *doc                             = ::GetCurrentDocument ();
    // MFC: CGraphicView *graphic_view = doc->GetGraphicView ();
    // MFC: CameraClass *camera                  = graphic_view->GetCamera ();
    
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
    
    // MFC: bool manual_fov         = (SendDlgItemMessage (IDC_FOV_CHECK, BM_GETCHECK) == 1);
    // MFC: bool manual_planes      = (SendDlgItemMessage (IDC_CLIP_PLANE_CHECK, BM_GETCHECK) == 1);
    
    bool manual_fov = m_idc_fov_check->GetValue();
    bool manual_planes = m_idc_clip_plane_check->GetValue();
    
    // MFC: doc->Set_Manual_FOV (manual_fov);
    // MFC: doc->Set_Manul_Clip_Planes (manual_planes);
    doc->Set_Manual_FOV(manual_fov);
    doc->Set_Manul_Clip_Planes(manual_planes);  // Note: MFC typo preserved
    
    // MFC: if (manual_fov == false) {
    // MFC:     graphic_view->Reset_FOV ();
    // MFC: } else {
    // MFC:     //
    // MFC:     //      Update the camera's FOV
    // MFC:     //
    // MFC:     float hfov_deg = ::GetDlgItemFloat (m_hWnd, IDC_HFOV_EDIT);
    // MFC:     float vfov_deg = ::GetDlgItemFloat (m_hWnd, IDC_VFOV_EDIT);
    // MFC:     camera->Set_View_Plane (DEG_TO_RAD (hfov_deg), DEG_TO_RAD (vfov_deg));
    // MFC: }
    
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
    
    // MFC: //
    // MFC: //      Update the camera's clip planes
    // MFC: //
    // MFC: float znear = ::GetDlgItemFloat (m_hWnd, IDC_NEAR_CLIP_EDIT);
    // MFC: float zfar = ::GetDlgItemFloat (m_hWnd, IDC_FAR_CLIP_EDIT);
    // MFC: camera->Set_Clip_Planes (znear, zfar);
    // MFC: doc->Save_Camera_Settings ();
    
    float znear = GetDlgItemFloat(m_idc_near_clip_edit);
    float zfar = GetDlgItemFloat(m_idc_far_clip_edit);
    camera->Set_Clip_Planes(znear, zfar);
    
    // TODO: Phase 4.2 - Implement Save_Camera_Settings() in W3DViewDoc
    // This saves settings to registry/config. For now, settings are applied but not persisted.
    // doc->Save_Camera_Settings();
    
    // MFC: //
    // MFC: // Update the fog settings. The fog near clip plane should always be equal
    // MFC: // to the camera near clip plane, but the fog far clip plane is scene
    // MFC: // dependent. We will be sure to modify only the near clip plane here.
    // MFC: //
    // MFC: float fog_near, fog_far;
    // MFC: doc->GetScene()->Get_Fog_Range(&fog_near, &fog_far);
    // MFC: doc->GetScene()->Set_Fog_Range(znear, fog_far);
    // MFC: doc->GetScene()->Recalculate_Fog_Planes();
    
    ViewerSceneClass *scene = doc->GetScene();
    if (scene)
    {
        float fog_near, fog_far;
        scene->Get_Fog_Range(&fog_near, &fog_far);
        scene->Set_Fog_Range(znear, fog_far);  // Update near clip to match camera
        scene->Recalculate_Fog_Planes();
    }
    
    // MFC: //
    // MFC: //      Refresh the camera settings
    // MFC: //
    // MFC: RenderObjClass *render_obj = doc->GetDisplayedObject ();
    // MFC: if (render_obj != nullptr) {
    // MFC:     graphic_view->Reset_Camera_To_Display_Object (*render_obj);
    // MFC: }
    
    RenderObjClass *render_obj = doc->GetDisplayedObject();
    if (render_obj != nullptr)
    {
        graphic_view->Reset_Camera_To_Display_Object(*render_obj);
    }
    
    // MFC: CDialog::OnOK ();
    // MFC: return ;
    
    return true;  // Success
}
