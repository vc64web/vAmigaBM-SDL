// -----------------------------------------------------------------------------
// This file is part of vAmiga Bare Metal
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#pragma once

namespace mm {

class WindowAssociate
{
protected:
    
    class Window *window;
    
public:

    WindowAssociate(Window &win);
    
    class Renderer &renderer();
};

}
