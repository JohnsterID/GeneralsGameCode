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

#pragma once

#include <wx/dialog.h>
#include <wx/slider.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/button.h>

class BackgroundColorDialog : public wxDialog
{
public:
    BackgroundColorDialog(wxWindow* parent);
    virtual ~BackgroundColorDialog();

    // Accessors for color values (0-100 range)
    int GetRedValue() const { return m_redSlider->GetValue(); }
    int GetGreenValue() const { return m_greenSlider->GetValue(); }
    int GetBlueValue() const { return m_blueSlider->GetValue(); }

    void SetInitialColors(int red, int green, int blue);

private:
    void CreateControls();
    void OnSliderChanged(wxScrollEvent& event);
    void OnGrayscaleCheck(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);
    void UpdateDocumentColor();

    // Controls
    wxSlider* m_redSlider;
    wxSlider* m_greenSlider;
    wxSlider* m_blueSlider;
    wxCheckBox* m_grayscaleCheck;

    // Initial values for cancel restoration
    int m_initialRed;
    int m_initialGreen;
    int m_initialBlue;

    wxDECLARE_EVENT_TABLE();
};
