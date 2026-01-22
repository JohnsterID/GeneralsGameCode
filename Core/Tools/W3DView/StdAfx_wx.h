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

// TheSuperHackers: wxWidgets precompiled header replacement for StdAfx.h

#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/string.h>
#include <wx/arrstr.h>
#include <vector>

// MFC-to-wxWidgets compatibility types
typedef wxString CString;

template<class T>
class DynamicVectorClass {
public:
    DynamicVectorClass() {}
    ~DynamicVectorClass() {}
    
    void Delete_All() { m_data.clear(); }
    void Add(const T& item) { m_data.push_back(item); }
    int Count() const { return (int)m_data.size(); }
    T& operator[](int index) { return m_data[index]; }
    const T& operator[](int index) const { return m_data[index]; }
    
private:
    std::vector<T> m_data;
};

// Specialization for CString/wxString
template<>
class DynamicVectorClass<CString> {
public:
    DynamicVectorClass() {}
    ~DynamicVectorClass() {}
    
    void Delete_All() { m_data.Clear(); }
    void Add(const CString& item) { m_data.Add(item); }
    int Count() const { return (int)m_data.GetCount(); }
    CString& operator[](size_t index) { return m_data[index]; }
    const CString& operator[](size_t index) const { return m_data[index]; }
    
private:
    wxArrayString m_data;
};
