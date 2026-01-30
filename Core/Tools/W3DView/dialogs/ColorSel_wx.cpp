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
    // TODO: Map ON_WM_PAINT manually
    // MFC: ON_WM_PAINT()
    EVT_CHECKBOX(XRCID("IDC_GRAYSCALE_CHECK"), ColorSel::OnGrayscaleCheck)  // Button/Checkbox click
    EVT_TEXT(XRCID("IDC_BLUE_EDIT"), ColorSel::OnChangeBlueEdit)  // Text control change
    EVT_TEXT(XRCID("IDC_GREEN_EDIT"), ColorSel::OnChangeGreenEdit)  // Text control change
    EVT_TEXT(XRCID("IDC_RED_EDIT"), ColorSel::OnChangeRedEdit)  // Text control change
    EVT_INIT_DIALOG(ColorSel::OnInitDialog)
wxEND_EVENT_TABLE()

ColorSel::ColorSel(wxWindow *parent)
    : ColorSelBase(parent)
{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}

void ColorSel::OnOK(wxCommandEvent &event)
{
    // Validate and close
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
    // MFC Reference: ColorSelectionDialog.cpp (OnHScroll)
    // Function: Update text edits when slider moves
    //
    // MFC Implementation:
    //   Update_Sliders(::GetWindowLong(*pScrollBar, GWL_ID));
    //   CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
    
    // Update text edit controls to match slider values
    if (m_idc_slider_red && m_idc_red_edit)
    {
        int value = m_idc_slider_red->GetValue();
        m_idc_red_edit->SetValue(wxString::Format("%d", value));
    }
    
    if (m_idc_slider_green && m_idc_green_edit)
    {
        int value = m_idc_slider_green->GetValue();
        m_idc_green_edit->SetValue(wxString::Format("%d", value));
    }
    
    if (m_idc_slider_blue && m_idc_blue_edit)
    {
        int value = m_idc_slider_blue->GetValue();
        m_idc_blue_edit->SetValue(wxString::Format("%d", value));
    }
    
    // TODO(Phase 3 - Color Preview): Update_Sliders() for grayscale sync and preview
    //   MFC calls Update_Sliders which:
    //   1. Determines which slider moved (from event source)
    //   2. If grayscale mode, syncs all sliders to moved slider
    //   3. Updates m_PaintColor Vector3 (normalized RGB)
    //   4. Calls Paint_Color_Window() to update color preview
    //   5. Updates spin controls
    //   Priority: MEDIUM - text edits update but no grayscale sync/preview
}

void ColorSel::OnGrayscaleCheck(wxCommandEvent &event)
{
    // MFC Reference: ColorSelectionDialog.cpp (OnGrayscaleCheck)
    // Function: Sync green/blue sliders to red when grayscale mode enabled
    //
    // MFC Implementation:
    //   if (SendDlgItemMessage(IDC_GRAYSCALE_CHECK, BM_GETCHECK)) {
    //       m_GreenSlider.SetPos(m_RedSlider.GetPos());
    //       m_BlueSlider.SetPos(m_RedSlider.GetPos());
    //       m_PaintColor.X = float(m_RedSlider.GetPos()) / 255.00F;
    //       m_PaintColor.Y = float(m_GreenSlider.GetPos()) / 255.00F;
    //       m_PaintColor.Z = float(m_BlueSlider.GetPos()) / 255.00F;
    //       Paint_Color_Window();
    //   }
    
    // Check if grayscale mode is enabled
    bool is_checked = false;
    if (m_idc_grayscale_check)
    {
        is_checked = m_idc_grayscale_check->GetValue();
    }
    
    if (is_checked)
    {
        // Sync green and blue sliders to match red slider
        int red_value = 0;
        if (m_idc_slider_red)
        {
            red_value = m_idc_slider_red->GetValue();
        }
        
        if (m_idc_slider_green)
        {
            m_idc_slider_green->SetValue(red_value);
        }
        
        if (m_idc_slider_blue)
        {
            m_idc_slider_blue->SetValue(red_value);
        }
        
        // TODO(Phase 3 - Rendering): Update m_PaintColor Vector3 and call Paint_Color_Window()
        //   MFC calculates: m_PaintColor.X/Y/Z = float(slider_pos) / 255.0F
        //   Then calls Paint_Color_Window() to update the color preview panel
        //   This requires:
        //   1. m_PaintColor member variable (Vector3)
        //   2. Paint_Color_Window() implementation (uses GDI/wxDC to draw preview)
        //   Priority: MEDIUM - grayscale sync works, but preview won't update
    }
}

void ColorSel::OnChangeBlueEdit(wxCommandEvent &event)
{
    // MFC Reference: ColorSelectionDialog.cpp (OnChangeBlueEdit)
    // Function: Sync slider when blue text edit changes
    //
    // MFC Implementation:
    //   if (::IsWindow(m_BlueSlider)) {
    //       int value = GetDlgItemInt(IDC_BLUE_EDIT);
    //       m_BlueSlider.SetPos(value);
    //       Update_Sliders(IDC_SLIDER_BLUE);
    //       SendDlgItemMessage(IDC_BLUE_EDIT, EM_SETSEL, (WPARAM)(int)10, (LPARAM)(int)20);
    //   }
    
    if (m_idc_slider_blue && m_idc_blue_edit)
    {
        wxString text = m_idc_blue_edit->GetValue();
        long value = 0;
        
        if (text.ToLong(&value))
        {
            // Clamp to valid range (0-255)
            if (value < 0) value = 0;
            if (value > 255) value = 255;
            
            // Update slider
            m_idc_slider_blue->SetValue(static_cast<int>(value));
            
            // TODO(Phase 3 - Color Preview): Update_Sliders(IDC_SLIDER_BLUE)
            //   MFC calls Update_Sliders which:
            //   1. Syncs other sliders if grayscale mode enabled
            //   2. Updates m_PaintColor Vector3 (normalized RGB)
            //   3. Calls Paint_Color_Window() to update preview
            //   4. Updates spin controls
            //   Priority: MEDIUM - slider syncs but no preview update
        }
    }
}

void ColorSel::OnChangeGreenEdit(wxCommandEvent &event)
{
    // MFC Reference: ColorSelectionDialog.cpp (OnChangeGreenEdit)
    // Function: Sync slider when green text edit changes
    //
    // MFC Implementation:
    //   if (::IsWindow(m_GreenSlider)) {
    //       int value = GetDlgItemInt(IDC_GREEN_EDIT);
    //       m_GreenSlider.SetPos(value);
    //       Update_Sliders(IDC_SLIDER_GREEN);
    //       SendDlgItemMessage(IDC_GREEN_EDIT, EM_SETSEL, (WPARAM)(int)10, (LPARAM)(int)20);
    //   }
    
    if (m_idc_slider_green && m_idc_green_edit)
    {
        wxString text = m_idc_green_edit->GetValue();
        long value = 0;
        
        if (text.ToLong(&value))
        {
            // Clamp to valid range (0-255)
            if (value < 0) value = 0;
            if (value > 255) value = 255;
            
            // Update slider
            m_idc_slider_green->SetValue(static_cast<int>(value));
            
            // TODO(Phase 3 - Color Preview): Update_Sliders(IDC_SLIDER_GREEN)
            //   MFC calls Update_Sliders which:
            //   1. Syncs other sliders if grayscale mode enabled
            //   2. Updates m_PaintColor Vector3 (normalized RGB)
            //   3. Calls Paint_Color_Window() to update preview
            //   4. Updates spin controls
            //   Priority: MEDIUM - slider syncs but no preview update
        }
    }
}

void ColorSel::OnChangeRedEdit(wxCommandEvent &event)
{
    // MFC Reference: ColorSelectionDialog.cpp (OnChangeRedEdit)
    // Function: Sync slider when red text edit changes
    //
    // MFC Implementation:
    //   if (::IsWindow(m_RedSlider)) {
    //       int value = GetDlgItemInt(IDC_RED_EDIT);
    //       m_RedSlider.SetPos(value);
    //       Update_Sliders(IDC_SLIDER_RED);
    //       SendDlgItemMessage(IDC_RED_EDIT, EM_SETSEL, (WPARAM)(int)10, (LPARAM)(int)20);
    //   }
    
    if (m_idc_slider_red && m_idc_red_edit)
    {
        wxString text = m_idc_red_edit->GetValue();
        long value = 0;
        
        if (text.ToLong(&value))
        {
            // Clamp to valid range (0-255)
            if (value < 0) value = 0;
            if (value > 255) value = 255;
            
            // Update slider
            m_idc_slider_red->SetValue(static_cast<int>(value));
            
            // TODO(Phase 3 - Color Preview): Update_Sliders(IDC_SLIDER_RED)
            //   MFC calls Update_Sliders which:
            //   1. Syncs other sliders if grayscale mode enabled
            //   2. Updates m_PaintColor Vector3 (normalized RGB)
            //   3. Calls Paint_Color_Window() to update preview
            //   4. Updates spin controls
            //   Priority: MEDIUM - slider syncs but no preview update
        }
    }
}


// ============================================================================
// Phase 2.5: Dialog Infrastructure (Auto-generated)
// ============================================================================

void ColorSel::OnInitDialog(wxInitDialogEvent& event)
{
    // Initialize controls after they're created
    // Allow the base class to process this message
    
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
    // TODO: Declare: int red_value = int(m_Color.X * 255.00F);
    // TODO: Declare: int green_value = int(m_Color.Y * 255.00F);
    // TODO: Declare: int blue_value = int(m_Color.Z * 255.00F);
    // TODO: Convert: if ((red_value == green_value) &&
    // Check the grayscale checkbox
    if (m_idc_grayscale_check) {
        m_idc_grayscale_check->SetValue(true);
    }
    // Set the initial slider positions
    // TODO: Convert: m_RedSlider.SetPos (red_value);
    // TODO: Convert: m_GreenSlider.SetPos (green_value);
    // TODO: Convert: m_BlueSlider.SetPos (blue_value);
    // TODO: Convert: m_RedSpin.SetPos (red_value);
    // TODO: Convert: m_GreenSpin.SetPos (green_value);
    // TODO: Convert: m_BlueSpin.SetPos (blue_value);
    // TODO: Convert: return TRUE;

    event.Skip();
}

bool ColorSel::TransferDataToWindow()
{
    // Data is transferred in OnInitDialog for this dialog
    return true;
}

bool ColorSel::TransferDataFromWindow()
{
    // Extract data from controls and apply to business logic

    // TODO: Convert: // Record the color
    // TODO: Convert: m_Color = m_PaintColor;
    // TODO: Convert: // Allow the base class to process this message
    // TODO: Convert: return ;

    return true;
}
