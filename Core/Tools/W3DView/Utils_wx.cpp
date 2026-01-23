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
