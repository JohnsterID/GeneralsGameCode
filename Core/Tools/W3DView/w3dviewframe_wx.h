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
    void OnViewPatchGapFill(wxCommandEvent &event);
    void OnUpdateViewPatchGapFill(wxUpdateUIEvent &event);
    void OnViewSubdivision1(wxCommandEvent &event);
    void OnUpdateViewSubdivision1(wxUpdateUIEvent &event);
    void OnViewSubdivision2(wxCommandEvent &event);
    void OnUpdateViewSubdivision2(wxUpdateUIEvent &event);
    void OnViewSubdivision3(wxCommandEvent &event);
    void OnUpdateViewSubdivision3(wxUpdateUIEvent &event);
    void OnViewSubdivision4(wxCommandEvent &event);
    void OnUpdateViewSubdivision4(wxUpdateUIEvent &event);
    void OnViewSubdivision5(wxCommandEvent &event);
    void OnUpdateViewSubdivision5(wxUpdateUIEvent &event);
    void OnViewSubdivision6(wxCommandEvent &event);
    void OnUpdateViewSubdivision6(wxUpdateUIEvent &event);
    void OnViewSubdivision7(wxCommandEvent &event);
    void OnUpdateViewSubdivision7(wxUpdateUIEvent &event);
    void OnViewSubdivision8(wxCommandEvent &event);
    void OnUpdateViewSubdivision8(wxUpdateUIEvent &event);
    void OnAnimationSettings(wxCommandEvent &event);
    void OnBackgroundColor(wxCommandEvent &event);
    void OnBackgroundBmp(wxCommandEvent &event);
    void OnBackgroundObject(wxCommandEvent &event);
    void OnBackgroundFog(wxCommandEvent &event);
    void OnUpdateBackgroundFog(wxUpdateUIEvent &event);
    void OnCameraSettings(wxCommandEvent &event);
    // Light menu handlers
    void OnLightRotateY(wxCommandEvent &event);
    void OnLightRotateZ(wxCommandEvent &event);
    void OnLightAmbient(wxCommandEvent &event);
    void OnLightScene(wxCommandEvent &event);
    void OnIncAmbientLight(wxCommandEvent &event);
    void OnDecAmbientLight(wxCommandEvent &event);
    void OnIncSceneLight(wxCommandEvent &event);
    void OnDecSceneLight(wxCommandEvent &event);
    void OnLightingExpose(wxCommandEvent &event);
    void OnUpdateLightingExpose(wxUpdateUIEvent &event);
    void OnKillSceneLight(wxCommandEvent &event);
    void OnPrelitVertex(wxCommandEvent &event);
    void OnUpdatePrelitVertex(wxUpdateUIEvent &event);
    void OnPrelitMultipass(wxCommandEvent &event);
    void OnUpdatePrelitMultipass(wxUpdateUIEvent &event);
    void OnPrelitMultitex(wxCommandEvent &event);
    void OnUpdatePrelitMultitex(wxUpdateUIEvent &event);
    // Settings menu handlers
    void OnTexturePathSettings(wxCommandEvent &event);
    void OnDeviceSelection(wxCommandEvent &event);
    void OnResolutionSettings(wxCommandEvent &event);
    void OnEnableGammaCorrection(wxCommandEvent &event);
    void OnUpdateEnableGammaCorrection(wxUpdateUIEvent &event);
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
