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

#include "CameraDistance_wx.h"
#include <wx/spinbutt.h>
#include <wx/xrc/xmlres.h>
#include "../GraphicView_wx.h"
#include "../Utils.h"
#include <wx/msgdlg.h>

wxBEGIN_EVENT_TABLE(CameraDistance, CameraDistanceBase)
    EVT_INIT_DIALOG(CameraDistance::OnInitDialog)
    EVT_SPIN(XRCID("IDC_DISTANCE_SPIN"), CameraDistance::OnDistanceSpin)
    EVT_BUTTON(wxID_OK, CameraDistance::OnOK)
    EVT_BUTTON(wxID_CANCEL, CameraDistance::OnCancel)
wxEND_EVENT_TABLE()

CameraDistance::CameraDistance(wxWindow *parent)
    : CameraDistanceBase(parent)
{
    Centre();
}

// ============================================================================
// Phase 2.5: Initialization and Data Transfer
// ============================================================================

void CameraDistance::OnInitDialog(wxInitDialogEvent& event)
{
    // Initialize controls after they're created
    CGraphicView* graphicView = Get_Graphic_View();
    if (graphicView) {
        float distance = graphicView->Get_Camera_Distance();
        
        // Set spin button range (wxSpinButton uses int, so scale down)
        if (m_idc_distance_spin) {
            m_idc_distance_spin->SetRange(0, 25000);
            m_idc_distance_spin->SetValue(static_cast<int>(distance));
        }
        
        // Set edit box value
        if (m_idc_distance_edit) {
            m_idc_distance_edit->SetValue(wxString::Format("%.2f", distance));
        }
    }
    
    event.Skip();
}

bool CameraDistance::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this simple dialog
    return true;
}

bool CameraDistance::TransferDataFromWindow()
{
    // Extract distance value and update GraphicView
    if (m_idc_distance_edit) {
        double distance;
        if (m_idc_distance_edit->GetValue().ToDouble(&distance)) {
            CGraphicView* graphicView = Get_Graphic_View();
            if (graphicView) {
                graphicView->Set_Camera_Distance(static_cast<float>(distance));
                return true;
            }
        }
        
        // Invalid value
        wxMessageBox("Please enter a valid distance value", "Invalid Input", 
                     wxOK | wxICON_ERROR, this);
        return false;
    }
    
    return false;
}

// ============================================================================
// Phase 2: Event Handlers
// ============================================================================

void CameraDistance::OnDistanceSpin(wxSpinEvent& event)
{
    // Handle spinner updates (MFC OnNotify with UDN_DELTAPOS)
    // MFC: Update_Spinner_Buddy(pheader->hwndFrom, pupdown->iDelta)
    // MFC behavior: increment by delta/100.0 (0.01 per step)
    
    if (!m_idc_distance_edit) return;
    
    // Get current value from edit box
    wxString value = m_idc_distance_edit->GetValue();
    double currentValue = 0.0;
    value.ToDouble(&currentValue);
    
    // Determine delta direction from spin event
    int delta = event.GetPosition();
    currentValue += delta * 0.01f;  // MFC: delta/100.0
    
    // Clamp to valid range
    if (currentValue < 0.0) currentValue = 0.0;
    if (currentValue > 25000.0) currentValue = 25000.0;
    
    // Update edit box with float format
    m_idc_distance_edit->SetValue(wxString::Format("%.2f", currentValue));
}

void CameraDistance::OnOK(wxCommandEvent &event)
{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void CameraDistance::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}
