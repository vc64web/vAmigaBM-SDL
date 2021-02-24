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

class Renderer
{
    SDL_Renderer *renderer = nullptr;
 
public:
    
    Renderer();
    ~Renderer();
    
    SDL_Renderer *opaque() { return renderer; }
    
    void create(class Window &window, int index, u32 flags);
    void destroy();
    
    void setRenderTarget(class Texture &texture);
    void clearRenderTarget();
    
    void clear(const class Color &color);
    void clear();
};

}
