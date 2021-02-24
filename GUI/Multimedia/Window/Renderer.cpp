// -----------------------------------------------------------------------------
// This file is part of vAmiga Bare Metal
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#include "Aliases.h"
#include "Exception.h"
#include "Multimedia.h"

namespace mm {

Renderer::Renderer()
{
    
}

Renderer::~Renderer()
{
    if (renderer) SDL_DestroyRenderer(renderer);
}

void
Renderer::create(class Window &window, int index, u32 flags)
{
    renderer = SDL_CreateRenderer(window.opaque(), index, flags);
    if (renderer == nullptr) {
        throw Exception("Unable to create Renderer");
    }
}

void
Renderer::destroy()
{
    SDL_DestroyRenderer(renderer);
    renderer = nullptr; 
}

void
Renderer::setRenderTarget(class Texture &texture)
{
    SDL_SetRenderTarget(renderer, texture.opaque());
}

void
Renderer::clearRenderTarget()
{
    SDL_SetRenderTarget(renderer, nullptr);
}

void
Renderer::clear(const Color &color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    clear();
}

void
Renderer::clear()
{
    SDL_RenderClear(renderer);
}

}
