// -----------------------------------------------------------------------------
// This file is part of vAmiga Bare Metal
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#pragma once

#include "Layer.h"
#include "Multimedia.h"

class Canvas : public Layer {
    
    /*
public:
    
    // Texture constants
private:
    
    // The current screen buffer
    ScreenBuffer screenBuffer = { nullptr, false };
    
    // The emulator texture
    sf::Texture emuTex;
 
    // Render object
    ImageView view = ImageView(Align::UpperLeft);
    
    // Indicates if the aspect ratio should be kept constant
    bool letterbox = true;
    
    // Initial mouse position after releasing
    int baseX, baseY;
    */
    
public:
        
    //
    // Initializing
    //
    
public:
    
    Canvas(class Application &ref);
    ~Canvas();
    
    // Delegation methods
    void init();
    void configure();
    
    /*

    //
    // Methods from Layer class
    //
    
    void handle(const sf::Event &event) override;
    void update(sf::Time dt) override; 
    void render() override;
    void resize(float width, float height) override;
    */
    
    //
    // Performing continuous tasks
    //
    
    void update(i64 frame, mm::Time dt);
    void render();
    
    
    //
    // Responding to events
    //

    void respond(mm::Event &event);
    void resize(int w, int h);
    void mouseMoved(int dx, int dy);
    
    
    //
    // Opening and closing
    //
    
public:
    
    // Shows or hides the canvas window
    void open() { setTargetAlpha(0xFF, 0.5); }
    void close() { setTargetAlpha(0x00, 0.5); }
    void toggle() { isVisible() ? close() : open(); }
};
