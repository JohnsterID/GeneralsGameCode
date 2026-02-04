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
// MFC Reference: ParticleFrameKeyDialog.cpp

#include "ParticleFrameKey_wx.h"
#include <wx/xrc/xmlres.h>
#include <wx/spinbutt.h>

wxBEGIN_EVENT_TABLE(ParticleFrameKey, ParticleFrameKeyBase)
    EVT_INIT_DIALOG(ParticleFrameKey::OnInitDialog)
    EVT_SPIN(XRCID("IDC_FRAME_SPIN"), ParticleFrameKey::OnFrameSpinChange)
wxEND_EVENT_TABLE()

ParticleFrameKey::ParticleFrameKey(float frame, wxWindow *parent)
    : ParticleFrameKeyBase(parent),
      m_Frame(frame)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void ParticleFrameKey::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void ParticleFrameKey::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void ParticleFrameKey::OnInitDialog(wxInitDialogEvent& event)
{
    // MFC Reference: ParticleFrameKeyDialog.cpp:44-52 (OnInitDialog)
    // Initialize spinner control with range and initial value
    if (m_idc_frame_spin) {
        m_idc_frame_spin->SetRange(-1024, 1024);
        m_idc_frame_spin->SetValue(static_cast<int>(m_Frame));
    }
    
    // Set initial text value in edit box
    if (m_idc_frame_edit) {
        m_idc_frame_edit->SetValue(wxString::Format("%.2f", m_Frame));
    }

    event.Skip();
}

bool ParticleFrameKey::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool ParticleFrameKey::TransferDataFromWindow()
{
    // MFC Reference: ParticleFrameKeyDialog.cpp:54-58 (OnOK)
    // Extract frame value from edit control
    if (m_idc_frame_edit) {
        wxString text = m_idc_frame_edit->GetValue();
        double temp;
        if (text.ToDouble(&temp)) {
            m_Frame = static_cast<float>(temp);
        }
    }
    return true;
}

void ParticleFrameKey::OnFrameSpinChange(wxSpinEvent& event)
{
    // Handle spinner updates (MFC OnNotify with UDN_DELTAPOS)
    // MFC: Update_Spinner_Buddy(pheader->hwndFrom, pupdown->iDelta)
    // MFC behavior: increment by delta/100.0 (0.01 per step)
    
    // Get current value from edit box
    wxString value = m_idc_frame_edit->GetValue();
    double currentValue = 0.0;
    value.ToDouble(&currentValue);
    
    // Determine delta direction from spin event
    int delta = event.GetPosition();
    currentValue += delta * 0.01f;  // MFC: delta/100.0
    
    // Clamp to valid range
    if (currentValue < -1024.0) currentValue = -1024.0;
    if (currentValue > 1024.0) currentValue = 1024.0;
    
    // Update edit box with float format
    m_idc_frame_edit->SetValue(wxString::Format("%.2f", currentValue));
    
    event.Skip();
}
