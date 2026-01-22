/*
**	Command & Conquer Renegade(tm)
**	Copyright 2026 TheSuperHackers
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

// TheSuperHackers: wxWidgets Display Speed Dialog implementation

#include "DisplaySpeedDialog_wx.h"
#include <wx/xrc/xmlres.h>

wxBEGIN_EVENT_TABLE(DisplaySpeedDialog, DisplaySpeedDialogBase)
    EVT_BUTTON(XRCID("IDOK"), DisplaySpeedDialog::OnOK)
    EVT_BUTTON(XRCID("IDCANCEL"), DisplaySpeedDialog::OnCancel)
wxEND_EVENT_TABLE()

DisplaySpeedDialog::DisplaySpeedDialog(wxWindow *parent)
    : DisplaySpeedDialogBase(parent)
    , m_speed(50)
    , m_blendFrames(false)
    , m_compressQ(false)
    , m_16bit(false)
    , m_8bit(false)
{
    // Set slider range (0-100 for speed percentage)
    if (m_speedSlider) {
        m_speedSlider->SetRange(0, 100);
    }

    // Transfer initial data to controls
    TransferDataToWindow();

    Centre();
}

bool DisplaySpeedDialog::TransferDataToWindow()
{
    // Transfer data from member variables to controls
    if (m_speedSlider) {
        m_speedSlider->SetValue(m_speed);
    }

    if (m_blendCheckbox) {
        m_blendCheckbox->SetValue(m_blendFrames);
    }

    if (m_compressQCheckbox) {
        m_compressQCheckbox->SetValue(m_compressQ);
    }

    if (m_16bitCheckbox) {
        m_16bitCheckbox->SetValue(m_16bit);
    }

    if (m_8bitCheckbox) {
        m_8bitCheckbox->SetValue(m_8bit);
    }

    return true;
}

bool DisplaySpeedDialog::TransferDataFromWindow()
{
    // Transfer data from controls to member variables
    if (m_speedSlider) {
        m_speed = m_speedSlider->GetValue();
    }

    if (m_blendCheckbox) {
        m_blendFrames = m_blendCheckbox->GetValue();
    }

    if (m_compressQCheckbox) {
        m_compressQ = m_compressQCheckbox->GetValue();
    }

    if (m_16bitCheckbox) {
        m_16bit = m_16bitCheckbox->GetValue();
    }

    if (m_8bitCheckbox) {
        m_8bit = m_8bitCheckbox->GetValue();
    }

    return true;
}

void DisplaySpeedDialog::OnOK(wxCommandEvent &event)
{
    // Validate and transfer data
    if (Validate() && TransferDataFromWindow()) {
        EndModal(wxID_OK);
    }
}

void DisplaySpeedDialog::OnCancel(wxCommandEvent &event)
{
    // Close without saving
    EndModal(wxID_CANCEL);
}
