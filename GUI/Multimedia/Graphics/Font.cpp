// -----------------------------------------------------------------------------
// This file is part of vAmiga Bare Metal
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#include "Font.h"
#include "Color.h"
#include "Surface.h"

#include <SDL_ttf.h>

namespace mm {

Font::Font()
{
    
}

Font::~Font()
{
    
}

int
Font::width(const std::string &text)
{
    int w = 0;
    TTF_SizeText(font, text.c_str(), &w, nullptr);
    return w;
}

int
Font::height(const std::string &text)
{
    int h = 0;
    TTF_SizeText(font, text.c_str(), nullptr, &h);
    return h;
}

bool
Font::loadFromFile(Renderer &renderer, const std::string &path, int size)
{
    font = TTF_OpenFont(path.c_str(), size);
    return font != nullptr;
}

Surface
Font::render(std::string text, const class Color &color)
{
    if (font) {
        return Surface(TTF_RenderText_Blended(font, text.c_str(), color.sdl()));
    } else {
        return Surface(nullptr);
    }
}

}
