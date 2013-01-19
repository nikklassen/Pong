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

class Timer
{
private:
    //The clock time when the timer started
    int startTicks;
    
    //The ticks stored when the timer was paused
    int pausedTicks;
    
    //The timer status
    bool paused;
    bool started;
    
public:
    //Initializes variables
    Timer();
    
    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();
    
    //Gets the timer's time
    int get_ticks();
    
    //Checks the status of the timer
    bool is_started();
    bool is_paused();
};

#endif /* defined(__SDL_Test__Timer__) */
