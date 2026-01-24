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

#include "ScaleKey_wx.h"
#include "Utils.h"
#include <wx/xrc/xmlres.h>
#include <wx/spinbutt.h>
#include <wx/spinctrl.h>
#include <wx/textctrl.h>
#include <wx/msgdlg.h>

wxBEGIN_EVENT_TABLE(ScaleKey, ScaleKeyBase)
    EVT_INIT_DIALOG(ScaleKey::OnInitDialog)
    EVT_SPIN(XRCID("IDC_SIZE_SPIN"), ScaleKey::OnSizeSpinChange)
wxEND_EVENT_TABLE()

ScaleKey::ScaleKey(float scale, wxWindow *parent, const wxString& prompt_string)
    : ScaleKeyBase(parent),
      m_Scale(scale),
      m_Prompt(prompt_string)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void ScaleKey::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void ScaleKey::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void ScaleKey::OnInitDialog(wxInitDialogEvent& event)
{
    // Initialize spinner control with range and initial value
    // MFC: m_ScaleSpin.SetRange(1, 10000); m_ScaleSpin.SetPos(int(m_Scale * 100.0F));
    m_idc_size_spin->SetRange(1, 10000);
    m_idc_size_spin->SetValue((int)(m_Scale * 100.0F));
    
    // Set initial text value
    m_idc_size_edit->SetValue(wxString::Format("%.2f", m_Scale));
    
    // If we were given a different prompt upon creation, apply it now
    // MFC: if (!m_Prompt.IsEmpty()) SetDlgItemText(IDC_PROMPT, m_Prompt);
    if (!m_Prompt.IsEmpty()) {
        m_idc_prompt->SetLabel(m_Prompt);
    }

    event.Skip();
}

bool ScaleKey::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool ScaleKey::TransferDataFromWindow()
{
    // Extract data from controls and apply to business logic
    // MFC: int pos = m_ScaleSpin.GetPos();
    int pos = m_idc_size_spin->GetValue();
    
    // MFC: if (pos & 0xffff0000) - Error condition (out of range)
    // wxWidgets handles range internally, but we still validate
    if (pos < 1 || pos > 10000) {
        wxMessageBox("Invalid scale value. Please enter a number between 1 and 10,000",
                     "Invalid Scale", wxOK | wxICON_INFORMATION);
        return false;  // Prevent dialog close
    }
    
    // MFC: m_Scale = ((float)pos) / 100.0F;
    m_Scale = ((float)pos) / 100.0F;
    
    // MFC: We cannot accept this value if it is less than or equal to zero
    if (m_Scale <= 0.0f) {
        wxMessageBox("Scale must be a value greater than zero!", 
                     "Invalid Scale", wxOK | wxICON_INFORMATION);
        return false;  // Prevent dialog close
    }

    return true;
}

void ScaleKey::OnSizeSpinChange(wxSpinEvent& event)
{
    // Handle spinner updates
    // MFC OnNotify has Update_Spinner_Buddy commented out, so we just update display
    int newValue = m_idc_size_spin->GetValue();
    float scale = ((float)newValue) / 100.0F;
    m_idc_size_edit->SetValue(wxString::Format("%.2f", scale));
    
    event.Skip();
}
