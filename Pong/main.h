//
//  main.h
//  Pong
//
//  Created by Nik Klassen on 2012-12-30.
//  Copyright (c) 2012 Nik Klassen. All rights reserved.
//

#ifndef __Pong__main__
#define __Pong__main__

#define sign(x) x/abs(x)

#include <iostream>
#include <sstream>

#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>
#include <SDL_ttf/SDL_ttf.h>

#include "Paddle.h"
#include "Ball.h"
#include "Timer.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const int BAR_HEIGHT = 40;

const int FRAMES_PER_SECOND = 40;

enum Collision {
    COLLISION_TB = -2,
    COLLISION_LR = 2,
    COLLISION_CORNER = 1,
    COLLISION_NONE = 0
};

SDL_Surface *load_image(std::string,int = -1,int = -1,int = -1);
void init(void);
void load(void);
void draw(void);
void close(void);

int collides(SDL_Rect, SDL_Rect);
void update_score(void);

void op_movement(void);

void log( std::string msg );

#endif /* defined(__Pong__main__) */
