#!/usr/bin/env python3
"""
XRC Initialization Code Generator
Automatically generates InitXmlResource() function to load all XRC files
"""

import sys
from pathlib import Path

def generate_xrc_init(xrc_dir, output_dir):
    """Generate XRC initialization code"""
    xrc_dir = Path(xrc_dir)
    output_dir = Path(output_dir)
    
    # Find all XRC files
    xrc_files = sorted(xrc_dir.glob('*.xrc'))
    
    if not xrc_files:
        print(f"Error: No XRC files found in {xrc_dir}")
        return False
    
    print(f"🔄 Generating XRC initialization code for {len(xrc_files)} files")
    
    # Generate header file
    header_content = f'''/*
**Command & Conquer Renegade(tm)
**Copyright 2025 Electronic Arts Inc.
**
**This program is free software: you can redistribute it and/or modify
**it under the terms of the GNU General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.
**
**This program is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**GNU General Public License for more details.
**
**You should have received a copy of the GNU General Public License
**along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Auto-generated XRC resource initialization
// Generated from {len(xrc_files)} XRC files

#pragma once

// Initialize all XRC resources for W3DView dialogs
// Call this once at application startup before creating any dialogs
void InitW3DViewXmlResources();
'''
    
    # Generate source file with LoadFile calls
    load_statements = []
    for xrc_file in xrc_files:
        rel_path = f"ui/{xrc_file.name}"
        load_statements.append(f'    wxXmlResource::Get()->Load("{rel_path}");')
    
    loads_str = '\n'.join(load_statements)
    
    source_content = f'''/*
**Command & Conquer Renegade(tm)
**Copyright 2025 Electronic Arts Inc.
**
**This program is free software: you can redistribute it and/or modify
**it under the terms of the GNU General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.
**
**This program is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**GNU General Public License for more details.
**
**You should have received a copy of the GNU General Public License
**along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Auto-generated XRC resource initialization
// Generated from {len(xrc_files)} XRC files

#include "W3DViewUI.h"
#include <wx/xrc/xmlres.h>

void InitW3DViewXmlResources()
{{
    // Load all {len(xrc_files)} XRC dialog definitions
{loads_str}
}}
'''
    
    # Create output directory
    output_dir.mkdir(parents=True, exist_ok=True)
    
    # Write files
    header_file = output_dir / "W3DViewUI.h"
    source_file = output_dir / "W3DViewUI.cpp"
    
    header_file.write_text(header_content, encoding='utf-8')
    source_file.write_text(source_content, encoding='utf-8')
    
    print(f"✅ Generated XRC initialization code")
    print(f"   Header: {header_file}")
    print(f"   Source: {source_file}")
    print(f"   XRC files: {len(xrc_files)}")
    
    return True

def main():
    if len(sys.argv) < 3:
        print("Usage: generate_xrc_init.py <xrc_dir> <output_dir>")
        sys.exit(1)
    
    xrc_dir = sys.argv[1]
    output_dir = sys.argv[2]
    
    if generate_xrc_init(xrc_dir, output_dir):
        sys.exit(0)
    else:
        sys.exit(1)

if __name__ == "__main__":
    main()
