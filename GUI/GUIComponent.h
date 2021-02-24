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

class Amiga;
class Application;
class Controller;
class SplashScreen;
class Canvas;
class Console;


// This class is the base class for all GUI components
class GUIComponent {

protected:

    Amiga &amiga;
    Application &app;
    Controller &controller;
    SplashScreen &splash;
    Canvas &canvas;
    Console &console;

public:

    GUIComponent (Application& ref);
    
    // Translates a logical dimension to a physical dimension
    int pixels(int value);
};
