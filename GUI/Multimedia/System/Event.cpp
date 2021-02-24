// -----------------------------------------------------------------------------
// This file is part of vAmiga Bare Metal
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#include "Event.h"

namespace mm {

/*
WindowEvent
Event::asWindowEvent()
{
    return WindowEvent(*this);
}
*/

void
WindowEvent::print()
{
    switch (event->event) {
            
        case SDL_WINDOWEVENT_SHOWN:
            printf("Window shown\n");
            break;
            
        case SDL_WINDOWEVENT_HIDDEN:
            printf("Window hidden\n");
            break;
            
        case SDL_WINDOWEVENT_EXPOSED:
            printf("Window exposed\n");
            break;
            
        case SDL_WINDOWEVENT_MOVED:
            printf("Window moved to %d,%d\n", event->data1, event->data2);
            break;
            
        case SDL_WINDOWEVENT_RESIZED:
            printf("Window resized to %dx%d\n", event->data1, event->data2);
            break;
            
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            printf("Window size changed to %dx%d\n", event->data1, event->data2);
            break;
            
        case SDL_WINDOWEVENT_MINIMIZED:
            printf("Window minimized\n");
            break;
            
        case SDL_WINDOWEVENT_MAXIMIZED:
            printf("Window maximized\n");
            break;
            
        case SDL_WINDOWEVENT_RESTORED:
            printf("Window restored\n");
            break;
            
        case SDL_WINDOWEVENT_ENTER:
            printf("Mouse entered window\n");
            break;
            
        case SDL_WINDOWEVENT_LEAVE:
            printf("Mouse left window\n");
            break;
            
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            printf("Window gained keyboard focus\n");
            break;
            
        case SDL_WINDOWEVENT_FOCUS_LOST:
            printf("Window lost keyboard focus\n");
            break;
            
        case SDL_WINDOWEVENT_CLOSE:
            printf("Window closed\n");
            break;
            
        case SDL_WINDOWEVENT_TAKE_FOCUS:
            printf("Window is offered a focus\n");
            break;
            
        case SDL_WINDOWEVENT_HIT_TEST:
            printf("Window has a special hit test\n");
            break;
            
        default:
            printf("Window got unknown event %d\n", event->event);
            break;
    }
}

}
