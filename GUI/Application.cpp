// -----------------------------------------------------------------------------
// This file is part of vAmiga Bare Metal
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#include "Application.h"
#include "Controller.h"
#include "Amiga.h"

#include "Multimedia.h"

Application::Application(int argc, const char *argv[]) :
GUIComponent(*this),
controller(*this),
canvas(*this),
console(*this),
splashScreen(*this),
surfaces(this->window.renderer),
fonts(this->window.renderer)
/*
:
controller(*this),
os(*this),
console(*this),
splashScreen(*this),
canvas(*this),
musicStream(*this)
*/
{
    for (int i = 0; i < argc; i++) {
        this->argv.push_back(string(argv[i]));
    }
}

Application::~Application()
{
}

void
Application::check()
{
    // No checks performed, yet
}

void
Application::init()
{
    window.create("vAmiga Bare Metal", CUTOUT_W, 2 * CUTOUT_H);
            
    controller.init();
    splashScreen.init();
    canvas.init();
    console.init();
    /*
    musicStream.init();
     */

    // Fire a resize event
    resize(window.subPixelWidth(), window.subPixelHeight());
}

void
Application::configure()
{
    /*
    controller.configure();
    splashScreen.configure();
    canvas.configure();
    console.configure();
    */
}

void
Application::run()
{
    mm::Clock clock;
    mm::Clock fpsClock;
    mm::SyncClock sync(60);
    
    mm::Time start;
    mm::Time dt;
    i64 frame = 0;
    
    // musicStream.setVolume(50.0);
    // musicStream.play();
    
    mm::Event event;
        
    while (window.isOpen()) {
        
        dt = clock.restart();

        while (event.poll()) { respond(event); }
        update(frame++, dt);
        render();

        sync.wait();
    }
    
    // controller.deinit();
}

void
Application::respond(mm::Event &event)
{
    switch (event.type()) {
            
        case SDL_QUIT:
            
            window.close();
            break;
            
        case SDL_WINDOWEVENT:
            
            respondToWindowEvent(event);
            break;
            
        case SDL_KEYDOWN:
            respondToKeyboardEvent(event);
            break;
        
        case SDL_TEXTINPUT:
            printf("SDL_TEXTINPUT: %s\n", event.opaque().text.text);
            break;
            
        default:
            break;
            
    }

    // Distribute the event to the uppermost visible layer
    if (console.isVisible()) console.respond(event);
    else if (canvas.isVisible()) canvas.respond(event);
    else if (splashScreen.isVisible()) splashScreen.respond(event);

    
    /*
    sf::Event event;

    while (window.pollEvent(event)) {
        
        switch (event.type) {
                
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::F11) console.toggle();
                break;

            case sf::Event::MouseButtonPressed:
                break;
                
            case sf::Event::Resized:
                resize(event.size.width, event.size.height);
                break;

            default:
                break;
        }
        
        // Distribute the event to the uppermost visible layer
        if (console.isVisible()) console.handle(event);
        else if (canvas.isVisible()) canvas.handle(event);
        else if (splashScreen.isVisible()) splashScreen.handle(event);
    }
    */
}

void
Application::respondToWindowEvent(mm::Event &event)
{
    auto windowEvent = mm::WindowEvent(event);
    
    windowEvent.print();

    switch (windowEvent.opaque()->event) {
            
        case SDL_WINDOWEVENT_RESIZED:
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            break;
            
        default:
            break;
    }
}

void
Application::respondToKeyboardEvent(mm::Event &event)
{
    auto keyboardEvent = mm::KeyboardEvent(event);
    
    switch (keyboardEvent.opaque()->keysym.sym) {
            
        case SDLK_F11:
            printf("F11\n");
            console.toggle();
            break;

        case SDLK_F12:
            printf("F12\n");
            break;
            
        default:
            break;
    }
}

void
Application::resize(int w, int h)
{
    /*
    // Restore the minimal window size if the proposed size is smaller
    if (w < winXmin || h < winYmin) {
        
        w = winXmin;
        h = winYmin;
        
        window.setSize(sf::Vector2u{(unsigned)w,(unsigned)h});
    }
    
    // Adjust the view to the new size
    window.setView(sf::View(sf::FloatRect(0, 0, w, h)));
    */
    
    // Inform all layers
    splashScreen.resize(w, h);
    canvas.resize(w, h);
    console.resize(w, h);
}

void
Application::update(i64 frame, mm::Time dt)
{
    splashScreen.update(frame, dt);
    canvas.update(frame, dt);
    console.update(frame, dt);
}

void
Application::render()
{
    splashScreen.render();
    if (splashScreen.isVisible()) splashScreen.render();
    if (canvas.isVisible()) canvas.render();
    if (console.isVisible()) console.render();

    window.present();
}

/*
void
Application::play(SoundID id, float volume, isize min, isize max)
{
    // Search the pool for a free sound object
    for (isize i = min; i <= max; i++) {

        if (sound[i].getStatus() == sf::SoundSource::Status::Stopped) {
            
            sound[i].setBuffer(assets.get(id));
            sound[i].setVolume(volume);
            sound[i].play();
            break;
        }
    }
}
*/
