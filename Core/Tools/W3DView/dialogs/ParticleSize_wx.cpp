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

#include "ParticleSize_wx.h"
#include "Utils.h"
#include <wx/xrc/xmlres.h>
#include <wx/spinbutt.h>
#include <wx/spinctrl.h>
#include <wx/textctrl.h>

wxBEGIN_EVENT_TABLE(ParticleSize, ParticleSizeBase)
    EVT_INIT_DIALOG(ParticleSize::OnInitDialog)
    EVT_SPIN(XRCID("IDC_SIZE_SPIN"), ParticleSize::OnSizeSpinChange)
wxEND_EVENT_TABLE()

ParticleSize::ParticleSize(float size, wxWindow *parent)
    : ParticleSizeBase(parent),
      m_Size(size)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void ParticleSize::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void ParticleSize::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void ParticleSize::OnInitDialog(wxInitDialogEvent& event)
{
    // Initialize spinner control with range and initial value
    // MFC: Initialize_Spinner(m_SizeSpin, m_Size, 0, 10000)
    m_idc_size_spin->SetRange(0, 10000);
    m_idc_size_spin->SetValue((int)m_Size);
    
    // Set initial text value
    m_idc_size_edit->SetValue(wxString::Format("%.2f", m_Size));

    event.Skip();
}

bool ParticleSize::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool ParticleSize::TransferDataFromWindow()
{
    // Extract data from controls and apply to business logic
    // MFC: m_Size = GetDlgItemFloat(m_hWnd, IDC_SIZE_EDIT)
    
    wxString value = m_idc_size_edit->GetValue();
    double temp;
    if (value.ToDouble(&temp)) {
        m_Size = (float)temp;
    }

    return true;
}

void ParticleSize::OnSizeSpinChange(wxSpinEvent& event)
{
    // Handle spinner updates (matches MFC OnNotify with UDN_DELTAPOS)
    // MFC: Update_Spinner_Buddy(pheader->hwndFrom, pupdown->iDelta)
    
    int newValue = m_idc_size_spin->GetValue();
    m_idc_size_edit->SetValue(wxString::Format("%d", newValue));
    
    event.Skip();
}
