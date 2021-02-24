// -----------------------------------------------------------------------------
// This file is part of vAmiga Bare Metal
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

namespace mm {

class Font
{
    TTF_Font* font = nullptr;
    
public:
    
    Font();
    Font(TTF_Font *ref) : font(ref) { };
    ~Font();
    
    TTF_Font *opaque() { return font; }
    
    // Returns the drawing dimensions without rendering the text
    int width(const std::string &text);
    int height(const std::string &text);
    
    // Loads a font from disk
    bool loadFromFile(class Renderer &renderer, const std::string &path, int size);
    
    // Renders a text
    class Surface render(std::string text, const class Color &color);
};

}
