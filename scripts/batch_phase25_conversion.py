#!/usr/bin/env python3
"""
Batch Phase 2.5 Conversion Script

Processes all W3DView dialogs and generates Phase 2.5 infrastructure code.
"""

import re
import sys
import subprocess
from pathlib import Path
from dataclasses import dataclass

@dataclass
class DialogInfo:
    """Information about a dialog to convert"""
    name: str
    mfc_class: str
    wx_class: str
    mfc_cpp: str
    mfc_h: str
    wx_cpp: str
    wx_h: str

# Dialog list extracted from Phase 2 conversion
DIALOGS = [
    DialogInfo("Aboutbox", "CAboutDlg", "Aboutbox",
               "W3DView.cpp", "W3DView.h",  # Embedded in main file
               "dialogs/Aboutbox_wx.cpp", "dialogs/Aboutbox_wx.h"),
    
    DialogInfo("AddToLineup", "AddToLineupDialogClass", "AddToLineup",
               "AddToLineupDialog.cpp", "AddToLineupDialog.h",
               "dialogs/AddToLineup_wx.cpp", "dialogs/AddToLineup_wx.h"),
    
    DialogInfo("AnimatedSoundDialog", "AnimatedSoundOptionsDialogClass", "AnimatedSoundDialog",
               "AnimatedSoundOptionsDialog.cpp", "AnimatedSoundOptionsDialog.h",
               "dialogs/AnimatedSoundDialog_wx.cpp", "dialogs/AnimatedSoundDialog_wx.h"),
    
    DialogInfo("BackgroundBmp", "BackgroundBMPDialogClass", "BackgroundBmp",
               "BackgroundBMPDialog.cpp", "BackgroundBMPDialog.h",
               "dialogs/BackgroundBmp_wx.cpp", "dialogs/BackgroundBmp_wx.h"),
    
    DialogInfo("BackgroundColor", "BackgroundColorDialogClass", "BackgroundColor",
               "BackgroundColorDialog.cpp", "BackgroundColorDialog.h",
               "dialogs/BackgroundColor_wx.cpp", "dialogs/BackgroundColor_wx.h"),
    
    DialogInfo("BackgroundObject", "BackgroundObjectDialogClass", "BackgroundObject",
               "BackgroundObjectDialog.cpp", "BackgroundObjectDialog.h",
               "dialogs/BackgroundObject_wx.cpp", "dialogs/BackgroundObject_wx.h"),
    
    DialogInfo("BoneManagement", "BoneMgrDialogClass", "BoneManagement",
               "BoneMgrDialog.cpp", "BoneMgrDialog.h",
               "dialogs/BoneManagement_wx.cpp", "dialogs/BoneManagement_wx.h"),
    
    DialogInfo("CameraDistance", "CameraDistanceDialogClass", "CameraDistance",
               "CameraDistanceDialog.cpp", "CameraDistanceDialog.h",
               "dialogs/CameraDistance_wx.cpp", "dialogs/CameraDistance_wx.h"),
    
    DialogInfo("CameraSettings", "CameraSettingsDialogClass", "CameraSettings",
               "CameraSettingsDialog.cpp", "CameraSettingsDialog.h",
               "dialogs/CameraSettings_wx.cpp", "dialogs/CameraSettings_wx.h"),
    
    DialogInfo("ColorForm", "ColorFormDialogClass", "ColorForm",
               "ColorPickerDialogClass.cpp", "ColorPickerDialogClass.h",
               "dialogs/ColorForm_wx.cpp", "dialogs/ColorForm_wx.h"),
]

def extract_mfc_from_git(repo_root: Path, rel_path: str, output_file: Path):
    """Extract MFC file from git main branch"""
    try:
        result = subprocess.run(
            ['git', 'show', f'origin/main:Core/Tools/W3DView/{rel_path}'],
            cwd=repo_root,
            capture_output=True,
            text=True
        )
        if result.returncode == 0:
            output_file.write_text(result.stdout)
            return True
        else:
            print(f"  ⚠️  Could not extract {rel_path}: {result.stderr.strip()}")
            return False
    except Exception as e:
        print(f"  ❌ Error extracting {rel_path}: {e}")
        return False

def generate_infrastructure(dialog: DialogInfo, temp_dir: Path, repo_root: Path):
    """Generate Phase 2.5 infrastructure for a dialog"""
    
    print(f"\n{'=' * 70}")
    print(f"Processing: {dialog.name}")
    print(f"  MFC Class: {dialog.mfc_class}")
    print(f"  wx Class: {dialog.wx_class}")
    print(f"{'=' * 70}")
    
    # Extract MFC files from git
    mfc_cpp_path = temp_dir / f"{dialog.name}_mfc.cpp"
    mfc_h_path = temp_dir / f"{dialog.name}_mfc.h"
    
    print(f"Extracting MFC files...")
    if not extract_mfc_from_git(repo_root, dialog.mfc_cpp, mfc_cpp_path):
        return False
    if not extract_mfc_from_git(repo_root, dialog.mfc_h, mfc_h_path):
        return False
    
    # Find wxWidgets header for control mapping
    wx_h_path = repo_root / "Core" / "Tools" / "W3DView" / dialog.wx_h
    
    # Run enhanced generator
    print(f"Generating Phase 2.5 infrastructure...")
    output_file = temp_dir / f"{dialog.name}_phase25.cpp"
    
    try:
        cmd = [
            'python3',
            str(repo_root / 'scripts' / 'generate_phase25_enhanced.py'),
            str(mfc_cpp_path),
            str(mfc_h_path),
            dialog.mfc_class
        ]
        
        if wx_h_path.exists():
            cmd.append(str(wx_h_path))
        
        result = subprocess.run(cmd, capture_output=True, text=True, cwd=repo_root)
        
        if result.returncode == 0:
            output_file.write_text(result.stdout)
            print(f"  ✅ Generated: {output_file}")
            
            # Show summary
            lines = result.stdout.count('\n')
            todos = result.stdout.count('TODO')
            includes = result.stdout.count('#include')
            print(f"  📊 Stats: {lines} lines, {includes} includes, {todos} TODOs")
            
            return True
        else:
            print(f"  ❌ Generation failed: {result.stderr}")
            return False
            
    except Exception as e:
        print(f"  ❌ Error generating: {e}")
        return False

def main():
    """Main batch conversion process"""
    
    # Find repository root
    repo_root = Path(__file__).parent.parent
    if not (repo_root / '.git').exists():
        repo_root = Path.cwd()
    
    print(f"Repository: {repo_root}")
    print(f"Processing {len(DIALOGS)} dialogs...")
    
    # Create temp directory for output
    temp_dir = Path('/tmp/phase25_batch_output')
    temp_dir.mkdir(exist_ok=True)
    print(f"Output directory: {temp_dir}")
    
    # Process each dialog
    success_count = 0
    failed_dialogs = []
    
    for dialog in DIALOGS:
        try:
            if generate_infrastructure(dialog, temp_dir, repo_root):
                success_count += 1
            else:
                failed_dialogs.append(dialog.name)
        except KeyboardInterrupt:
            print("\n\n⚠️  Interrupted by user")
            break
        except Exception as e:
            print(f"\n❌ Unexpected error processing {dialog.name}: {e}")
            failed_dialogs.append(dialog.name)
    
    # Summary
    print()
    print("=" * 70)
    print("BATCH CONVERSION SUMMARY")
    print("=" * 70)
    print(f"Total dialogs: {len(DIALOGS)}")
    print(f"Successful: {success_count}")
    print(f"Failed: {len(failed_dialogs)}")
    
    if failed_dialogs:
        print(f"\nFailed dialogs:")
        for name in failed_dialogs:
            print(f"  - {name}")
    
    print(f"\nGenerated files: {temp_dir}")
    print()
    print("Next steps:")
    print("  1. Review generated code in temp directory")
    print("  2. Manually integrate into wxWidgets dialog files")
    print("  3. Test compilation")
    print("  4. Refine patterns for remaining TODOs")

if __name__ == '__main__':
    main()
