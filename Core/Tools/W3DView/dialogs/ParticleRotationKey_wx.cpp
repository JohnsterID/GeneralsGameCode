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
#include <wx/xrc/xmlres.h>
#include <wx/spinbutt.h>

wxBEGIN_EVENT_TABLE(ParticleRotationKey, ParticleRotationKeyBase)

wxEND_EVENT_TABLE()

ParticleRotationKey::ParticleRotationKey(wxWindow *parent)
    : ParticleRotationKeyBase(parent)
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

// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void ParticleRotationKeyBase::OnInitDialog(wxInitDialogEvent& event)
{
    // Initialize controls after they're created
    // TODO: Convert: Initialize_Spinner (m_RotationSpin, m_Rotation, -10000, 10000);
    // TODO: Convert: return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE

    event.Skip();
}

bool ParticleRotationKeyBase::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool ParticleRotationKeyBase::TransferDataFromWindow()
{
    // Extract data from controls and apply to business logic

    // TODO: Convert: m_Rotation = GetDlgItemFloat (m_hWnd, IDC_ROTATION_EDIT);

    return true;
}

}
