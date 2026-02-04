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

#include "PropPageEmitterLineprops_wx.h"
#include <wx/xrc/xmlres.h>
#include <wx/spinbutt.h>

wxBEGIN_EVENT_TABLE(PropPageEmitterLineprops, PropPageEmitterLinepropsBase)
    EVT_SPIN(XRCID("IDC_SUBDIVISION_LEVEL_SPIN"), PropPageEmitterLineprops::OnSubdivisionLevelSpin)
    EVT_SPIN(XRCID("IDC_NOISE_AMPLITUDE_SPIN"), PropPageEmitterLineprops::OnNoiseAmplitudeSpin)
    EVT_SPIN(XRCID("IDC_MERGE_ABORT_FACTOR_SPIN"), PropPageEmitterLineprops::OnMergeAbortFactorSpin)
    EVT_SPIN(XRCID("IDC_UVTILING_SPIN"), PropPageEmitterLineprops::OnUVTilingSpin)
    EVT_SPIN(XRCID("IDC_UPERSEC_SPIN"), PropPageEmitterLineprops::OnUPerSecSpin)
    EVT_SPIN(XRCID("IDC_VPERSEC_SPIN"), PropPageEmitterLineprops::OnVPerSecSpin)
    EVT_INIT_DIALOG(PropPageEmitterLineprops::OnInitDialog)
wxEND_EVENT_TABLE()

PropPageEmitterLineprops::PropPageEmitterLineprops(wxWindow *parent)
    : PropPageEmitterLinepropsBase(parent),
      m_NoiseAmplitude(0.0f),
      m_MergeAbortFactor(0.0f),
      m_TextureTileFactor(1.0f),
      m_UPerSec(0.0f),
      m_VPerSec(0.0f),
      m_MappingMode(0),
      m_MergeIntersections(false),
      m_EndCaps(false),
      m_DisableSorting(false)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void PropPageEmitterLineprops::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void PropPageEmitterLineprops::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void PropPageEmitterLineprops::OnInitDialog(wxInitDialogEvent& event)
{
    // Initialize controls after they're created
    // Set up the spinner ranges
    // Converted: m_SubdivisionLevelSpin.SetRange(0,8);
    // Converted: m_SubdivisionLevelSpin.SetPos(m_SubdivisionLevel);
    if (m_idc_noise_amplitude_spin) {
        m_idc_noise_amplitude_spin->SetRange(-10000, 10000);
        m_idc_noise_amplitude_spin->SetValue(static_cast<int>(m_NoiseAmplitude));
    }
    if (m_idc_merge_abort_factor_spin) {
        m_idc_merge_abort_factor_spin->SetRange(-10000, 10000);
        m_idc_merge_abort_factor_spin->SetValue(static_cast<int>(m_MergeAbortFactor));
    }
    if (m_idc_uvtiling_spin) {
        m_idc_uvtiling_spin->SetRange(0.0f, 8.0f);
        m_idc_uvtiling_spin->SetValue(static_cast<int>(m_TextureTileFactor));
    }
    if (m_idc_upersec_spin) {
        m_idc_upersec_spin->SetRange(0.0f, 32.0f);
        m_idc_upersec_spin->SetValue(static_cast<int>(m_UPerSec));
    }
    if (m_idc_vpersec_spin) {
        m_idc_vpersec_spin->SetRange(0.0f, 32.0f);
        m_idc_vpersec_spin->SetValue(static_cast<int>(m_VPerSec));
    }
    // Set the combo box
    if (m_idc_mapmode_combo) {
        m_idc_mapmode_combo->SetSelection(m_MappingMode);
    }
    // Set the checkboxes
    if (m_idc_merge_intersections_check) {
        m_idc_merge_intersections_check->SetValue(m_MergeIntersections);
    }
    if (m_idc_end_caps_check) {
        m_idc_end_caps_check->SetValue(m_EndCaps);
    }
    if (m_idc_disable_sorting_check) {
        m_idc_disable_sorting_check->SetValue(m_DisableSorting);
    }
    
    // TODO(MFC-Implementation): Control enable/disable logic requires m_pEmitterList
    // which should be set via a SetEmitterList() method before showing the dialog.
    // MFC implementation:
    //   bool enable = (m_pEmitterList && m_pEmitterList->Get_Render_Mode() == W3D_EMITTER_RENDER_MODE_LINE);
    //   Enable(enable);  // Enable/disable all dialog controls
    // Required when: Emitter property pages are wired to document emitter list

    event.Skip();
}

bool PropPageEmitterLineprops::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool PropPageEmitterLineprops::TransferDataFromWindow()
{
    // Extract data from controls
    if (m_idc_noise_amplitude_spin) {
        m_NoiseAmplitude = static_cast<float>(m_idc_noise_amplitude_spin->GetValue());
    }
    
    if (m_idc_merge_abort_factor_spin) {
        m_MergeAbortFactor = static_cast<float>(m_idc_merge_abort_factor_spin->GetValue());
    }
    
    if (m_idc_uvtiling_spin) {
        m_TextureTileFactor = static_cast<float>(m_idc_uvtiling_spin->GetValue());
    }
    
    if (m_idc_upersec_spin) {
        m_UPerSec = static_cast<float>(m_idc_upersec_spin->GetValue());
    }
    
    if (m_idc_vpersec_spin) {
        m_VPerSec = static_cast<float>(m_idc_vpersec_spin->GetValue());
    }
    
    if (m_idc_mapmode_combo) {
        m_MappingMode = m_idc_mapmode_combo->GetSelection();
    }
    
    if (m_idc_merge_intersections_check) {
        m_MergeIntersections = m_idc_merge_intersections_check->GetValue();
    }
    
    if (m_idc_end_caps_check) {
        m_EndCaps = m_idc_end_caps_check->GetValue();
    }
    
    if (m_idc_disable_sorting_check) {
        m_DisableSorting = m_idc_disable_sorting_check->GetValue();
    }

    return true;
}


// ============================================================================
// Spin Button Handlers (MFC: OnNotify with Update_Spinner_Buddy)
// ============================================================================

void PropPageEmitterLineprops::UpdateSpinnerBuddy(wxTextCtrl* edit, int delta, float minVal, float maxVal)
{
    // MFC Reference: Utils.cpp Update_Spinner_Buddy
    // Increments/decrements edit box value by delta/100.0 (0.01 per step)
    if (!edit) return;
    
    double currentValue = 0.0;
    edit->GetValue().ToDouble(&currentValue);
    
    currentValue += delta * 0.01f;  // Match MFC: delta / 100.0
    
    // Clamp to range
    if (currentValue < minVal) currentValue = minVal;
    if (currentValue > maxVal) currentValue = maxVal;
    
    edit->SetValue(wxString::Format("%.2f", currentValue));
}

void PropPageEmitterLineprops::UpdateSpinnerBuddyInt(wxTextCtrl* edit, int delta, int minVal, int maxVal)
{
    // Integer version for subdivision level (whole numbers)
    if (!edit) return;
    
    long currentValue = 0;
    edit->GetValue().ToLong(&currentValue);
    
    currentValue += delta;
    
    // Clamp to range
    if (currentValue < minVal) currentValue = minVal;
    if (currentValue > maxVal) currentValue = maxVal;
    
    edit->SetValue(wxString::Format("%ld", currentValue));
}

void PropPageEmitterLineprops::OnSubdivisionLevelSpin(wxSpinEvent &event)
{
    // Subdivision level is an integer 0-8
    UpdateSpinnerBuddyInt(m_idc_subdivision_level_edit, event.GetPosition(), 0, 8);
}

void PropPageEmitterLineprops::OnNoiseAmplitudeSpin(wxSpinEvent &event)
{
    UpdateSpinnerBuddy(m_idc_noise_amplitude_edit, event.GetPosition(), -10000.0f, 10000.0f);
}

void PropPageEmitterLineprops::OnMergeAbortFactorSpin(wxSpinEvent &event)
{
    UpdateSpinnerBuddy(m_idc_merge_abort_factor_edit, event.GetPosition(), -10000.0f, 10000.0f);
}

void PropPageEmitterLineprops::OnUVTilingSpin(wxSpinEvent &event)
{
    UpdateSpinnerBuddy(m_idc_uvtiling_edit, event.GetPosition(), 0.0f, 8.0f);
}

void PropPageEmitterLineprops::OnUPerSecSpin(wxSpinEvent &event)
{
    UpdateSpinnerBuddy(m_idc_upersec_edit, event.GetPosition(), 0.0f, 32.0f);
}

void PropPageEmitterLineprops::OnVPerSecSpin(wxSpinEvent &event)
{
    UpdateSpinnerBuddy(m_idc_vpersec_edit, event.GetPosition(), 0.0f, 32.0f);
}
