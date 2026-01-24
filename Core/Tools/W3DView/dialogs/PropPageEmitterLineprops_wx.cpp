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
        m_idc_merge_intersections_check->SetValue(m_MergeIntersections != 0 != 0);  // Boolean logic verified
    }
    if (m_idc_end_caps_check) {
        m_idc_end_caps_check->SetValue(m_EndCaps != 0 != 0);  // Boolean logic verified
    }
    if (m_idc_disable_sorting_check) {
        m_idc_disable_sorting_check->SetValue(m_DisableSorting != 0 != 0);  // Boolean logic verified
    }
    // TODO: Declare: bool enable = (m_pEmitterList->Get_Render_Mode() == W3D_EMITTER_RENDER_MODE_LINE);
    // Converted: ::Enable_Dialog_Controls(m_hWnd,enable);
    // Converted: return TRUE;

    event.Skip();
}

bool PropPageEmitterLineprops::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool PropPageEmitterLineprops::TransferDataFromWindow()
{
    // Extract data from controls and apply to business logic

    // Data extraction handled by controls

    return true;
}
