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

#include "Graphics/Color.h"
#include "Window/WindowAssociate.h"

namespace mm {

struct Align {

    static const usize Centered     = 0b0000000;
    static const usize Left         = 0b0000001;
    static const usize Right        = 0b0000010;
    static const usize Top          = 0b0000100;
    static const usize Bottom       = 0b0001000;
    
    static const usize UpperLeft    = 0b0000101;
    static const usize LowerLeft    = 0b0001001;
    static const usize UpperRight   = 0b0000110;
    static const usize LowerRight   = 0b0001010;

    static const usize Proportional = 0b0010000;
    // static const usize FlippedX     = 0b0100000;
    // static const usize FlippedY     = 0b1000000;
};

class View : public WindowAssociate {
 
protected:
    
    Texture texture;
    
public:
 
    //
    // Members
    //
    
// protected:
public:
    
    // Object position (normalized coordinate + pixel offset)
    float x = 0; int dx = 0;
    float y = 0; int dy = 0;
    
    // Object size;
    int w = 0;
    int h = 0;

    // Alignment flags
    usize flags = 0;
    
    // Render position (final object position)
    int rx = 0;
    int ry = 0;
    
    
    //
    // Constructing and initializing
    //
    
public:
    
    View(Window &win);
    View(Window &win, usize flags);
    
    // void init(int x, int y, int w, int h);
    
    
    //
    // Accessing
    //
    
    // Returns the view's texture
    Texture &getTexture() { return texture; }
    
    // Returns the dimensions of the view
    int width() { return w; }
    int height() { return h; }
 
    // Adjusts the view position
    void setX(float x, int dx = 0);
    void setY(float y, int dy = 0);
    void setPosition(float x, float y, int dx = 0, int dy = 0);

    // Modifies the view size
    void setW(int w);
    void setH(int h);
    void setSize(int w, int h);

    // Sets the view's opacity
    void setAlpha(u8 alpha);

    
    //
    // Rendering
    //

    // Computes the render position and updates the texture
    virtual void update();
    
    // Renders the view
    void render();
    void render(Texture &texture);
};


//
// Render view
//

class RenderView : public View {

public:
        
    // Inherit constructors
    using View::View;

    // Initializers
    void init(int w, int h);
        
    // Clears the render texture with a given color
    void clear(const Color &color);
    
    // Methods from View
    void update() override;
};


//
// Image view
//

class ImageView : public View {
        
public:
        
    // Inherit constructors
    using View::View;
    
    // Initializers
    void init(Surface &surface);
        
    // Methods from View
    void update() override;
};


//
// Gradient view
//

class GradientView : public View {
        
    Color ul = Color::Black;
    Color ur = Color::Black;
    Color ll = Color::Black;
    Color lr = Color::Black;
    
public:
    
    // Inherit constructors
    using View::View;
    
    void init(int w, int h,
              const Color &ul, const Color &ur, const Color &ll, const Color &lr);

    // Methods from View
    void update() override;
};


//
// Text view
//

class TextView : public View {

    Font font;
    Color color;
    string text;
    
public:
    
    // Inherit constructors
    using View::View;
    
    // void init(int x, int y, const Font &font, const Color &color);
    void setString(const string &str);
    void setFont(const Font &font);
    void setColor(const Color &color);
    
    // Methods from View
    void update();
};

}
