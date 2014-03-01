//
//  Timer.h
//  SDL Test
//
//  Created by Nik Klassen on 2012-12-30.
//  Copyright (c) 2012 Nik Klassen. All rights reserved.
//

#ifndef __SDL_Test__Timer__
#define __SDL_Test__Timer__

#include <iostream>
#include <SDL/SDL.h>

class Timer {
    
private:
    int startTicks;
    int pausedTicks;
    bool paused;
    bool started;
    
public:
    Timer();
    
    void start();
    void stop();
    void pause();
    void unpause();
    
    int get_ticks();
    
    bool is_started();
    bool is_paused();
};

#endif /* defined(__SDL_Test__Timer__) */
