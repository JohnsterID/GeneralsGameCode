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

// TheSuperHackers: wxWidgets About Dialog implementation

#include "AboutDialog_wx.h"
#include <wx/xrc/xmlres.h>

wxBEGIN_EVENT_TABLE(AboutDialog, AboutDialogBase)
    EVT_BUTTON(XRCID("IDOK"), AboutDialog::OnOK)
wxEND_EVENT_TABLE()

AboutDialog::AboutDialog(wxWindow *parent)
    : AboutDialogBase(parent)
{
    // Center the dialog on parent
    Centre();
}

void AboutDialog::OnOK(wxCommandEvent &event)
{
    // Close the dialog with OK result
    EndModal(wxID_OK);
}
