/*
**Command & Conquer Renegade(tm)
**XRC Loading Test Program
**Copyright 2026 TheSuperHackers
**
**This program is free software: you can redistribute it and/or modify
**it under the terms of the GNU General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.
*/

#include "W3DViewUI.h"
#include <wx/wx.h>
#include <wx/xrc/xmlres.h>
#include <iostream>
#include <vector>
#include <string>

// List of all dialog IDs to test
const std::vector<std::string> DIALOG_IDS = {
    "IDD_ABOUTBOX",
    "IDD_ADD_TO_LINEUP",
    "IDD_ANIMATED_SOUND_DIALOG",
    "IDD_BACKGROUND_BMP",
    "IDD_BACKGROUND_COLOR",
    "IDD_BACKGROUND_OBJECT",
    "IDD_BONE_MANAGEMENT",
    "IDD_CAMERA_DISTANCE",
    "IDD_CAMERA_SETTINGS",
    "IDD_COLOR_FORM",
    "IDD_COLOR_PICKER",
    "IDD_COLOR_SEL",
    "IDD_DISPLAYSPEED",
    "IDD_EDIT_LOD",
    "IDD_FORMVIEW",
    "IDD_GAMMA_DIALOG",
    "IDD_LIGHT_AMBIENT_DIALOG",
    "IDD_LIGHT_SCENE_DIALOG",
    "IDD_MAKE_AGGREGATE",
    "IDD_OPACITY",
    "IDD_OPACITY_VECTOR",
    "IDD_PARTICLE_BLUR_TIME_KEY",
    "IDD_PARTICLE_FRAME_KEY",
    "IDD_PARTICLE_ROTATION_KEY",
    "IDD_PARTICLE_SIZE",
    "IDD_PLAY_SOUND_EFFECT",
    "IDD_PROP_PAGE_ADVANIM_MIXING",
    "IDD_PROP_PAGE_ADVANIM_REPORT",
    "IDD_PROP_PAGE_ANIMATION",
    "IDD_PROP_PAGE_EMITTER_COLOR",
    "IDD_PROP_PAGE_EMITTER_FRAME",
    "IDD_PROP_PAGE_EMITTER_GEN",
    "IDD_PROP_PAGE_EMITTER_LINEGROUP",
    "IDD_PROP_PAGE_EMITTER_LINEPROPS",
    "IDD_PROP_PAGE_EMITTER_PARTICLE",
    "IDD_PROP_PAGE_EMITTER_PHYSICS",
    "IDD_PROP_PAGE_EMITTER_ROTATION",
    "IDD_PROP_PAGE_EMITTER_SIZE",
    "IDD_PROP_PAGE_EMITTER_USER",
    "IDD_PROP_PAGE_HIERARCHY",
    "IDD_PROP_PAGE_MESH",
    "IDD_PROP_PAGE_RING_COLOR",
    "IDD_PROP_PAGE_RING_GEN",
    "IDD_PROP_PAGE_RING_SCALE",
    "IDD_PROP_PAGE_SPHERE_COLOR",
    "IDD_PROP_PAGE_SPHERE_GEN",
    "IDD_PROP_PAGE_SPHERE_SCALE",
    "IDD_RENAME_AGGREGATE",
    "IDD_RENDER_DEVICE_SELECTOR",
    "IDD_RESOLUTION",
    "IDD_SAVE_SETTINGS",
    "IDD_SCALE_KEY",
    "IDD_SOUND_EDIT",
    "IDD_TEXTURE_MANAGMENT",
    "IDD_TEXTURE_MANAGMENT1",
    "IDD_TEXTURE_PATHS",
    "IDD_TEXTURE_SETTINGS",
    "IDD_VOLUME_RANDOMIZER",
    "IDD_XXX_BROWSE_DIRECTORY"
};

class XRCTestApp : public wxApp
{
public:
    virtual bool OnInit() override;
    virtual int OnRun() override;
};

bool XRCTestApp::OnInit()
{
    // Initialize XRC system
    wxXmlResource::Get()->InitAllHandlers();
    
    // Load all W3DView dialog resources
    std::cout << "🔄 Loading XRC resources..." << std::endl;
    InitW3DViewXmlResources();
    std::cout << "✅ XRC resources loaded\n" << std::endl;
    
    return true;
}

int XRCTestApp::OnRun()
{
    std::cout << "🧪 Testing " << DIALOG_IDS.size() << " dialog definitions\n" << std::endl;
    
    int loaded = 0;
    int failed = 0;
    
    for (const auto& dialog_id : DIALOG_IDS) {
        // Try to load dialog
        wxDialog* dialog = wxXmlResource::Get()->LoadDialog(nullptr, dialog_id);
        
        if (dialog) {
            std::cout << "✅ " << dialog_id << std::endl;
            dialog->Destroy();
            loaded++;
        } else {
            std::cerr << "❌ " << dialog_id << " - FAILED TO LOAD" << std::endl;
            failed++;
        }
    }
    
    std::cout << "\n======================================" << std::endl;
    std::cout << "📊 XRC Loading Test Results" << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << "   ✅ Loaded: " << loaded << "/" << DIALOG_IDS.size() << std::endl;
    std::cout << "   ❌ Failed: " << failed << "/" << DIALOG_IDS.size() << std::endl;
    
    if (failed == 0) {
        std::cout << "\n✅ ALL DIALOGS LOADED SUCCESSFULLY!" << std::endl;
        return 0;
    } else {
        std::cerr << "\n❌ SOME DIALOGS FAILED TO LOAD" << std::endl;
        return 1;
    }
}

wxIMPLEMENT_APP_NO_MAIN(XRCTestApp);

int main(int argc, char** argv)
{
    wxApp::SetInstance(new XRCTestApp());
    return wxEntry(argc, argv);
}
