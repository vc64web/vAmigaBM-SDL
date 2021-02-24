// -----------------------------------------------------------------------------
// This file is part of vAmiga Bare Metal
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#include "Color.h"
#include <algorithm>

namespace mm {

const Color Color::Black   (0x00, 0x00, 0x00);
const Color Color::White   (0xFF, 0xFF, 0xFF);
const Color Color::Red     (0xFF, 0x00, 0x00);
const Color Color::Green   (0x00, 0xFF, 0x00);
const Color Color::Blue    (0x00, 0x00, 0xFF);
const Color Color::Yellow  (0xFF, 0xFF, 0x00);
const Color Color::Magenta (0xFF, 0x00, 0xFF);
const Color Color::Cyan    (0x00, 0xFF, 0xFF);
const Color Color::Grey1   (0x10, 0x10, 0x10);
const Color Color::Grey2   (0x20, 0x20, 0x20);
const Color Color::Grey3   (0x30, 0x30, 0x30);
const Color Color::Grey4   (0x40, 0x40, 0x40);
const Color Color::Grey5   (0x50, 0x50, 0x50);
const Color Color::Grey6   (0x60, 0x60, 0x60);
const Color Color::Grey7   (0x70, 0x70, 0x70);
const Color Color::Grey8   (0x80, 0x80, 0x80);
const Color Color::Grey9   (0x90, 0x90, 0x90);
const Color Color::Grey10  (0xA0, 0xA0, 0xA0);
const Color Color::Grey11  (0xB0, 0xB0, 0xB0);
const Color Color::Grey12  (0xC0, 0xC0, 0xC0);
const Color Color::Grey13  (0xD0, 0xD0, 0xD0);
const Color Color::Grey14  (0xE0, 0xE0, 0xE0);

Color::Color() : Color(0, 0, 0, 0xFF) { }

Color::Color(u32 rgba)
{
    this->r = (u8)(rgba >> 24);
    this->g = (u8)(rgba >> 16);
    this->b = (u8)(rgba >> 8);
    this->a = (u8)(rgba >> 0);
}

Color::Color(u8 r, u8 g, u8 b, u8 a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

Color::Color(u8 r, u8 g, u8 b) : Color(r, g, b, 0xFF) { }

Color::Color(const Color& c1, const Color &c2, float weight)
{
    this->r = (u8)(c1.r + (c2.r - c1.r) * weight);
    this->g = (u8)(c1.g + (c2.g - c1.g) * weight);
    this->b = (u8)(c1.b + (c2.b - c1.b) * weight);
    this->a = (u8)(c1.a + (c2.a - c1.a) * weight);
}

bool
Color::operator==(const Color& rhs) const
{
    return r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a;
}

bool
Color::operator!=(const Color& rhs) const
{
    return !(*this == rhs);
}

Color
Color::operator+(const Color& rhs) const
{
    return Color((u8)(std::min(int(r) + rhs.r, 0xFF)),
                 (u8)(std::min(int(g) + rhs.g, 0xFF)),
                 (u8)(std::min(int(b) + rhs.b, 0xFF)),
                 (u8)(std::min(int(a) + rhs.a, 0xFF)));
}

Color
Color::operator-(const Color& rhs) const
{
    return Color((u8)(std::max(int(r) - rhs.r, 0)),
                 (u8)(std::max(int(g) - rhs.g, 0)),
                 (u8)(std::max(int(b) - rhs.b, 0)),
                 (u8)(std::max(int(a) - rhs.a, 0)));
}

Color
Color::operator*(const Color& rhs) const
{
    return Color((u8)(r * rhs.r / 255),
                 (u8)(g * rhs.g / 255),
                 (u8)(b * rhs.b / 255),
                 (u8)(a * rhs.a / 255));
}

Color&
Color::operator+=(const Color& rhs)
{
    return *this = *this + rhs;
}

Color&
Color::operator-=(const Color& rhs)
{
    return *this = *this - rhs;
}

Color&
Color::operator*=(const Color& rhs)
{
    return *this = *this * rhs;
}

}
