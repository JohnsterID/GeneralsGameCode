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

#include "PropPageEmitterFrame_wx.h"
#include <wx/xrc/xmlres.h>
#include <wx/spinbutt.h>

wxBEGIN_EVENT_TABLE(PropPageEmitterFrame, PropPageEmitterFrameBase)
    EVT_INIT_DIALOG(PropPageEmitterFrame::OnInitDialog)
wxEND_EVENT_TABLE()

PropPageEmitterFrame::PropPageEmitterFrame(wxWindow *parent)
    : PropPageEmitterFrameBase(parent)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void PropPageEmitterFrame::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void PropPageEmitterFrame::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void PropPageEmitterFrame::OnInitDialog(wxInitDialogEvent& event)
{
    // Set the frame layout combo box based on emitter mode
    // TODO(Phase 3): Requires m_pEmitterList->Get_Frame_Mode() to select correct item
    // MFC: switch (mode) {
    //   case W3D_EMITTER_FRAME_MODE_1x1: SetCurSel(0); break;
    //   case W3D_EMITTER_FRAME_MODE_2x2: SetCurSel(1); break;
    //   case W3D_EMITTER_FRAME_MODE_4x4: SetCurSel(2); break;
    //   case W3D_EMITTER_FRAME_MODE_8x8: SetCurSel(3); break;
    //   case W3D_EMITTER_FRAME_MODE_16x16: SetCurSel(4); break;
    //   default: SetCurSel(4); break;
    // }
    if (m_idc_frame_layout_combo) {
        m_idc_frame_layout_combo->SetSelection(4);  // Default to 16x16 until m_pEmitterList available
    }

    // TODO(Phase 3 - ColorBarClass): Create keyframe control
    // MFC: m_FrameBar = ColorBarClass::Get_Color_Bar(::GetDlgItem(m_hWnd, IDC_FRAME_BAR));

    // TODO(Phase 3): Setup spinner with emitter data
    // MFC: Initialize_Spinner(m_FrameRandomSpin, m_Frames.Rand, 0, 10000);

    // TODO(Phase 3 - ColorBarClass): Reset and populate keyframe control
    // MFC: m_FrameBar->Set_Range(0, 1);
    // MFC: m_FrameBar->Clear_Points();
    // MFC: m_FrameBar->Modify_Point(0, 0, 0, 0, 0);
    // MFC: m_FrameBar->Set_Graph_Percent(0, Normalize_Frame(m_Frames.Start));
    // MFC: for loop to load keyframes from m_Frames

    event.Skip();
}

bool PropPageEmitterFrame::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool PropPageEmitterFrame::TransferDataFromWindow()
{
    // TODO(Phase 3 - ColorBarClass): Extract frame keyframes from m_FrameBar
    // MFC reads: m_Frames.Rand = GetDlgItemFloat(IDC_FRAME_RANDOM_EDIT)
    // MFC reads keyframe data from m_FrameBar (ColorBarClass)
    return true;
}
