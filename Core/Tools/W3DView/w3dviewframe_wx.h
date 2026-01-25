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

// TheSuperHackers: wxWidgets frame implementation for W3DView

#pragma once

#include <wx/frame.h>
#include <wx/docview.h>
#include <wx/splitter.h>
#include <wx/statusbr.h>

class W3DViewFrame : public wxDocParentFrame
{
public:
    W3DViewFrame(wxDocManager *manager);
    virtual ~W3DViewFrame();

    wxSplitterWindow *GetSplitter() { return m_splitter; }

private:
    void OnClose(wxCloseEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnObjectProperties(wxCommandEvent &event);
    void OnLodGenerate(wxCommandEvent &event);
    void OnViewReset(wxCommandEvent &event);
    void OnAlternateMaterial(wxCommandEvent &event);
    void OnAnimationSettings(wxCommandEvent &event);
    void OnBackgroundColor(wxCommandEvent &event);
    void OnBackgroundBmp(wxCommandEvent &event);
    void OnBackgroundObject(wxCommandEvent &event);
    void OnBackgroundFog(wxCommandEvent &event);
    void OnCameraSettings(wxCommandEvent &event);
    void OnLightSettings(wxCommandEvent &event);
    void OnTexturePathSettings(wxCommandEvent &event);
    void OnDeviceSelection(wxCommandEvent &event);
    void OnResolutionSettings(wxCommandEvent &event);
    void OnGammaSettings(wxCommandEvent &event);

    void CreateMenuBar();
    void InitToolBar();
    void InitStatusBar();
    void CreateUI();

private:
    wxDocManager *m_docManager;
    wxSplitterWindow *m_splitter;
    wxStatusBar *m_statusBar;

    wxDECLARE_EVENT_TABLE();
};
