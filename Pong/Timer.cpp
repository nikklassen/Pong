//
//  Timer.cpp
//  SDL Test
//
//  Created by Nik Klassen on 2012-12-30.
//  Copyright (c) 2012 Nik Klassen. All rights reserved.
//

#include "Timer.h"

Timer::Timer() {
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::start() {
    started = true;
    paused = false;
    
    startTicks = SDL_GetTicks();
}

void Timer::stop() {
    started = false;
    paused = false;
}

int Timer::get_ticks() {
    
    if( started ) {
        return paused ? pausedTicks : SDL_GetTicks() - startTicks;
    }
    
    return 0;
}

void Timer::pause() {

    if( started && !paused ) {
        paused = true;
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause() {
    if( paused ) {

        paused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        
        pausedTicks = 0;
    }
}

bool Timer::is_started() {
    return started;
}

bool Timer::is_paused() {
    return paused;
}
