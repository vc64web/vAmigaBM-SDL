// -----------------------------------------------------------------------------
// This file is part of vAmiga Bare Metal
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#pragma once

#include "Multimedia.h"

#include "GUIComponent.h"
#include "Amiga.h"
#include "Canvas.h"
#include "Console.h"
#include "Utils.h"
#include "OS.h"
#include "Controller.h"
#include "SplashScreen.h"
#include "AssetManager.h"

/*
#include "Exception.h"
#include "Controller.h"
#include "Screen.h"
#include "Layer.h"
#include "SplashScreen.h"
#include "Canvas.h"
#include "Console.h"
#include "Interpreter.h"
#include "AssetManager.h"
#include "View.h"
#include "AmigaMusicStream.h"
*/

class Application : public GUIComponent
{

public:
    
    //
    // Constants
    //
    
 
    //
    // Members
    //

public:
        
    // The application window
    mm::Window window;
    
    // The emulator instance
    Amiga amiga;
    
    // Gateway to the emulator
    Controller controller;
    
    // Gateway to the host operating system
    // OS os;
        
    // Splash screen layer
    SplashScreen splashScreen;

    // The emulator layer
    Canvas canvas;

    // The debug console layer
    Console console;

    // The music stream
    // AmigaMusicStream musicStream;

    // The command line parameters
    std::vector<string> argv;
    
    // Asset managers
    SurfaceManager surfaces;
    FontManager fonts;
    
    // Sound object pools
    // sf::Sound sound[16];
    
    
    //
    // Querying system properties
    //

    
    
    //
    // Initializing
    //
    
public:
    
    Application(int argc, const char *argv[]);
    ~Application();
    
    
    //
    // Launching the app
    //
    
    /* On start, the application executes the following launch sequence:
     *
     * 1. check     : The applications performs several system checks to see if
     *                it can run in the given environment. E.g., it is checked
     *                the underlying graphics system offers shader support.
     *
     * 2. init      : All sub components enter their initial state.
     *
     * 3. configure : All components configure themself. Beside other things,
     *                a configuration file is read which configures the
     *                virtual Amiga.
     *
     * 4. run       : The application enters the main event loop. It remains
     *                in this loop until the user quits the application.
     */
    void check();
    void init();
    void configure();
    void run();

    
    //
    // Performing continuous tasks
    //
    
    void update(i64 frame, mm::Time dt);
    void render();
    
    
    //
    // Responding to events
    //

    void respond(mm::Event &event);
    void respondToWindowEvent(mm::Event &event);
    void respondToKeyboardEvent(mm::Event &event);
    
    void resize(int w, int h);
        
    
    //
    // Working with the audio backend
    //

    /* This functions searches the object pool for a free sound object,
     * attaches a sound buffer from the asset storage and plays the sound. The
     * min and max parameters can be used to limit the search range. This
     * feature is used for the clicking sounds to limit the number of sounds
     * that are played simultaneously.
     */
    /*
    void play(SoundID, float volume = 25.0, isize min = 0, isize max = 15);

    void playInsert() { play(SoundID::insert, 25.0); }
    void playEject()  { play(SoundID::eject, 25.0); }
    void playClick()  { play(SoundID::click, 25.0, 13, 15); }
     */
};

