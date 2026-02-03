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

wxBEGIN_EVENT_TABLE(ColorSel, ColorSelBase)
EVT_SLIDER(XRCID("IDC_SLIDER_RED"), ColorSel::OnHscroll)  // Red slider
    EVT_SLIDER(XRCID("IDC_SLIDER_GREEN"), ColorSel::OnHscroll)  // Green slider
    EVT_SLIDER(XRCID("IDC_SLIDER_BLUE"), ColorSel::OnHscroll)  // Blue slider
    // MFC: ON_WM_PAINT() - paints gradients on IDC_RED/GREEN/BLUE_GRADIENT panels
    // wxWidgets: Paint_Color_Window() uses SetBackgroundColour() for color preview
    // Gradient painting deferred to Phase 4 (advanced UI features)
    EVT_CHECKBOX(XRCID("IDC_GRAYSCALE_CHECK"), ColorSel::OnGrayscaleCheck)  // Button/Checkbox click
    EVT_TEXT(XRCID("IDC_BLUE_EDIT"), ColorSel::OnChangeBlueEdit)  // Text control change
    EVT_TEXT(XRCID("IDC_GREEN_EDIT"), ColorSel::OnChangeGreenEdit)  // Text control change
    EVT_TEXT(XRCID("IDC_RED_EDIT"), ColorSel::OnChangeRedEdit)  // Text control change
    EVT_INIT_DIALOG(ColorSel::OnInitDialog)
wxEND_EVENT_TABLE()

// MFC: ColorSelectionDialogClass(const Vector3 &def_color, CWnd *pParent)
//      : m_Color(def_color), m_PaintColor(def_color), CDialog(IDD, pParent)
ColorSel::ColorSel(wxWindow *parent, const Vector3 &def_color)
    : ColorSelBase(parent),
      m_Color(def_color),
      m_PaintColor(def_color)
{
    Centre();
}

void ColorSel::OnOK(wxCommandEvent &event)
{
    // MFC: OnOK() calls:
    //     m_Color = m_PaintColor;  // Record the color
    //     CDialog::OnOK();         // Allow base to close
    // TransferDataFromWindow() handles m_Color = m_PaintColor assignment
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
    // MFC: Update_Sliders(::GetWindowLong(*pScrollBar, GWL_ID));
    //      CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
    
    // Determine which slider sent the event
    int slider_id = event.GetId();
    
    // Update sliders and color preview
    Update_Sliders(slider_id);
}

void ColorSel::OnGrayscaleCheck(wxCommandEvent &event)
{
    // MFC: if (SendDlgItemMessage(IDC_GRAYSCALE_CHECK, BM_GETCHECK)) {
    //          m_GreenSlider.SetPos(m_RedSlider.GetPos());
    //          m_BlueSlider.SetPos(m_RedSlider.GetPos());
    //          m_PaintColor.X = float(m_RedSlider.GetPos()) / 255.00F;
    //          m_PaintColor.Y = float(m_GreenSlider.GetPos()) / 255.00F;
    //          m_PaintColor.Z = float(m_BlueSlider.GetPos()) / 255.00F;
    //          Paint_Color_Window();
    //      }
    
    bool is_checked = m_idc_grayscale_check ? m_idc_grayscale_check->GetValue() : false;
    
    if (is_checked) {
        // Sync green and blue sliders to match red slider
        int red_value = m_idc_slider_red ? m_idc_slider_red->GetValue() : 0;
        
        if (m_idc_slider_green) {
            m_idc_slider_green->SetValue(red_value);
        }
        if (m_idc_slider_blue) {
            m_idc_slider_blue->SetValue(red_value);
        }
        
        // Update m_PaintColor and color preview
        m_PaintColor.X = static_cast<float>(red_value) / 255.0f;
        m_PaintColor.Y = static_cast<float>(red_value) / 255.0f;
        m_PaintColor.Z = static_cast<float>(red_value) / 255.0f;
        
        // Update spins and text edits
        if (m_idc_red_spin) m_idc_red_spin->SetValue(red_value);
        if (m_idc_green_spin) m_idc_green_spin->SetValue(red_value);
        if (m_idc_blue_spin) m_idc_blue_spin->SetValue(red_value);
        
        if (m_idc_red_edit) m_idc_red_edit->SetValue(wxString::Format("%d", red_value));
        if (m_idc_green_edit) m_idc_green_edit->SetValue(wxString::Format("%d", red_value));
        if (m_idc_blue_edit) m_idc_blue_edit->SetValue(wxString::Format("%d", red_value));
        
        Paint_Color_Window();
    }
}

void ColorSel::OnChangeBlueEdit(wxCommandEvent &event)
{
    // MFC: if (::IsWindow(m_BlueSlider)) {
    //          int value = GetDlgItemInt(IDC_BLUE_EDIT);
    //          m_BlueSlider.SetPos(value);
    //          Update_Sliders(IDC_SLIDER_BLUE);
    //          SendDlgItemMessage(IDC_BLUE_EDIT, EM_SETSEL, 10, 20);
    //      }
    
    if (m_idc_slider_blue && m_idc_blue_edit) {
        long value = 0;
        if (m_idc_blue_edit->GetValue().ToLong(&value)) {
            // Clamp to valid range (0-255)
            if (value < 0) value = 0;
            if (value > 255) value = 255;
            
            m_idc_slider_blue->SetValue(static_cast<int>(value));
        }
        Update_Sliders(XRCID("IDC_SLIDER_BLUE"));
    }
}

void ColorSel::OnChangeGreenEdit(wxCommandEvent &event)
{
    // MFC: if (::IsWindow(m_GreenSlider)) {
    //          int value = GetDlgItemInt(IDC_GREEN_EDIT);
    //          m_GreenSlider.SetPos(value);
    //          Update_Sliders(IDC_SLIDER_GREEN);
    //          SendDlgItemMessage(IDC_GREEN_EDIT, EM_SETSEL, 10, 20);
    //      }
    
    if (m_idc_slider_green && m_idc_green_edit) {
        long value = 0;
        if (m_idc_green_edit->GetValue().ToLong(&value)) {
            // Clamp to valid range (0-255)
            if (value < 0) value = 0;
            if (value > 255) value = 255;
            
            m_idc_slider_green->SetValue(static_cast<int>(value));
        }
        Update_Sliders(XRCID("IDC_SLIDER_GREEN"));
    }
}

void ColorSel::OnChangeRedEdit(wxCommandEvent &event)
{
    // MFC: if (::IsWindow(m_RedSlider)) {
    //          int value = GetDlgItemInt(IDC_RED_EDIT);
    //          m_RedSlider.SetPos(value);
    //          Update_Sliders(IDC_SLIDER_RED);
    //          SendDlgItemMessage(IDC_RED_EDIT, EM_SETSEL, 10, 20);
    //      }
    
    if (m_idc_slider_red && m_idc_red_edit) {
        long value = 0;
        if (m_idc_red_edit->GetValue().ToLong(&value)) {
            // Clamp to valid range (0-255)
            if (value < 0) value = 0;
            if (value > 255) value = 255;
            
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
    // MFC: CDialog::OnInitDialog();
    
    // Set the ranges of the slider and spin controls
    // MFC: m_RedSlider.SetRange(0, 255);
    // MFC: m_GreenSlider.SetRange(0, 255);
    // MFC: m_BlueSlider.SetRange(0, 255);
    // MFC: m_RedSpin.SetRange(0, 255);
    // MFC: m_GreenSpin.SetRange(0, 255);
    // MFC: m_BlueSpin.SetRange(0, 255);
    if (m_idc_slider_red) {
        m_idc_slider_red->SetRange(0, 255);
    }
    if (m_idc_slider_green) {
        m_idc_slider_green->SetRange(0, 255);
    }
    if (m_idc_slider_blue) {
        m_idc_slider_blue->SetRange(0, 255);
    }
    if (m_idc_red_spin) {
        m_idc_red_spin->SetRange(0, 255);
    }
    if (m_idc_green_spin) {
        m_idc_green_spin->SetRange(0, 255);
    }
    if (m_idc_blue_spin) {
        m_idc_blue_spin->SetRange(0, 255);
    }
    
    // Determine the initial settings (in integers)
    // MFC: int red_value = int(m_Color.X * 255.00F);
    // MFC: int green_value = int(m_Color.Y * 255.00F);
    // MFC: int blue_value = int(m_Color.Z * 255.00F);
    int red_value = static_cast<int>(m_Color.X * 255.0f);
    int green_value = static_cast<int>(m_Color.Y * 255.0f);
    int blue_value = static_cast<int>(m_Color.Z * 255.0f);
    
    // MFC: if ((red_value == green_value) && (red_value == blue_value)) {
    //          SendDlgItemMessage(IDC_GRAYSCALE_CHECK, BM_SETCHECK, (WPARAM)TRUE);
    //      }
    if (m_idc_grayscale_check) {
        if ((red_value == green_value) && (red_value == blue_value)) {
            m_idc_grayscale_check->SetValue(true);
        } else {
            m_idc_grayscale_check->SetValue(false);
        }
    }
    
    // Set the initial slider positions
    // MFC: m_RedSlider.SetPos(red_value);
    // MFC: m_GreenSlider.SetPos(green_value);
    // MFC: m_BlueSlider.SetPos(blue_value);
    if (m_idc_slider_red) {
        m_idc_slider_red->SetValue(red_value);
    }
    if (m_idc_slider_green) {
        m_idc_slider_green->SetValue(green_value);
    }
    if (m_idc_slider_blue) {
        m_idc_slider_blue->SetValue(blue_value);
    }
    
    // MFC: m_RedSpin.SetPos(red_value);
    // MFC: m_GreenSpin.SetPos(green_value);
    // MFC: m_BlueSpin.SetPos(blue_value);
    if (m_idc_red_spin) {
        m_idc_red_spin->SetValue(red_value);
    }
    if (m_idc_green_spin) {
        m_idc_green_spin->SetValue(green_value);
    }
    if (m_idc_blue_spin) {
        m_idc_blue_spin->SetValue(blue_value);
    }
    
    // Update text edits to match
    if (m_idc_red_edit) {
        m_idc_red_edit->SetValue(wxString::Format("%d", red_value));
    }
    if (m_idc_green_edit) {
        m_idc_green_edit->SetValue(wxString::Format("%d", green_value));
    }
    if (m_idc_blue_edit) {
        m_idc_blue_edit->SetValue(wxString::Format("%d", blue_value));
    }
    
    // MFC: return TRUE;
    event.Skip();
}

bool ColorSel::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool ColorSel::TransferDataFromWindow()
{
    // MFC: OnOK() calls m_Color = m_PaintColor;
    // Record the color from current paint state
    m_Color = m_PaintColor;
    
    return true;
}

// MFC: Paint_Color_Window() - fills the color preview window with selected color
void ColorSel::Paint_Color_Window()
{
    if (m_idc_color_window) {
        // Set background color of the panel to match m_PaintColor
        wxColour color(
            static_cast<unsigned char>(m_PaintColor.X * 255.0f),
            static_cast<unsigned char>(m_PaintColor.Y * 255.0f),
            static_cast<unsigned char>(m_PaintColor.Z * 255.0f)
        );
        m_idc_color_window->SetBackgroundColour(color);
        m_idc_color_window->Refresh();
    }
}

// MFC: Update_Sliders(int slider_id) - syncs sliders and updates color preview
void ColorSel::Update_Sliders(int slider_id)
{
    // MFC: Are the sliders moving together? (grayscale mode)
    bool is_grayscale = false;
    if (m_idc_grayscale_check) {
        is_grayscale = m_idc_grayscale_check->GetValue();
    }
    
    if (is_grayscale) {
        int position = 0;
        
        // Determine which slider sent this message and use its current position
        if (slider_id == XRCID("IDC_SLIDER_RED") && m_idc_slider_red) {
            position = m_idc_slider_red->GetValue();
        } else if (slider_id == XRCID("IDC_SLIDER_GREEN") && m_idc_slider_green) {
            position = m_idc_slider_green->GetValue();
        } else if (m_idc_slider_blue) {
            position = m_idc_slider_blue->GetValue();
        }
        
        // Make all the sliders the same position
        if (m_idc_slider_red) {
            m_idc_slider_red->SetValue(position);
        }
        if (m_idc_slider_green) {
            m_idc_slider_green->SetValue(position);
        }
        if (m_idc_slider_blue) {
            m_idc_slider_blue->SetValue(position);
        }
    }
    
    // Update the edit controls (and their spin controls)
    int red_val = m_idc_slider_red ? m_idc_slider_red->GetValue() : 0;
    int green_val = m_idc_slider_green ? m_idc_slider_green->GetValue() : 0;
    int blue_val = m_idc_slider_blue ? m_idc_slider_blue->GetValue() : 0;
    
    if (m_idc_red_spin) {
        m_idc_red_spin->SetValue(red_val);
    }
    if (m_idc_green_spin) {
        m_idc_green_spin->SetValue(green_val);
    }
    if (m_idc_blue_spin) {
        m_idc_blue_spin->SetValue(blue_val);
    }
    
    // Update text edits
    if (m_idc_red_edit) {
        m_idc_red_edit->SetValue(wxString::Format("%d", red_val));
    }
    if (m_idc_green_edit) {
        m_idc_green_edit->SetValue(wxString::Format("%d", green_val));
    }
    if (m_idc_blue_edit) {
        m_idc_blue_edit->SetValue(wxString::Format("%d", blue_val));
    }
    
    // Record the selected color for later use
    // MFC: m_PaintColor.X = red_val / 255.00F;
    m_PaintColor.X = static_cast<float>(red_val) / 255.0f;
    m_PaintColor.Y = static_cast<float>(green_val) / 255.0f;
    m_PaintColor.Z = static_cast<float>(blue_val) / 255.0f;
    
    // Update the window that displays the color the user has selected
    Paint_Color_Window();
}
