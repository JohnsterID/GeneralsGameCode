#!/usr/bin/env python3
"""
batch_convert_all_dialogs.py - Run mfc2wx_events.py on all dialogs

Creates event tables for all 59 W3DView dialogs
"""

import subprocess
import sys
from pathlib import Path
import json


def find_xrc_file(wx_name, ui_dir):
    """Find the XRC file for a given wx dialog name"""
    # Try lowercase version of dialog name
    xrc_path = ui_dir / f"idd_{wx_name.lower()}.xrc"
    if xrc_path.exists():
        return xrc_path
    
    # Try with underscores converted from camel case
    import re
    # Insert underscore before uppercase letters
    snake_case = re.sub(r'(?<!^)(?=[A-Z])', '_', wx_name).lower()
    xrc_path = ui_dir / f"idd_{snake_case}.xrc"
    if xrc_path.exists():
        return xrc_path
    
    return None


def main():
    root_dir = Path(__file__).parent.parent
    mfc_dir = Path("/tmp/mfc_dialogs")
    wx_dialogs_dir = root_dir / "Core/Tools/W3DView/dialogs"
    ui_dir = root_dir / "Core/Tools/W3DView/ui"
    
    # Load dialog mapping
    mapping_file = root_dir / "dialog_mapping.json"
    if not mapping_file.exists():
        print("Error: dialog_mapping.json not found!")
        print("Run: python3 scripts/build_dialog_mapping.py")
        return 1
    
    with open(mapping_file, 'r') as f:
        mapping_data = json.load(f)
    
    DIALOG_MAPPING = mapping_data['mapping']
    
    print("=" * 70)
    print(f"Loaded mapping for {len(DIALOG_MAPPING)} dialogs")
    print("=" * 70)
    
    # First, extract all MFC dialog files
    print("\n" + "=" * 70)
    print("Step 1: Extracting MFC dialog files from git history")
    print("=" * 70)
    
    mfc_dir.mkdir(parents=True, exist_ok=True)
    
    for mfc_file in DIALOG_MAPPING.keys():
        src_path = f"Core/Tools/W3DView/{mfc_file}"
        dest_path = mfc_dir / mfc_file
        
        cmd = ['git', 'show', f'2df1d9b3^:{src_path}']
        try:
            result = subprocess.run(cmd, capture_output=True, text=True, cwd=root_dir)
            if result.returncode == 0:
                dest_path.write_text(result.stdout)
                print(f"  ✓ Extracted {mfc_file}")
            else:
                print(f"  ✗ Failed to extract {mfc_file}: {result.stderr.strip()}")
        except Exception as e:
            print(f"  ✗ Error extracting {mfc_file}: {e}")
    
    # Run conversion on all dialogs
    print("\n" + "=" * 70)
    print("Step 2: Converting MFC message maps to wxWidgets event tables")
    print("=" * 70)
    
    results = {
        'success': [],
        'failed': [],
        'stats': {}
    }
    
    for mfc_file, wx_name in DIALOG_MAPPING.items():
        mfc_path = mfc_dir / mfc_file
        wx_path = wx_dialogs_dir / f"{wx_name}_wx.cpp"
        xrc_path = find_xrc_file(wx_name, ui_dir)
        
        if not mfc_path.exists():
            print(f"\n{mfc_file} -> {wx_name}")
            print(f"  ✗ MFC file not found")
            results['failed'].append((mfc_file, "MFC file not found"))
            continue
        
        if not wx_path.exists():
            print(f"\n{mfc_file} -> {wx_name}")
            print(f"  ✗ WX file not found: {wx_path}")
            results['failed'].append((mfc_file, "WX file not found"))
            continue
        
        if not xrc_path:
            print(f"\n{mfc_file} -> {wx_name}")
            print(f"  ⚠ XRC file not found (will continue without control type info)")
            xrc_path = "/dev/null"  # Dummy path
        
        print(f"\n{mfc_file} -> {wx_name}")
        
        # Run mfc2wx_events.py
        cmd = [
            'python3',
            str(root_dir / 'scripts/mfc2wx_events.py'),
            str(mfc_path),
            str(wx_path),
            str(xrc_path)
        ]
        
        try:
            result = subprocess.run(cmd, capture_output=True, text=True, cwd=root_dir, timeout=5)
            
            # Parse output for statistics
            lines = result.stdout.split('\n')
            stats = {}
            for line in lines:
                if 'Found' in line and 'message map entries' in line:
                    count = line.split('Found')[1].split('message')[0].strip()
                    stats['message_map_entries'] = int(count)
                elif 'Found' in line and 'control bindings' in line:
                    count = line.split('Found')[1].split('control')[0].strip()
                    stats['control_bindings'] = int(count)
                elif 'Found' in line and 'controls in XRC' in line:
                    count = line.split('Found')[1].split('controls')[0].strip()
                    stats['xrc_controls'] = int(count)
            
            if result.returncode == 0:
                print(f"  ✓ Generated event table:")
                print(f"    - {stats.get('message_map_entries', 0)} message map entries")
                print(f"    - {stats.get('control_bindings', 0)} control bindings")
                print(f"    - {stats.get('xrc_controls', 0)} XRC controls")
                results['success'].append(mfc_file)
                results['stats'][mfc_file] = stats
            else:
                print(f"  ✗ Conversion failed")
                print(f"    {result.stderr[:200]}")
                results['failed'].append((mfc_file, "Conversion error"))
        
        except subprocess.TimeoutExpired:
            print(f"  ✗ Timeout")
            results['failed'].append((mfc_file, "Timeout"))
        except Exception as e:
            print(f"  ✗ Error: {e}")
            results['failed'].append((mfc_file, str(e)))
    
    # Summary
    print("\n" + "=" * 70)
    print("SUMMARY")
    print("=" * 70)
    print(f"✓ Success: {len(results['success'])}/{len(DIALOG_MAPPING)}")
    print(f"✗ Failed:  {len(results['failed'])}/{len(DIALOG_MAPPING)}")
    
    if results['failed']:
        print("\nFailed conversions:")
        for mfc_file, reason in results['failed']:
            print(f"  - {mfc_file}: {reason}")
    
    # Total statistics
    total_entries = sum(s.get('message_map_entries', 0) for s in results['stats'].values())
    total_bindings = sum(s.get('control_bindings', 0) for s in results['stats'].values())
    total_controls = sum(s.get('xrc_controls', 0) for s in results['stats'].values())
    
    print(f"\nTotal across all dialogs:")
    print(f"  - {total_entries} message map entries to convert")
    print(f"  - {total_bindings} control bindings found")
    print(f"  - {total_controls} XRC controls identified")
    
    # Save results
    results_file = root_dir / "BATCH_CONVERSION_RESULTS.json"
    with open(results_file, 'w') as f:
        json.dump(results, f, indent=2)
    
    print(f"\nDetailed results saved to: {results_file}")
    print(f"Generated files saved to: Core/Tools/W3DView/dialogs/*_events_generated.txt")
    
    return 0 if not results['failed'] else 1


if __name__ == '__main__':
    sys.exit(main())
