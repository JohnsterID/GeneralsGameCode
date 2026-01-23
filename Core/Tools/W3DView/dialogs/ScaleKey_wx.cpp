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
#include <wx/xrc/xmlres.h>
#include <wx/spinbutt.h>

wxBEGIN_EVENT_TABLE(ScaleKey, ScaleKeyBase)
    EVT_INIT_DIALOG(ScaleKey::OnInitDialog)
wxEND_EVENT_TABLE()

ScaleKey::ScaleKey(wxWindow *parent)
    : ScaleKeyBase(parent)
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
    // Initialize controls after they're created
    // TODO: Convert: m_ScaleSpin.SetRange (1, 10000);
    // TODO: Convert: m_ScaleSpin.SetPos (int(m_Scale * 100.0F));
    // If we were given a different prompt upon creation, apply it now.
    // TODO: Convert: if (!m_Prompt.IsEmpty())
    if (m_idc_prompt) {
        m_idc_prompt->SetValue(m_Prompt);
    }
    // TODO: Convert: return TRUE;

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

    // TODO: Convert: int pos = m_ScaleSpin.GetPos();
    // TODO: Convert: if (pos & 0xffff0000) {
    // TODO: Convert: // Error condition. Most likely the value is out of range.
    // TODO: Convert: MessageBox("Invalid scale value. Please enter a number between 1 and 10,000",
    // TODO: Convert: "Invalid Scale", MB_OK | MB_ICONINFORMATION);
    // TODO: Convert: return;
    // TODO: Convert: }
    // TODO: Convert: m_Scale = ((float)pos) / 100.0F;
    // TODO: Convert: // We cannot accept this value if it is less than or equal to zero.
    // TODO: Convert: if (m_Scale <= 0.0f) {
    // TODO: Convert: MessageBox("Scale must be a value greater than zero!", "Invalid Scale",
    // TODO: Convert: MB_OK | MB_ICONINFORMATION);
    // TODO: Convert: return;
    // TODO: Convert: }
    // TODO: Convert: return ;

    return true;
}
