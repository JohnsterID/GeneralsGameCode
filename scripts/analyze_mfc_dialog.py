#!/usr/bin/env python3
"""
Phase 2.5: Analyze MFC dialog for infrastructure requirements

Extracts:
1. OnInitDialog() implementation
2. DoDataExchange() DDX_ calls
3. Constructor parameters (business objects)
4. Member variables
5. Helper methods for initialization
"""

import re
import sys
from pathlib import Path

def extract_constructor_params(cpp_content, class_name):
    """Extract constructor parameters to identify business objects"""
    pattern = rf'{class_name}::{class_name}\s*\((.*?)\)'
    match = re.search(pattern, cpp_content, re.DOTALL)
    
    if not match:
        return []
    
    params_str = match.group(1)
    params = []
    
    # Parse parameter list
    for param in params_str.split(','):
        param = param.strip()
        if param and 'CWnd' not in param and 'parent' not in param.lower():
            params.append(param)
    
    return params

def extract_member_variables(h_content, class_name):
    """Extract member variables from header file"""
    # Find class definition
    class_pattern = rf'class\s+{class_name}[^{{]*{{(.*?)^}};'
    class_match = re.search(class_pattern, h_content, re.MULTILINE | re.DOTALL)
    
    if not class_match:
        return []
    
    class_body = class_match.group(1)
    
    # Extract member variables (typically in protected/private sections)
    members = []
    for line in class_body.split('\n'):
        line = line.strip()
        
        # Skip empty lines, comments, methods
        if not line or line.startswith('//') or '(' in line:
            continue
        
        # Look for member variable declarations
        if re.match(r'\w+\s+[*&]?m_\w+', line):
            members.append(line.rstrip(';'))
    
    return members

def extract_oninitdialog(cpp_content, class_name):
    """Extract OnInitDialog implementation"""
    pattern = rf'(BOOL|bool)\s+{class_name}::OnInitDialog\s*\((.*?)\)\s*{{(.*?)^}}'
    match = re.search(pattern, cpp_content, re.MULTILINE | re.DOTALL)
    
    if not match:
        return None
    
    return {
        'return_type': match.group(1),
        'params': match.group(2).strip(),
        'body': match.group(3).strip()
    }

def extract_dodataexchange(cpp_content, class_name):
    """Extract DoDataExchange implementation"""
    pattern = rf'void\s+{class_name}::DoDataExchange\s*\((.*?)\)\s*{{(.*?)^}}'
    match = re.search(pattern, cpp_content, re.MULTILINE | re.DOTALL)
    
    if not match:
        return None
    
    body = match.group(2).strip()
    
    # Extract DDX_ calls
    ddx_controls = []
    ddx_data = []
    
    for line in body.split('\n'):
        line = line.strip()
        
        # DDX_Control - bind control to member variable
        ddx_control_match = re.match(r'DDX_Control\s*\(\s*pDX\s*,\s*(\w+)\s*,\s*(\w+)\s*\)', line)
        if ddx_control_match:
            ddx_controls.append({
                'control_id': ddx_control_match.group(1),
                'member_var': ddx_control_match.group(2)
            })
        
        # DDX_Text/DDX_Check/etc - bind data to control
        ddx_data_match = re.match(r'(DDX_\w+)\s*\(\s*pDX\s*,\s*(\w+)\s*,\s*(\w+)\s*\)', line)
        if ddx_data_match:
            ddx_data.append({
                'type': ddx_data_match.group(1),
                'control_id': ddx_data_match.group(2),
                'member_var': ddx_data_match.group(3)
            })
    
    return {
        'params': match.group(1).strip(),
        'ddx_controls': ddx_controls,
        'ddx_data': ddx_data,
        'body': body
    }

def analyze_dialog(cpp_file, h_file, class_name):
    """Analyze MFC dialog files"""
    
    if not cpp_file.exists():
        print(f"❌ CPP file not found: {cpp_file}")
        return None
    
    if not h_file.exists():
        print(f"❌ Header file not found: {h_file}")
        return None
    
    cpp_content = cpp_file.read_text()
    h_content = h_file.read_text()
    
    print(f"Analyzing {class_name}...")
    print("=" * 70)
    
    # Extract constructor parameters
    ctor_params = extract_constructor_params(cpp_content, class_name)
    print(f"\nConstructor Parameters ({len(ctor_params)}):")
    for param in ctor_params:
        print(f"  - {param}")
    
    # Extract member variables
    members = extract_member_variables(h_content, class_name)
    print(f"\nMember Variables ({len(members)}):")
    for member in members[:10]:  # Show first 10
        print(f"  - {member}")
    if len(members) > 10:
        print(f"  ... and {len(members) - 10} more")
    
    # Extract OnInitDialog
    init_dialog = extract_oninitdialog(cpp_content, class_name)
    if init_dialog:
        print(f"\n✓ OnInitDialog Found:")
        print(f"  Return: {init_dialog['return_type']}")
        print(f"  Params: {init_dialog['params'] or '(void)'}")
        print(f"  Body: {len(init_dialog['body'])} characters")
        print(f"\n  First 200 chars:")
        print("  " + init_dialog['body'][:200].replace('\n', '\n  '))
    else:
        print(f"\n❌ OnInitDialog NOT found")
    
    # Extract DoDataExchange
    ddx = extract_dodataexchange(cpp_content, class_name)
    if ddx:
        print(f"\n✓ DoDataExchange Found:")
        print(f"  DDX_Control calls: {len(ddx['ddx_controls'])}")
        for ctrl in ddx['ddx_controls'][:5]:
            print(f"    - {ctrl['control_id']} → {ctrl['member_var']}")
        if len(ddx['ddx_controls']) > 5:
            print(f"    ... and {len(ddx['ddx_controls']) - 5} more")
        
        print(f"  DDX_Data calls: {len(ddx['ddx_data'])}")
        for data in ddx['ddx_data'][:5]:
            print(f"    - {data['type']}: {data['control_id']} ↔ {data['member_var']}")
        if len(ddx['ddx_data']) > 5:
            print(f"    ... and {len(ddx['ddx_data']) - 5} more")
    else:
        print(f"\n❌ DoDataExchange NOT found")
    
    return {
        'class_name': class_name,
        'ctor_params': ctor_params,
        'members': members,
        'oninitdialog': init_dialog,
        'dodataexchange': ddx
    }

if __name__ == '__main__':
    if len(sys.argv) < 4:
        print("Usage: analyze_mfc_dialog.py <cpp_file> <h_file> <class_name>")
        print()
        print("Example:")
        print("  python3 analyze_mfc_dialog.py \\")
        print("    Core/Tools/W3DView/EmitterGeneralPropPage.cpp \\")
        print("    Core/Tools/W3DView/EmitterGeneralPropPage.h \\")
        print("    EmitterGeneralPropPageClass")
        sys.exit(1)
    
    cpp_file = Path(sys.argv[1])
    h_file = Path(sys.argv[2])
    class_name = sys.argv[3]
    
    result = analyze_dialog(cpp_file, h_file, class_name)
    
    if result:
        print()
        print("=" * 70)
        print("✅ Analysis complete")
        print()
        print("Next steps:")
        print("  1. Review OnInitDialog body for control initialization")
        print("  2. Map DDX_Control calls to XRCCTRL statements")
        print("  3. Map DDX_Data calls to TransferDataToWindow/FromWindow")
        print("  4. Add business object parameters to wxWidgets constructor")
