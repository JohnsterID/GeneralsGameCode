#!/usr/bin/env python3
"""
XRC File Validator
Validates all XRC files for correct XML syntax and wxWidgets XRC structure
Part of the automated conversion and debugging loop
"""

import sys
import xml.etree.ElementTree as ET
from pathlib import Path

def validate_xrc_file(xrc_path):
    """Validate a single XRC file"""
    errors = []
    warnings = []
    
    try:
        # Parse XML
        tree = ET.parse(xrc_path)
        root = tree.getroot()
        
        # Check root element
        if root.tag not in ['resource', '{http://www.wxwidgets.org/wxxrc}resource']:
            errors.append(f"Invalid root element: {root.tag}")
        
        # Find dialog object
        dialog = root.find('.//{http://www.wxwidgets.org/wxxrc}object[@class="wxDialog"]')
        if dialog is None:
            dialog = root.find('.//object[@class="wxDialog"]')
        
        if dialog is None:
            errors.append("No wxDialog object found")
            return errors, warnings, None
        
        dialog_name = dialog.get('name')
        if not dialog_name:
            errors.append("Dialog missing 'name' attribute")
        
        # Count controls
        controls = []
        for obj in dialog.findall('.//{http://www.wxwidgets.org/wxxrc}object') or dialog.findall('.//object'):
            class_name = obj.get('class', '')
            if 'Sizer' not in class_name and class_name != 'wxDialog':
                control_name = obj.get('name', '')
                if control_name and control_name not in ['wxID_ANY', '-1']:
                    controls.append((class_name, control_name))
        
        # Warnings for common issues
        if len(controls) == 0:
            warnings.append("Dialog has no named controls")
        
        # Check for duplicate control names (except IDC_STATIC which is expected)
        control_names = [name for _, name in controls if name != 'IDC_STATIC']
        duplicates = set([name for name in control_names if control_names.count(name) > 1])
        if duplicates:
            warnings.append(f"Duplicate control names: {', '.join(duplicates)}")
        
        return errors, warnings, {
            'dialog_name': dialog_name,
            'control_count': len(controls),
            'controls': controls
        }
        
    except ET.ParseError as e:
        errors.append(f"XML parse error: {e}")
        return errors, warnings, None
    except Exception as e:
        errors.append(f"Unexpected error: {e}")
        return errors, warnings, None

def main():
    if len(sys.argv) < 2:
        print("Usage: validate_xrc_files.py <xrc_dir>")
        sys.exit(1)
    
    xrc_dir = Path(sys.argv[1])
    
    if not xrc_dir.exists():
        print(f"Error: Directory {xrc_dir} not found")
        sys.exit(1)
    
    xrc_files = sorted(xrc_dir.glob('*.xrc'))
    
    if not xrc_files:
        print(f"Error: No XRC files found in {xrc_dir}")
        sys.exit(1)
    
    print(f"🔍 Validating {len(xrc_files)} XRC files")
    print()
    
    valid_count = 0
    warning_count = 0
    error_count = 0
    
    for xrc_file in xrc_files:
        errors, warnings, info = validate_xrc_file(xrc_file)
        
        if errors:
            print(f"❌ {xrc_file.name}")
            for error in errors:
                print(f"   ERROR: {error}")
            error_count += 1
        elif warnings:
            print(f"⚠️  {xrc_file.name}")
            if info:
                print(f"   Dialog: {info['dialog_name']} ({info['control_count']} controls)")
            for warning in warnings:
                print(f"   WARNING: {warning}")
            warning_count += 1
        else:
            if info:
                print(f"✅ {xrc_file.name:40s} → {info['dialog_name']:40s} ({info['control_count']} controls)")
            valid_count += 1
    
    print()
    print("=" * 70)
    print(f"📊 Validation Results")
    print("=" * 70)
    print(f"   ✅ Valid: {valid_count}/{len(xrc_files)}")
    print(f"   ⚠️  Warnings: {warning_count}/{len(xrc_files)}")
    print(f"   ❌ Errors: {error_count}/{len(xrc_files)}")
    
    if error_count > 0:
        print()
        print("❌ VALIDATION FAILED - Fix errors and re-run")
        sys.exit(1)
    elif warning_count > 0:
        print()
        print("⚠️  VALIDATION PASSED WITH WARNINGS")
        sys.exit(0)
    else:
        print()
        print("✅ ALL XRC FILES VALID")
        sys.exit(0)

if __name__ == "__main__":
    main()
