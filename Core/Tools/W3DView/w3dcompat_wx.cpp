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

// TheSuperHackers: wxWidgets compatibility helpers for W3DView

#include "w3dcompat_wx.h"
#include "w3dviewdoc_wx.h"
#include "GraphicView_wx.h"

#include <wx/textctrl.h>
#include <wx/spinctrl.h>
#include <wx/docview.h>

// ============================================================================
// Phase 3A: Helper Function Implementations
// ============================================================================

W3DViewDoc* GetCurrentDocument_wx()
{
    // Get the active document from wxWidgets document manager
    wxDocManager* docManager = wxDocManager::GetDocumentManager();
    if (!docManager)
    {
        return nullptr;
    }
    
    // Get the current document (last active)
    wxDocument* doc = docManager->GetCurrentDocument();
    if (!doc)
    {
        // If no current document, try to get any document
        wxList& docs = docManager->GetDocuments();
        if (!docs.IsEmpty())
        {
            doc = static_cast<wxDocument*>(docs.GetFirst()->GetData());
        }
    }
    
    // Cast to W3DViewDoc
    return dynamic_cast<W3DViewDoc*>(doc);
}

float GetDlgItemFloat(wxTextCtrl* ctrl)
{
    if (!ctrl)
    {
        return 0.0f;
    }
    
    double value = 0.0;
    if (ctrl->GetValue().ToDouble(&value))
    {
        return static_cast<float>(value);
    }
    
    return 0.0f;
}

void SetDlgItemFloat(wxTextCtrl* ctrl, float value)
{
    if (!ctrl)
    {
        return;
    }
    
    ctrl->SetValue(wxString::Format("%.2f", value));
}

void Initialize_Spinner(wxSpinCtrl* spin, float value, float min, float max)
{
    if (!spin)
    {
        return;
    }
    
    // wxSpinCtrl uses integers, so we need to scale float values
    // For now, just cast to int (dialogs can override if they need float precision)
    spin->SetRange(static_cast<int>(min), static_cast<int>(max));
    spin->SetValue(static_cast<int>(value));
}
