// -----------------------------------------------------------------------------
// This file is part of vAmiga Bare Metal
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#include "Window/WindowAssociate.h"
#include "Window/Window.h"

namespace mm {

WindowAssociate::WindowAssociate(Window &win) : window(&win)
{

}

class Renderer &
WindowAssociate::renderer()
{
    return window->renderer;
}

}
