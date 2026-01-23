#!/usr/bin/env python3
"""
integrate_phase2_events.py - Integrate generated Phase 2 event handlers into dialog files

Takes generated event handler files and integrates them into existing dialog .h and .cpp files.
"""

import re
import sys
from pathlib import Path


def parse_generated_file(generated_file):
    """Parse a generated event handler file into sections"""
    with open(generated_file, 'r') as f:
        content = f.read()
    
    # Extract event table entries
    event_table_match = re.search(
        r'// Add these to your wxBEGIN_EVENT_TABLE block:\n(.*?)(?=\n// Handler method stubs)',
        content,
        re.DOTALL
    )
    event_table_entries = event_table_match.group(1).strip() if event_table_match else ""
    
    # Extract handler declarations (for .h file)
    h_declarations_match = re.search(
        r'// In \.h file:\n(.*?)(?=\n// In \.cpp file:)',
        content,
        re.DOTALL
    )
    h_declarations = h_declarations_match.group(1).strip() if h_declarations_match else ""
    
    # Extract handler implementations (for .cpp file)
    cpp_implementations_match = re.search(
        r'// In \.cpp file:\n\n(.*)',
        content,
        re.DOTALL
    )
    cpp_implementations = cpp_implementations_match.group(1).strip() if cpp_implementations_match else ""
    
    return {
        'event_table_entries': event_table_entries,
        'h_declarations': h_declarations,
        'cpp_implementations': cpp_implementations
    }


def integrate_event_table(cpp_content, event_entries):
    """Replace placeholder event table with real entries"""
    # Find the existing event table
    pattern = r'(wxBEGIN_EVENT_TABLE\([^)]+\))\s*EVT_BUTTON\(wxID_OK[^)]+\)[^;]*;\s*EVT_BUTTON\(wxID_CANCEL[^)]+\)[^;]*;\s*// Add more event handlers as needed\s*(wxEND_EVENT_TABLE\(\))'
    
    def replacer(match):
        begin = match.group(1)
        end = match.group(2)
        # Keep OK/Cancel buttons, add new entries
        new_table = f"{begin}\n    EVT_BUTTON(wxID_OK, OnOK)\n    EVT_BUTTON(wxID_CANCEL, OnCancel)\n{event_entries}\n{end}"
        return new_table
    
    new_content = re.sub(pattern, replacer, cpp_content, flags=re.DOTALL)
    
    # If pattern didn't match, try simpler pattern
    if new_content == cpp_content:
        pattern2 = r'(wxBEGIN_EVENT_TABLE\([^)]+\)).*?// Add more event handlers as needed\s*(wxEND_EVENT_TABLE\(\))'
        new_content = re.sub(
            pattern2,
            lambda m: f"{m.group(1)}\n{event_entries}\n{m.group(2)}",
            cpp_content,
            flags=re.DOTALL
        )
    
    return new_content


def integrate_h_declarations(h_content, declarations):
    """Add handler declarations to .h file before closing brace"""
    if not declarations:
        return h_content
    
    # Find the last private: or protected: section before closing brace
    # Or add before the final closing brace
    
    # Look for existing event handler section
    if 'Event handlers' in h_content or 'event handlers' in h_content:
        # Add after existing comment
        pattern = r'(// Event handlers.*?\n)(.*?)(private:|protected:|};)'
        new_content = re.sub(
            pattern,
            lambda m: f"{m.group(1)}{declarations}\n\n    {m.group(3)}",
            h_content,
            flags=re.DOTALL
        )
        if new_content != h_content:
            return new_content
    
    # Add new section before closing brace
    pattern = r'(\n)(};[\s]*$)'
    new_section = f"\nprivate:\n    // Event handlers (Phase 2)\n{declarations}\n"
    new_content = re.sub(pattern, lambda m: f"{new_section}{m.group(2)}", h_content)
    
    return new_content


def integrate_cpp_implementations(cpp_content, implementations):
    """Add handler implementations to .cpp file at the end"""
    if not implementations:
        return cpp_content
    
    # Add at the end of the file with a header comment
    header = "\n// ============================================================================\n// Event Handlers (Phase 2 - Auto-integrated)\n// ============================================================================\n\n"
    
    # Check if already has event handlers section
    if '// Event Handlers' in cpp_content or '// Event handlers' in cpp_content:
        # Replace existing TODO implementations
        # For now, just append
        return cpp_content.rstrip() + "\n" + header + implementations + "\n"
    else:
        return cpp_content.rstrip() + "\n" + header + implementations + "\n"


def integrate_dialog(dialog_name, generated_file, dialogs_dir):
    """Integrate generated events into a dialog's .h and .cpp files"""
    h_file = dialogs_dir / f"{dialog_name}_wx.h"
    cpp_file = dialogs_dir / f"{dialog_name}_wx.cpp"
    
    if not h_file.exists() or not cpp_file.exists():
        print(f"  ⚠️  Dialog files not found: {dialog_name}")
        return False
    
    # Parse generated file
    parsed = parse_generated_file(generated_file)
    
    # Read current files
    with open(h_file, 'r') as f:
        h_content = f.read()
    with open(cpp_file, 'r') as f:
        cpp_content = f.read()
    
    # Integrate changes
    new_cpp = integrate_event_table(cpp_content, parsed['event_table_entries'])
    new_cpp = integrate_cpp_implementations(new_cpp, parsed['cpp_implementations'])
    new_h = integrate_h_declarations(h_content, parsed['h_declarations'])
    
    # Check if anything changed
    h_changed = new_h != h_content
    cpp_changed = new_cpp != cpp_content
    
    if not h_changed and not cpp_changed:
        print(f"  ℹ️  No changes needed: {dialog_name}")
        return True
    
    # Write updated files
    with open(h_file, 'w') as f:
        f.write(new_h)
    with open(cpp_file, 'w') as f:
        f.write(new_cpp)
    
    changes = []
    if h_changed:
        changes.append('.h')
    if cpp_changed:
        changes.append('.cpp')
    
    print(f"  ✅ Updated: {dialog_name} ({', '.join(changes)})")
    return True


def main():
    if len(sys.argv) != 3:
        print("Usage: integrate_phase2_events.py <generated_dir> <dialogs_dir>")
        print("\nExample:")
        print("  python3 integrate_phase2_events.py /tmp/phase2_generated Core/Tools/W3DView/dialogs")
        return 1
    
    generated_dir = Path(sys.argv[1])
    dialogs_dir = Path(sys.argv[2])
    
    if not generated_dir.exists():
        print(f"Error: Generated files directory not found: {generated_dir}")
        return 1
    
    if not dialogs_dir.exists():
        print(f"Error: Dialogs directory not found: {dialogs_dir}")
        return 1
    
    # Find all generated files
    generated_files = list(generated_dir.glob("*_events_generated.txt"))
    
    if not generated_files:
        print(f"Error: No generated event files found in {generated_dir}")
        return 1
    
    print("=" * 70)
    print(f"Phase 2 Event Handler Integration")
    print("=" * 70)
    print(f"Generated files: {len(generated_files)}")
    print(f"Target directory: {dialogs_dir}")
    print()
    
    success_count = 0
    error_count = 0
    
    for generated_file in sorted(generated_files):
        # Extract dialog name from filename
        # Example: Displayspeed_wx_events_generated.txt -> Displayspeed
        dialog_name = generated_file.stem.replace('_wx_events_generated', '')
        
        try:
            if integrate_dialog(dialog_name, generated_file, dialogs_dir):
                success_count += 1
            else:
                error_count += 1
        except Exception as e:
            print(f"  ❌ Error processing {dialog_name}: {e}")
            error_count += 1
    
    print()
    print("=" * 70)
    print(f"Integration Complete")
    print("=" * 70)
    print(f"✅ Success: {success_count}/{len(generated_files)}")
    print(f"❌ Errors:  {error_count}/{len(generated_files)}")
    
    return 0 if error_count == 0 else 1


if __name__ == '__main__':
    sys.exit(main())
