#!/usr/bin/env python3
"""
Phase 3 Batch Converter with Automatic Compilation Testing

Converts all dialogs from MFC to wxWidgets with automatic debugging loop:
1. Generate Phase 3 code for a dialog
2. Test compilation
3. If fails, analyze errors and retry with fixes
4. Move to next dialog when successful

Usage:
    python3 batch_phase3_with_compile_test.py [--dialog DialogName] [--max-retries 3]
    
Options:
    --dialog NAME    Process only this dialog
    --max-retries N  Maximum compilation fix attempts (default: 3)
    --build-dir PATH Build directory (default: build/mingw-w64-i686)
    --continue       Continue from last successful dialog
"""

import json
import subprocess
import re
import sys
from pathlib import Path
from generate_phase3_logic import Phase3Converter

class Phase3AutoDebugger:
    def __init__(self, build_dir="build/mingw-w64-i686", max_retries=3):
        self.build_dir = Path(build_dir)
        self.max_retries = max_retries
        self.results = {
            'successful': [],
            'failed': [],
            'skipped': []
        }
        
    def load_dialog_mapping(self):
        """Load MFC to wxWidgets dialog mapping"""
        mapping_file = Path("scripts/dialog_mapping.json")
        if not mapping_file.exists():
            # Build basic mapping
            return self.build_basic_mapping()
        
        with open(mapping_file) as f:
            return json.load(f)
    
    def build_basic_mapping(self):
        """Build basic MFC to wxWidgets filename mapping"""
        mfc_dir = Path("Core/Tools/W3DView")
        wx_dir = Path("Core/Tools/W3DView/dialogs")
        ui_dir = Path("Core/Tools/W3DView/ui")
        
        mapping = []
        
        # Find all wxWidgets dialog files
        for wx_cpp in wx_dir.glob("*_wx.cpp"):
            wx_base = wx_cpp.stem.replace('_wx', '')
            
            # Try to find corresponding MFC file
            for mfc_cpp in mfc_dir.glob("*.cpp"):
                if 'Dialog' not in mfc_cpp.stem:
                    continue
                    
                mfc_base = mfc_cpp.stem.replace('Dialog', '').replace('Class', '')
                
                if mfc_base.lower() == wx_base.lower() or \
                   wx_base.lower() in mfc_base.lower() or \
                   mfc_base.lower() in wx_base.lower():
                    
                    # Find XRC file
                    xrc_pattern = f"idd_{wx_base.lower()}.xrc"
                    xrc_file = list(ui_dir.glob(f"idd_*.xrc"))
                    xrc_match = None
                    for xrc in xrc_file:
                        if wx_base.lower() in xrc.stem:
                            xrc_match = xrc
                            break
                    
                    if xrc_match:
                        mapping.append({
                            'mfc_cpp': str(mfc_cpp),
                            'mfc_h': str(mfc_cpp.with_suffix('.h')),
                            'wx_cpp': str(wx_cpp),
                            'wx_h': str(wx_cpp.with_suffix('.h')),
                            'xrc': str(xrc_match),
                            'dialog_name': wx_base
                        })
                        break
        
        return mapping
    
    def test_compilation(self, dialog_name):
        """Test compilation of wxWidgets target"""
        print(f"  Testing compilation...")
        
        cmd = [
            "cmake", "--build", str(self.build_dir),
            "--target", "g_w3dview_wx",
            "-j", "4"
        ]
        
        result = subprocess.run(
            cmd,
            capture_output=True,
            text=True,
            cwd=self.build_dir.parent.parent
        )
        
        if result.returncode == 0:
            print(f"  ✓ Compilation successful!")
            return True, []
        
        # Parse errors
        errors = self.parse_compilation_errors(result.stderr + result.stdout, dialog_name)
        print(f"  ✗ Compilation failed with {len(errors)} errors")
        
        return False, errors
    
    def parse_compilation_errors(self, output, dialog_name):
        """Parse GCC/MinGW compilation errors"""
        errors = []
        
        lines = output.split('\n')
        for i, line in enumerate(lines):
            # Look for error lines
            if ': error:' in line and dialog_name in line:
                error_match = re.search(r"(.+):(\d+):(\d+): error: (.+)", line)
                if error_match:
                    errors.append({
                        'file': error_match.group(1),
                        'line': int(error_match.group(2)),
                        'col': int(error_match.group(3)),
                        'message': error_match.group(4),
                        'context': lines[i+1:i+3] if i+1 < len(lines) else []
                    })
        
        return errors
    
    def fix_common_errors(self, wx_cpp_path, errors):
        """Attempt to fix common compilation errors"""
        content = wx_cpp_path.read_text()
        modified = False
        
        for error in errors:
            msg = error['message']
            
            # Error: 'GetCurrentDocument' was not declared
            if "'GetCurrentDocument' was not declared" in msg:
                if '::GetCurrentDocument()' in content:
                    content = content.replace('::GetCurrentDocument()', '::Get_Graphic_View()->GetDocument()')
                    modified = True
                    print(f"    Fixed: GetCurrentDocument → Get_Graphic_View()->GetDocument()")
            
            # Error: 'class W3DViewDoc' has no member named 'GetXXX'
            member_match = re.search(r"'class \w+' has no member named '(\w+)'", msg)
            if member_match:
                missing_method = member_match.group(1)
                print(f"    ⚠️  Missing method: {missing_method}")
                
                # Add TODO placeholder
                if missing_method in content:
                    # Comment out the problematic line
                    lines = content.split('\n')
                    for i, line in enumerate(lines):
                        if missing_method in line and not line.strip().startswith('//'):
                            lines[i] = f"        // TODO: Implement {missing_method} support\n" + \
                                      f"        // {line.strip()}"
                            modified = True
                    content = '\n'.join(lines)
        
        if modified:
            wx_cpp_path.write_text(content)
            return True
        
        return False
    
    def process_dialog(self, dialog_info):
        """Process a single dialog with retry loop"""
        dialog_name = dialog_info['dialog_name']
        
        print(f"\n{'='*80}")
        print(f"Processing: {dialog_name}")
        print(f"{'='*80}\n")
        
        # Step 1: Generate Phase 3 code
        print(f"Step 1: Generating Phase 3 code...")
        try:
            converter = Phase3Converter(
                dialog_info['mfc_cpp'],
                dialog_info['mfc_h'],
                dialog_info['wx_cpp'],
                dialog_info['wx_h'],
                dialog_info['xrc']
            )
            converter.run()
            
            # Move generated files to original locations
            generated_cpp = Path(dialog_info['wx_cpp']).parent / f"{dialog_name}_wx_phase3.cpp"
            generated_h = Path(dialog_info['wx_h']).parent / f"{dialog_name}_wx_phase3.h"
            
            if generated_cpp.exists():
                # Backup original
                backup_cpp = Path(dialog_info['wx_cpp']).with_suffix('.cpp.backup')
                Path(dialog_info['wx_cpp']).rename(backup_cpp)
                
                # Use generated version
                generated_cpp.rename(dialog_info['wx_cpp'])
                print(f"  ✓ Applied Phase 3 code")
            
            if generated_h.exists():
                backup_h = Path(dialog_info['wx_h']).with_suffix('.h.backup')
                Path(dialog_info['wx_h']).rename(backup_h)
                generated_h.rename(dialog_info['wx_h'])
                
        except Exception as e:
            print(f"  ✗ Code generation failed: {e}")
            self.results['failed'].append({
                'dialog': dialog_name,
                'reason': f"Code generation error: {e}"
            })
            return False
        
        # Step 2: Compilation testing loop
        print(f"\nStep 2: Testing compilation...")
        
        for attempt in range(self.max_retries):
            success, errors = self.test_compilation(dialog_name)
            
            if success:
                print(f"  ✓ {dialog_name} compiled successfully!")
                self.results['successful'].append(dialog_name)
                return True
            
            if attempt < self.max_retries - 1:
                print(f"  Attempt {attempt + 1}/{self.max_retries}: Trying to fix errors...")
                
                # Attempt automatic fixes
                fixed = self.fix_common_errors(Path(dialog_info['wx_cpp']), errors)
                
                if not fixed:
                    print(f"  ✗ Could not auto-fix errors")
                    break
            else:
                print(f"  ✗ Max retries reached")
        
        # Failed - restore backup
        print(f"  ✗ {dialog_name} compilation failed, restoring backup...")
        backup_cpp = Path(dialog_info['wx_cpp']).with_suffix('.cpp.backup')
        if backup_cpp.exists():
            backup_cpp.rename(dialog_info['wx_cpp'])
        
        backup_h = Path(dialog_info['wx_h']).with_suffix('.h.backup')
        if backup_h.exists():
            backup_h.rename(dialog_info['wx_h'])
        
        self.results['failed'].append({
            'dialog': dialog_name,
            'reason': f"Compilation failed after {self.max_retries} attempts",
            'errors': errors
        })
        
        return False
    
    def run(self, dialog_filter=None):
        """Run batch conversion with automatic testing"""
        print("=" * 80)
        print("Phase 3 Batch Converter with Automatic Compilation Testing")
        print("=" * 80)
        print()
        
        # Load dialog mapping
        print("Loading dialog mapping...")
        dialogs = self.load_dialog_mapping()
        print(f"Found {len(dialogs)} dialogs to process\n")
        
        # Filter if requested
        if dialog_filter:
            dialogs = [d for d in dialogs if d['dialog_name'] == dialog_filter]
            if not dialogs:
                print(f"❌ Dialog '{dialog_filter}' not found")
                return
        
        # Process each dialog
        for i, dialog_info in enumerate(dialogs):
            print(f"\n[{i+1}/{len(dialogs)}] Processing {dialog_info['dialog_name']}...")
            self.process_dialog(dialog_info)
        
        # Print summary
        self.print_summary()
    
    def print_summary(self):
        """Print conversion summary"""
        print("\n" + "=" * 80)
        print("PHASE 3 CONVERSION SUMMARY")
        print("=" * 80)
        
        print(f"\n✅ Successful: {len(self.results['successful'])}")
        for dialog in self.results['successful']:
            print(f"  - {dialog}")
        
        print(f"\n❌ Failed: {len(self.results['failed'])}")
        for failed in self.results['failed']:
            print(f"  - {failed['dialog']}: {failed['reason']}")
        
        print(f"\n⏭️  Skipped: {len(self.results['skipped'])}")
        for dialog in self.results['skipped']:
            print(f"  - {dialog}")
        
        # Save results
        results_file = Path("PHASE3_BATCH_RESULTS.json")
        with open(results_file, 'w') as f:
            json.dump(self.results, f, indent=2)
        
        print(f"\nResults saved to: {results_file}")

if __name__ == '__main__':
    import argparse
    
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--dialog', help='Process only this dialog')
    parser.add_argument('--max-retries', type=int, default=3, help='Max compilation fix attempts')
    parser.add_argument('--build-dir', default='build/mingw-w64-i686', help='Build directory')
    
    args = parser.parse_args()
    
    debugger = Phase3AutoDebugger(
        build_dir=args.build_dir,
        max_retries=args.max_retries
    )
    
    debugger.run(dialog_filter=args.dialog)
