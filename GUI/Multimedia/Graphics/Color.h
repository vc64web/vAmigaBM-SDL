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

class Color {
 
public:
    
    u8 r, g, b, a;

    static const Color Black;
    static const Color White;
    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Yellow;
    static const Color Magenta;
    static const Color Cyan;
    static const Color Grey1;
    static const Color Grey2;
    static const Color Grey3;
    static const Color Grey4;
    static const Color Grey5;
    static const Color Grey6;
    static const Color Grey7;
    static const Color Grey8;
    static const Color Grey9;
    static const Color Grey10;
    static const Color Grey11;
    static const Color Grey12;
    static const Color Grey13;
    static const Color Grey14;
    
    Color(u8 r, u8 g, u8 b, u8 a);
    Color(u8 r, u8 g, u8 b);
    Color(u32 rgba);
    Color();
    Color(const Color& c1, const Color &c2, float weight);

    u32 rgba() const { return r << 24 | g << 16 | b << 8 | a; }
    SDL_Color sdl() const { return SDL_Color { r, g, b, a }; }
    
    bool operator==(const Color& rhs) const;
    bool operator!=(const Color& rhs) const;
    Color operator+(const Color& rhs) const;
    Color operator-(const Color& rhs) const;
    Color operator*(const Color& rhs) const;
    Color& operator+=(const Color& rhs);
    Color& operator-=(const Color& rhs);
    Color& operator*=(const Color& rhs);
};

}
