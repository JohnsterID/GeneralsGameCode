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

#include "PropPageEmitterParticle_wx.h"
#include <wx/xrc/xmlres.h>
#include <wx/spinbutt.h>

wxBEGIN_EVENT_TABLE(PropPageEmitterParticle, PropPageEmitterParticleBase)
EVT_BUTTON(XRCID("IDC_SPECIFY_CREATION_VOLUME"), PropPageEmitterParticle::OnSpecifyCreationVolume)  // Button/Checkbox click
    EVT_CHECKBOX(XRCID("IDC_MAX_PARTICLES_CHECK"), PropPageEmitterParticle::OnMaxParticlesCheck)  // Button/Checkbox click
    EVT_INIT_DIALOG(PropPageEmitterParticle::OnInitDialog)
wxEND_EVENT_TABLE()

PropPageEmitterParticle::PropPageEmitterParticle(wxWindow *parent)
    : PropPageEmitterParticleBase(parent),
      m_Rate(0.0f),
      m_MaxParticles(0)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void PropPageEmitterParticle::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void PropPageEmitterParticle::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}

// ============================================================================
// Event Handlers (Phase 2 - Auto-integrated)
// ============================================================================

void PropPageEmitterParticle::OnSpecifyCreationVolume(wxCommandEvent &event)
{
    // Open dialog to specify particle creation volume parameters
}

void PropPageEmitterParticle::OnMaxParticlesCheck(wxCommandEvent &event)
{
    // Max particles checkbox toggled - enable/disable related controls
    bool enabled = m_idc_max_particles_check->GetValue();
    // Enable/disable max particles edit and spin controls based on checkbox state
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void PropPageEmitterParticle::OnInitDialog(wxInitDialogEvent& event)
{
    // Initialize controls after they're created
    // Set up burst size spin control
    if (m_idc_burst_size_spin) {
        m_idc_burst_size_spin->SetRange(0, 10000);
        // Burst size value will be set by calling code
    }
    // Set up emission rate spin
    if (m_idc_emission_rate_spin) {
        m_idc_emission_rate_spin->SetRange(-10000, 10000);
        m_idc_emission_rate_spin->SetValue(static_cast<int>(m_Rate));
    }
    // Set up max particles controls
    if (m_idc_max_particles_spin) {
        m_idc_max_particles_spin->SetRange(0, 10000);
        m_idc_max_particles_spin->SetValue(m_MaxParticles);
    }
    if (m_idc_max_particles_check) {
        m_idc_max_particles_check->SetValue(m_MaxParticles != 0);
    }
    event.Skip();
}

bool PropPageEmitterParticle::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool PropPageEmitterParticle::TransferDataFromWindow()
{
    // Extract data from controls
    if (m_idc_emission_rate_spin) {
        m_Rate = static_cast<float>(m_idc_emission_rate_spin->GetValue());
    }
    
    if (m_idc_max_particles_check && m_idc_max_particles_spin) {
        if (m_idc_max_particles_check->GetValue()) {
            m_MaxParticles = m_idc_max_particles_spin->GetValue();
        } else {
            m_MaxParticles = 0;  // Checkbox unchecked means unlimited
        }
    }
    
    return true;
}
