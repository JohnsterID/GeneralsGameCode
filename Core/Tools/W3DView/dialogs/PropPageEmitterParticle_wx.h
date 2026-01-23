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

#pragma once

#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/panel.h>
#include <wx/spinbutt.h>
#include <wx/statbmp.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/xrc/xmlres.h>

// Base class that loads from XRC
class PropPageEmitterParticleBase : public wxDialog
{
public:
    PropPageEmitterParticleBase() {}
    PropPageEmitterParticleBase(wxWindow *parent)
    {
        Create(parent);
    }

    bool Create(wxWindow *parent)
    {
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "IDD_PROP_PAGE_EMITTER_PARTICLE")) {
            return false;
        }

        // Get references to controls
        m_idc_static_1 = XRCCTRL(*this, "IDC_STATIC", wxStaticBitmap);
        m_idc_static_2 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_3 = XRCCTRL(*this, "IDC_STATIC", wxPanel);
        m_idc_static_4 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_5 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_emission_rate_edit = XRCCTRL(*this, "IDC_EMISSION_RATE_EDIT", wxTextCtrl);
        m_idc_emission_rate_spin = XRCCTRL(*this, "IDC_EMISSION_RATE_SPIN", wxSpinButton);
        m_idc_static_6 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_static_7 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_burst_size_edit = XRCCTRL(*this, "IDC_BURST_SIZE_EDIT", wxTextCtrl);
        m_idc_burst_size_spin = XRCCTRL(*this, "IDC_BURST_SIZE_SPIN", wxSpinButton);
        m_idc_static_8 = XRCCTRL(*this, "IDC_STATIC", wxPanel);
        m_idc_static_9 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_max_particles_check = XRCCTRL(*this, "IDC_MAX_PARTICLES_CHECK", wxCheckBox);
        m_idc_max_particles_edit = XRCCTRL(*this, "IDC_MAX_PARTICLES_EDIT", wxTextCtrl);
        m_idc_max_particles_spin = XRCCTRL(*this, "IDC_MAX_PARTICLES_SPIN", wxSpinButton);
        m_idc_static_10 = XRCCTRL(*this, "IDC_STATIC", wxPanel);
        m_idc_static_11 = XRCCTRL(*this, "IDC_STATIC", wxStaticText);
        m_idc_specify_creation_volume = XRCCTRL(*this, "IDC_SPECIFY_CREATION_VOLUME", wxButton);

        return true;
    }

protected:
    wxStaticBitmap *m_idc_static_1;
    wxStaticText *m_idc_static_2;
    wxPanel *m_idc_static_3;
    wxStaticText *m_idc_static_4;
    wxStaticText *m_idc_static_5;
    wxTextCtrl *m_idc_emission_rate_edit;
    wxSpinButton *m_idc_emission_rate_spin;
    wxStaticText *m_idc_static_6;
    wxStaticText *m_idc_static_7;
    wxTextCtrl *m_idc_burst_size_edit;
    wxSpinButton *m_idc_burst_size_spin;
    wxPanel *m_idc_static_8;
    wxStaticText *m_idc_static_9;
    wxCheckBox *m_idc_max_particles_check;
    wxTextCtrl *m_idc_max_particles_edit;
    wxSpinButton *m_idc_max_particles_spin;
    wxPanel *m_idc_static_10;
    wxStaticText *m_idc_static_11;
    wxButton *m_idc_specify_creation_volume;
};

// Derived class for event handlers and custom logic
class PropPageEmitterParticle : public PropPageEmitterParticleBase
{
public:
    PropPageEmitterParticle(wxWindow *parent);
    
    // Dialog data (MFC compatibility)
    float m_Rate;                  // Particle emission rate
    int m_MaxParticles;            // Maximum particles allowed

protected:
    // Override for data transfer if needed
    // bool TransferDataToWindow() override;
    // bool TransferDataFromWindow() override;

private:
    void OnOK(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
private:
    // Phase 2.5: Dialog infrastructure
    void OnInitDialog(wxInitDialogEvent& event);
    bool TransferDataToWindow() override;
    bool TransferDataFromWindow() override;

    // Event handlers (Phase 2)
void OnSpecifyCreationVolume(wxCommandEvent &event);  // Button/Checkbox click
    void OnMaxParticlesCheck(wxCommandEvent &event);  // Button/Checkbox click
};
