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
#include <wx/xrc/xmlres.h>

wxBEGIN_EVENT_TABLE(ParticleBlurTimeKey, ParticleBlurTimeKeyBase)
EVT_BUTTON(XRCID("IDOK2"), ParticleBlurTimeKey::OnOk2)  // Button/Checkbox click
wxEND_EVENT_TABLE()

ParticleBlurTimeKey::ParticleBlurTimeKey(wxWindow *parent)
    : ParticleBlurTimeKeyBase(parent)
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
    // TODO: Implement OnOk2
    // Control ID: IDOK2
}
