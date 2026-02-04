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

#include "PropPageEmitterSize_wx.h"
#include <wx/xrc/xmlres.h>
#include <wx/spinbutt.h>

wxBEGIN_EVENT_TABLE(PropPageEmitterSize, PropPageEmitterSizeBase)
    EVT_SPIN(XRCID("IDC_SIZE_RANDOM_SPIN"), PropPageEmitterSize::OnSizeRandomSpin)
    EVT_INIT_DIALOG(PropPageEmitterSize::OnInitDialog)
wxEND_EVENT_TABLE()

PropPageEmitterSize::PropPageEmitterSize(wxWindow *parent)
    : PropPageEmitterSizeBase(parent)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void PropPageEmitterSize::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void PropPageEmitterSize::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void PropPageEmitterSize::OnInitDialog(wxInitDialogEvent& event)
{
    // Initialize controls after they're created
    // Allow the base class to process this message
    // TODO: Convert: m_SizeBar = ColorBarClass::Get_Color_Bar (::GetDlgItem (m_hWnd, IDC_SIZE_BAR));
    // TODO: Convert: m_SizeBar->Set_Range (0, 1);
    //
    // Setup the spinners
    //
    // TODO: Convert: Initialize_Spinner (m_SizeRandomSpin, m_OrigSizes.Rand, 0, 10000);
    //
    //	Reset the color bars
    //
    // TODO: Convert: m_SizeBar->Set_Range (0, 1);
    // TODO: Convert: m_SizeBar->Clear_Points ();
    // TODO: Convert: m_SizeBar->Modify_Point (0, 0, 0, 0, 0);
    // TODO: Convert: m_SizeBar->Set_Graph_Percent (0, m_OrigSizes.Start / m_MaxSize);
    //
    //	Set-up the color bar
    //
    // TODO: Convert: m_SizeBar->Modify_Point (index + 1,
    // TODO: Convert: m_OrigSizes.KeyTimes[index] / m_Lifetime,
    // TODO: Convert: 0,
    // TODO: Convert: 0,
    // TODO: Convert: 0);
    // TODO: Convert: m_SizeBar->Set_Graph_Percent (index + 1, m_OrigSizes.Values[index] / m_MaxSize);
	// MFC: return TRUE;

    event.Skip();
}

bool PropPageEmitterSize::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool PropPageEmitterSize::TransferDataFromWindow()
{
    // TODO(Phase 3 - ColorBarClass): Extract size keyframes from m_SizeBar
    // MFC reads: m_CurrentSizes.Rand = GetDlgItemFloat(IDC_SIZE_RANDOM_EDIT)
    // MFC reads keyframe data from m_SizeBar (ColorBarClass)
    return true;
}


// ============================================================================
// Spin Button Handlers (MFC: OnNotify with Update_Spinner_Buddy)
// ============================================================================

void PropPageEmitterSize::UpdateSpinnerBuddy(wxTextCtrl* edit, int delta, float minVal, float maxVal)
{
    // MFC Reference: Utils.cpp Update_Spinner_Buddy
    if (!edit) return;
    
    double currentValue = 0.0;
    edit->GetValue().ToDouble(&currentValue);
    
    currentValue += delta * 0.01f;  // Match MFC: delta / 100.0
    
    if (currentValue < minVal) currentValue = minVal;
    if (currentValue > maxVal) currentValue = maxVal;
    
    edit->SetValue(wxString::Format("%.2f", currentValue));
}

void PropPageEmitterSize::OnSizeRandomSpin(wxSpinEvent &event)
{
    UpdateSpinnerBuddy(m_idc_size_random_edit, event.GetPosition(), 0.0f, 10000.0f);
    // TODO(Phase 3 - Emitter): m_pEmitterList->Set_Size_Random(m_CurrentSizes.Rand)
}
