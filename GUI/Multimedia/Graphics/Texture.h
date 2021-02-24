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
#include "Window/WindowAssociate.h"

#include <SDL.h>
#include <string>

using std::string;

namespace mm {

class Texture : public WindowAssociate
{
public: // REMOVE ASAP
    SDL_Texture *texture = nullptr;
    
public:
    
    Texture(Window &win) : WindowAssociate(win) { };
    Texture(Window &win, SDL_Texture *tex) : WindowAssociate(win), texture(tex) { };
    ~Texture();
    
    SDL_Texture *opaque() { return texture; }
    
    bool create(class Renderer &renderer, int w, int h);
    bool create(class Renderer &renderer, class Surface &surface);
    bool create(class Renderer &renderer, SDL_Surface *surface);
    void destroy();
    
    int width() const;
    int height() const;
    
    void setAlpha(u8 alpha);
    
    bool loadFromFile(class Renderer &renderer, const std::string &path);
};

}
