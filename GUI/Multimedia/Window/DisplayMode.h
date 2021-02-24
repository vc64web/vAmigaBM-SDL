// -----------------------------------------------------------------------------
// This file is part of vAmiga Bare Metal
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#pragma once

#include "Aliases.h"
#include <SDL.h>

namespace mm {

class DisplayMode {
    
    SDL_DisplayMode mode;
    
public:
    
    // Returns the number of available display modes
    static int count();

    // Lists all available display modes for debugging
    static void list();

    DisplayMode(int w, int h, u32 format);
    DisplayMode(int nr);
    
    SDL_DisplayMode *opaque() { return &mode; }
    
    u32 format() { return mode.format; }
    int width() { return mode.w; }
    int height() { return mode.h; }
    int hz() { return mode.refresh_rate; }
};

}

