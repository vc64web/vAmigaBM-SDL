// -----------------------------------------------------------------------------
// This file is part of vAmiga Bare Metal
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#include "Application.h"
#include "Surface.h"
#include "Exception.h"

#include <SDL.h>


//
// View
//

namespace mm {

View::View(Window &win, usize flags) : WindowAssociate(win), texture(win)
{
    this->flags = flags;
}

View::View(Window &win) : View(win, Align::UpperLeft)
{
    
}

/*
void
View::init(int x, int y, int w, int h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    
    if (!texture.opaque()) {
        texture.create(renderer(), w, h);
    }
    printf("View::init(%d,%d,%d,%d)\n", x,y,w,h);
    update();
}
*/

void
View::setX(float x, int dx)
{
    if (this->x != x || this->dx != dx) {
        
        this->x = x;
        this->dx = dx;
        update();
    }
}

void
View::setY(float y, int dy)
{
    if (this->y != y || this->dy != dy) {
        
        this->y = y;
        this->dy = dy;
        update();
    }
}

void
View::setPosition(float x, float y, int dx, int dy)
{
    if (this->x != x || this->y != y || this->dx != dx || this->dy != dy) {
        
        this->x = x;
        this->y = y;
        this->dx = dx;
        this->dy = dy;
        update();
    }
}

void
View::setW(int w)
{
    if (flags & Align::Proportional) { this->h = w * this->h / this->w; }
    
    if (this->w != w) {
        this->w = w;
        update();
    }
}

void
View::setH(int h)
{
    if (flags & Align::Proportional) { this->w = h * this->w / this->h; }

    if (this->h != h) {
        this->h = h;
        update();
    }
}

void
View::setSize(int w, int h)
{
    assert((flags & Align::Proportional) == 0);
    
    if (this->w != w || this->h != h) {
        
        this->w = w;
        this->h = h;
        update();
    }
}

void
View::setAlpha(u8 alpha)
{
    texture.setAlpha(alpha);
}

void
View::update()
{
    rx = x * window->subPixelWidth() + dx;
    ry = y * window->subPixelHeight() + dy;
    
    rx -= (flags & Align::Left) ? 0 : (flags & Align::Right) ? w : w / 2;
    ry -= (flags & Align::Top) ? 0 : (flags & Align::Bottom) ? h : h / 2;
}

void
View::render()
{
    if (auto tex = texture.opaque()) {
        
        SDL_Rect rect = { rx, ry, w, h };
        SDL_RenderCopy(renderer().opaque(), tex, nullptr, &rect);
    }
}

void
View::render(Texture &texture)
{
    renderer().setRenderTarget(texture);
    render();
    renderer().clearRenderTarget();
}


//
// Render view
//

void
RenderView::init(int w, int h)
{
    this->w = w;
    this->h = h;

    update();
}

void
RenderView::clear(const Color &color)
{
    renderer().setRenderTarget(texture);
    renderer().clear(color);
    renderer().clearRenderTarget();
}

void
RenderView::update()
{
    View::update();
    
    if (w != texture.width() || h != texture.height()) {
        texture.create(renderer(), w, h);
    }
}


//
// ImageView
//

void
ImageView::init(Surface &surface)
{
    this->texture.create(renderer(), surface);
    
    this->w = texture.width();
    this->h = texture.height();
}

void
ImageView::update()
{
    View::update();
}


//
// GradientView
//

void
GradientView::init(int w, int h,
                   const Color &ul, const Color &ur, const Color &ll, const Color &lr)
{
    this->w = w;
    this->h = h;
    this->ul = ul;
    this->ur = ur;
    this->ll = ll;
    this->lr = lr;
}

void
GradientView::update()
{
    View::update();
        
    Surface surface;
    
    int xx = 32; // w
    int yy = 32; // h
    surface.create(xx, yy);
    
    for (int y = 0; y < yy; y++) {

        Color l = Color(ul, ll, (float)y / (float)yy);
        Color r = Color(ur, lr, (float)y / (float)yy);
        
        for (int x = 0; x < xx; x++) {
            surface.setPixel(x, y, Color(l, r, (float)x / (float)xx).rgba());
        }
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    
    texture.create(renderer(), surface);
    if (texture.opaque() == nullptr) {
        throw Exception("GradientView: Unable to create surface\n");
    }
}


//
// TextView
//

void
TextView::setString(const string &text)
{
    this->text = text;
    update();
}

void
TextView::setFont(const Font &font)
{
    this->font = font;
    update();
}

void
TextView::setColor(const Color &color)
{
    this->color = color;
    update();
}

void
TextView::update()
{
    View::update();
    
    Surface surface = font.render(text, color);
    
    w = surface.width();
    h = surface.height();
    
    if (w != 0 && h != 0) {
        texture.create(renderer(), surface);
    }
}

}
