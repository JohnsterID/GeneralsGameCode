#!/usr/bin/env python3
"""
mfc2wx_events.py - Convert MFC message maps to wxWidgets event tables

Version 1: Basic event mapping
- Parse BEGIN_MESSAGE_MAP / END_MESSAGE_MAP
- Map common MFC events to wxWidgets
- Generate event table entries
- Create stub handler methods

Usage:
    python3 scripts/mfc2wx_events.py <mfc_dialog.cpp> <wx_dialog.cpp> <xrc_file>
"""

import sys
import re
import xml.etree.ElementTree as ET
from pathlib import Path

# MFC message map to wxWidgets event mapping
MFC_TO_WX_MAP = {
    'ON_WM_HSCROLL': {
        'wx_event': 'EVT_SLIDER',
        'event_type': 'wxCommandEvent',
        'needs_id': True,
        'comment': 'Horizontal scroll (slider)'
    },
    'ON_WM_VSCROLL': {
        'wx_event': 'EVT_SLIDER',
        'event_type': 'wxCommandEvent',
        'needs_id': True,
        'comment': 'Vertical scroll (slider)'
    },
    'ON_WM_DESTROY': {
        'wx_event': 'EVT_WINDOW_DESTROY',
        'event_type': 'wxWindowDestroyEvent',
        'needs_id': False,
        'comment': 'Window destruction'
    },
    'ON_BN_CLICKED': {
        'wx_event': 'EVT_BUTTON or EVT_CHECKBOX',  # Depends on control type
        'event_type': 'wxCommandEvent',
        'needs_id': True,
        'comment': 'Button/Checkbox click'
    },
    'ON_CBN_SELCHANGE': {
        'wx_event': 'EVT_COMBOBOX',
        'event_type': 'wxCommandEvent',
        'needs_id': True,
        'comment': 'Combobox selection change'
    },
    'ON_LBN_SELCHANGE': {
        'wx_event': 'EVT_LISTBOX',
        'event_type': 'wxCommandEvent',
        'needs_id': True,
        'comment': 'Listbox selection change'
    },
    'ON_EN_CHANGE': {
        'wx_event': 'EVT_TEXT',
        'event_type': 'wxCommandEvent',
        'needs_id': True,
        'comment': 'Text control change'
    },
    'ON_NOTIFY': {
        'wx_event': 'EVT_TREE_SEL_CHANGED or other',
        'event_type': 'various',
        'needs_id': True,
        'comment': 'Notification message (needs analysis)'
    },
}


class MFCMessageMapParser:
    """Parse MFC message maps from .cpp files"""
    
    def __init__(self, mfc_content):
        self.content = mfc_content
        self.class_name = None
        self.entries = []
        self.control_bindings = {}  # DDX_Control bindings
        
    def parse(self):
        """Parse the MFC file and extract message map entries"""
        # Extract class name
        self.class_name = self._extract_class_name()
        
        # Extract control bindings from DoDataExchange
        self.control_bindings = self._extract_control_bindings()
        
        # Extract message map
        self.entries = self._extract_message_map()
        
        return {
            'class_name': self.class_name,
            'entries': self.entries,
            'control_bindings': self.control_bindings
        }
    
    def _extract_class_name(self):
        """Extract the class name from BEGIN_MESSAGE_MAP"""
        pattern = r'BEGIN_MESSAGE_MAP\s*\(\s*(\w+)\s*,'
        match = re.search(pattern, self.content)
        if match:
            return match.group(1)
        return None
    
    def _extract_control_bindings(self):
        """Extract DDX_Control bindings from DoDataExchange"""
        bindings = {}
        
        # Find DoDataExchange function
        pattern = r'DoDataExchange.*?\{(.*?)\n\}'
        match = re.search(pattern, self.content, re.DOTALL)
        
        if not match:
            return bindings
        
        ddx_content = match.group(1)
        
        # Parse DDX_Control lines
        # Example: DDX_Control(pDX, IDC_SPEED_SLIDER, m_speedSlider);
        ddx_pattern = r'DDX_Control\s*\(\s*\w+\s*,\s*(\w+)\s*,\s*(\w+)\s*\)'
        
        for match in re.finditer(ddx_pattern, ddx_content):
            control_id = match.group(1)
            member_var = match.group(2)
            bindings[control_id] = member_var
        
        return bindings
    
    def _extract_message_map(self):
        """Extract all message map entries"""
        # Find the message map block
        pattern = r'BEGIN_MESSAGE_MAP.*?END_MESSAGE_MAP\s*\(\s*\)'
        match = re.search(pattern, self.content, re.DOTALL)
        
        if not match:
            return []
        
        map_content = match.group(0)
        entries = []
        
        # Parse each line in the message map
        for line in map_content.split('\n'):
            line = line.strip()
            
            # Skip comments and empty lines
            if not line or line.startswith('//') or 'AFX_MSG_MAP' in line:
                continue
            
            # Skip BEGIN and END lines
            if 'BEGIN_MESSAGE_MAP' in line or 'END_MESSAGE_MAP' in line:
                continue
            
            # Parse ON_xxx macros
            entry = self._parse_map_entry(line)
            if entry:
                entries.append(entry)
        
        return entries
    
    def _parse_map_entry(self, line):
        """Parse a single message map entry"""
        # Pattern for window messages (no parameters)
        # Example: ON_WM_HSCROLL()
        pattern1 = r'(ON_WM_\w+)\s*\(\s*\)'
        match = re.match(pattern1, line)
        if match:
            return {
                'mfc_macro': match.group(1),
                'control_id': None,
                'handler': self._guess_handler_name(match.group(1)),
                'raw': line
            }
        
        # Pattern for control notifications (with control ID and handler)
        # Example: ON_BN_CLICKED(IDC_BLEND, OnBlend)
        pattern2 = r'(ON_\w+)\s*\(\s*(\w+)\s*,\s*(\w+)\s*\)'
        match = re.match(pattern2, line)
        if match:
            return {
                'mfc_macro': match.group(1),
                'control_id': match.group(2),
                'handler': match.group(3),
                'raw': line
            }
        
        # Pattern for ON_NOTIFY (special case with more parameters)
        # Example: ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, OnSelChanged)
        pattern3 = r'ON_NOTIFY\s*\(\s*(\w+)\s*,\s*(\w+)\s*,\s*(\w+)\s*\)'
        match = re.match(pattern3, line)
        if match:
            return {
                'mfc_macro': 'ON_NOTIFY',
                'notify_code': match.group(1),
                'control_id': match.group(2),
                'handler': match.group(3),
                'raw': line
            }
        
        return None
    
    def _guess_handler_name(self, mfc_macro):
        """Guess handler name from MFC macro for window messages"""
        # ON_WM_HSCROLL -> OnHScroll
        if mfc_macro.startswith('ON_WM_'):
            name = mfc_macro[6:]  # Remove ON_WM_
            # Capitalize properly: HSCROLL -> HScroll
            return 'On' + name.capitalize()
        return 'OnUnknown'


class XRCControlAnalyzer:
    """Analyze XRC file to determine control types"""
    
    def __init__(self, xrc_path):
        self.xrc_path = xrc_path
        self.controls = {}
        
    def analyze(self):
        """Parse XRC and build control ID -> type mapping"""
        if not Path(self.xrc_path).exists():
            print(f"Warning: XRC file not found: {self.xrc_path}")
            return {}
        
        try:
            tree = ET.parse(self.xrc_path)
            root = tree.getroot()
            
            # Extract namespace if present
            ns = {'xrc': 'http://www.wxwidgets.org/wxxrc'}
            if '}' in root.tag:
                ns_uri = root.tag.split('}')[0][1:]
                ns = {'xrc': ns_uri}
            
            # Find all objects with names (recursively, since they're nested in sizers)
            # Try both with and without namespace
            for obj in list(root.iter('{%s}object' % ns['xrc'])) + list(root.iter('object')):
                class_name = obj.get('class', '')
                name_attr = obj.get('name', '')
                
                # Some XRC files use name attribute, others use name element
                control_id = name_attr
                
                if not control_id:
                    # Try to find name as child element (with and without namespace)
                    name_elem = obj.find('{%s}name' % ns['xrc'])
                    if name_elem is None:
                        name_elem = obj.find('name')
                    if name_elem is not None:
                        control_id = name_elem.text
                
                if control_id and control_id != 'IDD_DISPLAYSPEED':  # Skip dialog itself
                    self.controls[control_id] = self._map_xrc_to_wx_class(class_name)
            
            return self.controls
        
        except Exception as e:
            print(f"Warning: Could not parse XRC file: {e}")
            import traceback
            traceback.print_exc()
            return {}
    
    def _map_xrc_to_wx_class(self, xrc_class):
        """Map XRC class name to wxWidgets class"""
        mapping = {
            'wxButton': 'wxButton',
            'wxCheckBox': 'wxCheckBox',
            'wxRadioButton': 'wxRadioButton',
            'wxTextCtrl': 'wxTextCtrl',
            'wxComboBox': 'wxComboBox',
            'wxListBox': 'wxListBox',
            'wxSlider': 'wxSlider',
            'wxTreeCtrl': 'wxTreeCtrl',
            'wxListCtrl': 'wxListCtrl',
            'wxSpinCtrl': 'wxSpinCtrl',
        }
        return mapping.get(xrc_class, xrc_class)


class WxEventTableGenerator:
    """Generate wxWidgets event table from MFC message map"""
    
    def __init__(self, mfc_data, xrc_controls):
        self.mfc_data = mfc_data
        self.xrc_controls = xrc_controls
        self.control_bindings = mfc_data.get('control_bindings', {})
        self.wx_class_name = self._derive_wx_class_name()
        
    def _derive_wx_class_name(self):
        """Derive wxWidgets class name from MFC class name"""
        # CAnimationSpeed -> Displayspeed (based on existing pattern)
        # We'll need to look this up from the actual file
        return None  # Will be extracted from existing wx file
    
    def generate(self):
        """Generate event table entries and handler stubs"""
        entries = []
        handlers = []
        
        for entry in self.mfc_data['entries']:
            wx_entry = self._convert_entry(entry)
            if wx_entry:
                entries.append(wx_entry)
                handlers.append(self._generate_handler_stub(entry, wx_entry))
        
        return {
            'entries': entries,
            'handlers': handlers
        }
    
    def _convert_entry(self, entry):
        """Convert a single MFC entry to wxWidgets"""
        mfc_macro = entry['mfc_macro']
        
        if mfc_macro not in MFC_TO_WX_MAP:
            return {
                'type': 'unknown',
                'comment': f"// TODO: Map {mfc_macro} manually",
                'handler': entry['handler'],
                'raw_mfc': entry['raw']
            }
        
        mapping = MFC_TO_WX_MAP[mfc_macro]
        control_id = entry.get('control_id')
        
        # For window messages like ON_WM_HSCROLL, find the slider control ID
        if mfc_macro in ['ON_WM_HSCROLL', 'ON_WM_VSCROLL'] and not control_id:
            control_id = self._find_slider_control()
        
        # Determine actual wxWidgets event based on control type
        wx_event = mapping['wx_event']
        
        if control_id and 'or' in wx_event:
            # Need to check control type
            control_type = self.xrc_controls.get(control_id, 'unknown')
            wx_event = self._resolve_ambiguous_event(wx_event, control_type)
        
        return {
            'type': 'mapped',
            'wx_event': wx_event,
            'event_type': mapping['event_type'],
            'control_id': control_id,
            'handler': entry['handler'],
            'comment': mapping['comment'],
            'needs_id': mapping['needs_id']
        }
    
    def _find_slider_control(self):
        """Find slider control ID from control bindings or XRC"""
        # Look for slider in control bindings (DDX_Control with slider member)
        for control_id, member_var in self.control_bindings.items():
            if 'slider' in member_var.lower():
                return control_id
        
        # Look for slider in XRC controls
        for control_id, control_type in self.xrc_controls.items():
            if 'wxSlider' in control_type:
                return control_id
        
        return None
    
    def _resolve_ambiguous_event(self, wx_event, control_type):
        """Resolve ambiguous events based on control type"""
        if 'wxButton' in control_type:
            return 'EVT_BUTTON'
        elif 'wxCheckBox' in control_type:
            return 'EVT_CHECKBOX'
        elif 'wxRadioButton' in control_type:
            return 'EVT_RADIOBUTTON'
        else:
            return wx_event.split(' or ')[0]  # Take first option
    
    def _generate_handler_stub(self, mfc_entry, wx_entry):
        """Generate handler method stub"""
        if wx_entry['type'] == 'unknown':
            return None
        
        handler_name = mfc_entry['handler']
        event_type = wx_entry.get('event_type', 'wxCommandEvent')
        
        return {
            'name': handler_name,
            'event_type': event_type,
            'comment': wx_entry.get('comment', ''),
            'control_id': mfc_entry.get('control_id')
        }


class WxDialogUpdater:
    """Update existing wxWidgets dialog file with new event handlers"""
    
    def __init__(self, wx_cpp_path):
        self.wx_cpp_path = wx_cpp_path
        self.content = ""
        self.class_name = None
        
    def load(self):
        """Load existing wxWidgets dialog file"""
        with open(self.wx_cpp_path, 'r') as f:
            self.content = f.read()
        
        # Extract class name
        self._extract_class_name()
    
    def _extract_class_name(self):
        """Extract class name from wxBEGIN_EVENT_TABLE"""
        pattern = r'wxBEGIN_EVENT_TABLE\s*\(\s*(\w+)\s*,'
        match = re.search(pattern, self.content)
        if match:
            self.class_name = match.group(1)
    
    def update(self, generated_data):
        """Update event table and add handler stubs"""
        # For now, just generate output - don't modify existing file yet
        return self._generate_output(generated_data)
    
    def _generate_output(self, generated_data):
        """Generate output showing what would be added"""
        output = []
        output.append(f"// Generated event table entries for {self.class_name}\n")
        output.append("// Add these to your wxBEGIN_EVENT_TABLE block:\n")
        
        for entry in generated_data['entries']:
            if entry['type'] == 'unknown':
                output.append(f"    {entry['comment']}\n")
                output.append(f"    // MFC: {entry['raw_mfc']}\n")
            else:
                if entry['needs_id'] and entry['control_id']:
                    output.append(f"    {entry['wx_event']}(XRCID(\"{entry['control_id']}\"), {self.class_name}::{entry['handler']})  // {entry['comment']}\n")
                else:
                    output.append(f"    {entry['wx_event']}({self.class_name}::{entry['handler']})  // {entry['comment']}\n")
        
        output.append("\n// Handler method stubs to add to your class:\n")
        output.append("// In .h file:\n")
        
        for handler in generated_data['handlers']:
            if handler:
                output.append(f"    void {handler['name']}({handler['event_type']} &event);  // {handler['comment']}\n")
        
        output.append("\n// In .cpp file:\n")
        
        for handler in generated_data['handlers']:
            if handler:
                output.append(f"\nvoid {self.class_name}::{handler['name']}({handler['event_type']} &event)\n")
                output.append("{\n")
                output.append(f"    // TODO: Implement {handler['name']}\n")
                if handler['control_id']:
                    output.append(f"    // Control ID: {handler['control_id']}\n")
                output.append("}\n")
        
        return ''.join(output)


def main():
    if len(sys.argv) < 4:
        print("Usage: python3 mfc2wx_events.py <mfc_dialog.cpp> <wx_dialog.cpp> <xrc_file>")
        print()
        print("Example:")
        print("  python3 scripts/mfc2wx_events.py \\")
        print("    /tmp/mfc_dialogs/AnimationSpeed.cpp \\")
        print("    Core/Tools/W3DView/dialogs/Displayspeed_wx.cpp \\")
        print("    Core/Tools/W3DView/ui/idd_displayspeed.xrc")
        sys.exit(1)
    
    mfc_file = sys.argv[1]
    wx_file = sys.argv[2]
    xrc_file = sys.argv[3]
    
    print(f"MFC→wxWidgets Event Conversion Tool v1")
    print(f"=" * 60)
    print(f"MFC file:  {mfc_file}")
    print(f"WX file:   {wx_file}")
    print(f"XRC file:  {xrc_file}")
    print()
    
    # Step 1: Parse MFC message map
    print("[1/4] Parsing MFC message map...")
    with open(mfc_file, 'r') as f:
        mfc_content = f.read()
    
    parser = MFCMessageMapParser(mfc_content)
    mfc_data = parser.parse()
    
    print(f"  Found class: {mfc_data['class_name']}")
    print(f"  Found {len(mfc_data['entries'])} message map entries")
    print(f"  Found {len(mfc_data['control_bindings'])} control bindings (DDX_Control)")
    if mfc_data['control_bindings']:
        for ctrl_id, member in mfc_data['control_bindings'].items():
            print(f"    {ctrl_id} -> {member}")
    
    # Step 2: Analyze XRC controls
    print("[2/4] Analyzing XRC controls...")
    xrc_analyzer = XRCControlAnalyzer(xrc_file)
    xrc_controls = xrc_analyzer.analyze()
    print(f"  Found {len(xrc_controls)} controls in XRC")
    if xrc_controls:
        # Show first few
        for i, (ctrl_id, ctrl_type) in enumerate(list(xrc_controls.items())[:5]):
            print(f"    {ctrl_id}: {ctrl_type}")
        if len(xrc_controls) > 5:
            print(f"    ... and {len(xrc_controls) - 5} more")
    
    # Step 3: Generate wxWidgets event table
    print("[3/4] Generating wxWidgets event table...")
    generator = WxEventTableGenerator(mfc_data, xrc_controls)
    generated_data = generator.generate()
    
    # Step 4: Update wxWidgets file (or show output)
    print("[4/4] Generating output...")
    updater = WxDialogUpdater(wx_file)
    updater.load()
    
    output = updater.update(generated_data)
    
    print()
    print("=" * 60)
    print("GENERATED OUTPUT:")
    print("=" * 60)
    print(output)
    
    # Save to file
    output_file = wx_file.replace('.cpp', '_events_generated.txt')
    with open(output_file, 'w') as f:
        f.write(output)
    
    print()
    print(f"Output saved to: {output_file}")
    print()
    print("Review the generated code and manually integrate into your dialog class.")


if __name__ == '__main__':
    main()
