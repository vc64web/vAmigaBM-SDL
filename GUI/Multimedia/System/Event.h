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

struct Event
{
    SDL_Event event;
        
    Event() : Event(0) { }
    Event(u32 type) { event.type = type; }
    ~Event() { };
    
    SDL_Event &opaque() { return event; }
    
    u32 type() { return event.type; }
        
    bool poll() { return SDL_PollEvent(&event); }
};

struct WindowEvent
{
    SDL_WindowEvent *event;
    
    WindowEvent(Event &e) { this->event = &e.opaque().window; }
    SDL_WindowEvent *opaque() { return event; }
    
    void print();
};

struct KeyboardEvent
{
    SDL_KeyboardEvent *event;
    
    KeyboardEvent(Event &e) { this->event = &e.opaque().key; }
    SDL_KeyboardEvent *opaque() { return event; }
    
    i32 keyCode() { return event->keysym.sym; }
};

}
