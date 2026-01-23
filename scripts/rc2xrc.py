#!/usr/bin/env python3
"""
RC to XRC Converter - v4 with escaped quote support
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
    'ICON': 'wxStaticBitmap',
}

CUSTOM_CONTROL_MAP = {
    'msctls_trackbar32': 'wxSlider',
    'Static': 'wxStaticText',
    'Button': 'wxCheckBox',
    'SysTreeView32': 'wxTreeCtrl',
    'SysListView32': 'wxListCtrl',
    'SysTabControl32': 'wxNotebook',
    'msctls_progress32': 'wxGauge',
    'msctls_updown32': 'wxSpinButton',
    'RichEdit20A': 'wxTextCtrl',
    'RichEdit20W': 'wxTextCtrl',
}

def join_continuation_lines(text):
    """Join lines that are continuations (indented lines after control statements)"""
    lines = text.split('\n')
    result = []
    i = 0
    
    while i < len(lines):
        line = lines[i]
        
        # Check if this is a control statement
        if re.match(r'^\s*(CONTROL|LTEXT|RTEXT|CTEXT|PUSHBUTTON|DEFPUSHBUTTON|EDITTEXT|CHECKBOX|RADIOBUTTON|GROUPBOX|COMBOBOX|LISTBOX|ICON)\s+', line):
            combined = line
            i += 1
            
            # Collect continuation lines
            while i < len(lines):
                next_line = lines[i]
                # Heavily indented continuation or comma at end of previous line
                if (re.match(r'^\s{16,}', next_line) or combined.rstrip().endswith(',')) and \
                   not re.match(r'^\s*(CONTROL|LTEXT|RTEXT|CTEXT|PUSHBUTTON|DEFPUSHBUTTON|EDITTEXT|CHECKBOX|RADIOBUTTON|GROUPBOX|COMBOBOX|LISTBOX|ICON|END)\s+', next_line):
                    combined += ' ' + next_line.strip()
                    i += 1
                else:
                    break
            
            result.append(combined)
        else:
            result.append(line)
            i += 1
    
    return '\n'.join(result)

def extract_quoted_string(text, start_pos):
    """
    Extract a quoted string from text starting at start_pos.
    Handles escaped quotes ("").
    Returns (extracted_text, end_pos) or (None, start_pos) if not found.
    """
    if start_pos >= len(text) or text[start_pos] != '"':
        return None, start_pos
    
    result = []
    i = start_pos + 1  # Skip opening quote
    
    while i < len(text):
        if text[i] == '"':
            # Check if it's an escaped quote
            if i + 1 < len(text) and text[i + 1] == '"':
                # Escaped quote - add single quote to result
                result.append('"')
                i += 2
            else:
                # End of string
                return ''.join(result), i + 1
        else:
            result.append(text[i])
            i += 1
    
    # Unclosed quote
    return None, start_pos

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
    pattern = rf'^{dialog_id}\s+DIALOG(?:EX)?\s+(?:DISCARDABLE\s+)?(-?\d+)\s*,\s*(-?\d+)\s*,\s*(-?\d+)\s*,\s*(-?\d+)'
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
    
    # Join continuation lines BEFORE parsing
    dialog_block = join_continuation_lines(dialog_block)
    
    # Extract caption
    cap_match = re.search(r'CAPTION\s+"([^"]*)"', dialog_block)
    if cap_match:
        dialog.title = cap_match.group(1)
    
    # Parse controls with custom string extraction for escaped quotes
    # Process line by line
    for line in dialog_block.split('\n'):
        line = line.strip()
        if not line or line.startswith('//'):
            continue
        
        # Try ICON first (no quotes)
        # Match valid ID (numeric or identifier), not greedy to stop at comma
        icon_match = re.match(r'ICON\s+(\w+)\s*,\s*(-?\d+|[a-zA-Z_]\w*)\s*,\s*(-?\d+)\s*,\s*(-?\d+)\s*,\s*(-?\d+)\s*,\s*(-?\d+)', line)
        if icon_match:
            control = ControlInfo()
            control.type = 'ICON'
            control.text = ""
            control.icon_id = icon_match.group(1)
            control.id = icon_match.group(2)
            control.x = int(icon_match.group(3))
            control.y = int(icon_match.group(4))
            control.width = int(icon_match.group(5))
            control.height = int(icon_match.group(6))
            control.custom_class = None
            dialog.controls.append(control)
            continue
        
        # Try labeled controls (LTEXT, PUSHBUTTON, etc.) with custom string extraction
        for ctrl_type in ['DEFPUSHBUTTON', 'PUSHBUTTON', 'CHECKBOX', 'RADIOBUTTON', 'GROUPBOX', 'LTEXT', 'RTEXT', 'CTEXT']:
            pattern = rf'^{ctrl_type}\s+'
            if re.match(pattern, line):
                # Extract the quoted string manually
                quote_start = line.find('"')
                if quote_start == -1:
                    break
                
                text, quote_end = extract_quoted_string(line, quote_start)
                if text is None:
                    break
                
                # Parse the rest: ,ID,x,y,w,h
                rest = line[quote_end:].strip()
                # Match valid ID (numeric or identifier), not greedy to stop at comma
                coords_match = re.match(r',\s*(-?\d+|[a-zA-Z_]\w*)\s*,\s*(-?\d+)\s*,\s*(-?\d+)\s*,\s*(-?\d+)\s*,\s*(-?\d+)', rest)
                if coords_match:
                    control = ControlInfo()
                    control.type = ctrl_type
                    control.text = text
                    control.id = coords_match.group(1)
                    control.x = int(coords_match.group(2))
                    control.y = int(coords_match.group(3))
                    control.width = int(coords_match.group(4))
                    control.height = int(coords_match.group(5))
                    control.custom_class = None
                    dialog.controls.append(control)
                    break
        else:
            # Try unlabeled controls
            # Match valid ID (numeric or identifier), not greedy to stop at comma
            unlabeled_match = re.match(r'(EDITTEXT|COMBOBOX|LISTBOX)\s+(-?\d+|[a-zA-Z_]\w*)\s*,\s*(-?\d+)\s*,\s*(-?\d+)\s*,\s*(-?\d+)\s*,\s*(-?\d+)', line)
            if unlabeled_match:
                control = ControlInfo()
                control.type = unlabeled_match.group(1)
                control.text = ""
                control.id = unlabeled_match.group(2)
                control.x = int(unlabeled_match.group(3))
                control.y = int(unlabeled_match.group(4))
                control.width = int(unlabeled_match.group(5))
                control.height = int(unlabeled_match.group(6))
                control.custom_class = None
                dialog.controls.append(control)
                continue
            
            # Try CONTROL with text
            if line.startswith('CONTROL'):
                quote_start = line.find('"')
                if quote_start != -1:
                    text, quote_end = extract_quoted_string(line, quote_start)
                    if text is not None:
                        rest = line[quote_end:].strip()
                        # CONTROL "text",ID,"ClassName",styles,x,y,w,h
                        # Match valid ID (numeric or identifier), not greedy to stop at comma
                        control_match = re.match(r',\s*(-?\d+|[a-zA-Z_]\w*)\s*,\s*"([^"]+)"\s*,\s*[^,]+?\s*,\s*(-?\d+)\s*,\s*(-?\d+)\s*,\s*(-?\d+)\s*,\s*(-?\d+)', rest)
                        if control_match:
                            control = ControlInfo()
                            control.type = 'CONTROL'
                            control.text = text
                            control.id = control_match.group(1)
                            control.custom_class = control_match.group(2)
                            control.x = int(control_match.group(3))
                            control.y = int(control_match.group(4))
                            control.width = int(control_match.group(5))
                            control.height = int(control_match.group(6))
                            dialog.controls.append(control)
                            continue
                
                # Try CONTROL with numeric ID (bitmap)
                # Match valid ID (numeric or identifier), not greedy to stop at comma
                bitmap_match = re.match(r'CONTROL\s+(-?\d+)\s*,\s*(-?\d+|[a-zA-Z_]\w*)\s*,\s*"([^"]+)"\s*,\s*[^,]+?\s*,\s*(-?\d+)\s*,\s*(-?\d+)\s*,\s*(-?\d+)\s*,\s*(-?\d+)', line)
                if bitmap_match:
                    control = ControlInfo()
                    control.type = 'CONTROL'
                    control.text = ""
                    control.bitmap_id = bitmap_match.group(1)
                    control.id = bitmap_match.group(2)
                    control.custom_class = bitmap_match.group(3)
                    control.x = int(bitmap_match.group(4))
                    control.y = int(bitmap_match.group(5))
                    control.width = int(bitmap_match.group(6))
                    control.height = int(bitmap_match.group(7))
                    dialog.controls.append(control)
                    continue
    
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
            if ctrl.custom_class == 'Static':
                if hasattr(ctrl, 'bitmap_id'):
                    wx_type = 'wxStaticBitmap'
                elif not ctrl.text:
                    wx_type = 'wxPanel'
        elif ctrl.type == 'ICON':
            wx_type = 'wxStaticBitmap'
        else:
            wx_type = CONTROL_MAP.get(ctrl.type, 'wxControl')
        
        cw = dlu_to_px(ctrl.width)
        ch = dlu_to_px(ctrl.height)
        
        lines.append('      <object class="sizeritem">')
        lines.append('        <flag>wxALL</flag>')
        lines.append('        <border>5</border>')
        lines.append(f'        <object class="{wx_type}" name="{ctrl.id}">')
        
        if ctrl.text:
            # Escape XML special characters
            text = ctrl.text.replace('&', '&amp;').replace('<', '&lt;').replace('>', '&gt;')
            lines.append(f'          <label>{text}</label>')
        
        lines.append(f'          <size>{cw},{ch}</size>')
        
        # Add style hints
        if wx_type == 'wxSlider':
            lines.append('          <style>wxSL_HORIZONTAL</style>')
        elif wx_type == 'wxTextCtrl' and ctrl.type == 'EDITTEXT':
            lines.append('          <style>wxTE_LEFT</style>')
        elif wx_type == 'wxSpinButton':
            lines.append('          <style>wxSP_VERTICAL|wxSP_ARROW_KEYS</style>')
        
        lines.append('        </object>')
        lines.append('      </object>')
    
    lines.append('    </object>')
    lines.append('  </object>')
    lines.append('</resource>')
    
    return '\n'.join(lines)

def main():
    if len(sys.argv) < 3:
        print("Usage: rc2xrc_v4.py <input.rc> <dialog_id> [output.xrc]")
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
        if ctrl.type == 'CONTROL':
            ctype = ctrl.custom_class
        elif ctrl.type == 'ICON':
            ctype = 'ICON'
        else:
            ctype = ctrl.type
        control_types[ctype] = control_types.get(ctype, 0) + 1
    
    print(f"✅ Converted {dialog_id}")
    print(f"   Size: {dialog.width}x{dialog.height} DLU → {int(dialog.width*1.5)}x{int(dialog.height*1.5)} px")
    print(f"   Controls: {len(dialog.controls)}")
    if control_types:
        print(f"   Types: {', '.join(f'{k}:{v}' for k,v in sorted(control_types.items()))}")
    print(f"   Output: {out_file}")

if __name__ == "__main__":
    main()
