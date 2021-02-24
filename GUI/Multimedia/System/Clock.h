// -----------------------------------------------------------------------------
// This file is part of vAmiga Bare Metal
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#pragma once

#include "System/Time.h"

namespace mm {

class Clock {
        
    Time start;
    
public:
    
    Clock();

    Time getElapsedTime() const;
    Time restart();
};

class SyncClock {

    // Proposed frame delay
    Time slice;
    
    // The next wakeup cycle for this thread
    Time target;

    // A stop watch for computing fps and load
    Clock stopWatch;

    // Frames per second
    isize frames = 0;
    float hardFps;
    float softFps;
    
    // Cpu load
    Time  load;
    float hardLoad;
    float softLoad;
    
public:
    
    SyncClock(float Hz);

    float getFps(bool hard = true) { return hard ? hardFps : softFps; }
    float getLoad(bool hard = true) { return hard ? hardLoad : softLoad; }

    void wait();
    void restart();
};

}
