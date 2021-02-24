// -----------------------------------------------------------------------------
// This file is part of vAmiga Bare Metal
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#include "Exception.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

using std::string;

namespace mm
{

void init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw Exception(string("init(SDL_INIT_VIDEO) failed: ") + SDL_GetError());
    }
    if (TTF_Init() != 0) {
        throw Exception(string("init(TTF_INIT) failed: ") + TTF_GetError());
    }
        
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        throw Exception(string("init(IMG_INIT_PNG) failed: ") + SDL_GetError());
    }
}

void quit()
{
    SDL_Quit();
}

}
