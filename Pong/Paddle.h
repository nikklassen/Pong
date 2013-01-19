//
//  Paddle.h
//  Pong
//
//  Created by Nik Klassen on 2012-12-30.
//  Copyright (c) 2012 Nik Klassen. All rights reserved.
//

#ifndef __Pong__Paddle__
#define __Pong__Paddle__

#include <iostream>
#include <string>
#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>
#include "main.h"

class Paddle {
private:
    float speed = 5.0;
    
public:
    
    const int PADDLE_HEIGHT = 60;
    const int PADDLE_WIDTH = 15;
    const float MAX_SPEED = 10;
    
    int currentImage = 0;
    SDL_Surface *images[2];
    
    int x, y;
    float vy;
    
    Paddle();
    Paddle(int,int);
    ~Paddle(void);
    
    Paddle& operator= (const Paddle&);
    
    void handle_event(SDL_Event);
    void move();
    
    void draw(SDL_Surface *);
    void setCoodinates(int nx,int ny) {x = nx; y = ny; };
    
    SDL_Rect getRect(void);

};
#endif /* defined(__Pong__Paddle__) */
