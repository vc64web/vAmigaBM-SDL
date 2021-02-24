// -----------------------------------------------------------------------------
// This file is part of vAmiga Bare Metal
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#pragma once

#include "Multimedia.h"
#include "AssetManager.h"
#include "Layer.h"

class SplashScreen : public Layer {

public:
            
    // Background
    mm::GradientView background;
  
    // vAmiga logo
    mm::ImageView logo;
    
    // Text messages
    mm::TextView title1;
    mm::TextView title2;
    mm::TextView errMsg;
    mm::TextView runMsg;
    mm::TextView info1;
    mm::TextView info2;
    mm::TextView info3;

    // Location of the config file
    string configPath;
    string configFile;

    // Key actions
    typedef enum { None, Launch, Quit, Aros, Menu, Console } KeyAction;
    KeyAction spcAction = None;
    KeyAction f10Action = None;
    
    
    //
    // Initializing
    //

public:

    SplashScreen(class Application &ref);
    ~SplashScreen();
    
    // Delegation methods
    void init();
    void awake() { launchPhase(1); }
    
    // Runs a certain launch phase
    void launchPhase(isize phase);
        
    // Loads the Aros replacement Roms
    bool loadAros();
    
    
    //
    // Methods from Layer class
    //

public:
    
    virtual bool isVisible() override;
        
    
    //
    // Performing continuous tasks
    //
    
    void update(i64 frame, mm::Time dt);
    void render();
    
    
    //
    // Responding to events
    //

    void respond(mm::Event &event);
    void respondToKeyboardEvent(mm::Event &event);
    void resize(int w, int h);
    
    
    //
    // Receiving notifications
    //
    
    void alphaDidChange() override;
};
