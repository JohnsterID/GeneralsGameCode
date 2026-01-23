#!/usr/bin/env python3
"""
fix_phase2_notify_events.py - Fix Phase 2 ON_NOTIFY event handlers

This script fixes the 'various &event' bug by mapping MFC ON_NOTIFY
notification codes to proper wxWidgets event types.

MFC Notification Code → wxWidgets Event Mapping:
- UDN_DELTAPOS (spin control) → EVT_SPINCTRL, wxSpinEvent
- NM_DBLCLK (double-click) → EVT_LIST_ITEM_ACTIVATED, wxListEvent  
- LVN_ITEMCHANGED (list selection) → EVT_LIST_ITEM_SELECTED, wxListEvent
- TVN_SELCHANGED (tree selection) → EVT_TREE_SEL_CHANGED, wxTreeEvent
- NM_RELEASEDCAPTURE (slider) → EVT_SLIDER, wxCommandEvent
- LVN_KEYDOWN (list key) → EVT_LIST_KEY_DOWN, wxListEvent
"""

import re
import sys
from pathlib import Path

# Notification code to wxWidgets event mapping
NOTIFY_CODE_MAP = {
    'UDN_DELTAPOS': {
        'wx_event': 'EVT_SPIN',
        'event_type': 'wxSpinEvent',
        'comment': 'Spin button change'
    },
    'NM_DBLCLK': {
        'wx_event': 'EVT_LIST_ITEM_ACTIVATED',  # Default to list, check control type
        'event_type': 'wxListEvent',
        'comment': 'List item double-click'
    },
    'LVN_ITEMCHANGED': {
        'wx_event': 'EVT_LIST_ITEM_SELECTED',
        'event_type': 'wxListEvent',
        'comment': 'List item selection changed'
    },
    'TVN_SELCHANGED': {
        'wx_event': 'EVT_TREE_SEL_CHANGED',
        'event_type': 'wxTreeEvent',
        'comment': 'Tree item selection changed'
    },
    'NM_RELEASEDCAPTURE': {
        'wx_event': 'EVT_SLIDER',
        'event_type': 'wxCommandEvent',
        'comment': 'Slider capture released'
    },
    'LVN_KEYDOWN': {
        'wx_event': 'EVT_LIST_KEY_DOWN',
        'event_type': 'wxListEvent',
        'comment': 'List key press'
    },
}


def parse_mfc_notify(mfc_file):
    """Parse MFC file to extract ON_NOTIFY entries with notification codes"""
    with open(mfc_file, 'r') as f:
        content = f.read()
    
    # Find message map
    map_match = re.search(
        r'BEGIN_MESSAGE_MAP.*?END_MESSAGE_MAP\(\)',
        content,
        re.DOTALL
    )
    
    if not map_match:
        return []
    
    map_content = map_match.group(0)
    
    # Parse ON_NOTIFY entries
    # Pattern: ON_NOTIFY(NOTIFY_CODE, CONTROL_ID, HandlerName)
    pattern = r'ON_NOTIFY\s*\(\s*(\w+)\s*,\s*(\w+)\s*,\s*(\w+)\s*\)'
    
    entries = []
    for match in re.finditer(pattern, map_content):
        notify_code = match.group(1)
        control_id = match.group(2)
        handler = match.group(3)
        
        entries.append({
            'notify_code': notify_code,
            'control_id': control_id,
            'handler': handler
        })
    
    return entries


def fix_dialog_files(dialog_base, mfc_file):
    """Fix both .h and .cpp files for a dialog"""
    wx_h_file = Path(f"Core/Tools/W3DView/dialogs/{dialog_base}_wx.h")
    wx_cpp_file = Path(f"Core/Tools/W3DView/dialogs/{dialog_base}_wx.cpp")
    
    if not wx_h_file.exists() or not wx_cpp_file.exists():
        print(f"  ⚠ Skipping {dialog_base} - files not found")
        return False
    
    # Parse MFC notification codes
    mfc_path = Path(f"Core/Tools/W3DView/{mfc_file}")
    if not mfc_path.exists():
        print(f"  ⚠ MFC file not found: {mfc_path}")
        return False
    
    notify_entries = parse_mfc_notify(mfc_path)
    if not notify_entries:
        print(f"  ℹ No ON_NOTIFY entries found in {mfc_file}")
        return False
    
    print(f"  Found {len(notify_entries)} ON_NOTIFY entries")
    
    # Create mapping of handler name to correct event type
    handler_map = {}
    event_macro_map = {}
    
    for entry in notify_entries:
        notify_code = entry['notify_code']
        handler = entry['handler']
        control_id = entry['control_id']
        
        if notify_code in NOTIFY_CODE_MAP:
            mapping = NOTIFY_CODE_MAP[notify_code]
            handler_map[handler] = mapping['event_type']
            event_macro_map[control_id] = {
                'handler': handler,
                'wx_event': mapping['wx_event'],
                'comment': mapping['comment']
            }
            print(f"    {handler}: various → {mapping['event_type']}")
    
    # Fix .h file
    with open(wx_h_file, 'r') as f:
        h_content = f.read()
    
    h_modified = False
    for handler, event_type in handler_map.items():
        # Replace: void HandlerName(various &event);
        # With: void HandlerName(wxEventType &event);
        old_pattern = rf'void {handler}\s*\(\s*various\s*&\s*event\s*\)\s*;'
        new_decl = f'void {handler}({event_type} &event);'
        
        new_content = re.sub(old_pattern, new_decl, h_content)
        if new_content != h_content:
            h_content = new_content
            h_modified = True
    
    if h_modified:
        with open(wx_h_file, 'w') as f:
            f.write(h_content)
        print(f"  ✅ Fixed {wx_h_file.name}")
    
    # Fix .cpp file
    with open(wx_cpp_file, 'r') as f:
        cpp_content = f.read()
    
    cpp_modified = False
    
    # Fix handler implementations
    for handler, event_type in handler_map.items():
        # Replace: void DialogClass::HandlerName(various &event)
        old_pattern = rf'void\s+\w+::{handler}\s*\(\s*various\s*&\s*event\s*\)'
        new_impl = f'void {dialog_base}::{handler}({event_type} &event)'
        
        new_content = re.sub(old_pattern, new_impl, cpp_content)
        if new_content != cpp_content:
            cpp_content = new_content
            cpp_modified = True
    
    # Fix event table macros
    for control_id, mapping in event_macro_map.items():
        handler = mapping['handler']
        wx_event = mapping['wx_event']
        comment = mapping['comment']
        
        # Replace: EVT_TREE_SEL_CHANGED(XRCID("..."), ...)
        # With: EVT_SPINCTRL(XRCID("..."), ...) etc.
        
        # Pattern: any event macro for this control
        old_pattern = rf'EVT_\w+\s*\(\s*XRCID\s*\(\s*"{control_id}"\s*\)\s*,\s*{dialog_base}::{handler}\s*\)\s*//[^\n]*'
        new_macro = f'{wx_event}(XRCID("{control_id}"), {dialog_base}::{handler})  // {comment}'
        
        new_content = re.sub(old_pattern, new_macro, cpp_content)
        if new_content != cpp_content:
            cpp_content = new_content
            cpp_modified = True
    
    if cpp_modified:
        with open(wx_cpp_file, 'w') as f:
            f.write(cpp_content)
        print(f"  ✅ Fixed {wx_cpp_file.name}")
    
    return h_modified or cpp_modified


# Dialog name to MFC file mapping (for dialogs with ON_NOTIFY issues)
DIALOGS_TO_FIX = {
    'BackgroundObject': 'BackgroundObjectDialog.cpp',
    'BoneManagement': 'BoneMgrDialog.cpp',
    'EditLod': 'EditLODDialog.cpp',
    'GammaDialog': 'GammaDialog.cpp',
    'PropPageEmitterColor': 'EmitterColorPropPage.cpp',
    'PropPageHierarchy': 'HierarchyPropPage.cpp',
    'Resolution': 'ResolutionDialog.cpp',
    'TextureManagment': 'TextureMgrDialog.cpp',
}


def main():
    print("=" * 70)
    print("Phase 2 ON_NOTIFY Event Handler Fix")
    print("=" * 70)
    print()
    print("Fixing 'various &event' bug in Phase 2 generated dialogs...")
    print()
    
    fixed_count = 0
    failed_count = 0
    
    for dialog_base, mfc_file in DIALOGS_TO_FIX.items():
        print(f"Processing {dialog_base}...")
        try:
            if fix_dialog_files(dialog_base, mfc_file):
                fixed_count += 1
            else:
                failed_count += 1
        except Exception as e:
            print(f"  ❌ Error: {e}")
            failed_count += 1
        print()
    
    print("=" * 70)
    print(f"✅ Fixed: {fixed_count} dialogs")
    print(f"❌ Failed/Skipped: {failed_count} dialogs")
    print("=" * 70)
    print()
    print("Next step: Compile to verify fixes")
    print()


if __name__ == '__main__':
    main()
