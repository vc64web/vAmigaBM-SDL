// -----------------------------------------------------------------------------
// This file is part of vAmiga Bare Metal
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#include "Application.h"

SplashScreen::SplashScreen(Application &ref) : Layer(ref),

background(app.window, mm::Align::Top | mm::Align::Left),
logo(app.window, mm::Align::Top | mm::Align::Proportional),
title1(app.window, mm::Align::Right | mm::Align::Top),
title2(app.window, mm::Align::Left | mm::Align::Top),
errMsg(app.window, mm::Align::Centered),
runMsg(app.window, mm::Align::Centered),
info1(app.window, mm::Align::Centered),
info2(app.window, mm::Align::Centered),
info3(app.window, mm::Align::Centered)
{
    setTargetAlpha(255, 4.0);
}

SplashScreen::~SplashScreen()
{
    
}

void
SplashScreen::init()
{
    printf("SplashScreen init\n");
    
    Layer::init();
    
    // Background
    background.init(app.window.pixelWidth(),app.window.pixelHeight(),
                    mm::Color::Grey9, mm::Color::Grey9,
                    mm::Color::Grey14, mm::Color::Grey14);

    // vAmiga logo
    logo.init(app.surfaces.get(SurfaceID::logo));

    // Config file
    configPath = app.argv.size() <= 1 ? "startup.ini" : app.argv[1];
    configFile = extractName(configPath);
    
    // Messages
    title1.setString("vAmiga");
    title1.setColor(mm::Color::Grey4);

    title2.setString("Bare Metal");
    title2.setColor(mm::Color::Grey4);
    
    errMsg.setString("");
    errMsg.setColor(mm::Color(0xE0,0x50,0x50,0xFF));
    
    runMsg.setString("");
    runMsg.setColor(mm::Color::Grey4);
    
    info1.setString("");
    info1.setColor(mm::Color::Grey4);

    info2.setString("Press F11 to open the debug console");
    info2.setColor(mm::Color::Grey4);

    info3.setString("Press F12 to open the menu");
    info3.setColor(mm::Color::Grey4);
    
    isDirty = true;
}

void
SplashScreen::launchPhase(isize phase)
{
    /*
    std::ifstream stream;
    
    switch (phase) {
            
        case 1: // Open and process the config file
            
            stream.open(configPath);
            if (!stream.is_open()) {
                errMsg.setString("Failed to open " + configFile);
                runMsg.setString("Press SPACE to quit");
                spcAction = Quit;
                f10Action = None;
                return;
            }
            
            try { app.console.exec(stream); }
            catch (Exception &e) {
                errMsg.setString(configFile + ": Error in line " + std::to_string(e.data));
                // runMsg.setString("Press SPACE to quit");
                runMsg.setString("");
                info[0].setString("Press SPACE to quit");
                spcAction = Quit;
                f10Action = None;
                return;
            }
            
            [[fallthrough]];
            
        case 2: // Check the Kickstart Rom
            
            if (!app.amiga.mem.hasKickRom()) {
                errMsg.setString("No Kickstart Rom");
                runMsg.setString("");
                info[0].setString("Press F10 to install the Aros Kickstart replacement");
                spcAction = None;
                f10Action = Aros;
                return;
            }
            
            [[fallthrough]];
            
        case 3: // Check if the emulator can run with the current config
            
            if (!app.amiga.isReady()) {
                errMsg.setString("Failed to launch the emulator");
                runMsg.setString("Press SPACE to quit");
                spcAction = Quit;
                f10Action = None;
                return;
            }
        
            [[fallthrough]];
            
        case 4: // All clear. Ready to lift off
            
            errMsg.setString("");
            runMsg.setString("Press SPACE to start");
            info[0].setString("");
            spcAction = Launch;
            f10Action = None;
            return;
    }
    */
}

bool
SplashScreen::loadAros()
{
    try {
        app.amiga.mem.loadRomFromFile("aros-amiga-m68k-rom.bin");
        app.amiga.mem.loadExtFromFile("aros-amiga-m68k-ext.bin");
        app.amiga.configure(OPT_EXT_START, 0xE0);
        return true;
        
    } catch (VAError &err) {
        printf("Failed to load Aros: %s\n", ErrorCodeEnum::key(err.errorCode));
        return false;
    }
}

bool
SplashScreen::isVisible()
{
    return app.amiga.isPoweredOff() || app.canvas.isAnimating();
}

void
SplashScreen::update(i64 frame, mm::Time dt)
{
    Layer::update(dt);
    
    if (isDirty) {
        
        printf("SplashScreen is dirty\n");
        
        int width = app.window.subPixelWidth();
        int height = app.window.subPixelHeight();
        
        // Get fonts
        mm::Font &largeBold = app.fonts.get(FontID::sans_b, height / 13);
        mm::Font &large     = app.fonts.get(FontID::sans_l, height / 13);
        mm::Font &medium    = app.fonts.get(FontID::sans_l, height / 20);
        mm::Font &small     = app.fonts.get(FontID::sans_l, height / 28);

        // Background
        background.setSize(width, height);
        
        // vAmiga logo
        logo.setPosition(0.5, 0.08);
        logo.setH(height * 0.46);
        
        // vAmiga title
        title1.setFont(largeBold);
        title2.setFont(large);
        int offset = (title1.width() - title2.width()) / 2;
        title1.setPosition(0.49, 0.57, offset, 0);
        title2.setPosition(0.51, 0.57, offset, 0);
        
        // Messages
        runMsg.setFont(medium);
        errMsg.setFont(small);
        info1.setFont(small);
        info2.setFont(small);
        info3.setFont(small);
        errMsg.setPosition(0.5, 0.685);
        runMsg.setPosition(0.5, 0.74);
        info1.setPosition(0.5, 0.80);
        info2.setPosition(0.5, 0.85);
        info3.setPosition(0.5, 0.90);
        
        isDirty = false;
    }
}

void
SplashScreen::render()
{
    background.render();
    logo.render();
    title1.render();
    title2.render();
    errMsg.render();
    runMsg.render();
    info1.render();
    info2.render();
    info3.render();
}

void
SplashScreen::respond(mm::Event &event)
{
    switch (event.type()) {
            
        case SDL_KEYDOWN:
            respondToKeyboardEvent(event);
            break;
            
        default:
            break;
            
    }
}

void
SplashScreen::respondToKeyboardEvent(mm::Event &event)
{
    auto keyCode = mm::KeyboardEvent(event).keyCode();
    
    KeyAction action =
    (keyCode == SDLK_F10) ? f10Action :
    (keyCode == SDLK_SPACE) ? spcAction : None;
    
    switch (action) {
            
        case Launch:
            spcAction = None;
            app.amiga.run();
            break;
            
        case Quit:
            app.window.close();
            break;
            
        case Aros:
            loadAros();
            launchPhase(3);
            break;
            
        default:
            break;
    }
}

void
SplashScreen::resize(int width, int height)
{
    isDirty = true;
}

void
SplashScreen::alphaDidChange()
{
    logo.setAlpha(alpha);
    /*
    background.setAlpha(alpha);
    title1.setAlpha(alpha);
    title2.setAlpha(alpha);
    info1.setAlpha(alpha);
    info2.setAlpha(alpha);
    info3.setAlpha(alpha);
    */
}
