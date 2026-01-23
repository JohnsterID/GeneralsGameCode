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

#include "PropPageEmitterLinegroup_wx.h"
#include <wx/xrc/xmlres.h>
#include <wx/spinbutt.h>

wxBEGIN_EVENT_TABLE(PropPageEmitterLinegroup, PropPageEmitterLinegroupBase)

wxEND_EVENT_TABLE()

PropPageEmitterLinegroup::PropPageEmitterLinegroup(wxWindow *parent)
    : PropPageEmitterLinegroupBase(parent)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void PropPageEmitterLinegroup::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void PropPageEmitterLinegroup::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);

// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void PropPageEmitterLinegroupBase::OnInitDialog(wxInitDialogEvent& event)
{
    // Initialize controls after they're created
    //
    // Create the keyframe control
    //
    // TODO: Convert: m_BlurTimeBar = ColorBarClass::Get_Color_Bar (::GetDlgItem (m_hWnd, IDC_BLUR_TIME_BAR));
    //
    // Setup the spinners
    //
    // TODO: Convert: Initialize_Spinner (m_BlurTimeRandomSpin, m_BlurTimes.Rand, 0, 10000);
    //
    //	Reset the keyframe control
    //
    // TODO: Convert: m_BlurTimeBar->Set_Range (0, 1);
    // TODO: Convert: m_BlurTimeBar->Clear_Points ();
    // TODO: Convert: m_BlurTimeBar->Modify_Point (0, 0, 0, 0, 0);
    // TODO: Convert: m_BlurTimeBar->Set_Graph_Percent (0, Normalize_Blur_Time(m_BlurTimes.Start));
    //
    // Load the current set of frame keyframes into the control
    //
    // TODO: Convert: m_BlurTimeBar->Modify_Point (index + 1,
    // TODO: Convert: m_BlurTimes.KeyTimes[index] / m_Lifetime,
    // TODO: Convert: 0,
    // TODO: Convert: 0,
    // TODO: Convert: 0);
    // TODO: Convert: m_BlurTimeBar->Set_Graph_Percent (index + 1, Normalize_Blur_Time(m_BlurTimes.Values[index]));
    // TODO: Convert: return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE

    event.Skip();
}

bool PropPageEmitterLinegroupBase::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool PropPageEmitterLinegroupBase::TransferDataFromWindow()
{
    // Extract data from controls and apply to business logic

    // TODO: Extract data from controls

    return true;
}

}
