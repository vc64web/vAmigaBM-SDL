// -----------------------------------------------------------------------------
// This file is part of vAmiga Bare Metal
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#include "Application.h"

#include <SDL_image.h>

void
SurfaceManager::load(int id)
{
    std::string path = "";
    
    switch (id) {
            
        case SurfaceID::logo: path = "logo.png"; break;
        case SurfaceID::title: path = "title.png"; break;

        default:
            assert(false);
    }
    
    std::unique_ptr<mm::Surface> asset(new mm::Surface());
    
    if (asset->create(path)) {
        cache.insert(std::make_pair(id, std::move(asset)));
    } else {
        throw std::runtime_error("AssetManager::loadSurface: Can't load " + path);
    }
}

void
FontManager::load(int id)
{
    std::string path = "";
    
    switch (id & 0xFFFF) {
            
        case FontID::console: path = "IBMPlexMono-Medium.ttf"; break;
        case FontID::sans_l:  path = "SourceSansPro-Light.ttf"; break;
        case FontID::sans_r:  path = "SourceSansPro-Regular.ttf"; break;
        case FontID::sans_sb: path = "SourceSansPro-SemiBold.ttf"; break;
        case FontID::sans_b:  path = "SourceSansPro-Bold.ttf"; break;
        case FontID::sans_bk: path = "SourceSansPro-Black.ttf"; break;

        default:
            assert(false);
    }
    
    std::unique_ptr<mm::Font> asset(new mm::Font());
    
    if (asset->loadFromFile(renderer, path, id >> 16)) {
        cache.insert(std::make_pair(id, std::move(asset)));
    } else {
        throw std::runtime_error("AssetManager::loadFont: Can't load " + path);
    }
}

/*
void
SoundManager::load(SoundID id)
{
    std::string path = "";
    
    switch (id) {
            
        case SoundID::insert: path = "insert.aiff"; break;
        case SoundID::eject:  path = "eject.aiff"; break;
        case SoundID::click:  path = "click.wav"; break;

        default:
            assert(false);
    }
    
    std::unique_ptr<sf::SoundBuffer> asset(new sf::SoundBuffer());
    
    if (asset->loadFromFile(path)) {
        cache.insert(std::make_pair(id, std::move(asset)));
    } else {
        throw std::runtime_error("AssetManager::loadFont: Can't load " + path);
    }
}

void
ShaderManager::load(ShaderID id)
{
    assert(false);
}
*/
