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

// TheSuperHackers: wxWidgets application implementation for W3DView

#pragma once

#include <wx/app.h>
#include <wx/docview.h>

class W3DViewFrame;

class W3DViewApp : public wxApp
{
public:
    W3DViewApp();
    virtual ~W3DViewApp();

    virtual bool OnInit() override;
    virtual int OnExit() override;

    W3DViewFrame *GetMainFrame() { return m_frame; }
    wxDocManager *GetDocManager() { return m_docManager; }

private:
    void InitializeGraphicsSystem();
    void ShutdownGraphicsSystem();
    bool DoVersionCheck();

private:
    W3DViewFrame *m_frame;
    wxDocManager *m_docManager;
    bool m_initialized;
};

wxDECLARE_APP(W3DViewApp);
