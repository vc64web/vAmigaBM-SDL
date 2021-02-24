// -----------------------------------------------------------------------------
// This file is part of vAmiga Bare Metal
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#include "Multimedia.h"
#include "Exception.h"
#include <string>

using std::string;

namespace mm
{

Window::Window()
{
 
}

Window::~Window()
{
    if (window) SDL_DestroyWindow(window);
}

void
Window::create(const char *title, int w, int h, u32 flags) {
    
    int posx = SDL_WINDOWPOS_UNDEFINED;
    int posy = SDL_WINDOWPOS_UNDEFINED;
    
    flags |= SDL_WINDOW_ALLOW_HIGHDPI;
    
    if (!(window = SDL_CreateWindow(title, posx, posy, w, h, flags))) {
        throw Exception(string("Unable to open window: ") + SDL_GetError());
    }
    
    renderer.create(*this, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    scale = subPixelWidth() / pixelWidth();
    
    printf("Window size: %d x %d\n", pixelWidth(), pixelHeight());
    printf("Drawable size: %d x %d\n", subPixelWidth(), subPixelHeight());
    printf("Scaling factor: %d\n", scale);    
}

void
Window::destroy()
{
    SDL_DestroyWindow(window);
    window = nullptr;
}

int
Window::pixelWidth()
{
    int result;
    SDL_GetWindowSize(opaque(), &result, nullptr);
    return result;
}

int
Window::pixelHeight()
{
    int result;
    SDL_GetWindowSize(opaque(), nullptr, &result);
    return result;
}

int
Window::subPixelWidth()
{
    int w;
    SDL_GL_GetDrawableSize(window, &w, nullptr);
    return w;
}

int
Window::subPixelHeight()
{
    int h;
    SDL_GL_GetDrawableSize(window, nullptr, &h);
    return h;
}

void
Window::close()
{
    renderer.destroy();
    destroy();
}

void
Window::clear(mm::Color color)
{
    SDL_SetRenderDrawColor(renderer.opaque(),
                           color.r, color.g, color.b, color.a);
    clear();
}

void
Window::clear()
{
    SDL_RenderClear(renderer.opaque());
}

void
Window::present()
{
    SDL_RenderPresent(renderer.opaque());
}

}
