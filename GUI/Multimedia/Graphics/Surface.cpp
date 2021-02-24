// -----------------------------------------------------------------------------
// This file is part of vAmiga Bare Metal
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#include "Surface.h"

#include <assert.h>
#include <SDL_image.h>
#include <string>

namespace mm {

bool
Surface::create(int w, int h)
{
    surface = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, SDL_PIXELFORMAT_RGBA8888);
    return surface != nullptr;
}

bool
Surface::create(const std::string &path)
{
    surface = IMG_Load(path.c_str());
    return surface != nullptr;
}

void
Surface::setPixel(int x, int y, u32 pixel)
{
    assert(x >= 0 && x < width());
    assert(y >= 0 && y < height());
    
    u32 *p = (u32 *)surface->pixels;
    p[x + y * width()] = pixel;
}

}
