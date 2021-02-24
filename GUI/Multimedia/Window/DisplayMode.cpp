// -----------------------------------------------------------------------------
// This file is part of vAmiga Bare Metal
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#include "DisplayMode.h"
#include <SDL.h>

namespace mm {

int
DisplayMode::count()
{
    return SDL_GetNumDisplayModes(0);
}

DisplayMode::DisplayMode(int w, int h, u32 format)
{
    mode.w = w;
    mode.h = h;
    mode.format = format;
    mode.refresh_rate = 0;
    mode.driverdata = nullptr;
}

DisplayMode::DisplayMode(int nr) : DisplayMode(0, 0, 0)
{
    SDL_GetDisplayMode(0, nr, &mode);
}

void
DisplayMode::list()
{
    for (int i = 0; i < count(); i++) {
        
        auto mode = DisplayMode(i);
        printf("Mode %d: %dx%d %d Hz\n",
               i, mode.width(), mode.height(), mode.hz());
    }
}

}
