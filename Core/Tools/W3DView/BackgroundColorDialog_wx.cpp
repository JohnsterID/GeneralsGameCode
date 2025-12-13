/*
**	Command & Conquer Renegade(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// TheSuperHackers: wxWidgets version of Background Color Dialog

#include "BackgroundColorDialog_wx.h"
#include "w3dviewdoc_wx.h"
#include "w3dviewapp_wx.h"

#include <wx/docview.h>

wxBEGIN_EVENT_TABLE(BackgroundColorDialog, wxDialog)
    EVT_SCROLL(BackgroundColorDialog::OnSliderChanged)
    EVT_CHECKBOX(wxID_ANY, BackgroundColorDialog::OnGrayscaleCheck)
    EVT_BUTTON(wxID_CANCEL, BackgroundColorDialog::OnCancel)
wxEND_EVENT_TABLE()

BackgroundColorDialog::BackgroundColorDialog(wxWindow* parent)
    : wxDialog(parent, wxID_ANY, wxT("Background Color"), wxDefaultPosition, wxSize(400, 250))
    , m_redSlider(nullptr)
    , m_greenSlider(nullptr)
    , m_blueSlider(nullptr)
    , m_grayscaleCheck(nullptr)
    , m_initialRed(0)
    , m_initialGreen(0)
    , m_initialBlue(0)
{
    CreateControls();
    Centre();
}

BackgroundColorDialog::~BackgroundColorDialog()
{
}

void BackgroundColorDialog::CreateControls()
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Red slider
    wxBoxSizer* redSizer = new wxBoxSizer(wxHORIZONTAL);
    redSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Red:"), wxDefaultPosition, wxSize(60, -1)),
                  0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    m_redSlider = new wxSlider(this, wxID_ANY, 0, 0, 100, wxDefaultPosition, wxSize(250, -1));
    redSizer->Add(m_redSlider, 1, wxEXPAND);
    mainSizer->Add(redSizer, 0, wxEXPAND | wxALL, 10);

    // Green slider
    wxBoxSizer* greenSizer = new wxBoxSizer(wxHORIZONTAL);
    greenSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Green:"), wxDefaultPosition, wxSize(60, -1)),
                    0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    m_greenSlider = new wxSlider(this, wxID_ANY, 0, 0, 100, wxDefaultPosition, wxSize(250, -1));
    greenSizer->Add(m_greenSlider, 1, wxEXPAND);
    mainSizer->Add(greenSizer, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);

    // Blue slider
    wxBoxSizer* blueSizer = new wxBoxSizer(wxHORIZONTAL);
    blueSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Blue:"), wxDefaultPosition, wxSize(60, -1)),
                   0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    m_blueSlider = new wxSlider(this, wxID_ANY, 0, 0, 100, wxDefaultPosition, wxSize(250, -1));
    blueSizer->Add(m_blueSlider, 1, wxEXPAND);
    mainSizer->Add(blueSizer, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);

    // Grayscale checkbox
    m_grayscaleCheck = new wxCheckBox(this, wxID_ANY, wxT("Grayscale"));
    mainSizer->Add(m_grayscaleCheck, 0, wxALL, 10);

    // Button sizer
    wxSizer* buttonSizer = CreateStdDialogButtonSizer(wxOK | wxCANCEL);
    mainSizer->Add(buttonSizer, 0, wxALIGN_RIGHT | wxALL, 10);

    SetSizer(mainSizer);
}

void BackgroundColorDialog::SetInitialColors(int red, int green, int blue)
{
    m_initialRed = red;
    m_initialGreen = green;
    m_initialBlue = blue;

    m_redSlider->SetValue(red);
    m_greenSlider->SetValue(green);
    m_blueSlider->SetValue(blue);

    // Check grayscale if all values are equal
    if (red == green && red == blue)
    {
        m_grayscaleCheck->SetValue(true);
    }
}

void BackgroundColorDialog::OnSliderChanged(wxScrollEvent& event)
{
    // If grayscale is checked, sync all sliders
    if (m_grayscaleCheck->GetValue())
    {
        wxSlider* changedSlider = wxDynamicCast(event.GetEventObject(), wxSlider);
        if (changedSlider)
        {
            int value = changedSlider->GetValue();
            m_redSlider->SetValue(value);
            m_greenSlider->SetValue(value);
            m_blueSlider->SetValue(value);
        }
    }

    UpdateDocumentColor();
}

void BackgroundColorDialog::OnGrayscaleCheck(wxCommandEvent& event)
{
    if (m_grayscaleCheck->GetValue())
    {
        // Sync all sliders to red value
        int redValue = m_redSlider->GetValue();
        m_greenSlider->SetValue(redValue);
        m_blueSlider->SetValue(redValue);
        UpdateDocumentColor();
    }
}

void BackgroundColorDialog::OnCancel(wxCommandEvent& event)
{
    // Restore initial colors before closing
    m_redSlider->SetValue(m_initialRed);
    m_greenSlider->SetValue(m_initialGreen);
    m_blueSlider->SetValue(m_initialBlue);
    UpdateDocumentColor();
    
    event.Skip(); // Allow dialog to close
}

void BackgroundColorDialog::UpdateDocumentColor()
{
    // Get the current document
    wxDocManager* docManager = wxGetApp().GetDocumentManager();
    if (docManager)
    {
        W3DViewDoc* doc = wxDynamicCast(docManager->GetCurrentDocument(), W3DViewDoc);
        if (doc)
        {
            float red = m_redSlider->GetValue() / 100.0f;
            float green = m_greenSlider->GetValue() / 100.0f;
            float blue = m_blueSlider->GetValue() / 100.0f;
            
            // TODO: Set background color in document
            // doc->SetBackgroundColor(red, green, blue);
        }
    }
}
