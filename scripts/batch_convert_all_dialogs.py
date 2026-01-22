#!/usr/bin/env python3
"""
batch_convert_all_dialogs.py - Run mfc2wx_events.py on all dialogs

Creates event tables for all 59 W3DView dialogs
"""

import subprocess
import sys
from pathlib import Path
import json

# Mapping of MFC dialog names to wxWidgets dialog names
# Based on existing files in dialogs/ directory
DIALOG_MAPPING = {
    # MFC .cpp filename -> wxWidgets filename (without _wx.cpp)
    'AnimationSpeed.cpp': 'Displayspeed',
    'BackgroundColorDialog.cpp': 'BackgroundColor',
    'BackgroundBMPDialog.cpp': 'BackgroundBmp',
    'BackgroundObjectDialog.cpp': 'BackgroundObject',
    'BoneMgrDialog.cpp': 'BoneManagement',
    'CameraDistanceDialog.cpp': 'CameraDistance',
    'CameraSettingsDialog.cpp': 'CameraSettings',
    'AddToLineupDialog.cpp': 'AddToLineup',
    'AggregateNameDialog.cpp': 'AggregateName',
    'AmbientLightDialog.cpp': 'AmbientLight',
    'AnimatedSoundOptionsDialog.cpp': 'AnimatedSoundDialog',
    'AnimationPropPage.cpp': 'PropPageAnimation',
    'AssetPropertySheet.cpp': 'AssetPropertySheet',
    'ColorSelectionDialog.cpp': 'ColorSel',
    'DeviceSelectionDialog.cpp': 'DeviceSelection',
    'DirectoryDialog.cpp': 'Directory',
    'EditLODDialog.cpp': 'EditLod',
    'EmitterInstancePropPage.cpp': 'PropPageEmitterInstance',
    'EmitterPropPage.cpp': 'PropPageEmitter',
    'EmitterUserPage.cpp': 'PropPageEmitterUser',
    'FXNuggetPropPage.cpp': 'PropPageFxNugget',
    'FXShaderPropPage.cpp': 'PropPageFxShader',
    'FXTexturePropPage.cpp': 'PropPageFxTexture',
    'GeneralPropPage.cpp': 'PropPageGeneral',
    'HierarchyPropPage.cpp': 'PropPageHierarchy',
    'HLodPropPage.cpp': 'PropPageHlod',
    'LightSettingsDialog.cpp': 'LightSettings',
    'MaterialEditorDialog.cpp': 'MaterialEditor',
    'MaterialPassDlg.cpp': 'MaterialPass',
    'MeshPropPage.cpp': 'PropPageMesh',
    'NormalMapGeneratorDialog.cpp': 'NormalMapGenerator',
    'ObjectPropertiesDlg.cpp': 'ObjectProperties',
    'ParticlePropertySheet.cpp': 'ParticlePropertySheet',
    'PreviewLODDialog.cpp': 'PreviewLod',
    'ScriptDialog.cpp': 'Script',
    'SelectAnimationDialog.cpp': 'SelectAnimation',
    'ShaderDlg.cpp': 'Shader',
    'SkinPropPage.cpp': 'PropPageSkin',
    'SoundRObjDlg.cpp': 'SoundRobj',
    'TexturePathDialog.cpp': 'TexturePath',
    'TextureReductionDialog.cpp': 'TextureReduction',
    'VertexMaterialDlg.cpp': 'VertexMaterial',
    'AdvancedAnimSheet.cpp': 'AdvancedAnimSheet',
    'AnimMixingPage.cpp': 'AnimMixingPage',
    'AnimReportPage.cpp': 'AnimReportPage',
}

# Additional XRC name mapping (some use different IDD names)
XRC_MAPPING = {
    'Displayspeed': 'idd_displayspeed',
    'BackgroundColor': 'idd_background_color',
    'BackgroundBmp': 'idd_background_bmp',
    'BackgroundObject': 'idd_background_object',
    'BoneManagement': 'idd_bone_management',
    'CameraDistance': 'idd_camera_distance',
    'CameraSettings': 'idd_camera_settings',
    'AddToLineup': 'idd_add_to_lineup',
    'AggregateName': 'idd_aggregate_name',
    'AmbientLight': 'idd_ambient_light',
    'AnimatedSoundDialog': 'idd_animated_sound_dialog',
    'PropPageAnimation': 'idd_animation',
    'AssetPropertySheet': 'idd_asset_property_sheet',
    'ColorSel': 'idd_color_sel',
    'DeviceSelection': 'idd_device_selection',
    'Directory': 'idd_directory',
    'EditLod': 'idd_edit_lod',
    'PropPageEmitterInstance': 'idd_emitter_instance',
    'PropPageEmitter': 'idd_emitter',
    'PropPageEmitterUser': 'idd_emitter_user',
    'PropPageFxNugget': 'idd_fx_nugget',
    'PropPageFxShader': 'idd_fx_shader',
    'PropPageFxTexture': 'idd_fx_texture',
    'PropPageGeneral': 'idd_general',
    'PropPageHierarchy': 'idd_hierarchy',
    'PropPageHlod': 'idd_hlod',
    'LightSettings': 'idd_light_settings',
    'MaterialEditor': 'idd_material_editor',
    'MaterialPass': 'idd_material_pass',
    'PropPageMesh': 'idd_mesh',
    'NormalMapGenerator': 'idd_normal_map_generator',
    'ObjectProperties': 'idd_object_properties',
    'ParticlePropertySheet': 'idd_particle_property_sheet',
    'PreviewLod': 'idd_preview_lod',
    'Script': 'idd_script',
    'SelectAnimation': 'idd_select_animation',
    'Shader': 'idd_shader',
    'PropPageSkin': 'idd_skin',
    'SoundRobj': 'idd_sound_robj',
    'TexturePath': 'idd_texture_path',
    'TextureReduction': 'idd_texture_reduction',
    'VertexMaterial': 'idd_vertex_material',
}


def find_xrc_file(wx_name, ui_dir):
    """Find the XRC file for a given wx dialog name"""
    xrc_base = XRC_MAPPING.get(wx_name)
    if xrc_base:
        xrc_path = ui_dir / f"{xrc_base}.xrc"
        if xrc_path.exists():
            return xrc_path
    
    # Try lowercase version of dialog name
    xrc_path = ui_dir / f"idd_{wx_name.lower()}.xrc"
    if xrc_path.exists():
        return xrc_path
    
    return None


def main():
    root_dir = Path(__file__).parent.parent
    mfc_dir = Path("/tmp/mfc_dialogs")
    wx_dialogs_dir = root_dir / "Core/Tools/W3DView/dialogs"
    ui_dir = root_dir / "Core/Tools/W3DView/ui"
    
    # First, extract all MFC dialog files
    print("=" * 70)
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
