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

#include "BackgroundColor_wx.h"
#include "../w3dviewdoc_wx.h"
#include <wx/xrc/xmlres.h>
#include <wx/docview.h>

wxBEGIN_EVENT_TABLE(BackgroundColor, BackgroundColorBase)
    EVT_INIT_DIALOG(BackgroundColor::OnInitDialog)
    EVT_SLIDER(XRCID("IDC_SLIDER_RED"), BackgroundColor::OnHscroll)
    EVT_SLIDER(XRCID("IDC_SLIDER_GREEN"), BackgroundColor::OnHscroll)
    EVT_SLIDER(XRCID("IDC_SLIDER_BLUE"), BackgroundColor::OnHscroll)
    EVT_CHECKBOX(XRCID("IDC_GRAYSCALE_CHECK"), BackgroundColor::OnGrayscaleCheck)
    EVT_BUTTON(wxID_OK, BackgroundColor::OnOK)
    EVT_BUTTON(wxID_CANCEL, BackgroundColor::OnCancel)
wxEND_EVENT_TABLE()

BackgroundColor::BackgroundColor(wxWindow *parent)
    : BackgroundColorBase(parent),
      m_initialRed(0),
      m_initialGreen(0),
      m_initialBlue(0)
{
    // MFC: OnInitDialog is called automatically after construction
    // wxWidgets: We trigger it explicitly with InitDialog()
    Centre();
}

// ============================================================================
// OnInitDialog - Initialize dialog with document's current background color
// ============================================================================
// MFC Reference: BackgroundColorDialog.cpp:42-77 (OnInitDialog)
// Behavior: Get current background color from document, initialize sliders,
//           set grayscale checkbox if R==G==B, save initial values for cancel

void BackgroundColor::OnInitDialog(wxInitDialogEvent &event)
{
    // Set slider ranges (0-100, matching MFC)
    m_idc_slider_red->SetRange(0, 100);
    m_idc_slider_green->SetRange(0, 100);
    m_idc_slider_blue->SetRange(0, 100);

    // Get current document
    wxDocManager *docManager = wxDocManager::GetDocumentManager();
    W3DViewDoc *doc = wxStaticCast(docManager->GetCurrentDocument(), W3DViewDoc);

    if (doc)
    {
        // Get the background color from the document
        // MFC: Vector3 colorSettings = pCDoc->GetBackgroundColor();
        const Vector3& colorSettings = doc->GetBackgroundColor();

        // Remember these initial settings so we can restore them if the user cancels
        // MFC: BackgroundColorDialog.cpp:64-66
        m_initialRed = int(colorSettings.X * 100.0f);
        m_initialGreen = int(colorSettings.Y * 100.0f);
        m_initialBlue = int(colorSettings.Z * 100.0f);
    }
    else
    {
        // No document - use defaults (black)
        m_initialRed = 0;
        m_initialGreen = 0;
        m_initialBlue = 0;
    }

    // Check the grayscale checkbox if all RGB values are equal
    // MFC: BackgroundColorDialog.cpp:69-73
    if ((m_initialRed == m_initialGreen) && (m_initialRed == m_initialBlue))
    {
        m_idc_grayscale_check->SetValue(true);
    }

    // Set the initial slider positions
    // MFC: BackgroundColorDialog.cpp:75-77
    m_idc_slider_red->SetValue(m_initialRed);
    m_idc_slider_green->SetValue(m_initialGreen);
    m_idc_slider_blue->SetValue(m_initialBlue);
}

// ============================================================================
// OnOK - Close dialog (color already set via real-time updates)
// ============================================================================
// MFC Reference: BackgroundColorDialog.cpp (no explicit OnOK, uses default)
// Behavior: Just close dialog, color was already set via OnHScroll

void BackgroundColor::OnOK(wxCommandEvent &event)
{
    // MFC: No explicit OnOK - uses base class (just closes)
    // Color was already set via real-time updates in OnHScroll
    EndModal(wxID_OK);
}

// ============================================================================
// OnCancel - Restore initial background color (undo live preview changes)
// ============================================================================
// MFC Reference: BackgroundColorDialog.cpp:127-145 (OnCancel)
// Behavior: Restore the background color to initial value when dialog opened

void BackgroundColor::OnCancel(wxCommandEvent &event)
{
    // MFC: BackgroundColorDialog.cpp:129-132
    // Restore the initial color values
    Vector3 colorSettings;
    colorSettings.X = float(m_initialRed) / 100.0f;
    colorSettings.Y = float(m_initialGreen) / 100.0f;
    colorSettings.Z = float(m_initialBlue) / 100.0f;

    // Get a pointer to the document so we can restore the background color
    // MFC: BackgroundColorDialog.cpp:135-142
    wxDocManager *docManager = wxDocManager::GetDocumentManager();
    W3DViewDoc *doc = wxStaticCast(docManager->GetCurrentDocument(), W3DViewDoc);
    if (doc)
    {
        // Restore the background color (undo all live preview changes)
        doc->SetBackgroundColor(colorSettings);
    }

    // Close the dialog
    EndModal(wxID_CANCEL);
}

// ============================================================================
// OnHscroll - Handle slider value changes with real-time color updates
// ============================================================================
// MFC Reference: BackgroundColorDialog.cpp:86-122 (OnHScroll)
// Behavior: When grayscale is checked, sync all sliders to same value
//           Update document background color in REAL-TIME (live preview)

void BackgroundColor::OnHscroll(wxCommandEvent &event)
{
    // MFC: BackgroundColorDialog.cpp:88-104
    // If grayscale is checked, make all sliders move together
    if (m_idc_grayscale_check->GetValue())
    {
        int currentPos = 0;
        wxObject *eventObject = event.GetEventObject();

        // Determine which slider moved
        if (eventObject == m_idc_slider_red) {
            currentPos = m_idc_slider_red->GetValue();
        } else if (eventObject == m_idc_slider_green) {
            currentPos = m_idc_slider_green->GetValue();
        } else {
            currentPos = m_idc_slider_blue->GetValue();
        }

        // Make all the sliders the same position (grayscale effect)
        m_idc_slider_red->SetValue(currentPos);
        m_idc_slider_green->SetValue(currentPos);
        m_idc_slider_blue->SetValue(currentPos);
    }

    // Get current slider values and convert to 0.0-1.0 range
    // MFC: BackgroundColorDialog.cpp:106-109
    Vector3 colorSettings;
    colorSettings.X = float(m_idc_slider_red->GetValue()) / 100.0f;
    colorSettings.Y = float(m_idc_slider_green->GetValue()) / 100.0f;
    colorSettings.Z = float(m_idc_slider_blue->GetValue()) / 100.0f;

    // Update the document's background color (REAL-TIME UPDATE)
    // MFC: BackgroundColorDialog.cpp:112-117
    wxDocManager *docManager = wxDocManager::GetDocumentManager();
    W3DViewDoc *doc = wxStaticCast(docManager->GetCurrentDocument(), W3DViewDoc);
    if (doc)
    {
        doc->SetBackgroundColor(colorSettings);
    }
}

// ============================================================================
// OnGrayscaleCheck - Handle grayscale checkbox toggle
// ============================================================================
// MFC: No explicit handler, but behavior implied by OnHScroll logic
// Behavior: When checked, sync all sliders immediately

void BackgroundColor::OnGrayscaleCheck(wxCommandEvent &event)
{
    // Grayscale checkbox toggled
    // If just checked, sync all sliders to current red slider value
    if (m_idc_grayscale_check->GetValue())
    {
        // Use red slider's value as the grayscale value
        int grayscaleValue = m_idc_slider_red->GetValue();
        m_idc_slider_green->SetValue(grayscaleValue);
        m_idc_slider_blue->SetValue(grayscaleValue);

        // Update document with grayscale color
        Vector3 colorSettings;
        colorSettings.X = float(grayscaleValue) / 100.0f;
        colorSettings.Y = float(grayscaleValue) / 100.0f;
        colorSettings.Z = float(grayscaleValue) / 100.0f;

        wxDocManager *docManager = wxDocManager::GetDocumentManager();
        W3DViewDoc *doc = wxStaticCast(docManager->GetCurrentDocument(), W3DViewDoc);
        if (doc) {
            doc->SetBackgroundColor(colorSettings);
        }
    }
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

bool BackgroundColor::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool BackgroundColor::TransferDataFromWindow()
{
    // Color values are managed by the slider controls
    // Calling code retrieves RGB values from the sliders directly
    return true;
}
