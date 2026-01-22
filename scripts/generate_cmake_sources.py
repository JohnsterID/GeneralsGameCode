#!/usr/bin/env python3
"""
CMakeLists.txt Source List Generator
Automatically generates source file list for CMakeLists.txt
"""

import sys
from pathlib import Path

def generate_source_list(directory, pattern='*_wx.*'):
    """Generate sorted list of source files"""
    directory = Path(directory)
    
    # Find all matching files
    headers = sorted(directory.glob(f'{pattern.replace(".*", ".h")}'))
    sources = sorted(directory.glob(f'{pattern.replace(".*", ".cpp")}'))
    
    # Pair them: .cpp then .h
    files = []
    for src in sources:
        files.append(src.name)
        # Find matching header
        header = src.with_suffix('.h')
        if header in headers:
            files.append(header.name)
    
    # Add any orphaned headers
    for hdr in headers:
        if hdr.name not in files:
            files.append(hdr.name)
    
    return files

def format_cmake_list(files, indent='        '):
    """Format files as CMake list entries"""
    lines = [f'{indent}"{f}"' for f in files]
    return '\n'.join(lines)

def main():
    if len(sys.argv) < 2:
        print("Usage: generate_cmake_sources.py <directory> [pattern]")
        print("Example: generate_cmake_sources.py Core/Tools/W3DView/dialogs '*_wx.*'")
        sys.exit(1)
    
    directory = sys.argv[1]
    pattern = sys.argv[2] if len(sys.argv) > 2 else '*_wx.*'
    
    files = generate_source_list(directory, pattern)
    
    print(f"# Auto-generated list of {len(files)} files from {directory}")
    print(format_cmake_list(files))
    
    print(f"\n# Total: {len(files)} files", file=sys.stderr)

if __name__ == "__main__":
    main()
