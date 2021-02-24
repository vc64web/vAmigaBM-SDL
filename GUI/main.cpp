// -----------------------------------------------------------------------------
// This file is part of vAmiga Bare Metal
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#include "main.h"
#include "Application.h"
#include "Multimedia/Multimedia.h"
#include "Window.h"
#include "Exception.h"

#include <stdio.h>

int main(int argc, const char *argv[]) {
    
    mm::init();
    
    Application app(argc, argv);

    // Launch the app
    try {
        app.check();
        app.init();
        app.configure();
        
        // app.configure(argc, argv);
        
    } catch (Exception &e) {
        std::cout << "Unable to launch vAmiga!" << std::endl;
        std::cout << "Error: " << e.what() << std::endl;
        exit(1);
    }
    
    // Enter the event loop
    app.run();
    
    mm::quit();
    return 0;
}

