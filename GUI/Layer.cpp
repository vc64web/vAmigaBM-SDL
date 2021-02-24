// -----------------------------------------------------------------------------
// This file is part of vAmiga Bare Metal
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#include "Layer.h"
#include "Application.h"
#include "Multimedia.h"

void
Layer::init()
{
    assert(app.window.isOpen());
}

void
Layer::setTargetAlpha(isize target, float seconds)
{
    targetAlpha = target;
    delay = seconds;
}

void
Layer::update(mm::Time dt)
{
    if (alpha != targetAlpha) {

        float delta = dt.asSeconds();
        if (delta >= delay) {
            alpha = targetAlpha;
        } else {
            alpha += (targetAlpha - alpha) * delta / delay;
            delay -= delta;
        }
        
        alphaDidChange();
    }
}
