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
    // TODO: Implement OnFovCheck
    // Control ID: IDC_FOV_CHECK
}

void CameraSettings::OnClipPlaneCheck(wxCommandEvent &event)
{
    // TODO: Implement OnClipPlaneCheck
    // Control ID: IDC_CLIP_PLANE_CHECK
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
    // TODO: Convert: CW3DViewDoc *doc				= ::GetCurrentDocument ();
    // TODO: Convert: CGraphicView *graphic_view = doc->GetGraphicView ();
    // TODO: Convert: CameraClass *camera			= graphic_view->GetCamera ();
    //
    //	Enable/disable the group boxes
    //
    if (m_idc_fov_check) {
        m_idc_fov_check->SetValue(doc->Is_FOV_Manual () != 0);
    }
    if (m_idc_clip_plane_check) {
        m_idc_clip_plane_check->SetValue(doc->Are_Clip_Planes_Manual () != 0);
    }
    // TODO: Declare: float znear = 0;
    // TODO: Declare: float zfar = 0;
    // TODO: Convert: camera->Get_Clip_Planes (znear, zfar);
    if (m_idc_near_clip_spin) {
        m_idc_near_clip_spin->SetRange(0.0F, 999999.0F);
        m_idc_near_clip_spin->SetValue(static_cast<int>(znear));
    }
    if (m_idc_far_clip_spin) {
        m_idc_far_clip_spin->SetRange(1.0F, 999999.0F);
        m_idc_far_clip_spin->SetValue(static_cast<int>(zfar));
    }
    //
    //	Setup the FOV controls
    //
    // TODO: Declare: int hfov_deg = (int)RAD_TO_DEG (camera->Get_Horizontal_FOV ());
    // TODO: Declare: int vfov_deg = (int)RAD_TO_DEG (camera->Get_Vertical_FOV ());
    // Declare variable before use
    float hfov = 0;  // TODO: Get actual value from: float hfov = camera->Get_Horizontal_FOV ();
    if (m_idc_hfov_spin) {
        m_idc_hfov_spin->SetRange(0.0F, 180.0F);
        m_idc_hfov_spin->SetValue(static_cast<int>(hfov_deg));
    }
    if (m_idc_vfov_spin) {
        m_idc_vfov_spin->SetRange(0.0F, 180.0F);
        m_idc_vfov_spin->SetValue(static_cast<int>(vfov_deg));
    }
    //
    //	Setup the camera lens controls
    //
    // TODO: Declare: float hfov = camera->Get_Horizontal_FOV ();
    // TODO: Convert: const float constant	= (18.0F / 1000.0F);
    // TODO: Declare: float lens				= (constant / (::tan (hfov / 2))) * 1000.0F;
    if (m_idc_lens_spin) {
        m_idc_lens_spin->SetRange(1.0F, 200.0F);
        m_idc_lens_spin->SetValue(static_cast<int>(lens));
    }
    // TODO: Convert: OnFovCheck ();
    // TODO: Convert: OnClipPlaneCheck ();
    // TODO: Convert: return TRUE;

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
    // TODO: Convert: doc->Set_Manual_FOV (manual_fov);
    // TODO: Convert: doc->Set_Manul_Clip_Planes (manual_planes);
    // TODO: Convert: if (manual_fov == false) {
    // TODO: Convert: graphic_view->Reset_FOV ();
    // TODO: Convert: } else {
    // TODO: Convert: //
    // TODO: Convert: //	Update the camera's FOV
    // TODO: Convert: //
    double value;
    if (m_idc_hfov_edit && m_idc_hfov_edit->GetValue().ToDouble(&value)) {
        // Use value (cast to float if needed)
    } else {
        wxMessageBox("Please enter a valid numeric value", "Invalid Input", 
                     wxOK | wxICON_ERROR, this);
        return false;
    }
    double value;
    if (m_idc_vfov_edit && m_idc_vfov_edit->GetValue().ToDouble(&value)) {
        // Use value (cast to float if needed)
    } else {
        wxMessageBox("Please enter a valid numeric value", "Invalid Input", 
                     wxOK | wxICON_ERROR, this);
        return false;
    }
    // TODO: Convert: camera->Set_View_Plane (DEG_TO_RAD (hfov_deg), DEG_TO_RAD (vfov_deg));
    // TODO: Convert: }
    // TODO: Convert: //
    // TODO: Convert: //	Update the camera's clip planes
    // TODO: Convert: //
    double value;
    if (m_idc_near_clip_edit && m_idc_near_clip_edit->GetValue().ToDouble(&value)) {
        // Use value (cast to float if needed)
    } else {
        wxMessageBox("Please enter a valid numeric value", "Invalid Input", 
                     wxOK | wxICON_ERROR, this);
        return false;
    }
    double value;
    if (m_idc_far_clip_edit && m_idc_far_clip_edit->GetValue().ToDouble(&value)) {
        // Use value (cast to float if needed)
    } else {
        wxMessageBox("Please enter a valid numeric value", "Invalid Input", 
                     wxOK | wxICON_ERROR, this);
        return false;
    }
    // TODO: Convert: camera->Set_Clip_Planes (znear, zfar);
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
