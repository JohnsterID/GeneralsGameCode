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
    
    // TODO: Helper to get the current document (wxDocParentFrame doesn't have GetDocument())
    wxDocument* GetDocument() const;

private:
    void OnClose(wxCloseEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnObjectProperties(wxCommandEvent &event);
    void OnLodGenerate(wxCommandEvent &event);
    void OnObjectReset(wxCommandEvent &event);
    void OnObjectRotateX(wxCommandEvent &event);
    void OnObjectRotateY(wxCommandEvent &event);
    void OnObjectRotateZ(wxCommandEvent &event);
    void OnObjectRotateYBack(wxCommandEvent &event);
    void OnObjectRotateZBack(wxCommandEvent &event);
    void OnObjectAlternateMaterials(wxCommandEvent &event);
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
    void OnWireframe(wxCommandEvent &event);
    void OnUpdateWireframe(wxUpdateUIEvent &event);
    void OnPolygonSorting(wxCommandEvent &event);
    void OnUpdatePolygonSorting(wxUpdateUIEvent &event);
    void OnViewObjectBar(wxCommandEvent &event);
    void OnUpdateViewObjectBar(wxUpdateUIEvent &event);
    void OnViewAnimationBar(wxCommandEvent &event);
    void OnUpdateViewAnimationBar(wxUpdateUIEvent &event);
    void OnViewFullscreen(wxCommandEvent &event);
    void OnUpdateViewFullscreen(wxUpdateUIEvent &event);
    // Animation menu handlers
    void OnAnimationPlay(wxCommandEvent &event);
    void OnAnimationPause(wxCommandEvent &event);
    void OnAnimationStop(wxCommandEvent &event);
    void OnAnimationStepBack(wxCommandEvent &event);
    void OnAnimationStepForward(wxCommandEvent &event);
    void OnAnimationSettings(wxCommandEvent &event);
    void OnBackgroundColor(wxCommandEvent &event);
    void OnBackgroundBmp(wxCommandEvent &event);
    void OnBackgroundObject(wxCommandEvent &event);
    void OnBackgroundFog(wxCommandEvent &event);
    void OnUpdateBackgroundFog(wxUpdateUIEvent &event);
    // Camera menu handlers
    void OnCameraFront(wxCommandEvent &event);
    void OnCameraBack(wxCommandEvent &event);
    void OnCameraLeft(wxCommandEvent &event);
    void OnCameraRight(wxCommandEvent &event);
    void OnCameraTop(wxCommandEvent &event);
    void OnCameraBottom(wxCommandEvent &event);
    void OnCameraReset(wxCommandEvent &event);
    void OnCameraSettings(wxCommandEvent &event);
    void OnCameraAllowRotateX(wxCommandEvent &event);
    void OnUpdateCameraAllowRotateX(wxUpdateUIEvent &event);
    void OnCameraAllowRotateY(wxCommandEvent &event);
    void OnUpdateCameraAllowRotateY(wxUpdateUIEvent &event);
    void OnCameraAllowRotateZ(wxCommandEvent &event);
    void OnUpdateCameraAllowRotateZ(wxUpdateUIEvent &event);
    void OnCopyScreenSize(wxCommandEvent &event);
    void OnSetCameraDistance(wxCommandEvent &event);
    void OnCameraAnimate(wxCommandEvent &event);
    void OnUpdateCameraAnimate(wxUpdateUIEvent &event);
    void OnCameraBonePosX(wxCommandEvent &event);
    void OnUpdateCameraBonePosX(wxUpdateUIEvent &event);
    void OnCameraResetOnLoad(wxCommandEvent &event);
    void OnUpdateCameraResetOnLoad(wxUpdateUIEvent &event);
    // Light menu handlers
    void OnLightRotateY(wxCommandEvent &event);
    void OnLightRotateZ(wxCommandEvent &event);
    void OnLightRotateYBack(wxCommandEvent &event);
    void OnLightRotateZBack(wxCommandEvent &event);
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
