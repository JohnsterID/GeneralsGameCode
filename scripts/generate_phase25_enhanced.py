#!/usr/bin/env python3
"""
Enhanced Phase 2.5 Infrastructure Generator

Uses pattern database for intelligent MFC → wxWidgets conversion.
"""

import re
import sys
from pathlib import Path

# Import pattern conversion
sys.path.insert(0, str(Path(__file__).parent))
from analyze_mfc_dialog import analyze_dialog
from mfc_to_wx_patterns import convert_mfc_line, detect_required_includes, map_control_ids_to_members

def convert_oninitdialog_body(init_body, control_mappings, class_name):
    """Convert OnInitDialog body using pattern database"""
    
    lines = []
    lines.append(f"void {class_name}::OnInitDialog(wxInitDialogEvent& event)")
    lines.append("{")
    lines.append("    // Initialize controls after they're created")
    
    # Process each line of the MFC OnInitDialog
    for line in init_body.split('\n'):
        line_stripped = line.strip()
        
        # Skip empty lines and base class calls
        if not line_stripped or 'CDialog::OnInitDialog' in line or 'CPropertyPage::OnInitDialog' in line:
            continue
        
        # Preserve comments
        if line_stripped.startswith('//'):
            lines.append(f"    {line_stripped}")
            continue
        
        # Try pattern conversion
        wx_code = convert_mfc_line(line_stripped, control_mappings)
        if wx_code:
            # Indent the converted code
            for wx_line in wx_code.split('\n'):
                lines.append(f"    {wx_line}")
        else:
            # Fallback: preserve as TODO
            if line_stripped and not line_stripped.endswith('{') and not line_stripped == '}':
                lines.append(f"    // TODO: Convert: {line_stripped}")
    
    lines.append("")
    lines.append("    event.Skip();")
    lines.append("}")
    
    return '\n'.join(lines)

def extract_onok_logic(cpp_content, class_name):
    """Extract logic from OnOK for TransferDataFromWindow"""
    
    pattern = rf'void\s+{class_name}::OnOK\s*\([^)]*\)\s*{{(.*?)^}}'
    match = re.search(pattern, cpp_content, re.MULTILINE | re.DOTALL)
    
    if not match:
        return None
    
    body = match.group(1).strip()
    
    # Extract lines that aren't base class calls
    logic_lines = []
    for line in body.split('\n'):
        line_stripped = line.strip()
        if line_stripped and not 'CDialog::OnOK' in line and not 'EndModal' in line:
            logic_lines.append(line_stripped)
    
    return logic_lines

def generate_transfer_from_window(class_name, onok_logic, control_mappings):
    """Generate TransferDataFromWindow from OnOK logic"""
    
    lines = []
    lines.append(f"bool {class_name}::TransferDataFromWindow()")
    lines.append("{")
    lines.append("    // Extract data from controls and apply to business logic")
    lines.append("")
    
    if onok_logic:
        for line in onok_logic:
            # Try pattern conversion
            wx_code = convert_mfc_line(line, control_mappings)
            if wx_code:
                for wx_line in wx_code.split('\n'):
                    lines.append(f"    {wx_line}")
            else:
                lines.append(f"    // TODO: Convert: {line}")
    else:
        lines.append("    // TODO: Extract data from controls")
    
    lines.append("")
    lines.append("    return true;")
    lines.append("}")
    
    return '\n'.join(lines)

def detect_spinner_notify_handler(cpp_content, class_name):
    """Detect if OnNotify handles spinner (UDN_DELTAPOS)"""
    
    pattern = rf'{class_name}::OnNotify.*?UDN_DELTAPOS'
    return bool(re.search(pattern, cpp_content, re.DOTALL))

def generate_enhanced_infrastructure(cpp_file, h_file, wx_h_file, class_name):
    """Generate enhanced Phase 2.5 infrastructure"""
    
    # Analyze MFC dialog
    analysis = analyze_dialog(cpp_file, h_file, class_name)
    if not analysis:
        return None
    
    cpp_content = cpp_file.read_text()
    h_content = h_file.read_text()
    
    # Build MFC → wx member variable mapping
    # Step 1: Get MFC member → Control ID from DDX_Control
    mfc_to_ctrl_id = {}
    if analysis['dodataexchange']:
        for ddx in analysis['dodataexchange']['ddx_controls']:
            ctrl_id = ddx['control_id']
            mfc_member = ddx['member_var']
            mfc_to_ctrl_id[mfc_member] = ctrl_id
    
    # Step 2: Get Control ID → wx member from XRCCTRL
    ctrl_id_to_wx = {}
    if wx_h_file and wx_h_file.exists():
        wx_h_content = wx_h_file.read_text()
        ctrl_id_to_wx = map_control_ids_to_members(wx_h_content)
    
    # Step 3: Combine: MFC member → wx member
    mfc_to_wx_member = {}
    for mfc_member, ctrl_id in mfc_to_ctrl_id.items():
        if ctrl_id in ctrl_id_to_wx:
            mfc_to_wx_member[mfc_member] = ctrl_id_to_wx[ctrl_id]
    
    print(f"Generating enhanced Phase 2.5 for {class_name}")
    print("=" * 70)
    print(f"Control ID mappings: {len(ctrl_id_to_wx)} controls")
    print(f"MFC → wx member mappings: {len(mfc_to_wx_member)} controls")
    if mfc_to_wx_member:
        print("  Sample mappings:")
        for mfc_m, wx_m in list(mfc_to_wx_member.items())[:3]:
            print(f"    {mfc_m:25} → {wx_m}")
    print()
    
    all_code = []
    
    # Generate OnInitDialog
    if analysis['oninitdialog']:
        init_code = convert_oninitdialog_body(
            analysis['oninitdialog']['body'],
            mfc_to_wx_member,
            class_name
        )
        all_code.append("// ============================================================================")
        all_code.append("// Phase 2.5: OnInitDialog → wxEVT_INIT_DIALOG")
        all_code.append("// ============================================================================")
        all_code.append("")
        all_code.append(init_code)
        all_code.append("")
    
    # Generate TransferDataToWindow
    all_code.append("// ============================================================================")
    all_code.append("// Phase 2.5: TransferDataToWindow")
    all_code.append("// ============================================================================")
    all_code.append("")
    all_code.append(f"bool {class_name}::TransferDataToWindow()")
    all_code.append("{")
    all_code.append("    // Data is transferred in OnInitDialog for this dialog")
    all_code.append("    return true;")
    all_code.append("}")
    all_code.append("")
    
    # Generate TransferDataFromWindow from OnOK logic
    onok_logic = extract_onok_logic(cpp_content, class_name)
    transfer_from_code = generate_transfer_from_window(class_name, onok_logic, mfc_to_wx_member)
    all_code.append("// ============================================================================")
    all_code.append("// Phase 2.5: TransferDataFromWindow")
    all_code.append("// ============================================================================")
    all_code.append("")
    all_code.append(transfer_from_code)
    all_code.append("")
    
    # Detect spinner handler
    has_spinner = detect_spinner_notify_handler(cpp_content, class_name)
    if has_spinner:
        all_code.append("// ============================================================================")
        all_code.append("// Phase 2.5: Spinner Event Handler")
        all_code.append("// ============================================================================")
        all_code.append("")
        all_code.append(f"void {class_name}::OnSpinButton(wxSpinEvent& event)")
        all_code.append("{")
        all_code.append("    // TODO: Update buddy control from spinner")
        all_code.append("    // if (m_spin_ctrl && m_edit_ctrl) {")
        all_code.append("    //     m_edit_ctrl->SetValue(wxString::Format(\"%d\", m_spin_ctrl->GetValue()));")
        all_code.append("    // }")
        all_code.append("}")
        all_code.append("")
    
    # Generate event table entries
    all_code.append("// ============================================================================")
    all_code.append("// Phase 2.5: Event Table Additions")
    all_code.append("// ============================================================================")
    all_code.append("")
    all_code.append("// Add to event table:")
    all_code.append(f"//   EVT_INIT_DIALOG({class_name}::OnInitDialog)")
    if has_spinner:
        all_code.append(f"//   EVT_SPIN(XRCID(\"IDC_..._SPIN\"), {class_name}::OnSpinButton)")
    all_code.append("")
    
    # Detect required includes
    full_code = '\n'.join(all_code)
    required_includes = detect_required_includes(full_code)
    
    if required_includes:
        all_code.insert(0, "// ============================================================================")
        all_code.insert(1, "// Phase 2.5: Required Includes")
        all_code.insert(2, "// ============================================================================")
        all_code.insert(3, "")
        for inc in required_includes:
            all_code.insert(4, inc)
        all_code.insert(4 + len(required_includes), "")
    
    return '\n'.join(all_code)

if __name__ == '__main__':
    if len(sys.argv) < 4:
        print("Usage: generate_phase25_enhanced.py <mfc_cpp> <mfc_h> <class_name> [wx_h_file]")
        print()
        print("Example:")
        print("  python3 generate_phase25_enhanced.py \\")
        print("    /tmp/CameraDistanceDialog.cpp \\")
        print("    /tmp/CameraDistanceDialog.h \\")
        print("    CameraDistanceDialogClass \\")
        print("    Core/Tools/W3DView/dialogs/CameraDistance_wx.h")
        sys.exit(1)
    
    cpp_file = Path(sys.argv[1])
    h_file = Path(sys.argv[2])
    class_name = sys.argv[3]
    wx_h_file = Path(sys.argv[4]) if len(sys.argv) > 4 else None
    
    code = generate_enhanced_infrastructure(cpp_file, h_file, wx_h_file, class_name)
    
    if code:
        print(code)
