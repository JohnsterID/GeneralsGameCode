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

#include "ParticleBlurTimeKey_wx.h"
#include "Utils.h"
#include <wx/xrc/xmlres.h>
#include <wx/spinbutt.h>
#include <wx/spinctrl.h>
#include <wx/textctrl.h>

wxBEGIN_EVENT_TABLE(ParticleBlurTimeKey, ParticleBlurTimeKeyBase)
EVT_BUTTON(XRCID("IDOK2"), ParticleBlurTimeKey::OnOk2)  // OK button
    EVT_INIT_DIALOG(ParticleBlurTimeKey::OnInitDialog)
    EVT_SPIN(XRCID("IDC_BLUR_TIME_SPIN"), ParticleBlurTimeKey::OnBlurTimeSpinChange)
wxEND_EVENT_TABLE()

ParticleBlurTimeKey::ParticleBlurTimeKey(float blur_time, wxWindow *parent)
    : ParticleBlurTimeKeyBase(parent),
      m_BlurTime(blur_time)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void ParticleBlurTimeKey::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void ParticleBlurTimeKey::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}

// ============================================================================
// Event Handlers (Phase 2 - Auto-integrated)
// ============================================================================

void ParticleBlurTimeKey::OnOk2(wxCommandEvent &event)
{
    // MFC: m_BlurTime = GetDlgItemFloat(m_hWnd, IDC_BLUR_TIME_EDIT); CDialog::OnOK();
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void ParticleBlurTimeKey::OnInitDialog(wxInitDialogEvent& event)
{
    // Initialize spinner control with range and initial value
    // MFC: Initialize_Spinner(m_BlurTimeSpin, m_BlurTime, -1024, 1024)
    m_idc_blur_time_spin->SetRange(-1024, 1024);
    m_idc_blur_time_spin->SetValue((int)m_BlurTime);
    
    // Set initial text value
    m_idc_blur_time_edit->SetValue(wxString::Format("%.2f", m_BlurTime));

    event.Skip();
}

bool ParticleBlurTimeKey::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool ParticleBlurTimeKey::TransferDataFromWindow()
{
    // Extract data from controls and apply to business logic
    // MFC: m_BlurTime = GetDlgItemFloat(m_hWnd, IDC_BLUR_TIME_EDIT)
    
    wxString value = m_idc_blur_time_edit->GetValue();
    double temp;
    if (value.ToDouble(&temp)) {
        m_BlurTime = (float)temp;
    }

    return true;
}

void ParticleBlurTimeKey::OnBlurTimeSpinChange(wxSpinEvent& event)
{
    // Handle spinner updates (matches MFC OnNotify with UDN_DELTAPOS)
    // MFC: Update_Spinner_Buddy(pheader->hwndFrom, pupdown->iDelta)
    
    int newValue = m_idc_blur_time_spin->GetValue();
    m_idc_blur_time_edit->SetValue(wxString::Format("%d", newValue));
    
    event.Skip();
}
