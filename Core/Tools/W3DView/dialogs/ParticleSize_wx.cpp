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
#include <wx/xrc/xmlres.h>
#include <wx/spinbutt.h>

wxBEGIN_EVENT_TABLE(ParticleSize, ParticleSizeBase)

wxEND_EVENT_TABLE()

ParticleSize::ParticleSize(wxWindow *parent)
    : ParticleSizeBase(parent)
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

// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void ParticleSizeBase::OnInitDialog(wxInitDialogEvent& event)
{
    // Initialize controls after they're created
    // TODO: Convert: Initialize_Spinner (m_SizeSpin, m_Size, 0, 10000);
    // TODO: Convert: return TRUE;

    event.Skip();
}

bool ParticleSizeBase::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool ParticleSizeBase::TransferDataFromWindow()
{
    // Extract data from controls and apply to business logic

    // TODO: Convert: m_Size = GetDlgItemFloat (m_hWnd, IDC_SIZE_EDIT);
    // TODO: Convert: return ;

    return true;
}

}
