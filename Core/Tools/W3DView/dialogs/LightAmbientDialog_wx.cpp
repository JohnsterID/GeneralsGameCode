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
#include "../w3dviewdoc_wx.h"
#include <wx/xrc/xmlres.h>
#include <wx/docview.h>

wxBEGIN_EVENT_TABLE(LightAmbientDialog, LightAmbientDialogBase)
    EVT_INIT_DIALOG(LightAmbientDialog::OnInitDialog)
    EVT_SLIDER(XRCID("IDC_SLIDER_RED"), LightAmbientDialog::OnHscroll)
    EVT_SLIDER(XRCID("IDC_SLIDER_GREEN"), LightAmbientDialog::OnHscroll)
    EVT_SLIDER(XRCID("IDC_SLIDER_BLUE"), LightAmbientDialog::OnHscroll)
    EVT_CHECKBOX(XRCID("IDC_GRAYSCALE_CHECK"), LightAmbientDialog::OnGrayscaleCheck)
    EVT_BUTTON(wxID_OK, LightAmbientDialog::OnOK)
    EVT_BUTTON(wxID_CANCEL, LightAmbientDialog::OnCancel)
wxEND_EVENT_TABLE()

LightAmbientDialog::LightAmbientDialog(wxWindow *parent)
    : LightAmbientDialogBase(parent),
      m_initialRed(0),
      m_initialGreen(0),
      m_initialBlue(0)
{
    // MFC: OnInitDialog is called automatically after construction
    // wxWidgets: We trigger it explicitly with InitDialog()
    Centre();
}

// ============================================================================
// OnInitDialog - Initialize dialog with scene's current ambient light
// ============================================================================
// MFC Reference: AmbientLightDialog.cpp:42-77 (OnInitDialog)
// Behavior: Get current ambient light from scene, initialize sliders,
//           set grayscale checkbox if R==G==B, save initial values for cancel

void LightAmbientDialog::OnInitDialog(wxInitDialogEvent &event)
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
        // Get the ambient light from the document/scene
        // MFC: Vector3 lightSettings = pCDoc->GetScene()->Get_Ambient_Light();
        // wxWidgets: Use wrapper method to avoid header include issues
        Vector3 lightSettings = doc->GetAmbientLight();

        // Remember these initial settings so we can restore them if the user cancels
        // MFC: AmbientLightDialog.cpp:64-66
        m_initialRed = int(lightSettings.X * 100.0f);
        m_initialGreen = int(lightSettings.Y * 100.0f);
        m_initialBlue = int(lightSettings.Z * 100.0f);
    }
    else
    {
        // No document - use defaults (black)
        m_initialRed = 0;
        m_initialGreen = 0;
        m_initialBlue = 0;
    }

    // Check the grayscale checkbox if all RGB values are equal
    // MFC: AmbientLightDialog.cpp:69-73
    if ((m_initialRed == m_initialGreen) && (m_initialRed == m_initialBlue))
    {
        m_idc_grayscale_check->SetValue(true);
    }

    // Set the initial slider positions
    // MFC: AmbientLightDialog.cpp:75-77
    m_idc_slider_red->SetValue(m_initialRed);
    m_idc_slider_green->SetValue(m_initialGreen);
    m_idc_slider_blue->SetValue(m_initialBlue);
}

// ============================================================================
// OnOK - Close dialog (ambient light already set via real-time updates)
// ============================================================================
// MFC Reference: AmbientLightDialog.cpp (no explicit OnOK, uses default)
// Behavior: Just close dialog, ambient light was already set via OnHScroll

void LightAmbientDialog::OnOK(wxCommandEvent &event)
{
    // MFC: No explicit OnOK - uses base class (just closes)
    // Ambient light was already set via real-time updates in OnHScroll
    EndModal(wxID_OK);
}

// ============================================================================
// OnCancel - Restore initial ambient light (undo live preview changes)
// ============================================================================
// MFC Reference: AmbientLightDialog.cpp:127-145 (OnCancel)
// Behavior: Restore the ambient light to initial value when dialog opened

void LightAmbientDialog::OnCancel(wxCommandEvent &event)
{
    // MFC: AmbientLightDialog.cpp:129-132
    // Restore the initial light values
    Vector3 lightSettings;
    lightSettings.X = float(m_initialRed) / 100.0f;
    lightSettings.Y = float(m_initialGreen) / 100.0f;
    lightSettings.Z = float(m_initialBlue) / 100.0f;

    // Get a pointer to the document so we can restore the ambient light
    // MFC: AmbientLightDialog.cpp:135-142
    wxDocManager *docManager = wxDocManager::GetDocumentManager();
    W3DViewDoc *doc = wxStaticCast(docManager->GetCurrentDocument(), W3DViewDoc);
    if (doc)
    {
        // Restore the ambient light (undo all live preview changes)
        // MFC: pCDoc->GetScene()->Set_Ambient_Light(lightSettings);
        // wxWidgets: Use wrapper method to avoid header include issues
        doc->SetAmbientLight(lightSettings);
    }

    // Close the dialog
    EndModal(wxID_CANCEL);
}

// ============================================================================
// OnHscroll - Handle slider value changes with real-time ambient light updates
// ============================================================================
// MFC Reference: AmbientLightDialog.cpp:86-122 (OnHScroll)
// Behavior: When grayscale is checked, sync all sliders to same value
//           Update scene ambient light in REAL-TIME (live preview)

void LightAmbientDialog::OnHscroll(wxCommandEvent &event)
{
    // MFC: AmbientLightDialog.cpp:88-104
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
    // MFC: AmbientLightDialog.cpp:106-109
    Vector3 lightSettings;
    lightSettings.X = float(m_idc_slider_red->GetValue()) / 100.0f;
    lightSettings.Y = float(m_idc_slider_green->GetValue()) / 100.0f;
    lightSettings.Z = float(m_idc_slider_blue->GetValue()) / 100.0f;

    // Update the scene's ambient light (REAL-TIME UPDATE)
    // MFC: AmbientLightDialog.cpp:112-117
    wxDocManager *docManager = wxDocManager::GetDocumentManager();
    W3DViewDoc *doc = wxStaticCast(docManager->GetCurrentDocument(), W3DViewDoc);
    if (doc)
    {
        // MFC: pCDoc->GetScene()->Set_Ambient_Light(lightSettings);
        // wxWidgets: Use wrapper method to avoid header include issues
        doc->SetAmbientLight(lightSettings);
    }
}

// ============================================================================
// OnGrayscaleCheck - Handle grayscale checkbox toggle
// ============================================================================
// MFC: No explicit handler, but behavior implied by OnHScroll logic
// Behavior: When checked, sync all sliders immediately

void LightAmbientDialog::OnGrayscaleCheck(wxCommandEvent &event)
{
    // Grayscale checkbox toggled
    // If just checked, sync all sliders to current red slider value
    if (m_idc_grayscale_check->GetValue())
    {
        // Use red slider's value as the grayscale value
        int grayscaleValue = m_idc_slider_red->GetValue();
        m_idc_slider_green->SetValue(grayscaleValue);
        m_idc_slider_blue->SetValue(grayscaleValue);

        // Update scene with grayscale ambient light
        Vector3 lightSettings;
        lightSettings.X = float(grayscaleValue) / 100.0f;
        lightSettings.Y = float(grayscaleValue) / 100.0f;
        lightSettings.Z = float(grayscaleValue) / 100.0f;

        wxDocManager *docManager = wxDocManager::GetDocumentManager();
        W3DViewDoc *doc = wxStaticCast(docManager->GetCurrentDocument(), W3DViewDoc);
        if (doc) {
            // MFC: pCDoc->GetScene()->Set_Ambient_Light(lightSettings);
            // wxWidgets: Use wrapper method to avoid header include issues
            doc->SetAmbientLight(lightSettings);
        }
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
