// -----------------------------------------------------------------------------
// This file is part of vAmiga Bare Metal
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#include "Clock.h"
#include "stdio.h"

namespace mm {

Clock::Clock()
{
    start = Time::now();
}

Time
Clock::getElapsedTime() const
{
    return Time::now() - start;
}

Time
Clock::restart()
{
    Time result = getElapsedTime();
    start = Time::now();
    
    return result;
}

SyncClock::SyncClock(float hz)
{
    slice = Time((i64)(1000000000 / hz));
    target = Time::now() + slice;
}

void
SyncClock::wait()
{
    // How long do we need to sleep?
    Time delay = target.diff();
    
    // Restart the clock if it got out of sync
    if (delay.abs() > slice * 4) restart();

    // Once in a while...
    if (++frames == 60) {
        
        Time delta = stopWatch.restart();
        
        // ...compute the frames per second
        hardFps = frames / delta.asSeconds();
        softFps = 0.5 * softFps + 0.5 * hardFps;
        frames = 0;
        
        // ...compute the CPU load for this thread
        hardLoad = load.asSeconds() / delta.asSeconds();
        softLoad = 0.5 * softLoad + 0.5 * hardLoad;
        load = 0;
        
        /*
        printf("fps: %f (~ %f) load: %2.1f%% (~ %2.1f%%)\n",
               hardFps, softFps, hardLoad * 100, softLoad * 100);
        */
    }
    
    // Sleep
    delay.sleep();
    target = target + slice;
    load = load + slice - delay;
}

void
SyncClock::restart()
{
    printf("Restarting sync clock\n");
    target = Time::now() + slice;
}

}
