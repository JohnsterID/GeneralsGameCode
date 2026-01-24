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

#include "ParticleRotationKey_wx.h"
#include "Utils.h"
#include <wx/xrc/xmlres.h>
#include <wx/spinbutt.h>
#include <wx/spinctrl.h>
#include <wx/textctrl.h>

wxBEGIN_EVENT_TABLE(ParticleRotationKey, ParticleRotationKeyBase)
    EVT_INIT_DIALOG(ParticleRotationKey::OnInitDialog)
    EVT_SPIN(XRCID("IDC_ROTATION_SPIN"), ParticleRotationKey::OnRotationSpinChange)
wxEND_EVENT_TABLE()

ParticleRotationKey::ParticleRotationKey(float rotation, wxWindow *parent)
    : ParticleRotationKeyBase(parent),
      m_Rotation(rotation)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void ParticleRotationKey::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void ParticleRotationKey::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void ParticleRotationKey::OnInitDialog(wxInitDialogEvent& event)
{
    // Initialize spinner control with range and initial value
    // MFC: Initialize_Spinner(m_RotationSpin, m_Rotation, -10000, 10000)
    m_idc_rotation_spin->SetRange(-10000, 10000);
    m_idc_rotation_spin->SetValue((int)m_Rotation);
    
    // Set initial text value
    m_idc_rotation_edit->SetValue(wxString::Format("%.2f", m_Rotation));

    event.Skip();
}

bool ParticleRotationKey::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool ParticleRotationKey::TransferDataFromWindow()
{
    // Extract data from controls and apply to business logic
    // MFC: m_Rotation = GetDlgItemFloat(m_hWnd, IDC_ROTATION_EDIT)
    
    wxString value = m_idc_rotation_edit->GetValue();
    double temp;
    if (value.ToDouble(&temp)) {
        m_Rotation = (float)temp;
    }

    return true;
}

void ParticleRotationKey::OnRotationSpinChange(wxSpinEvent& event)
{
    // Handle spinner updates (matches MFC OnNotify with UDN_DELTAPOS)
    // MFC: Update_Spinner_Buddy(pheader->hwndFrom, pupdown->iDelta)
    
    int newValue = m_idc_rotation_spin->GetValue();
    m_idc_rotation_edit->SetValue(wxString::Format("%d", newValue));
    
    event.Skip();
}
