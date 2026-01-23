#!/usr/bin/env python3
"""
MFC to wxWidgets Pattern Conversion Database

Contains regex patterns and code generation templates for converting
common MFC patterns to wxWidgets equivalents.
"""

import re

# Pattern database: MFC function → wxWidgets code generator
PATTERNS = {
    'Initialize_Spinner': {
        'regex': r'::Initialize_Spinner\s*\(\s*(\w+)\s*,\s*([^,]+),\s*([^,]+),\s*([^)]+)\)',
        'generator': lambda m, ctrl_name: f"""if ({ctrl_name}) {{
    {ctrl_name}->SetRange({m.group(3)}, {m.group(4)});
    {ctrl_name}->SetValue(static_cast<int>({m.group(2)}));
}}"""
    },
    
    'SetDlgItemFloat': {
        'regex': r'::SetDlgItemFloat\s*\(\s*[^,]+,\s*(\w+)\s*,\s*([^)]+)\)',
        'generator': lambda m, ctrl_name: f"""if ({ctrl_name}) {{
    {ctrl_name}->SetValue(wxString::Format("%.2f", {m.group(2)}));
}}"""
    },
    
    'SetDlgItemText': {
        'regex': r'SetDlgItemText\s*\(\s*(?:\w+\s*,\s*)?(\w+)\s*,\s*([^)]+)\)',
        'generator': lambda m, ctrl_name: f"""if ({ctrl_name}) {{
    {ctrl_name}->SetValue({m.group(2)});
}}"""
    },
    
    'GetDlgItemFloat': {
        'regex': r'::GetDlgItemFloat\s*\(\s*[^,]+,\s*(\w+)\)',
        'generator': lambda m, ctrl_name, var_name='value': f"""double {var_name};
if ({ctrl_name} && {ctrl_name}->GetValue().ToDouble(&{var_name})) {{
    // Use {var_name} (cast to float if needed)
}} else {{
    wxMessageBox("Please enter a valid numeric value", "Invalid Input", 
                 wxOK | wxICON_ERROR, this);
    return false;
}}"""
    },
    
    'ComboBox_AddString': {
        'regex': r'(\w+)\.AddString\s*\(\s*"([^"]+)"\s*\)',
        'generator': lambda m, ctrl_name: f"""if ({ctrl_name}) {{
    {ctrl_name}->Append("{m.group(2)}");
}}"""
    },
    
    'ComboBox_SetCurSel': {
        'regex': r'(\w+)\.SetCurSel\s*\(\s*([^)]+)\)',
        'generator': lambda m, ctrl_name: f"""if ({ctrl_name}) {{
    {ctrl_name}->SetSelection({m.group(2)});
}}"""
    },
    
    'SendDlgItemMessage_BM_SETCHECK': {
        'regex': r'SendDlgItemMessage\s*\(\s*(\w+)\s*,\s*BM_SETCHECK\s*,\s*(?:WPARAM\s*)?\(([^)]+)\)',
        'generator': lambda m, ctrl_name: f"""if ({ctrl_name}) {{
    {ctrl_name}->SetValue({m.group(2)} != 0);
}}"""
    },
}

def convert_mfc_line(line, control_mappings):
    """
    Convert a single MFC code line to wxWidgets equivalent
    
    Args:
        line: MFC code line
        control_mappings: dict mapping control IDs to member variable names
                         e.g., {'IDC_DISTANCE_SPIN': 'm_idc_distance_spin'}
    
    Returns:
        Converted wxWidgets code or None if no pattern matches
    """
    
    for pattern_name, pattern_info in PATTERNS.items():
        match = re.search(pattern_info['regex'], line)
        if match:
            # Extract control ID from match
            control_id = match.group(1)
            
            # Map to member variable name
            ctrl_var = control_mappings.get(control_id, f"m_{control_id.lower()}")
            
            # Generate wxWidgets code
            try:
                wx_code = pattern_info['generator'](match, ctrl_var)
                return wx_code
            except Exception as e:
                return f"// TODO: Convert {pattern_name}: {line.strip()}\n// Error: {e}"
    
    return None

def detect_required_includes(code):
    """Detect required includes based on code patterns"""
    includes = set()
    
    if 'wxSpinEvent' in code or 'EVT_SPIN' in code or 'wxSpinButton' in code:
        includes.add('#include <wx/spinbutt.h>')
    
    if 'Get_Graphic_View' in code:
        includes.add('#include "../GraphicView.h"')
        includes.add('#include "../Utils.h"')
    
    if 'wxMessageBox' in code:
        includes.add('#include <wx/msgdlg.h>')
    
    return sorted(includes)

def map_control_ids_to_members(xrc_base_class_body):
    """
    Extract control ID to member variable mapping from XRC base class
    
    Args:
        xrc_base_class_body: Source code of the XRC base class
        
    Returns:
        dict mapping control IDs to member variable names
    """
    mappings = {}
    
    # Find XRCCTRL calls
    # Example: m_idc_distance_edit = XRCCTRL(*this, "IDC_DISTANCE_EDIT", wxTextCtrl);
    pattern = r'(\w+)\s*=\s*XRCCTRL\s*\(\s*\*this\s*,\s*"(\w+)"\s*,'
    
    for match in re.finditer(pattern, xrc_base_class_body):
        member_var = match.group(1)
        control_id = match.group(2)
        mappings[control_id] = member_var
    
    return mappings

if __name__ == '__main__':
    # Test pattern conversion
    test_lines = [
        '::Initialize_Spinner (m_DistanceSpinCtrl, graphic_view->Get_Camera_Distance (), 0, 25000.0F);',
        '::SetDlgItemFloat (m_hWnd, IDC_DISTANCE_EDIT, graphic_view->Get_Camera_Distance ());',
        'SetDlgItemText (IDC_NAME_EDIT, m_EmitterName);',
        'm_ComboBox.AddString("Item 1");',
        'm_ComboBox.SetCurSel(0);',
    ]
    
    control_mappings = {
        'IDC_DISTANCE_EDIT': 'm_idc_distance_edit',
        'IDC_DISTANCE_SPIN': 'm_idc_distance_spin',
        'IDC_NAME_EDIT': 'm_idc_name_edit',
    }
    
    print("Testing MFC → wxWidgets Pattern Conversion:")
    print("=" * 70)
    
    for line in test_lines:
        print(f"\nMFC: {line}")
        wx_code = convert_mfc_line(line, control_mappings)
        if wx_code:
            print(f"wxWidgets:\n{wx_code}")
        else:
            print("wxWidgets: No pattern match")
