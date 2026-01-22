#!/usr/bin/env python3
"""
RC to XRC Converter v2 - Enhanced with CONTROL statement support
"""

import re
import sys
from pathlib import Path

CONTROL_MAP = {
    'PUSHBUTTON': 'wxButton',
    'DEFPUSHBUTTON': 'wxButton',
    'EDITTEXT': 'wxTextCtrl',
    'LTEXT': 'wxStaticText',
    'RTEXT': 'wxStaticText',
    'CTEXT': 'wxStaticText',
    'GROUPBOX': 'wxStaticBox',
    'CHECKBOX': 'wxCheckBox',
    'RADIOBUTTON': 'wxRadioButton',
    'COMBOBOX': 'wxComboBox',
    'LISTBOX': 'wxListBox',
    'SCROLLBAR': 'wxScrollBar',
}

# Map MFC custom control classes to wxWidgets
CUSTOM_CONTROL_MAP = {
    'msctls_trackbar32': 'wxSlider',
    'Static': 'wxStaticText',  # Generic static control
    'Button': 'wxCheckBox',  # Button with BS_AUTOCHECKBOX style
    'SysTreeView32': 'wxTreeCtrl',
    'SysListView32': 'wxListCtrl',
    'SysTabControl32': 'wxNotebook',
    'msctls_progress32': 'wxGauge',
    'msctls_updown32': 'wxSpinButton',
    'RichEdit20A': 'wxTextCtrl',
    'RichEdit20W': 'wxTextCtrl',
}

def parse_rc_dialog(rc_content, dialog_id):
    """Parse a specific dialog from RC content"""
    class DialogInfo:
        pass
    class ControlInfo:
        pass
    
    dialog = DialogInfo()
    dialog.id = dialog_id
    dialog.title = ""
    dialog.controls = []
    
    # Find dialog definition
    pattern = rf'^{dialog_id}\s+DIALOG(?:EX)?\s+(?:DISCARDABLE\s+)?(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)'
    match = re.search(pattern, rc_content, re.MULTILINE)
    
    if not match:
        return None
    
    dialog.x = int(match.group(1))
    dialog.y = int(match.group(2))
    dialog.width = int(match.group(3))
    dialog.height = int(match.group(4))
    
    # Find BEGIN...END block
    start = match.end()
    begin_match = re.search(r'\nBEGIN', rc_content[start:start+200])
    if not begin_match:
        return None
    
    block_start = start + begin_match.end()
    
    # Find matching END
    depth = 1
    pos = block_start
    while depth > 0 and pos < len(rc_content):
        end_match = re.search(r'\b(BEGIN|END)\b', rc_content[pos:])
        if not end_match:
            break
        if end_match.group(1) == 'BEGIN':
            depth += 1
        else:
            depth -= 1
        pos += end_match.end()
        if depth == 0:
            block_end = pos - 3
            break
    else:
        return None
    
    dialog_block = rc_content[block_start:block_end]
    
    # Extract caption
    cap_match = re.search(r'CAPTION\s+"([^"]*)"', dialog_block)
    if cap_match:
        dialog.title = cap_match.group(1)
    
    # Parse controls - enhanced patterns
    patterns = [
        # Standard labeled controls: PUSHBUTTON "OK",IDOK,x,y,w,h
        (r'(DEFPUSHBUTTON|PUSHBUTTON|CHECKBOX|RADIOBUTTON|GROUPBOX|LTEXT|RTEXT|CTEXT)\s+"([^"]*)"\s*,\s*(\w+)\s*,\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)', 'labeled'),
        # Unlabeled controls: EDITTEXT ID,x,y,w,h
        (r'(EDITTEXT|COMBOBOX|LISTBOX)\s+(\w+)\s*,\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)', 'unlabeled'),
        # CONTROL with class: CONTROL "text",ID,"ClassName",style,x,y,w,h
        (r'CONTROL\s+"([^"]*)"\s*,\s*(\w+)\s*,\s*"([^"]*)"\s*,\s*[^,]+\s*,\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)', 'control_class'),
    ]
    
    for pattern, ptype in patterns:
        for m in re.finditer(pattern, dialog_block):
            control = ControlInfo()
            if ptype == 'labeled':
                control.type = m.group(1)
                control.text = m.group(2)
                control.id = m.group(3)
                control.x = int(m.group(4))
                control.y = int(m.group(5))
                control.width = int(m.group(6))
                control.height = int(m.group(7))
                control.custom_class = None
            elif ptype == 'unlabeled':
                control.type = m.group(1)
                control.text = ""
                control.id = m.group(2)
                control.x = int(m.group(3))
                control.y = int(m.group(4))
                control.width = int(m.group(5))
                control.height = int(m.group(6))
                control.custom_class = None
            elif ptype == 'control_class':
                control.type = 'CONTROL'
                control.text = m.group(1)
                control.id = m.group(2)
                control.custom_class = m.group(3)
                control.x = int(m.group(4))
                control.y = int(m.group(5))
                control.width = int(m.group(6))
                control.height = int(m.group(7))
            
            dialog.controls.append(control)
    
    return dialog

def generate_xrc(dialog):
    """Generate XRC from dialog"""
    def dlu_to_px(dlu):
        return int(dlu * 1.5)
    
    w = dlu_to_px(dialog.width)
    h = dlu_to_px(dialog.height)
    
    lines = [
        '<?xml version="1.0" encoding="UTF-8"?>',
        '<resource xmlns="http://www.wxwidgets.org/wxxrc" version="2.5.3.0">',
        f'  <object class="wxDialog" name="{dialog.id}">',
        '    <style>wxDEFAULT_DIALOG_STYLE</style>',
        f'    <size>{w},{h}</size>',
    ]
    
    if dialog.title:
        lines.append(f'    <title>{dialog.title}</title>')
    
    lines.append('    <object class="wxBoxSizer">')
    lines.append('      <orient>wxVERTICAL</orient>')
    
    for ctrl in dialog.controls:
        # Determine wx control type
        if ctrl.type == 'CONTROL' and ctrl.custom_class:
            wx_type = CUSTOM_CONTROL_MAP.get(ctrl.custom_class, 'wxPanel')
            # Special handling for Static with SS_BLACKFRAME (gradient displays)
            if ctrl.custom_class == 'Static' and not ctrl.text:
                wx_type = 'wxPanel'  # Empty static = colored panel
        else:
            wx_type = CONTROL_MAP.get(ctrl.type, 'wxControl')
        
        cw = dlu_to_px(ctrl.width)
        ch = dlu_to_px(ctrl.height)
        
        lines.append('      <object class="sizeritem">')
        lines.append('        <flag>wxALL</flag>')
        lines.append('        <border>5</border>')
        lines.append(f'        <object class="{wx_type}" name="{ctrl.id}">')
        
        if ctrl.text:
            lines.append(f'          <label>{ctrl.text}</label>')
        
        lines.append(f'          <size>{cw},{ch}</size>')
        
        # Add style hints based on control type
        if wx_type == 'wxSlider':
            lines.append('          <style>wxSL_HORIZONTAL</style>')
        elif wx_type == 'wxTextCtrl' and ctrl.type == 'EDITTEXT':
            lines.append('          <style>wxTE_LEFT</style>')
        
        lines.append('        </object>')
        lines.append('      </object>')
    
    lines.append('    </object>')
    lines.append('  </object>')
    lines.append('</resource>')
    
    return '\n'.join(lines)

def main():
    if len(sys.argv) < 3:
        print("Usage: rc2xrc_v2.py <input.rc> <dialog_id> [output.xrc]")
        sys.exit(1)
    
    rc_file = Path(sys.argv[1])
    dialog_id = sys.argv[2]
    out_file = Path(sys.argv[3]) if len(sys.argv) > 3 else Path(f"{dialog_id.lower()}.xrc")
    
    rc_content = rc_file.read_text(encoding='latin-1')
    dialog = parse_rc_dialog(rc_content, dialog_id)
    
    if not dialog:
        print(f"Error: Dialog {dialog_id} not found")
        sys.exit(1)
    
    xrc = generate_xrc(dialog)
    out_file.write_text(xrc, encoding='utf-8')
    
    # Count control types
    control_types = {}
    for ctrl in dialog.controls:
        ctype = ctrl.custom_class if ctrl.type == 'CONTROL' else ctrl.type
        control_types[ctype] = control_types.get(ctype, 0) + 1
    
    print(f"✅ Converted {dialog_id}")
    print(f"   Size: {dialog.width}x{dialog.height} DLU → {int(dialog.width*1.5)}x{int(dialog.height*1.5)} px")
    print(f"   Controls: {len(dialog.controls)}")
    if control_types:
        print(f"   Types: {', '.join(f'{k}:{v}' for k,v in sorted(control_types.items()))}")
    print(f"   Output: {out_file}")

if __name__ == "__main__":
    main()
