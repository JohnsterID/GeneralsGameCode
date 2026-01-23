#!/usr/bin/env python3
"""
Phase 2.5: Generate wxWidgets infrastructure from MFC analysis

Generates:
1. wxEVT_INIT_DIALOG handler
2. TransferDataToWindow() implementation
3. TransferDataFromWindow() implementation
4. Business object member variables
5. Updated constructor signature
"""

import re
import sys
from pathlib import Path

def generate_init_dialog_handler(class_name, init_body, indent="    "):
    """Generate wxEVT_INIT_DIALOG handler from MFC OnInitDialog"""
    
    code = []
    code.append(f"void {class_name}::OnInitDialog(wxInitDialogEvent& event)")
    code.append("{")
    code.append(f"{indent}// Initialize controls after they're created")
    code.append("")
    
    # Parse initialization code
    # Look for patterns like:
    # - SetDlgItemText() → wxTextCtrl::SetValue()
    # - ComboBox::AddString() → wxComboBox::Append()
    # - SetCheck() → wxCheckBox::SetValue()
    
    for line in init_body.split('\n'):
        line_stripped = line.strip()
        
        # Skip base class call and comments
        if 'CPropertyPage::OnInitDialog' in line or line_stripped.startswith('//') or not line_stripped:
            if line_stripped.startswith('//'):
                code.append(f"{indent}{line_stripped}")
            continue
        
        # Convert SetDlgItemText
        set_text_match = re.match(r'SetDlgItemText\s*\(\s*(\w+)\s*,\s*(\w+)\s*\)', line_stripped)
        if set_text_match:
            ctrl_id = set_text_match.group(1)
            var_name = set_text_match.group(2)
            code.append(f"{indent}// TODO: Convert SetDlgItemText({ctrl_id}, {var_name})")
            code.append(f"{indent}// wxTextCtrl* ctrl = XRCCTRL(*this, \"{ctrl_id}\", wxTextCtrl);")
            code.append(f"{indent}// if (ctrl) ctrl->SetValue({var_name});")
            continue
        
        # Convert combo box operations
        if 'Add_Shader_To_Combo' in line:
            code.append(f"{indent}// TODO: Convert combo box population")
            code.append(f"{indent}// wxComboBox* combo = XRCCTRL(*this, \"IDC_SHADER_COMBO\", wxComboBox);")
            code.append(f"{indent}// if (combo) {{ combo->Append(\"item\"); }}")
            continue
        
        # Keep original line as TODO
        if line_stripped and not line_stripped.endswith('}'):
            code.append(f"{indent}// TODO: Convert: {line_stripped}")
    
    code.append("")
    code.append(f"{indent}// Call base class")
    code.append(f"{indent}event.Skip();")
    code.append("}")
    
    return '\n'.join(code)

def generate_transfer_to_window(class_name, members, ddx_data, indent="    "):
    """Generate TransferDataToWindow from member variables"""
    
    code = []
    code.append(f"bool {class_name}::TransferDataToWindow()")
    code.append("{")
    code.append(f"{indent}// Populate controls from business object / member variables")
    code.append("")
    
    if ddx_data:
        for data in ddx_data:
            ctrl_id = data['control_id']
            member_var = data['member_var']
            ddx_type = data['type']
            
            code.append(f"{indent}// TODO: {ddx_type}({ctrl_id}, {member_var})")
            
            if 'Text' in ddx_type:
                code.append(f"{indent}// wxTextCtrl* ctrl = XRCCTRL(*this, \"{ctrl_id}\", wxTextCtrl);")
                code.append(f"{indent}// if (ctrl) ctrl->SetValue({member_var});")
            elif 'Check' in ddx_type:
                code.append(f"{indent}// wxCheckBox* ctrl = XRCCTRL(*this, \"{ctrl_id}\", wxCheckBox);")
                code.append(f"{indent}// if (ctrl) ctrl->SetValue({member_var});")
            
            code.append("")
    else:
        code.append(f"{indent}// TODO: Implement data transfer from member variables to controls")
    
    code.append(f"{indent}return true;")
    code.append("}")
    
    return '\n'.join(code)

def generate_transfer_from_window(class_name, ddx_data, indent="    "):
    """Generate TransferDataFromWindow"""
    
    code = []
    code.append(f"bool {class_name}::TransferDataFromWindow()")
    code.append("{")
    code.append(f"{indent}// Extract data from controls to member variables / business object")
    code.append("")
    
    if ddx_data:
        for data in ddx_data:
            ctrl_id = data['control_id']
            member_var = data['member_var']
            ddx_type = data['type']
            
            code.append(f"{indent}// TODO: {ddx_type}({ctrl_id}, {member_var})")
            
            if 'Text' in ddx_type:
                code.append(f"{indent}// wxTextCtrl* ctrl = XRCCTRL(*this, \"{ctrl_id}\", wxTextCtrl);")
                code.append(f"{indent}// if (ctrl) {member_var} = ctrl->GetValue();")
            elif 'Check' in ddx_type:
                code.append(f"{indent}// wxCheckBox* ctrl = XRCCTRL(*this, \"{ctrl_id}\", wxCheckBox);")
                code.append(f"{indent}// if (ctrl) {member_var} = ctrl->GetValue();")
            
            code.append("")
    else:
        code.append(f"{indent}// TODO: Implement data extraction from controls to member variables")
    
    code.append(f"{indent}return true;")
    code.append("}")
    
    return '\n'.join(code)

def generate_infrastructure(analysis_result):
    """Generate Phase 2.5 infrastructure code"""
    
    class_name = analysis_result['class_name']
    
    print(f"Generating Phase 2.5 infrastructure for {class_name}")
    print("=" * 70)
    print()
    
    # Generate OnInitDialog
    if analysis_result['oninitdialog']:
        init_body = analysis_result['oninitdialog']['body']
        init_handler = generate_init_dialog_handler(class_name, init_body)
        
        print("// ============================================================================")
        print("// Phase 2.5: OnInitDialog → wxEVT_INIT_DIALOG")
        print("// ============================================================================")
        print()
        print(init_handler)
        print()
    
    # Generate TransferDataToWindow
    ddx = analysis_result['dodataexchange']
    ddx_data = ddx['ddx_data'] if ddx else []
    members = analysis_result['members']
    
    print("// ============================================================================")
    print("// Phase 2.5: DoDataExchange → TransferDataToWindow")
    print("// ============================================================================")
    print()
    print(generate_transfer_to_window(class_name, members, ddx_data))
    print()
    
    # Generate TransferDataFromWindow
    print("// ============================================================================")
    print("// Phase 2.5: DoDataExchange → TransferDataFromWindow")
    print("// ============================================================================")
    print()
    print(generate_transfer_from_window(class_name, ddx_data))
    print()
    
    # Generate event table entry
    print("// ============================================================================")
    print("// Phase 2.5: Add to event table")
    print("// ============================================================================")
    print()
    print("wxBEGIN_EVENT_TABLE({}, {}Base)".format(class_name, class_name))
    print("    EVT_INIT_DIALOG({}::OnInitDialog)  // Phase 2.5: Initialization".format(class_name))
    print("    // ... Phase 2 event handlers ...")
    print("wxEND_EVENT_TABLE()")
    print()
    
    # Generate constructor signature
    if analysis_result['ctor_params']:
        print("// ============================================================================")
        print("// Phase 2.5: Updated constructor with business object")
        print("// ============================================================================")
        print()
        print(f"{class_name}::{class_name}(wxWindow *parent, {analysis_result['ctor_params'][0]})")
        print(f"    : {class_name}Base(parent)")
        
        # Extract parameter name
        param = analysis_result['ctor_params'][0]
        param_name = param.split()[-1].lstrip('*')
        print(f"    , {param_name}({param_name})  // Business object reference")
        print("{")
        print("    Centre();")
        print("}")
        print()

if __name__ == '__main__':
    # This script is meant to be used with analyze_mfc_dialog.py output
    # For now, just demonstrate the concept
    
    if len(sys.argv) < 4:
        print("Usage: generate_phase25_infrastructure.py <cpp_file> <h_file> <class_name>")
        print()
        print("This script analyzes MFC dialog and generates Phase 2.5 infrastructure.")
        sys.exit(1)
    
    # Import analysis script
    sys.path.insert(0, str(Path(__file__).parent))
    from analyze_mfc_dialog import analyze_dialog
    
    cpp_file = Path(sys.argv[1])
    h_file = Path(sys.argv[2])
    class_name = sys.argv[3]
    
    result = analyze_dialog(cpp_file, h_file, class_name)
    
    if result:
        print()
        print()
        generate_infrastructure(result)
