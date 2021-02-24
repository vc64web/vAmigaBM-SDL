// -----------------------------------------------------------------------------
// This file is part of vAmiga Bare Metal
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#pragma once

#include "Renderer.h"
#include "Surface.h"
#include "Font.h"

#include <map>

namespace SurfaceID { enum {
    
    logo,
    title
};}

namespace FontID { enum {
    
    console,
    sans_l,
    sans_r,
    sans_sb,
    sans_b,
    sans_bk,
};}

namespace SoundID { enum {

    insert,
    eject,
    click
};}

namespace ShaderID { enum {

    blur
};}

template <typename Asset>
class AssetManager
{
protected:
    
    // Asset storage
    std::map<int, std::unique_ptr<Asset>> cache;

    // The associated renderer
    mm::Renderer &renderer;
    
public:
        
    AssetManager(mm::Renderer &ref) : renderer(ref) { }
    
    // Requests an asset
    Asset &get(int id, int data = 0)
    {
        int token = data << 16 | id;
        
        // Lookup the requested element
        auto it = cache.find(token);
        
        // Load the element if it is not cached
        if (it == cache.end()) {
            load(token);
            it = cache.find(token);
            assert(it != cache.end());
        }
        
        return *it->second;
    }
    
    // Caches an asset
    virtual void load(int id) = 0;
};

class SurfaceManager : public AssetManager<mm::Surface> {
    using AssetManager<mm::Surface>::AssetManager;
    void load(int id) override;
};

class FontManager : public AssetManager<mm::Font> {
    using AssetManager<mm::Font>::AssetManager;
    void load(int id) override;
};
/*

class SoundManager : public AssetManager<sf::SoundBuffer, SoundID> {
    void load(SoundID id) override;
};

class ShaderManager : public AssetManager<sf::Shader, ShaderID> {
    void load(ShaderID id) override;
};
*/
