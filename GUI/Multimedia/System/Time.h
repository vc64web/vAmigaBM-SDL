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

#ifdef __MACH__
#include <mach/mach_time.h>
#endif

namespace mm {

class Time {
    
    i64 ticks;

public:
    
    static Time now();
    
    Time() : ticks(0) { };
    Time(i64 value) : ticks(value) { };
    
    i64 asNanoseconds()  const { return ticks; }
    i64 asMicroseconds() const { return ticks / 1000; }
    i64 asMilliseconds() const { return ticks / 1000000; }
    float asSeconds()    const { return ticks / 1000000000.f; }
    
    bool operator==(const Time &rhs) const;
    bool operator!=(const Time &rhs) const;
    bool operator<=(const Time &rhs) const;
    bool operator>=(const Time &rhs) const;
    bool operator<(const Time &rhs) const;
    bool operator>(const Time &rhs) const;
    Time operator+(const Time &rhs) const;
    Time operator-(const Time &rhs) const;
    Time operator*(const int i) const;
    Time& operator+=(const Time &rhs);
    Time& operator-=(const Time &rhs);
    Time& operator*=(const int i);
    Time abs() const;
    Time diff() const;
    
    void sleep();
    void sleepUntil();
};

}
