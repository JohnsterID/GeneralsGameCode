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

#include "GammaDialog_wx.h"
#include <wx/xrc/xmlres.h>

wxBEGIN_EVENT_TABLE(GammaDialog, GammaDialogBase)
EVT_SLIDER(XRCID("IDC_GAMMA_SLIDER"), GammaDialog::OnReleasedcaptureGammaSlider)  // Slider capture released
    EVT_INIT_DIALOG(GammaDialog::OnInitDialog)
wxEND_EVENT_TABLE()

GammaDialog::GammaDialog(wxWindow *parent)
    : GammaDialogBase(parent)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void GammaDialog::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void GammaDialog::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}

// ============================================================================
// Event Handlers (Phase 2 - Auto-integrated)
// ============================================================================

void GammaDialog::OnReleasedcaptureGammaSlider(wxCommandEvent &event)
{
    // TODO: Implement OnReleasedcaptureGammaSlider
    // Control ID: IDC_GAMMA_SLIDER
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void GammaDialog::OnInitDialog(wxInitDialogEvent& event)
{
    // Initialize controls after they're created
    // TODO: Add extra initialization here
    // Load gamma setting from config (TODO: Phase 3 - use wxConfig)
    // For now, use default value
    int m_gamma = 10;  // AfxGetApp()->GetProfileInt("Config", "Gamma", 10);
    if (m_gamma < 10) m_gamma = 10;
    if (m_gamma > 30) m_gamma = 30;
    
    // Setup gamma slider
    if (m_idc_gamma_slider) {
        m_idc_gamma_slider->SetRange(10, 30);
        m_idc_gamma_slider->SetValue(m_gamma);
    }
    
    // Display current gamma value
    wxString gamma_text = wxString::Format("%3.2f", m_gamma / 10.0f);
    if (m_idc_gamma_display) {
        m_idc_gamma_display->SetLabel(gamma_text);  // wxStaticText uses SetLabel()
    }
    
    // Setup calibration instructions
    wxString instructions = "Calibration instructions\n";
    instructions += "A. Set Gamma to 1.0 and Monitor Contrast and Brightness to maximum\n";
    instructions += "B. Adjust Monitor Brightness down so Bar 3 is barely visible\n";
    instructions += "C. Adjust Monitor Contrast as preferred but Bars 1,2,3,4 must be distinguishable from each other\n";
    instructions += "D. Set the Gamma using the Slider below so the gray box on the left matches it's checkered surroundings\n";
    instructions += "E. Press OK to save settings";
    
    if (m_idc_instructions) {
        m_idc_instructions->SetLabel(instructions);  // wxStaticText uses SetLabel()
    }

    event.Skip();
}

bool GammaDialog::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool GammaDialog::TransferDataFromWindow()
{
    // Extract data from controls and apply to business logic

    // TODO: Convert: // TODO: Add extra validation here
    // TODO: Convert: m_gamma=m_gammaslider.GetPos();
    // TODO: Convert: if (m_gamma<10) m_gamma=10;
    // TODO: Convert: if (m_gamma>30) m_gamma=30;
    // TODO: Convert: ::AfxGetApp()->WriteProfileInt("Config","Gamma",m_gamma);
    // TODO: Convert: DX8Wrapper::Set_Gamma(m_gamma/10.0f,0.0f,1.0f);

    return true;
}
