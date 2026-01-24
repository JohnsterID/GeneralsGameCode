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

#include "LightAmbientDialog_wx.h"
#include <wx/xrc/xmlres.h>

wxBEGIN_EVENT_TABLE(LightAmbientDialog, LightAmbientDialogBase)
EVT_SLIDER(XRCID("IDC_SLIDER_BLUE"), LightAmbientDialog::OnHscroll)  // Horizontal scroll (slider)
    EVT_CHECKBOX(XRCID("IDC_GRAYSCALE_CHECK"), LightAmbientDialog::OnGrayscaleCheck)  // Button/Checkbox click
wxEND_EVENT_TABLE()

LightAmbientDialog::LightAmbientDialog(wxWindow *parent)
    : LightAmbientDialogBase(parent)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void LightAmbientDialog::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void LightAmbientDialog::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}

// ============================================================================
// Event Handlers (Phase 2 - Auto-integrated)
// ============================================================================

void LightAmbientDialog::OnHscroll(wxCommandEvent &event)
{
    // Slider value changed - update ambient light color preview
    // RGB values are managed by the slider controls themselves
}

void LightAmbientDialog::OnGrayscaleCheck(wxCommandEvent &event)
{
    // Grayscale checkbox toggled
    // When enabled, force RGB sliders to same value for grayscale ambient light
    bool grayscale = m_idc_grayscale_check->GetValue();
    if (grayscale && m_idc_slider_red && m_idc_slider_green && m_idc_slider_blue) {
        int avg = (m_idc_slider_red->GetValue() + 
                   m_idc_slider_green->GetValue() + 
                   m_idc_slider_blue->GetValue()) / 3;
        m_idc_slider_red->SetValue(avg);
        m_idc_slider_green->SetValue(avg);
        m_idc_slider_blue->SetValue(avg);
    }
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

bool LightAmbientDialog::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool LightAmbientDialog::TransferDataFromWindow()
{
    // RGB ambient light values are managed by the slider controls
    // Calling code retrieves values directly from the sliders:
    //   int red = m_idc_slider_red->GetValue();
    //   int green = m_idc_slider_green->GetValue();
    //   int blue = m_idc_slider_blue->GetValue();
    return true;
}
