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

/////////////////////////////////////////////////////////////////////////////
//
//  Utils_wx.cpp
//
//  wxWidgets-compatible utility functions (subset of Utils.cpp)
//  Phase 3A.3: Provides minimal implementations for asset manager
//
/////////////////////////////////////////////////////////////////////////////

#include "StdAfx_wx.h"
#include "Utils.h"
#include "Vector.h"
#include <wx/filename.h>
#include <wx/dcmemory.h>
#include <wx/dcclient.h>
#include <wx/panel.h>

////////////////////////////////////////////////////////////////////////////
//
//  Paint_Gradient_wx
//
//  wxWidgets implementation of MFC Paint_Gradient
//  Paints a color gradient from black to the specified base color
//  MFC Reference: Utils.cpp:122-166 (Paint_Gradient)
//
////////////////////////////////////////////////////////////////////////////
void Paint_Gradient_wx(wxWindow* window, unsigned char baseRed, unsigned char baseGreen, unsigned char baseBlue)
{
	if (!window) {
		return;
	}

	// Get the window size
	wxSize size = window->GetClientSize();
	int width = size.GetWidth();
	int height = size.GetHeight();

	if (width <= 0 || height <= 0) {
		return;
	}

	// Create a device context for the window
	wxClientDC dc(window);

	// Calculate width per shade (256 shades from black to full color)
	float widthPerShade = static_cast<float>(width) / 256.0f;

	// Loop through each shade and paint its sliver
	float posX = 0.0f;
	for (int shade = 0; shade < 256; shade++) {
		// Calculate the color for this shade
		unsigned char r = static_cast<unsigned char>(shade * baseRed / 255);
		unsigned char g = static_cast<unsigned char>(shade * baseGreen / 255);
		unsigned char b = static_cast<unsigned char>(shade * baseBlue / 255);

		// Calculate sliver width (at least 1 pixel)
		int sliverWidth = (widthPerShade >= 1.0f) ? static_cast<int>(widthPerShade) + 1 : 1;

		// Paint this sliver
		dc.SetPen(wxPen(wxColour(r, g, b)));
		dc.SetBrush(wxBrush(wxColour(r, g, b)));
		dc.DrawRectangle(static_cast<int>(posX), 0, sliverWidth, height);

		// Increment the current position
		posX += widthPerShade;
	}
}

////////////////////////////////////////////////////////////////////////////
//
//  Find_Missing_Textures
//
//  wxWidgets implementation - tracks missing texture files
//
////////////////////////////////////////////////////////////////////////////
void Find_Missing_Textures(
	DynamicVectorClass<CString>& list,
	LPCTSTR name,
	int frame_count
)
{
	// Check if file exists using wxWidgets API
	wxString filename(name);
	wxFileName fn(filename);
	
	if (!fn.FileExists()) {
		// Add to missing textures list
		list.Add(filename);
	}
}
