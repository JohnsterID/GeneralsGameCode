#!/usr/bin/env python3
"""
Integrate Phase 2.5 generated code into actual wx dialog files.

This script:
1. Reads generated Phase 2.5 code
2. Extracts methods (OnInitDialog, TransferDataToWindow, TransferDataFromWindow)
3. Adds methods to *_wx.cpp file (before final closing brace)
4. Adds declarations to *_wx.h file (in private/protected section)
5. Updates event table with EVT_INIT_DIALOG if OnInitDialog exists

Usage:
    python3 integrate_phase25.py <dialog_name>
    
Example:
    python3 integrate_phase25.py PropPageAdvanimMixing
"""

import re
import sys
from pathlib import Path

def extract_methods(phase25_content):
    """Extract all Phase 2.5 methods from generated file"""
    methods = {}
    
    # Extract OnInitDialog if present
    oninit_match = re.search(
        r'void\s+\w+::OnInitDialog\(wxInitDialogEvent&\s+event\)\s*\{.*?\n\}',
        phase25_content,
        re.DOTALL
    )
    if oninit_match:
        methods['OnInitDialog'] = oninit_match.group(0)
    
    # Extract TransferDataToWindow
    transfer_to_match = re.search(
        r'bool\s+\w+::TransferDataToWindow\(\)\s*\{.*?\n\}',
        phase25_content,
        re.DOTALL
    )
    if transfer_to_match:
        methods['TransferDataToWindow'] = transfer_to_match.group(0)
    
    # Extract TransferDataFromWindow
    transfer_from_match = re.search(
        r'bool\s+\w+::TransferDataFromWindow\(\)\s*\{.*?\n\}',
        phase25_content,
        re.DOTALL
    )
    if transfer_from_match:
        methods['TransferDataFromWindow'] = transfer_from_match.group(0)
    
    # Extract includes
    includes = []
    for line in phase25_content.split('\n'):
        if line.strip().startswith('#include'):
            includes.append(line.strip())
    
    return methods, includes

def find_insertion_point_cpp(cpp_content):
    """Find where to insert methods in .cpp file (at the end)"""
    lines = cpp_content.split('\n')
    
    # Simply insert at the end of the file
    # This is safest and works for all file structures
    return len(lines)

def add_methods_to_cpp(cpp_path, methods, includes, target_class_name):
    """Add Phase 2.5 methods to _wx.cpp file"""
    content = cpp_path.read_text()
    
    # Check if Phase 2.5 methods already exist
    if '// Phase 2.5: Dialog Infrastructure (Auto-generated)' in content:
        print(f"  ℹ️  Phase 2.5 methods already exist, skipping")
        return content
    
    # Replace MFC class names with wx class name in methods
    for method_name, method_code in methods.items():
        # Find MFC class name in method signature
        mfc_class_match = re.search(r'(\w+)::' + method_name, method_code)
        if mfc_class_match:
            mfc_class = mfc_class_match.group(1)
            # Replace with target wx class name
            methods[method_name] = method_code.replace(f'{mfc_class}::', f'{target_class_name}::')
    
    # Add includes at the top (after existing includes)
    if includes:
        # Find last #include
        lines = content.split('\n')
        last_include_idx = -1
        for i, line in enumerate(lines):
            if line.strip().startswith('#include'):
                last_include_idx = i
        
        if last_include_idx >= 0:
            # Add new includes after last existing include
            for inc in includes:
                if inc not in content:
                    lines.insert(last_include_idx + 1, inc)
                    last_include_idx += 1
            content = '\n'.join(lines)
    
    # Add methods before the final closing brace
    insertion_idx = find_insertion_point_cpp(content)
    lines = content.split('\n')
    
    # Add a separator comment and methods
    new_lines = [
        '',
        '// ============================================================================',
        '// Phase 2.5: Dialog Infrastructure (Auto-generated)',
        '// ============================================================================',
        ''
    ]
    
    for method_name in ['OnInitDialog', 'TransferDataToWindow', 'TransferDataFromWindow']:
        if method_name in methods:
            new_lines.append(methods[method_name])
            new_lines.append('')
    
    # Insert before the insertion point
    lines[insertion_idx:insertion_idx] = new_lines
    
    return '\n'.join(lines)

def add_declarations_to_header(header_path, methods, class_name):
    """Add method declarations to _wx.h file"""
    content = header_path.read_text()
    
    # Check if Phase 2.5 declarations already exist
    if '// Phase 2.5: Dialog infrastructure' in content:
        print(f"  ℹ️  Phase 2.5 declarations already exist, skipping")
        return content
    
    # Check for individual declarations (in case they exist without the comment)
    # Need to check for uncommented declarations only
    needs_declarations = []
    
    # Check each line to see if declaration exists and is not commented
    lines = content.split('\n')
    
    has_uncommented_oninit = any(
        'void OnInitDialog(wxInitDialogEvent& event)' in line and not line.strip().startswith('//')
        for line in lines
    )
    has_uncommented_transfer_to = any(
        'bool TransferDataToWindow() override' in line and not line.strip().startswith('//')
        for line in lines
    )
    has_uncommented_transfer_from = any(
        'bool TransferDataFromWindow() override' in line and not line.strip().startswith('//')
        for line in lines
    )
    
    if 'OnInitDialog' in methods and not has_uncommented_oninit:
        needs_declarations.append('OnInitDialog')
    if 'TransferDataToWindow' in methods and not has_uncommented_transfer_to:
        needs_declarations.append('TransferDataToWindow')
    if 'TransferDataFromWindow' in methods and not has_uncommented_transfer_from:
        needs_declarations.append('TransferDataFromWindow')
    
    if not needs_declarations:
        print(f"  ℹ️  All declarations already exist, skipping")
        return content
    
    # Find the class definition
    class_match = re.search(rf'class\s+{class_name}\s*:\s*public\s+\w+\s*\{{', content)
    if not class_match:
        print(f"  ⚠️  Could not find class {class_name} in header")
        return content
    
    # Find private: or protected: section
    # Look for the last private: or protected: before the closing };
    private_match = None
    for match in re.finditer(r'(private|protected):', content[class_match.end():]):
        private_match = match
    
    if not private_match:
        # No private/protected section, add one before the closing brace
        class_end_match = re.search(r'\};', content[class_match.end():])
        if class_end_match:
            insertion_point = class_match.end() + class_end_match.start()
            new_section = '\nprivate:\n    // Phase 2.5: Dialog infrastructure\n'
        else:
            print(f"  ⚠️  Could not find class end in header")
            return content
    else:
        # Insert after private/protected keyword
        insertion_point = class_match.end() + private_match.end()
        new_section = '\n    // Phase 2.5: Dialog infrastructure\n'
    
    # Generate declarations only for methods that don't exist
    declarations = []
    if 'OnInitDialog' in needs_declarations:
        declarations.append('    void OnInitDialog(wxInitDialogEvent& event);')
    if 'TransferDataToWindow' in needs_declarations:
        declarations.append('    bool TransferDataToWindow() override;')
    if 'TransferDataFromWindow' in needs_declarations:
        declarations.append('    bool TransferDataFromWindow() override;')
    
    if not declarations:
        return content
    
    decl_text = new_section + '\n'.join(declarations) + '\n'
    
    # Insert declarations
    new_content = content[:insertion_point] + decl_text + content[insertion_point:]
    
    return new_content

def update_event_table(cpp_content, class_name, has_oninit):
    """Add EVT_INIT_DIALOG to event table if OnInitDialog exists"""
    if not has_oninit:
        return cpp_content
    
    # Find event table
    evt_table_match = re.search(
        rf'(wxBEGIN_EVENT_TABLE\s*\(\s*{class_name}\s*,\s*\w+\s*\))(.*?)(wxEND_EVENT_TABLE\s*\(\s*\))',
        cpp_content,
        re.DOTALL
    )
    
    if not evt_table_match:
        print(f"  ⚠️  Could not find event table for {class_name}")
        return cpp_content
    
    begin = evt_table_match.group(1)
    middle = evt_table_match.group(2)
    end = evt_table_match.group(3)
    
    # Check if EVT_INIT_DIALOG already exists
    if 'EVT_INIT_DIALOG' in middle:
        print(f"  ℹ️  EVT_INIT_DIALOG already in event table")
        return cpp_content
    
    # Add EVT_INIT_DIALOG as first entry (after BEGIN)
    new_middle = middle.rstrip() + '\n    EVT_INIT_DIALOG(' + class_name + '::OnInitDialog)\n'
    
    new_event_table = begin + new_middle + end
    
    # Replace in content
    new_content = cpp_content[:evt_table_match.start()] + new_event_table + cpp_content[evt_table_match.end():]
    
    return new_content

def integrate_dialog(dialog_name, phase25_dir, dialogs_dir):
    """Integrate Phase 2.5 code for a single dialog"""
    print(f"\nIntegrating: {dialog_name}")
    print(f"{'='*70}")
    
    # Read generated Phase 2.5 file
    phase25_file = phase25_dir / f"{dialog_name}_phase25.cpp"
    if not phase25_file.exists():
        print(f"  ❌ Generated file not found: {phase25_file}")
        return False
    
    phase25_content = phase25_file.read_text()
    
    # Extract methods
    methods, includes = extract_methods(phase25_content)
    
    if not methods:
        print(f"  ⚠️  No methods found in generated file")
        return False
    
    print(f"  📝 Found methods: {', '.join(methods.keys())}")
    if includes:
        print(f"  📦 Found includes: {len(includes)}")
    
    # Find target files
    cpp_file = dialogs_dir / f"{dialog_name}_wx.cpp"
    h_file = dialogs_dir / f"{dialog_name}_wx.h"
    
    if not cpp_file.exists():
        print(f"  ❌ Target .cpp file not found: {cpp_file}")
        return False
    
    if not h_file.exists():
        print(f"  ❌ Target .h file not found: {h_file}")
        return False
    
    # Extract class name from header
    # We want the derived class (not the Base class)
    # The derived class typically comes after the base class and doesn't end with "Base"
    h_content = h_file.read_text()
    
    # Find all classes
    all_classes = re.findall(r'class\s+(\w+)\s*:\s*public', h_content)
    
    # Filter out classes ending with "Base"
    derived_classes = [c for c in all_classes if not c.endswith('Base')]
    
    if not derived_classes:
        # Fallback: use the first class
        if all_classes:
            class_name = all_classes[0]
        else:
            print(f"  ❌ Could not find class name in header")
            return False
    else:
        # Use the first derived class (not ending with Base)
        class_name = derived_classes[0]
    
    print(f"  🎯 Target class: {class_name}")
    
    # Backup original files
    backup_dir = dialogs_dir / 'backup_phase25'
    backup_dir.mkdir(exist_ok=True)
    
    import shutil
    shutil.copy2(cpp_file, backup_dir / cpp_file.name)
    shutil.copy2(h_file, backup_dir / h_file.name)
    print(f"  💾 Backed up to: {backup_dir}")
    
    # Add methods to .cpp
    new_cpp_content = add_methods_to_cpp(cpp_file, methods, includes, class_name)
    
    # Update event table if OnInitDialog exists
    if 'OnInitDialog' in methods:
        new_cpp_content = update_event_table(new_cpp_content, class_name, True)
    
    # Add declarations to .h
    new_h_content = add_declarations_to_header(h_file, methods, class_name)
    
    # Write updated files
    cpp_file.write_text(new_cpp_content)
    h_file.write_text(new_h_content)
    
    print(f"  ✅ Integrated successfully!")
    print(f"  📄 Updated: {cpp_file.name}, {h_file.name}")
    
    # Count TODOs
    todo_count = new_cpp_content.count('TODO')
    print(f"  📋 Remaining TODOs: {todo_count}")
    
    return True

def main():
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)
    
    dialog_name = sys.argv[1]
    
    # Paths
    phase25_dir = Path('/tmp/phase25_all_output')
    repo_root = Path('/workspace/project/GeneralsGameCode')
    dialogs_dir = repo_root / 'Core/Tools/W3DView/dialogs'
    
    if not phase25_dir.exists():
        print(f"❌ Phase 2.5 output directory not found: {phase25_dir}")
        sys.exit(1)
    
    if not dialogs_dir.exists():
        print(f"❌ Dialogs directory not found: {dialogs_dir}")
        sys.exit(1)
    
    # Integrate the dialog
    success = integrate_dialog(dialog_name, phase25_dir, dialogs_dir)
    
    sys.exit(0 if success else 1)

if __name__ == '__main__':
    main()
