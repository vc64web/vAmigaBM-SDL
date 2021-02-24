// -----------------------------------------------------------------------------
// This file is part of vAmiga Bare Metal
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#include "Texture.h"
#include "Surface.h"
#include "Renderer.h"

#include <SDL_image.h>

namespace mm {

Texture::~Texture()
{
    destroy();
}

bool
Texture::create(class Renderer &renderer, int w, int h)
{
    destroy();
    
    texture = SDL_CreateTexture(renderer.opaque(),
                                SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_TARGET,
                                w,h);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    
    return texture != nullptr;
}

bool
Texture::create(Renderer &renderer, Surface &surface)
{
    return create(renderer, surface.opaque());
}

bool
Texture::create(Renderer &renderer, SDL_Surface *surface)
{
    destroy();
    texture = SDL_CreateTextureFromSurface(renderer.opaque(), surface);
    // SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    return texture != nullptr;
}

void
Texture::destroy()
{
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

int
Texture::width() const
{
    int w;
    SDL_QueryTexture(texture, NULL, NULL, &w, NULL);
    return w;
}

int
Texture::height() const
{
    int h;
    SDL_QueryTexture(texture, NULL, NULL, NULL, &h);
    return h;
}

void
Texture::setAlpha(u8 alpha)
{
    if (SDL_SetTextureAlphaMod(texture, alpha) == -1) {
        printf("NO ALPHA MODULATION\n");
    }
        
}

bool
Texture::loadFromFile(Renderer &renderer, const string &path)
{
    texture = IMG_LoadTexture(renderer.opaque(), path.c_str());
    return texture != nullptr;
}

}
