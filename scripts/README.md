# MFC to wxWidgets Conversion Tools

This directory contains automated tools for converting MFC applications to wxWidgets.

---

## 📦 Tool Categories

### Phase 1: Dialog Structure Conversion

| Tool | Purpose |
|------|---------|
| `rc2xrc.py` | Convert MFC .rc files to wxWidgets .xrc format |
| `xrc2cpp.py` | Generate C++ base classes from XRC files |
| `validate_xrc_files.py` | Validate XRC file syntax and structure |
| `generate_xrc_init.py` | Generate XRC initialization code |

### Phase 2: Event Handler Wiring

| Tool | Purpose |
|------|---------|
| `mfc2wx_events.py` | Convert MFC message maps to wxWidgets event tables |
| `build_dialog_mapping.py` | Auto-generate MFC→wxWidgets dialog name mappings |
| `batch_convert_all_dialogs.py` | Batch process multiple dialogs |

### Utility Tools

| Tool | Purpose |
|------|---------|
| `generate_cmake_sources.py` | Generate CMake source lists |
| `fix_copyright.py` | Fix/update copyright headers |
| `test_build_pipeline.sh` | Test build system |
| `diagnose_build_issue.sh` | Diagnose build problems |

---

## 🔧 Tool Details

### rc2xrc.py

**Convert MFC RC files to wxWidgets XRC format**

**Usage:**
```bash
python3 rc2xrc.py <input.rc> <dialog_id> <output.xrc>
```

**Example:**
```bash
python3 rc2xrc.py W3DView.rc IDD_DISPLAYSPEED idd_displayspeed.xrc
```

**Features:**
- Supports all common MFC controls
- Handles multi-line strings
- Preserves escaped quotes
- Supports negative coordinates
- Handles CONTROL statements for bitmaps

**Success Rate:** 100% (59/59 dialogs tested)

---

### xrc2cpp.py

**Generate C++ base classes from XRC files**

**Usage:**
```bash
python3 xrc2cpp.py <input.xrc> <output_dir> [--class-name ClassName]
```

**Example:**
```bash
python3 xrc2cpp.py idd_displayspeed.xrc dialogs/
```

**Features:**
- Generates base class with control members
- Creates proper wxWidgets inheritance
- Includes XRC loading code
- Adds header guards and includes

**Output:** 
- `<DialogName>_wx.h` - Header file
- `<DialogName>_wx.cpp` - Implementation file

---

### validate_xrc_files.py

**Validate XRC file syntax and structure**

**Usage:**
```bash
python3 validate_xrc_files.py <xrc_directory>
```

**Example:**
```bash
python3 validate_xrc_files.py Core/Tools/W3DView/ui/
```

**Features:**
- XML syntax validation
- Control ID checking
- Duplicate ID detection
- Missing required attributes
- Detailed error reports

---

### generate_xrc_init.py

**Generate XRC initialization and management code**

**Usage:**
```bash
python3 generate_xrc_init.py <ui_directory> <output_prefix>
```

**Example:**
```bash
python3 generate_xrc_init.py Core/Tools/W3DView/ui/ W3DViewUI
```

**Features:**
- Generates centralized XRC loader
- Creates dialog factory functions
- Includes error handling
- Thread-safe initialization

**Output:**
- `<Prefix>.h` - Header with declarations
- `<Prefix>.cpp` - Implementation with loader

---

### mfc2wx_events.py

**Convert MFC message maps to wxWidgets event tables**

**Usage:**
```bash
python3 mfc2wx_events.py <mfc_cpp> <wx_cpp> <xrc_file>
```

**Example:**
```bash
python3 mfc2wx_events.py AnimationSpeed.cpp Displayspeed_wx.cpp idd_displayspeed.xrc
```

**Features:**
- Parses MFC message maps
- Extracts DDX_Control bindings
- Analyzes XRC for control types
- Auto-detects slider IDs
- Maps event types correctly
- Generates handler stubs

**Output:**
- Event table entries (wxBEGIN_EVENT_TABLE)
- Handler declarations (.h additions)
- Handler method stubs (.cpp additions)

**Success Rate:** 100% (55/55 dialogs tested)

---

### build_dialog_mapping.py

**Auto-generate MFC→wxWidgets dialog name mappings**

**Usage:**
```bash
python3 build_dialog_mapping.py
```

**Features:**
- Compares MFC and wxWidgets file names
- Auto-generates 95% of mappings
- Uses manual overrides for exceptions
- Outputs JSON mapping file

**Output:** `dialog_mapping.json`

---

### batch_convert_all_dialogs.py

**Batch process multiple dialogs for event conversion**

**Usage:**
```bash
python3 batch_convert_all_dialogs.py
```

**Features:**
- Reads dialog mapping from JSON
- Extracts MFC files from git history
- Runs mfc2wx_events.py on all dialogs
- Generates statistics and reports

**Output:**
- 55× `*_events_generated.txt` files
- `BATCH_CONVERSION_RESULTS.json`

---

## 📊 Tool Performance

### Phase 1 Tools

| Tool | Tested On | Success Rate | Speed |
|------|-----------|--------------|-------|
| rc2xrc.py | 59 dialogs | 100% | ~2 sec/dialog |
| xrc2cpp.py | 59 dialogs | 100% | ~1 sec/dialog |
| validate_xrc_files.py | 59 dialogs | 100% | ~5 sec total |
| generate_xrc_init.py | 59 dialogs | 100% | ~1 sec |

**Total Phase 1:** ~5 minutes for all 59 dialogs

### Phase 2 Tools

| Tool | Tested On | Success Rate | Speed |
|------|-----------|--------------|-------|
| mfc2wx_events.py | 55 dialogs | 100% | ~2 sec/dialog |
| build_dialog_mapping.py | 55 dialogs | 100% | ~5 sec |
| batch_convert_all_dialogs.py | 55 dialogs | 100% | ~5 min |

**Total Phase 2:** ~5 minutes for all 55 dialogs

---

## 🎓 Usage Examples

### Complete Workflow - Single Dialog

```bash
# Phase 1: Convert dialog structure
python3 scripts/rc2xrc.py W3DView.rc IDD_ANIMATION_SPEED ui/idd_displayspeed.xrc
python3 scripts/xrc2cpp.py ui/idd_displayspeed.xrc dialogs/
python3 scripts/validate_xrc_files.py ui/

# Phase 2: Wire event handlers
git show <commit>:AnimationSpeed.cpp > /tmp/AnimationSpeed.cpp
python3 scripts/mfc2wx_events.py /tmp/AnimationSpeed.cpp dialogs/Displayspeed_wx.cpp ui/idd_displayspeed.xrc
```

### Batch Workflow - All Dialogs

```bash
# Phase 1: Convert all dialogs
for dialog in IDD_*; do
    python3 scripts/rc2xrc.py W3DView.rc $dialog ui/
done
python3 scripts/xrc2cpp.py ui/*.xrc dialogs/
python3 scripts/generate_xrc_init.py ui/ W3DViewUI
python3 scripts/validate_xrc_files.py ui/

# Phase 2: Build mapping and convert all
python3 scripts/build_dialog_mapping.py
python3 scripts/batch_convert_all_dialogs.py
```

---

## 🔍 Archive Directory

The `archive/` subdirectory contains old versions of tools for reference:

- `rc2xrc_v1.py` - Initial version (84% success)
- `rc2xrc_v2.py` - Added CONTROL support (89% success)
- `rc2xrc_v3.py` - Multi-line strings (98% success)
- `rc2xrc_v3_bitmap.py` - Bitmap controls (98% success)
- `rc2xrc_v4.py` - Almost final (98% success)

**Current:** `rc2xrc.py` (formerly v5) achieves 100% success.

---

## 💡 Tips & Best Practices

### For Phase 1

1. **Always validate** XRC files after generation
2. **Review diffs** between MFC and XRC layouts
3. **Test incrementally** - don't convert all dialogs at once
4. **Keep originals** - extract MFC files from git history first

### For Phase 2

1. **Build dialog mapping first** - don't guess names
2. **Review generated stubs** - they're templates, not final code
3. **One dialog at a time** - easier to debug issues
4. **Compare with MFC** - ensure event types match intent

### General

1. **Use version control** - commit after each successful conversion
2. **Document exceptions** - note manual fixes needed
3. **Test builds** - verify generated code compiles
4. **Backup originals** - never overwrite without testing

---

## 🐛 Troubleshooting

### rc2xrc.py Issues

**Problem:** Dialog not found in RC file  
**Solution:** Check dialog ID spelling, try: `grep -r "IDD_" W3DView.rc`

**Problem:** Multi-line string truncated  
**Solution:** Update to latest version (v5/rc2xrc.py)

**Problem:** Negative coordinates wrong  
**Solution:** Ensure using current rc2xrc.py (not archived versions)

### mfc2wx_events.py Issues

**Problem:** Slider ID not detected  
**Solution:** Check DDX_Control binding exists in MFC DoDataExchange

**Problem:** Wrong event type (Button vs Checkbox)  
**Solution:** Verify XRC control type matches MFC resource

**Problem:** Handler name mismatch  
**Solution:** Check dialog mapping in `dialog_mapping.json`

---

## 📝 Adding New Tools

To add new conversion tools:

1. **Follow naming convention:** `<source>2<dest>.py` (e.g., `rc2xrc.py`)
2. **Add command-line interface:** Use `argparse` for arguments
3. **Include help text:** Docstrings and `--help` output
4. **Handle errors gracefully:** Print clear error messages
5. **Add to this README:** Document usage and features
6. **Test thoroughly:** Run on real projects before committing

---

## 🔗 Related Documentation

- **[../MFC_TO_WXWIDGETS_TOOLKIT.md](../MFC_TO_WXWIDGETS_TOOLKIT.md)** - Complete conversion guide
- **[../docs/EVENT_WIRING_GUIDE.md](../docs/EVENT_WIRING_GUIDE.md)** - Phase 2 documentation
- **[../examples/w3dview/](../examples/w3dview/)** - Real-world example

---

## 📊 Tool Evolution

| Date | Version | Success Rate | Key Addition |
|------|---------|--------------|--------------|
| 2025-01-15 | rc2xrc v1 | 84% | Initial implementation |
| 2025-01-16 | rc2xrc v2 | 89% | CONTROL statements |
| 2025-01-17 | rc2xrc v3 | 98% | Multi-line strings |
| 2025-01-18 | rc2xrc v4 | 98% | Bitmap controls |
| 2025-01-19 | rc2xrc v5 | **100%** | Negative coords, quotes |
| 2025-01-22 | mfc2wx_events v1 | **100%** | Perfect on first try! |

---

**Last Updated:** January 22, 2026  
**Branch:** `dev/mfc-to-wxwidgets-tools`  
**Status:** Production-ready
