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

#include "ColorSel_wx.h"
#include <wx/xrc/xmlres.h>
#include <wx/dcclient.h>

// Forward declaration for gradient painting utility
void Paint_Gradient_wx(wxWindow* window, unsigned char baseRed, unsigned char baseGreen, unsigned char baseBlue);

// MFC Reference: ColorSelectionDialog.cpp
wxBEGIN_EVENT_TABLE(ColorSel, ColorSelBase)
    EVT_SLIDER(XRCID("IDC_SLIDER_RED"), ColorSel::OnHscroll)
    EVT_SLIDER(XRCID("IDC_SLIDER_GREEN"), ColorSel::OnHscroll)
    EVT_SLIDER(XRCID("IDC_SLIDER_BLUE"), ColorSel::OnHscroll)
    EVT_PAINT(ColorSel::OnPaint)
    EVT_CHECKBOX(XRCID("IDC_GRAYSCALE_CHECK"), ColorSel::OnGrayscaleCheck)
    EVT_TEXT(XRCID("IDC_BLUE_EDIT"), ColorSel::OnChangeBlueEdit)
    EVT_TEXT(XRCID("IDC_GREEN_EDIT"), ColorSel::OnChangeGreenEdit)
    EVT_TEXT(XRCID("IDC_RED_EDIT"), ColorSel::OnChangeRedEdit)
    EVT_INIT_DIALOG(ColorSel::OnInitDialog)
wxEND_EVENT_TABLE()

ColorSel::ColorSel(wxWindow *parent, const Vector3 &def_color)
    : ColorSelBase(parent),
      m_Color(def_color),
      m_PaintColor(def_color)
{
    Centre();
}

void ColorSel::OnOK(wxCommandEvent &event)
{
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void ColorSel::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}

// ============================================================================
// Event Handlers (Phase 2 - Auto-integrated)
// ============================================================================

void ColorSel::OnHscroll(wxCommandEvent &event)
{
    Update_Sliders(event.GetId());
}

void ColorSel::OnGrayscaleCheck(wxCommandEvent &event)
{
    if (!m_idc_grayscale_check || !m_idc_grayscale_check->GetValue())
        return;
    
    // Sync all sliders to red value
    int red_value = m_idc_slider_red ? m_idc_slider_red->GetValue() : 0;
    
    if (m_idc_slider_green) m_idc_slider_green->SetValue(red_value);
    if (m_idc_slider_blue) m_idc_slider_blue->SetValue(red_value);
    
    m_PaintColor.X = static_cast<float>(red_value) / 255.0f;
    m_PaintColor.Y = m_PaintColor.X;
    m_PaintColor.Z = m_PaintColor.X;
    
    if (m_idc_red_spin) m_idc_red_spin->SetValue(red_value);
    if (m_idc_green_spin) m_idc_green_spin->SetValue(red_value);
    if (m_idc_blue_spin) m_idc_blue_spin->SetValue(red_value);
    
    if (m_idc_red_edit) m_idc_red_edit->SetValue(wxString::Format("%d", red_value));
    if (m_idc_green_edit) m_idc_green_edit->SetValue(wxString::Format("%d", red_value));
    if (m_idc_blue_edit) m_idc_blue_edit->SetValue(wxString::Format("%d", red_value));
    
    Paint_Color_Window();
}

void ColorSel::OnChangeBlueEdit(wxCommandEvent &event)
{
    if (m_idc_slider_blue && m_idc_blue_edit) {
        long value = 0;
        if (m_idc_blue_edit->GetValue().ToLong(&value)) {
            value = wxClip(value, 0L, 255L);
            m_idc_slider_blue->SetValue(static_cast<int>(value));
        }
        Update_Sliders(XRCID("IDC_SLIDER_BLUE"));
    }
}

void ColorSel::OnChangeGreenEdit(wxCommandEvent &event)
{
    if (m_idc_slider_green && m_idc_green_edit) {
        long value = 0;
        if (m_idc_green_edit->GetValue().ToLong(&value)) {
            value = wxClip(value, 0L, 255L);
            m_idc_slider_green->SetValue(static_cast<int>(value));
        }
        Update_Sliders(XRCID("IDC_SLIDER_GREEN"));
    }
}

void ColorSel::OnChangeRedEdit(wxCommandEvent &event)
{
    if (m_idc_slider_red && m_idc_red_edit) {
        long value = 0;
        if (m_idc_red_edit->GetValue().ToLong(&value)) {
            value = wxClip(value, 0L, 255L);
            m_idc_slider_red->SetValue(static_cast<int>(value));
        }
        Update_Sliders(XRCID("IDC_SLIDER_RED"));
    }
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void ColorSel::OnInitDialog(wxInitDialogEvent& event)
{
    // Set control ranges (0-255 for RGB)
    if (m_idc_slider_red) m_idc_slider_red->SetRange(0, 255);
    if (m_idc_slider_green) m_idc_slider_green->SetRange(0, 255);
    if (m_idc_slider_blue) m_idc_slider_blue->SetRange(0, 255);
    if (m_idc_red_spin) m_idc_red_spin->SetRange(0, 255);
    if (m_idc_green_spin) m_idc_green_spin->SetRange(0, 255);
    if (m_idc_blue_spin) m_idc_blue_spin->SetRange(0, 255);
    
    // Convert m_Color (0-1 float) to integer (0-255)
    int red_value = static_cast<int>(m_Color.X * 255.0f);
    int green_value = static_cast<int>(m_Color.Y * 255.0f);
    int blue_value = static_cast<int>(m_Color.Z * 255.0f);
    
    // Check grayscale if all values equal
    if (m_idc_grayscale_check) {
        m_idc_grayscale_check->SetValue(red_value == green_value && red_value == blue_value);
    }
    
    // Set slider positions
    if (m_idc_slider_red) m_idc_slider_red->SetValue(red_value);
    if (m_idc_slider_green) m_idc_slider_green->SetValue(green_value);
    if (m_idc_slider_blue) m_idc_slider_blue->SetValue(blue_value);
    
    // Set spin positions
    if (m_idc_red_spin) m_idc_red_spin->SetValue(red_value);
    if (m_idc_green_spin) m_idc_green_spin->SetValue(green_value);
    if (m_idc_blue_spin) m_idc_blue_spin->SetValue(blue_value);
    
    // Set edit text values
    if (m_idc_red_edit) m_idc_red_edit->SetValue(wxString::Format("%d", red_value));
    if (m_idc_green_edit) m_idc_green_edit->SetValue(wxString::Format("%d", green_value));
    if (m_idc_blue_edit) m_idc_blue_edit->SetValue(wxString::Format("%d", blue_value));
    
    event.Skip();
}

bool ColorSel::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool ColorSel::TransferDataFromWindow()
{
    m_Color = m_PaintColor;
    return true;
}

void ColorSel::Paint_Color_Window()
{
    if (!m_idc_color_window)
        return;
    
    wxColour color(
        static_cast<unsigned char>(m_PaintColor.X * 255.0f),
        static_cast<unsigned char>(m_PaintColor.Y * 255.0f),
        static_cast<unsigned char>(m_PaintColor.Z * 255.0f)
    );
    m_idc_color_window->SetBackgroundColour(color);
    m_idc_color_window->Refresh();
}

void ColorSel::Update_Sliders(int slider_id)
{
    bool is_grayscale = m_idc_grayscale_check && m_idc_grayscale_check->GetValue();
    
    if (is_grayscale) {
        // Sync all sliders to the one that changed
        int position = 0;
        if (slider_id == XRCID("IDC_SLIDER_RED") && m_idc_slider_red)
            position = m_idc_slider_red->GetValue();
        else if (slider_id == XRCID("IDC_SLIDER_GREEN") && m_idc_slider_green)
            position = m_idc_slider_green->GetValue();
        else if (m_idc_slider_blue)
            position = m_idc_slider_blue->GetValue();
        
        if (m_idc_slider_red) m_idc_slider_red->SetValue(position);
        if (m_idc_slider_green) m_idc_slider_green->SetValue(position);
        if (m_idc_slider_blue) m_idc_slider_blue->SetValue(position);
    }
    
    // Get current slider values
    int red_val = m_idc_slider_red ? m_idc_slider_red->GetValue() : 0;
    int green_val = m_idc_slider_green ? m_idc_slider_green->GetValue() : 0;
    int blue_val = m_idc_slider_blue ? m_idc_slider_blue->GetValue() : 0;
    
    // Update spin controls
    if (m_idc_red_spin) m_idc_red_spin->SetValue(red_val);
    if (m_idc_green_spin) m_idc_green_spin->SetValue(green_val);
    if (m_idc_blue_spin) m_idc_blue_spin->SetValue(blue_val);
    
    // Update text edits
    if (m_idc_red_edit) m_idc_red_edit->SetValue(wxString::Format("%d", red_val));
    if (m_idc_green_edit) m_idc_green_edit->SetValue(wxString::Format("%d", green_val));
    if (m_idc_blue_edit) m_idc_blue_edit->SetValue(wxString::Format("%d", blue_val));
    
    // Update paint color and preview
    m_PaintColor.X = static_cast<float>(red_val) / 255.0f;
    m_PaintColor.Y = static_cast<float>(green_val) / 255.0f;
    m_PaintColor.Z = static_cast<float>(blue_val) / 255.0f;
    
    Paint_Color_Window();
}

// ============================================================================
// OnPaint - Paint color gradients for the RGB panels
// ============================================================================
// MFC Reference: ColorSelectionDialog.cpp:176-178 (WindowProc handling WM_PAINT)
// Behavior: Paint gradients from black to red/green/blue on the gradient panels

void ColorSel::OnPaint(wxPaintEvent &event)
{
    // Paint the gradients for each color panel
    // MFC: Paint_Gradient(GetDlgItem(m_hWnd, IDC_RED_GRADIENT), 1, 0, 0);
    Paint_Gradient_wx(m_idc_red_gradient, 255, 0, 0);
    Paint_Gradient_wx(m_idc_green_gradient, 0, 255, 0);
    Paint_Gradient_wx(m_idc_blue_gradient, 0, 0, 255);

    // Let the event propagate to other handlers
    event.Skip();
}
