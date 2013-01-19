//
//  Ball.h
//  Pong
//
//  Created by Nik Klassen on 2012-12-31.
//  Copyright (c) 2012 Nik Klassen. All rights reserved.
//

#ifndef __Pong__Ball__
#define __Pong__Ball__

#include <iostream>
#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>

#include "main.h"

class Ball {

    SDL_Surface *image;
    
public:
    
    const int BALL_HEIGHT = 10;
    const int BALL_WIDTH = 10;
    const float MAX_SPEED = 10;
    const float MIN_SPEED = 5;
    
    int x, y;
    float vx, vy;
    float speed = 5.0;
    
    Ball() { image = NULL; };
    ~Ball() { SDL_FreeSurface(image); };
    
    void spawn(int,int);
    void setVels(int,int);
    
    void serve();
    bool isMoving();
    void move(void);
    void bounce(char, int=0);
    
    void draw(SDL_Surface *);
    SDL_Rect getRect(void);
    void setImage(SDL_Surface *img) {image = img;};

};

#endif /* defined(__Pong__Ball__) */