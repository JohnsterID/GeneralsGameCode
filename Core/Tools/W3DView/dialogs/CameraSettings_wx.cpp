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
    // TODO: Implement OnReset
    // Control ID: IDC_RESET
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void CameraSettings::OnInitDialog(wxInitDialogEvent& event)
{
    // Initialize controls after they're created
    // TODO: Phase 3 - Get actual document, view, and camera when available
    // CW3DViewDoc *doc = ::GetCurrentDocument();
    // CGraphicView *graphic_view = doc->GetGraphicView();
    // CameraClass *camera = graphic_view->GetCamera();
    
    // For now, use placeholder values until full engine integration
    bool manual_fov = false;  // TODO: doc->Is_FOV_Manual()
    bool manual_planes = false;  // TODO: doc->Are_Clip_Planes_Manual()
    float znear = 1.0f;  // TODO: camera->Get_Clip_Planes(znear, zfar)
    float zfar = 10000.0f;
    float hfov = 1.0f;  // TODO: camera->Get_Horizontal_FOV()
    float vfov = 0.75f;  // TODO: camera->Get_Vertical_FOV()
    
    // Convert radians to degrees for UI
    const float RAD_TO_DEG = 57.2957795f;  // 180/PI
    int hfov_deg = static_cast<int>(hfov * RAD_TO_DEG);
    int vfov_deg = static_cast<int>(vfov * RAD_TO_DEG);
    
    // Calculate lens from hfov
    const float constant = (18.0f / 1000.0f);
    float lens = (constant / (::tan(hfov / 2))) * 1000.0f;
    
    //
    //	Enable/disable the group boxes
    //
    if (m_idc_fov_check) {
        m_idc_fov_check->SetValue(manual_fov);
    }
    if (m_idc_clip_plane_check) {
        m_idc_clip_plane_check->SetValue(manual_planes);
    }
    
    // Setup clip plane controls
    if (m_idc_near_clip_spin) {
        m_idc_near_clip_spin->SetRange(0.0f, 999999.0f);
        m_idc_near_clip_spin->SetValue(static_cast<int>(znear));
    }
    if (m_idc_far_clip_spin) {
        m_idc_far_clip_spin->SetRange(1.0f, 999999.0f);
        m_idc_far_clip_spin->SetValue(static_cast<int>(zfar));
    }
    
    //
    //	Setup the FOV controls
    //
    if (m_idc_hfov_spin) {
        m_idc_hfov_spin->SetRange(0.0f, 180.0f);
        m_idc_hfov_spin->SetValue(hfov_deg);
    }
    if (m_idc_vfov_spin) {
        m_idc_vfov_spin->SetRange(0.0f, 180.0f);
        m_idc_vfov_spin->SetValue(vfov_deg);
    }
    
    //
    //	Setup the camera lens controls
    //
    if (m_idc_lens_spin) {
        m_idc_lens_spin->SetRange(1.0f, 200.0f);
        m_idc_lens_spin->SetValue(static_cast<int>(lens));
    }
    
    // MFC: OnFovCheck();
    // MFC: OnClipPlaneCheck();
    // Set initial enable/disable state for controls based on checkboxes
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
    // Extract data from controls and apply to business logic

    // TODO: Convert: CW3DViewDoc *doc				= ::GetCurrentDocument ();
    // TODO: Convert: CGraphicView *graphic_view = doc->GetGraphicView ();
    // TODO: Convert: CameraClass *camera			= graphic_view->GetCamera ();
    // TODO: Convert: bool manual_fov		= (SendDlgItemMessage (IDC_FOV_CHECK, BM_GETCHECK) == 1);
    // TODO: Convert: bool manual_planes	= (SendDlgItemMessage (IDC_CLIP_PLANE_CHECK, BM_GETCHECK) == 1);
    // TODO: Phase 3 - Apply settings to document/camera when available
    // doc->Set_Manual_FOV(manual_fov);
    // doc->Set_Manual_Clip_Planes(manual_planes);
    
    // Extract FOV values
    double hfov_value, vfov_value;
    if (m_idc_hfov_edit && m_idc_hfov_edit->GetValue().ToDouble(&hfov_value)) {
        // TODO: Phase 3 - camera->Set_View_Plane(DEG_TO_RAD(hfov_value), ...)
    } else {
        wxMessageBox("Please enter a valid horizontal FOV value", "Invalid Input", 
                     wxOK | wxICON_ERROR, this);
        return false;
    }
    
    if (m_idc_vfov_edit && m_idc_vfov_edit->GetValue().ToDouble(&vfov_value)) {
        // TODO: Phase 3 - camera->Set_View_Plane(..., DEG_TO_RAD(vfov_value))
    } else {
        wxMessageBox("Please enter a valid vertical FOV value", "Invalid Input", 
                     wxOK | wxICON_ERROR, this);
        return false;
    }
    
    // Extract clip plane values
    double znear_value, zfar_value;
    if (m_idc_near_clip_edit && m_idc_near_clip_edit->GetValue().ToDouble(&znear_value)) {
        // TODO: Phase 3 - camera->Set_Clip_Planes(znear_value, ...)
    } else {
        wxMessageBox("Please enter a valid near clip plane value", "Invalid Input", 
                     wxOK | wxICON_ERROR, this);
        return false;
    }
    
    if (m_idc_far_clip_edit && m_idc_far_clip_edit->GetValue().ToDouble(&zfar_value)) {
        // TODO: Phase 3 - camera->Set_Clip_Planes(..., zfar_value)
    } else {
        wxMessageBox("Please enter a valid far clip plane value", "Invalid Input", 
                     wxOK | wxICON_ERROR, this);
        return false;
    }
    // TODO: Convert: doc->Save_Camera_Settings ();
    // TODO: Convert: //
    // TODO: Convert: // Update the fog settings. The fog near clip plane should always be equal
    // TODO: Convert: // to the camera near clip plane, but the fog far clip plane is scene
    // TODO: Convert: // dependent. We will be sure to modify only the near clip plane here.
    // TODO: Convert: //
    // TODO: Convert: float fog_near, fog_far;
    // TODO: Convert: doc->GetScene()->Get_Fog_Range(&fog_near, &fog_far);
    // TODO: Convert: doc->GetScene()->Set_Fog_Range(znear, fog_far);
    // TODO: Convert: doc->GetScene()->Recalculate_Fog_Planes();
    // TODO: Convert: //
    // TODO: Convert: //	Refresh the camera settings
    // TODO: Convert: //
    // TODO: Convert: RenderObjClass *render_obj = doc->GetDisplayedObject ();
    // TODO: Convert: if (render_obj != nullptr) {
    // TODO: Convert: graphic_view->Reset_Camera_To_Display_Object (*render_obj);
    // TODO: Convert: }
    // TODO: Convert: return ;

    return true;
}
