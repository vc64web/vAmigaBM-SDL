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
#include "GUIComponent.h"

class Layer : public GUIComponent {
    
public:

    // Indicates whether the layer needs to update it's render objects
    bool isDirty = false;
            
    // Alpha channel parameters
    u8 alpha = 0, targetAlpha = 0;
    
    // Time until alpha is supposed to reach targetAlpha in seconds
    float delay;
    
    
    //
    // Initializing
    //
    
    Layer(Application &ref) : GUIComponent(ref) { }
    void init();

    
    //
    // Working with the layer
    //
    
    // Triggers an alpha animation
    void setTargetAlpha(isize target, float seconds);
    
    // Informs about the visual state of this layer
    virtual bool isVisible() { return alpha > 0; }
    virtual bool isTransparent() { return alpha < 255; }
    virtual bool isAnimating() { return alpha != targetAlpha; }
    virtual bool isFadingIn() { return targetAlpha > alpha; }
    virtual bool isFadingOut() { return targetAlpha < alpha; }
    
    void update(mm::Time dt);
    
    /*
    // Event loop handlers
    virtual void handle(const sf::Event &event) = 0;
    
    virtual void render() { };
    
    // Delegation methods
    virtual void resize(float width, float height) = 0;
    */
    
    // Notifications
    virtual void alphaDidChange() { }
};
