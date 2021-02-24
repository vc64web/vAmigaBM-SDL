// -----------------------------------------------------------------------------
// This file is part of vAmiga Bare Metal
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#pragma once

#include "Window/Renderer.h"
#include "Graphics/Color.h"

namespace mm {

class Window
{
    SDL_Window *window = nullptr;
        
public:
    
    Renderer renderer;
    
    int scale;
    
public:
    
    //
    // Constructing
    //
    
    Window();
    ~Window();
        
    // Constructing coordinates
    /*
    X x(Pixel value) { return X(*this, value); }
    Y y(Pixel value) { return Y(*this, value); }
    
    X x(SubPixel value) { return X(*this, value); }
    Y y(SubPixel value) { return Y(*this, value); }

    X x(Fraction value) { return X(*this, value); }
    Y y(Fraction value) { return Y(*this, value); }
    */
    
    //
    // Initializing
    //
    
    void create(const char *title, int w, int h, u32 flags = SDL_WINDOW_OPENGL);
    void destroy();
    
    
    //
    // Querying properties
    //
    
    SDL_Window *opaque() { return window; }

    // Returns the window dimensions in pixels or sub-pixels
    int pixelWidth();
    int pixelHeight();
    int subPixelWidth();
    int subPixelHeight();
        
    bool isOpen() { return window != nullptr; }
    void close();
    
    
    //
    // Rendering
    //
    
    // Clears the render target
    void clear(mm::Color color);
    void clear();
    
    // Renders the window
    void present();
};

}
