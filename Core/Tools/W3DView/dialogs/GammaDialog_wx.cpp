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
// TODO: dx8wrapper.h inclusion causes StringClass/const char* conflict in vertmaterial.h
// Need to investigate MFC/wxWidgets header ordering or add forward declarations
// #include "dx8wrapper.h"
#include <wx/xrc/xmlres.h>
#include <wx/slider.h>
#include <wx/config.h>

wxBEGIN_EVENT_TABLE(GammaDialog, GammaDialogBase)
EVT_SLIDER(XRCID("IDC_GAMMA_SLIDER"), GammaDialog::OnReleasedcaptureGammaSlider)  // Slider value changed
    EVT_INIT_DIALOG(GammaDialog::OnInitDialog)
wxEND_EVENT_TABLE()

GammaDialog::GammaDialog(wxWindow *parent)
    : GammaDialogBase(parent),
      m_gamma(10)
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
    // Update gamma preview when slider moves
    // MFC: m_gamma = m_gammaslider.GetPos(); DX8Wrapper::Set_Gamma(...); SetDlgItemText(...)
    m_gamma = m_idc_gamma_slider->GetValue();
    
    // Apply gamma immediately for preview
    // TODO: Re-enable after fixing dx8wrapper.h include issue
    // DX8Wrapper::Set_Gamma(m_gamma / 10.0f, 0.0f, 1.0f);
    
    // Update display text
    wxString gamma_text = wxString::Format("%3.2f", m_gamma / 10.0f);
    m_idc_gamma_display->SetLabel(gamma_text);
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void GammaDialog::OnInitDialog(wxInitDialogEvent& event)
{
    // Initialize controls after they're created
    // MFC: m_gamma = AfxGetApp()->GetProfileInt("Config", "Gamma", 10);
    wxConfig config("W3DView");
    m_gamma = config.Read("/Config/Gamma", 10L);
    
    if (m_gamma < 10) m_gamma = 10;
    if (m_gamma > 30) m_gamma = 30;
    
    // Setup gamma slider
    m_idc_gamma_slider->SetRange(10, 30);
    m_idc_gamma_slider->SetValue(m_gamma);
    
    // Display current gamma value
    wxString gamma_text = wxString::Format("%3.2f", m_gamma / 10.0f);
    m_idc_gamma_display->SetLabel(gamma_text);
    
    // Setup calibration instructions (exact MFC text)
    wxString instructions = "Calibration instructions\n";
    instructions += "A. Set Gamma to 1.0 and Monitor Contrast and Brightness to maximum\n";
    instructions += "B. Adjust Monitor Brightness down so Bar 3 is barely visible\n";
    instructions += "C. Adjust Monitor Contrast as preferred but Bars 1,2,3,4 must be distinguishable from each other\n";
    instructions += "D. Set the Gamma using the Slider below so the gray box on the left matches it's checkered surroundings\n";
    instructions += "E. Press OK to save settings";
    m_idc_instructions->SetLabel(instructions);

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
    // MFC: m_gamma = m_gammaslider.GetPos();
    m_gamma = m_idc_gamma_slider->GetValue();
    
    // Validate range
    if (m_gamma < 10) m_gamma = 10;
    if (m_gamma > 30) m_gamma = 30;
    
    // Save to config
    // MFC: AfxGetApp()->WriteProfileInt("Config", "Gamma", m_gamma);
    wxConfig config("W3DView");
    config.Write("/Config/Gamma", m_gamma);
    
    // Apply gamma setting
    // MFC: DX8Wrapper::Set_Gamma(m_gamma/10.0f, 0.0f, 1.0f);
    // TODO: Re-enable after fixing dx8wrapper.h include issue  
    // DX8Wrapper::Set_Gamma(m_gamma / 10.0f, 0.0f, 1.0f);

    return true;
}
