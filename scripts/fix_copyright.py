#!/usr/bin/env python3
"""
Fix Copyright Headers for Community Files
Changes EA copyright to TheSuperHackers copyright for new community files
"""

import sys
from pathlib import Path
import re

OLD_COPYRIGHT = "Copyright 2025 Electronic Arts Inc."
NEW_COPYRIGHT = "Copyright 2026 TheSuperHackers"

def fix_file_copyright(file_path):
    """Fix copyright in a single file"""
    try:
        content = file_path.read_text(encoding='utf-8')
        
        if OLD_COPYRIGHT in content:
            new_content = content.replace(OLD_COPYRIGHT, NEW_COPYRIGHT)
            file_path.write_text(new_content, encoding='utf-8')
            return True
        return False
    except Exception as e:
        print(f"Error processing {file_path}: {e}")
        return False

def main():
    if len(sys.argv) < 2:
        print("Usage: fix_copyright.py <directory_or_file> [...]")
        sys.exit(1)
    
    paths = [Path(p) for p in sys.argv[1:]]
    
    files_to_fix = []
    for path in paths:
        if path.is_file():
            files_to_fix.append(path)
        elif path.is_dir():
            files_to_fix.extend(path.rglob('*.h'))
            files_to_fix.extend(path.rglob('*.cpp'))
            files_to_fix.extend(path.rglob('*.py'))
    
    print(f"🔍 Checking {len(files_to_fix)} files for copyright corrections...")
    
    fixed_count = 0
    for file_path in files_to_fix:
        if fix_file_copyright(file_path):
            print(f"✅ Fixed: {file_path}")
            fixed_count += 1
    
    print(f"\n📊 Summary:")
    print(f"   ✅ Fixed: {fixed_count}")
    print(f"   ⏭️  Skipped: {len(files_to_fix) - fixed_count}")
    
    if fixed_count > 0:
        print(f"\n✅ Copyright headers corrected to: {NEW_COPYRIGHT}")

if __name__ == "__main__":
    main()
