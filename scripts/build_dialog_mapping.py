#!/usr/bin/env python3
"""
build_dialog_mapping.py - Auto-generate MFC to wxWidgets dialog name mapping

Compares MFC and wxWidgets dialog file names and creates mapping based on:
1. Exact matches (case-insensitive)
2. Partial matches (removing common suffixes)
3. Manual overrides for known mappings
"""

import re
from pathlib import Path
import json

# Known manual mappings (from previous work and IDD analysis)
MANUAL_MAPPINGS = {
    'AnimationSpeed.cpp': 'Displayspeed',
    'AnimatedSoundOptionsDialog.cpp': 'AnimatedSoundDialog',
    'BackgroundBMPDialog.cpp': 'BackgroundBmp',
    'BoneMgrDialog.cpp': 'BoneManagement',
    'ColorSelectionDialog.cpp': 'ColorSel',
    'DirectoryDialog.cpp': 'XxxBrowseDirectory',
    'EditLODDialog.cpp': 'EditLod',
    'AggregateNameDialog.cpp': 'MakeAggregate',  # IDD_MAKE_AGGREGATE
    'AmbientLightDialog.cpp': 'LightAmbientDialog',  # IDD_LIGHT_AMBIENT_DIALOG
    'AnimMixingPage.cpp': 'PropPageAdvanimMixing',  # IDD_PROP_PAGE_ADVANIM_MIXING
    'AnimReportPage.cpp': 'PropPageAdvanimReport',  # IDD_PROP_PAGE_ADVANIM_REPORT
    'DeviceSelectionDialog.cpp': 'RenderDeviceSelector',  # IDD_RENDER_DEVICE_SELECTOR
    'EmitterGeneralPropPage.cpp': 'PropPageEmitterGen',  # IDD_PROP_PAGE_EMITTER_GEN
    'RingGeneralPropPage.cpp': 'PropPageRingGen',  # IDD_PROP_PAGE_RING_GEN
    'RingSizePropPage.cpp': 'PropPageRingScale',  # IDD_PROP_PAGE_RING_SCALE
    'SceneLightDialog.cpp': 'LightSceneDialog',  # IDD_LIGHT_SCENE_DIALOG
    'SphereGeneralPropPage.cpp': 'PropPageSphereGen',  # IDD_PROP_PAGE_SPHERE_GEN
    'SphereSizePropPage.cpp': 'PropPageSphereScale',  # IDD_PROP_PAGE_SPHERE_SCALE
    'TextureMgrDialog.cpp': 'TextureManagment',  # IDD_TEXTURE_MANAGMENT
    'ScaleDialog.cpp': 'ScaleKey',  # Better match than PropPageRingScale
    'ColorPickerDialogClass.cpp': 'ColorPicker',  # Duplicate, same as ColorPicker.cpp
    'EmitterLinePropPage.cpp': 'PropPageEmitterLineprops',  # Better match than LineGroup
    'AdvancedAnimSheet.cpp': None,  # No match (skip - property sheet)
    'AssetPropertySheet.cpp': None,  # No match (skip - property sheet)
    'EmitterPropertySheet.cpp': None,  # No match (skip - property sheet)
    'RingPropertySheet.cpp': None,  # No match (skip - property sheet)
    'SpherePropertySheet.cpp': None,  # No match (skip - property sheet)
}


def normalize_name(name):
    """Normalize dialog name for comparison"""
    # Remove extension
    name = name.replace('.cpp', '')
    # Remove common suffixes
    name = re.sub(r'(Dialog|PropPage|Sheet)$', '', name)
    # Convert to lowercase for comparison
    return name.lower()


def find_best_match(mfc_file, wx_files):
    """Find best matching wxWidgets file for MFC file"""
    # Check manual mapping first
    if mfc_file in MANUAL_MAPPINGS:
        return MANUAL_MAPPINGS[mfc_file]
    
    mfc_norm = normalize_name(mfc_file)
    
    # Try exact match
    for wx_file in wx_files:
        if normalize_name(wx_file) == mfc_norm:
            return wx_file
    
    # Try partial match
    for wx_file in wx_files:
        wx_norm = normalize_name(wx_file)
        # Check if one is substring of other
        if mfc_norm in wx_norm or wx_norm in mfc_norm:
            # Check it's not too generic
            if len(mfc_norm) > 4 or len(wx_norm) > 4:
                return wx_file
    
    return None


def main():
    # MFC dialog files (from git history)
    mfc_dialogs = [
        'AddToLineupDialog.cpp',
        'AggregateNameDialog.cpp',
        'AmbientLightDialog.cpp',
        'AnimMixingPage.cpp',
        'AnimReportPage.cpp',
        'AnimatedSoundOptionsDialog.cpp',
        'AnimationPropPage.cpp',
        'AnimationSpeed.cpp',
        'BackgroundBMPDialog.cpp',
        'BackgroundColorDialog.cpp',
        'BackgroundObjectDialog.cpp',
        'BoneMgrDialog.cpp',
        'CameraDistanceDialog.cpp',
        'CameraSettingsDialog.cpp',
        'ColorPicker.cpp',
        'ColorPickerDialogClass.cpp',
        'ColorSelectionDialog.cpp',
        'DeviceSelectionDialog.cpp',
        'DirectoryDialog.cpp',
        'EditLODDialog.cpp',
        'EmitterColorPropPage.cpp',
        'EmitterFramePropPage.cpp',
        'EmitterGeneralPropPage.cpp',
        'EmitterLineGroupPropPage.cpp',
        'EmitterLinePropPage.cpp',
        'EmitterParticlePropPage.cpp',
        'EmitterPhysicsPropPage.cpp',
        'EmitterRotationPropPage.cpp',
        'EmitterSizePropPage.cpp',
        'EmitterUserPropPage.cpp',
        'GammaDialog.cpp',
        'HierarchyPropPage.cpp',
        'MeshPropPage.cpp',
        'OpacitySettingsDialog.cpp',
        'OpacityVectorDialog.cpp',
        'ParticleBlurTimeKeyDialog.cpp',
        'ParticleFrameKeyDialog.cpp',
        'ParticleRotationKeyDialog.cpp',
        'ParticleSizeDialog.cpp',
        'PlaySoundDialog.cpp',
        'ResolutionDialog.cpp',
        'RingColorPropPage.cpp',
        'RingGeneralPropPage.cpp',
        'RingSizePropPage.cpp',
        'SaveSettingsDialog.cpp',
        'ScaleDialog.cpp',
        'SceneLightDialog.cpp',
        'SoundEditDialog.cpp',
        'SphereColorPropPage.cpp',
        'SphereGeneralPropPage.cpp',
        'SphereSizePropPage.cpp',
        'TextureMgrDialog.cpp',
        'TexturePathDialog.cpp',
        'TextureSettingsDialog.cpp',
        'VolumeRandomDialog.cpp',
    ]
    
    # wxWidgets dialog files (current)
    wx_dir = Path('Core/Tools/W3DView/dialogs')
    wx_files = sorted([f.stem.replace('_wx', '') for f in wx_dir.glob('*_wx.cpp')])
    
    print("=" * 70)
    print("Building MFC → wxWidgets Dialog Mapping")
    print("=" * 70)
    print(f"MFC dialogs: {len(mfc_dialogs)}")
    print(f"wxWidgets dialogs: {len(wx_files)}")
    print()
    
    mapping = {}
    matched = []
    unmatched = []
    
    for mfc_file in mfc_dialogs:
        wx_match = find_best_match(mfc_file, wx_files)
        
        if wx_match:
            mapping[mfc_file] = wx_match
            matched.append((mfc_file, wx_match))
            print(f"✓ {mfc_file:40} → {wx_match}")
        else:
            unmatched.append(mfc_file)
            print(f"✗ {mfc_file:40} → NO MATCH")
    
    print()
    print("=" * 70)
    print(f"Matched: {len(matched)}/{len(mfc_dialogs)}")
    print(f"Unmatched: {len(unmatched)}/{len(mfc_dialogs)}")
    print("=" * 70)
    
    if unmatched:
        print("\nUnmatched MFC files:")
        for mfc_file in unmatched:
            print(f"  - {mfc_file}")
        
        print("\nAvailable wxWidgets files not matched:")
        matched_wx = set(mapping.values())
        unmatched_wx = [wx for wx in wx_files if wx not in matched_wx]
        for wx_file in unmatched_wx:
            print(f"  - {wx_file}")
    
    # Save mapping
    output_file = Path('dialog_mapping.json')
    with open(output_file, 'w') as f:
        json.dump({
            'mapping': mapping,
            'matched': len(matched),
            'total': len(mfc_dialogs),
            'unmatched_mfc': unmatched,
            'unmatched_wx': [wx for wx in wx_files if wx not in mapping.values()]
        }, f, indent=2)
    
    print(f"\nMapping saved to: {output_file}")
    
    return 0 if not unmatched else 1


if __name__ == '__main__':
    import sys
    sys.exit(main())
