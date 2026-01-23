#!/usr/bin/env python3
"""
XRC to C++ Dialog Class Generator
Automatically generates wxWidgets dialog .h/.cpp files from XRC layouts
"""

import re
import sys
import xml.etree.ElementTree as ET
from pathlib import Path
from collections import Counter

def sanitize_cpp_identifier(name):
    """
    Convert a control name to a valid C++ identifier.
    - Replace invalid characters (commas, hyphens, etc.) with underscores
    - Ensure it doesn't start with a digit
    - Ensure it's not empty
    """
    if not name:
        return "ctrl"
    
    # Replace invalid characters with underscores
    sanitized = re.sub(r'[^a-zA-Z0-9_]', '_', name)
    
    # Ensure it doesn't start with a digit
    if sanitized and sanitized[0].isdigit():
        sanitized = '_' + sanitized
    
    # Ensure it's not empty
    if not sanitized:
        return "ctrl"
    
    return sanitized

# Map XRC control classes to wxWidgets C++ types and headers
CONTROL_TYPE_MAP = {
    'wxButton': ('wxButton', 'wx/button.h'),
    'wxTextCtrl': ('wxTextCtrl', 'wx/textctrl.h'),
    'wxStaticText': ('wxStaticText', 'wx/stattext.h'),
    'wxStaticBitmap': ('wxStaticBitmap', 'wx/statbmp.h'),
    'wxStaticBox': ('wxStaticBox', 'wx/statbox.h'),
    'wxCheckBox': ('wxCheckBox', 'wx/checkbox.h'),
    'wxRadioButton': ('wxRadioButton', 'wx/radiobut.h'),
    'wxComboBox': ('wxComboBox', 'wx/combobox.h'),
    'wxListBox': ('wxListBox', 'wx/listbox.h'),
    'wxListCtrl': ('wxListCtrl', 'wx/listctrl.h'),
    'wxTreeCtrl': ('wxTreeCtrl', 'wx/treectrl.h'),
    'wxSlider': ('wxSlider', 'wx/slider.h'),
    'wxSpinButton': ('wxSpinButton', 'wx/spinbutt.h'),
    'wxSpinCtrl': ('wxSpinCtrl', 'wx/spinctrl.h'),
    'wxGauge': ('wxGauge', 'wx/gauge.h'),
    'wxNotebook': ('wxNotebook', 'wx/notebook.h'),
    'wxPanel': ('wxPanel', 'wx/panel.h'),
    'wxToggleButton': ('wxToggleButton', 'wx/tglbtn.h'),
}

def parse_xrc_file(xrc_path):
    """Parse XRC file and extract dialog and control information"""
    tree = ET.parse(xrc_path)
    root = tree.getroot()
    
    # Find the dialog object
    dialog = root.find('.//{http://www.wxwidgets.org/wxxrc}object[@class="wxDialog"]')
    if dialog is None:
        # Try without namespace
        dialog = root.find('.//object[@class="wxDialog"]')
    
    if dialog is None:
        return None
    
    info = {
        'dialog_name': dialog.get('name'),
        'title': '',
        'controls': []
    }
    
    # Get dialog title
    title_elem = dialog.find('.//{http://www.wxwidgets.org/wxxrc}title')
    if title_elem is None:
        title_elem = dialog.find('.//title')
    if title_elem is not None and title_elem.text:
        info['title'] = title_elem.text
    
    # Find all control objects (skip sizers and the dialog itself)
    for obj in dialog.findall('.//{http://www.wxwidgets.org/wxxrc}object') or dialog.findall('.//object'):
        class_name = obj.get('class', '')
        control_name = obj.get('name', '')
        
        # Skip sizers and dialogs
        if 'Sizer' in class_name or class_name == 'wxDialog':
            continue
        
        # Skip controls without names or with generic names
        if not control_name or control_name in ['wxID_ANY', '-1']:
            continue
        
        if class_name in CONTROL_TYPE_MAP:
            info['controls'].append({
                'class': class_name,
                'name': control_name,
                'cpp_type': CONTROL_TYPE_MAP[class_name][0],
                'header': CONTROL_TYPE_MAP[class_name][1]
            })
    
    return info

def to_camel_case(dialog_id):
    """Convert IDD_SOME_DIALOG to SomeDialog"""
    # Remove IDD_ prefix
    name = dialog_id.replace('IDD_', '')
    # Split by underscore and capitalize each word
    words = name.split('_')
    return ''.join(word.capitalize() for word in words)

def make_unique_var_names(controls):
    """Generate unique variable names for controls, handling duplicates"""
    name_counts = Counter(ctrl['name'] for ctrl in controls)
    name_indices = {}
    result = []
    
    for ctrl in controls:
        ctrl_name = ctrl['name']
        # Sanitize control name to ensure valid C++ identifier
        var_name = f"m_{sanitize_cpp_identifier(ctrl_name).lower()}"
        
        # If this name appears multiple times, add index
        if name_counts[ctrl_name] > 1:
            if ctrl_name not in name_indices:
                name_indices[ctrl_name] = 1
            else:
                name_indices[ctrl_name] += 1
            var_name = f"{var_name}_{name_indices[ctrl_name]}"
        
        result.append({
            **ctrl,
            'var_name': var_name
        })
    
    return result

def generate_header(dialog_info):
    """Generate .h file content"""
    dialog_id = dialog_info['dialog_name']
    class_name = to_camel_case(dialog_id)
    
    # Collect unique headers
    headers = set(['wx/dialog.h', 'wx/xrc/xmlres.h'])
    for ctrl in dialog_info['controls']:
        headers.add(ctrl['header'])
    
    header_includes = '\n'.join(f'#include <{h}>' for h in sorted(headers))
    
    # Generate unique variable names
    controls_with_vars = make_unique_var_names(dialog_info['controls'])
    
    # Generate control member declarations
    control_members = []
    control_inits = []
    for ctrl in controls_with_vars:
        control_members.append(f"    {ctrl['cpp_type']} *{ctrl['var_name']};")
        control_inits.append(f'        {ctrl["var_name"]} = XRCCTRL(*this, "{ctrl["name"]}", {ctrl["cpp_type"]});')
    
    controls_str = '\n'.join(control_members) if control_members else '    // No controls'
    inits_str = '\n'.join(control_inits) if control_inits else '        // No controls to initialize'
    
    header = f'''/*
**Command & Conquer Renegade(tm)
**Copyright 2026 TheSuperHackers
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

// Auto-generated from XRC by xrc2cpp.py

#pragma once

{header_includes}

// Base class that loads from XRC
class {class_name}Base : public wxDialog
{{
public:
    {class_name}Base() {{}}
    {class_name}Base(wxWindow *parent)
    {{
        Create(parent);
    }}

    bool Create(wxWindow *parent)
    {{
        if (!wxXmlResource::Get()->LoadDialog(this, parent, "{dialog_id}")) {{
            return false;
        }}

        // Get references to controls
{inits_str}

        return true;
    }}

protected:
{controls_str}
}};

// Derived class for event handlers and custom logic
class {class_name} : public {class_name}Base
{{
public:
    {class_name}(wxWindow *parent);

protected:
    // Override for data transfer if needed
    // bool TransferDataToWindow() override;
    // bool TransferDataFromWindow() override;

private:
    void OnOK(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
}};
'''
    return header

def generate_cpp(dialog_info):
    """Generate .cpp file content"""
    dialog_id = dialog_info['dialog_name']
    class_name = to_camel_case(dialog_id)
    header_name = f"{class_name}_wx.h"
    
    cpp = f'''/*
**Command & Conquer Renegade(tm)
**Copyright 2026 TheSuperHackers
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

// Auto-generated from XRC by xrc2cpp.py

#include "{header_name}"
#include <wx/xrc/xmlres.h>

wxBEGIN_EVENT_TABLE({class_name}, {class_name}Base)
    EVT_BUTTON(wxID_OK, {class_name}::OnOK)
    EVT_BUTTON(wxID_CANCEL, {class_name}::OnCancel)
    // Add more event handlers as needed
wxEND_EVENT_TABLE()

{class_name}::{class_name}(wxWindow *parent)
    : {class_name}Base(parent)
{{
    // Initialize dialog
    // TransferDataToWindow();
    Centre();
}}

void {class_name}::OnOK(wxCommandEvent &event)
{{
    // Validate and close
    if (Validate() && TransferDataFromWindow()) {{
        EndModal(wxID_OK);
    }}
}}

void {class_name}::OnCancel(wxCommandEvent &event)
{{
    // Close without saving
    EndModal(wxID_CANCEL);
}}
'''
    return cpp

def main():
    if len(sys.argv) < 2:
        print("Usage: xrc2cpp.py <xrc_file> [output_dir]")
        print("   or: xrc2cpp.py --all <xrc_dir> [output_dir]")
        sys.exit(1)
    
    if sys.argv[1] == '--all':
        # Batch mode
        if len(sys.argv) < 3:
            print("Error: --all requires <xrc_dir>")
            sys.exit(1)
        
        xrc_dir = Path(sys.argv[2])
        output_dir = Path(sys.argv[3]) if len(sys.argv) > 3 else Path('.')
        
        if not xrc_dir.exists():
            print(f"Error: Directory {xrc_dir} not found")
            sys.exit(1)
        
        # Create output directory
        output_dir.mkdir(parents=True, exist_ok=True)
        
        xrc_files = sorted(xrc_dir.glob('*.xrc'))
        
        print(f"🔄 Generating C++ classes for {len(xrc_files)} XRC files")
        print()
        
        generated = 0
        skipped = 0
        errors = 0
        
        for xrc_file in xrc_files:
            try:
                dialog_info = parse_xrc_file(xrc_file)
                
                if not dialog_info:
                    print(f"⚠️  Skipped {xrc_file.name}: No dialog found")
                    skipped += 1
                    continue
                
                class_name = to_camel_case(dialog_info['dialog_name'])
                header_file = output_dir / f"{class_name}_wx.h"
                cpp_file = output_dir / f"{class_name}_wx.cpp"
                
                # Generate files
                header_file.write_text(generate_header(dialog_info), encoding='utf-8')
                cpp_file.write_text(generate_cpp(dialog_info), encoding='utf-8')
                
                print(f"✅ {dialog_info['dialog_name']:40s} → {class_name:30s} ({len(dialog_info['controls'])} controls)")
                generated += 1
                
            except Exception as e:
                print(f"❌ Error processing {xrc_file.name}: {e}")
                errors += 1
        
        print()
        print(f"📊 Summary:")
        print(f"   ✅ Generated: {generated}")
        print(f"   ⚠️  Skipped: {skipped}")
        print(f"   ❌ Errors: {errors}")
        
    else:
        # Single file mode
        xrc_file = Path(sys.argv[1])
        output_dir = Path(sys.argv[2]) if len(sys.argv) > 2 else Path('.')
        
        if not xrc_file.exists():
            print(f"Error: File {xrc_file} not found")
            sys.exit(1)
        
        # Create output directory
        output_dir.mkdir(parents=True, exist_ok=True)
        
        dialog_info = parse_xrc_file(xrc_file)
        
        if not dialog_info:
            print("Error: No dialog found in XRC file")
            sys.exit(1)
        
        class_name = to_camel_case(dialog_info['dialog_name'])
        header_file = output_dir / f"{class_name}_wx.h"
        cpp_file = output_dir / f"{class_name}_wx.cpp"
        
        # Generate files
        header_file.write_text(generate_header(dialog_info), encoding='utf-8')
        cpp_file.write_text(generate_cpp(dialog_info), encoding='utf-8')
        
        print(f"✅ Generated {class_name}")
        print(f"   Header: {header_file}")
        print(f"   Source: {cpp_file}")
        print(f"   Controls: {len(dialog_info['controls'])}")

if __name__ == "__main__":
    main()
