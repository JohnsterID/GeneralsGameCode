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
    // Update edit box when spinner changes
    if (m_idc_distance_edit && m_idc_distance_spin) {
        int value = m_idc_distance_spin->GetValue();
        m_idc_distance_edit->SetValue(wxString::Format("%d", value));
    }
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
