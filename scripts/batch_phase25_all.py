#!/usr/bin/env python3
"""
Batch Phase 2.5 Conversion - ALL 59 Dialogs

Automatically processes all W3DView dialogs using the dialog mapping.
"""

import json
import subprocess
import sys
from pathlib import Path
from dataclasses import dataclass

@dataclass
class ConversionResult:
    name: str
    success: bool
    lines: int = 0
    includes: int = 0
    todos: int = 0
    error: str = ""

def load_dialog_mapping():
    """Load dialog mapping from JSON file or generate it"""
    mapping_file = Path('dialog_mapping.json')
    
    if not mapping_file.exists():
        print("Dialog mapping not found, generating...")
        result = subprocess.run(
            ['python3', 'scripts/build_dialog_mapping.py'],
            capture_output=True,
            text=True
        )
        if result.returncode != 0:
            print(f"Error generating mapping: {result.stderr}")
            return None
    
    with open(mapping_file) as f:
        return json.load(f)

def convert_dialog(mfc_cpp, mfc_h, mfc_class, wx_name, temp_dir, repo_root):
    """Convert single dialog using Phase 2.5 enhanced generator"""
    
    print(f"\n{'='*70}")
    print(f"Converting: {wx_name}")
    print(f"  MFC: {mfc_cpp} / {mfc_h}")
    print(f"  Class: {mfc_class}")
    print(f"{'='*70}")
    
    # Extract MFC files from git
    mfc_cpp_path = temp_dir / f"{wx_name}_mfc.cpp"
    mfc_h_path = temp_dir / f"{wx_name}_mfc.h"
    
    for src_file, dest_path in [(mfc_cpp, mfc_cpp_path), (mfc_h, mfc_h_path)]:
        try:
            result = subprocess.run(
                ['git', 'show', f'origin/main:Core/Tools/W3DView/{src_file}'],
                cwd=repo_root,
                capture_output=True,
                text=True
            )
            if result.returncode == 0:
                dest_path.write_text(result.stdout)
            else:
                # Try without origin/
                result = subprocess.run(
                    ['git', 'show', f'main:Core/Tools/W3DView/{src_file}'],
                    cwd=repo_root,
                    capture_output=True,
                    text=True
                )
                if result.returncode == 0:
                    dest_path.write_text(result.stdout)
                else:
                    print(f"  ⚠️  Could not extract {src_file}")
                    return ConversionResult(wx_name, False, error=f"Could not extract {src_file}")
        except Exception as e:
            print(f"  ❌ Error extracting {src_file}: {e}")
            return ConversionResult(wx_name, False, error=str(e))
    
    # Run enhanced generator
    output_file = temp_dir / f"{wx_name}_phase25.cpp"
    
    try:
        cmd = [
            'python3',
            str(repo_root / 'scripts' / 'generate_phase25_enhanced.py'),
            str(mfc_cpp_path),
            str(mfc_h_path),
            mfc_class
        ]
        
        result = subprocess.run(cmd, capture_output=True, text=True, cwd=repo_root)
        
        if result.returncode == 0:
            output_file.write_text(result.stdout)
            
            # Count stats
            lines = result.stdout.count('\n')
            todos = result.stdout.count('TODO')
            includes = result.stdout.count('#include')
            
            print(f"  ✅ Generated: {output_file.name}")
            print(f"  📊 Stats: {lines} lines, {includes} includes, {todos} TODOs")
            
            return ConversionResult(wx_name, True, lines, includes, todos)
        else:
            error = result.stderr or "Unknown error"
            print(f"  ❌ Generation failed: {error[:100]}")
            return ConversionResult(wx_name, False, error=error[:200])
    except Exception as e:
        print(f"  ❌ Error: {e}")
        return ConversionResult(wx_name, False, error=str(e))

def get_mfc_class_name(mfc_cpp):
    """Derive MFC class name from file name"""
    # Most follow pattern: XxxDialog.cpp → XxxDialogClass
    #                       XxxPropPage.cpp → XxxPropPageClass
    base = mfc_cpp.replace('.cpp', '')
    
    # Special cases
    if base == 'ColorPicker' or base == 'ColorPickerDialogClass':
        return 'ColorFormDialogClass'
    
    # Standard pattern
    return base + 'Class'

def main():
    repo_root = Path(__file__).parent.parent
    if not (repo_root / '.git').exists():
        repo_root = Path.cwd()
    
    print(f"Repository: {repo_root}")
    
    # Load dialog mapping
    mapping_data = load_dialog_mapping()
    if not mapping_data:
        print("❌ Failed to load dialog mapping")
        return 1
    
    mapping = mapping_data['mapping']
    
    # Create temp directory
    temp_dir = Path('/tmp/phase25_all_output')
    temp_dir.mkdir(exist_ok=True)
    print(f"Output directory: {temp_dir}")
    print(f"Processing {len(mapping)} mapped dialogs...")
    
    # Process each dialog
    results = []
    
    for mfc_cpp, wx_name in sorted(mapping.items()):
        mfc_h = mfc_cpp.replace('.cpp', '.h')
        mfc_class = get_mfc_class_name(mfc_cpp.replace('.cpp', ''))
        
        result = convert_dialog(mfc_cpp, mfc_h, mfc_class, wx_name, temp_dir, repo_root)
        results.append(result)
    
    # Process unmatched wxWidgets dialogs (embedded in main files)
    unmatched_wx = mapping_data.get('unmatched_wx', [])
    if 'Aboutbox' in unmatched_wx:
        # Aboutbox is in W3DView.cpp
        print(f"\n{'='*70}")
        print("Special: Aboutbox (embedded in W3DView.cpp)")
        print(f"{'='*70}")
        print("  ⏭️  Skipping (needs manual handling)")
        results.append(ConversionResult('Aboutbox', False, error="Embedded in W3DView.cpp"))
    
    # Summary
    print()
    print("="*70)
    print("BATCH CONVERSION SUMMARY")
    print("="*70)
    
    successful = [r for r in results if r.success]
    failed = [r for r in results if not r.success]
    
    print(f"Total attempted: {len(results)}")
    print(f"Successful: {len(successful)}")
    print(f"Failed: {len(failed)}")
    
    if successful:
        total_lines = sum(r.lines for r in successful)
        total_includes = sum(r.includes for r in successful)
        total_todos = sum(r.todos for r in successful)
        avg_todos = total_todos / len(successful) if successful else 0
        
        print(f"\nCode Generation Stats:")
        print(f"  Total lines: {total_lines}")
        print(f"  Total includes: {total_includes}")
        print(f"  Total TODOs: {total_todos}")
        print(f"  Average TODOs/dialog: {avg_todos:.1f}")
        
        # Category breakdown
        simple = [r for r in successful if r.todos <= 10]
        medium = [r for r in successful if 10 < r.todos <= 30]
        complex_dialogs = [r for r in successful if r.todos > 30]
        
        print(f"\nComplexity Breakdown:")
        print(f"  Simple (<= 10 TODOs): {len(simple)} dialogs")
        print(f"  Medium (11-30 TODOs): {len(medium)} dialogs")
        print(f"  Complex (> 30 TODOs): {len(complex_dialogs)} dialogs")
    
    if failed:
        print(f"\nFailed conversions:")
        for r in failed:
            print(f"  - {r.name}: {r.error[:50]}")
    
    print(f"\nGenerated files: {temp_dir}")
    print()
    print("Next steps:")
    print("  1. Review generated code")
    print("  2. Start with simple dialogs (<=10 TODOs)")
    print("  3. Manual integration (~10-20 min/dialog)")
    print("  4. Test compilation")
    
    return 0 if not failed else 1

if __name__ == '__main__':
    sys.exit(main())
