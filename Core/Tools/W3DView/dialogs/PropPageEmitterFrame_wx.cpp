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
    // Initialize controls after they're created
    //
    // Set the frame layout combo box
    //
    // TODO: Declare: int mode = m_pEmitterList->Get_Frame_Mode();
    if (m_idc_frame_layout_combo) {
        m_idc_frame_layout_combo->SetSelection(0);
    }
    if (m_idc_frame_layout_combo) {
        m_idc_frame_layout_combo->SetSelection(1);
    }
    if (m_idc_frame_layout_combo) {
        m_idc_frame_layout_combo->SetSelection(2);
    }
    if (m_idc_frame_layout_combo) {
        m_idc_frame_layout_combo->SetSelection(3);
    }
    if (m_idc_frame_layout_combo) {
        m_idc_frame_layout_combo->SetSelection(4);
    }
    // TODO: Convert: default:
    if (m_idc_frame_layout_combo) {
        m_idc_frame_layout_combo->SetSelection(4);
    }
    // TODO: Convert: break;
    //
    // Create the keyframe control
    //
    // TODO: Convert: m_FrameBar = ColorBarClass::Get_Color_Bar (::GetDlgItem (m_hWnd, IDC_FRAME_BAR));
    //
    // Setup the spinners
    //
    // TODO: Convert: Initialize_Spinner (m_FrameRandomSpin, m_Frames.Rand, 0, 10000);
    //
    //	Reset the keyframe control
    //
    // TODO: Convert: m_FrameBar->Set_Range (0, 1);
    // TODO: Convert: m_FrameBar->Clear_Points ();
    // TODO: Convert: m_FrameBar->Modify_Point (0, 0, 0, 0, 0);
    // TODO: Convert: m_FrameBar->Set_Graph_Percent (0, Normalize_Frame(m_Frames.Start));
    //
    // Load the current set of frame keyframes into the control
    //
    // TODO: Convert: m_FrameBar->Modify_Point (index + 1,
    // TODO: Convert: m_Frames.KeyTimes[index] / m_Lifetime,
    // TODO: Convert: 0,
    // TODO: Convert: 0,
    // TODO: Convert: 0);
    // TODO: Convert: m_FrameBar->Set_Graph_Percent (index + 1, Normalize_Frame(m_Frames.Values[index]));
    // TODO: Convert: return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE

    event.Skip();
}

bool PropPageEmitterFrame::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool PropPageEmitterFrame::TransferDataFromWindow()
{
    // Extract data from controls and apply to business logic

    // TODO: Extract data from controls

    return true;
}
