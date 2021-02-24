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
#include <string>
#include <SDL.h>

namespace mm {

class Surface
{
    SDL_Surface *surface = nullptr;
    
public:
    
    Surface() { };
    Surface(SDL_Surface *ref) : surface(ref) { };
    ~Surface() { destroy(); }
        
    //
    // Initializing
    //
    
    bool create(int w, int h);
    bool create(const std::string &path);
    void destroy() { SDL_FreeSurface(surface); }

    SDL_Surface *opaque() { return surface; }

    int width() { return surface ? surface->w : 0; }
    int height() { return surface ? surface->h : 0; }
    
    void setPixel(int x, int y, u32 pixel);
};

}
