//
//  Ball.cpp
//  Pong
//
//  Created by Nik Klassen on 2012-12-31.
//  Copyright (c) 2012 Nik Klassen. All rights reserved.
//

#include "Ball.h"

void Ball::spawn(int startX, int startY) {
    
    x = startX;
    y = startY;
    
    vx = 0;
    vy = 0;
}

void Ball::setVels(int newVX, int newVY) {

    if (newVX <= MAX_SPEED) vx = newVX;
    else vx = MAX_SPEED;
    
    if (newVY <= MAX_SPEED) vy = newVY;
    else vy = MAX_SPEED;
}

void Ball::serve() {
    
    vx = speed;
    vy = speed;
    
}

void Ball::move() {
    
    x += vx;
    y += vy;

}

bool Ball::isMoving() {
    if (vx || vy) return true;
    else return false;
}

void Ball::bounce(char c, int i) {
    
    if (c == 'x') {
        x -= vx;
        vx = -vx;
    }
    else {
        if ((vy < 0 && i < 0) || (vy > 0 && i > 0)) {
            y += i;
            vy += i;
            vy = -vy;
        } else {
            y -= vy;
            y += i;
        }
    }
}

void Ball::draw(SDL_Surface *src) {
    
    SDL_Rect rect;
    
    rect.x = x;
    rect.y = y;
    
    SDL_BlitSurface(image, NULL, src, &rect);
    
}

SDL_Rect Ball::getRect() {
    
    SDL_Rect rect;
    
    rect.x = x;
    rect.y = y;
    rect.w = BALL_WIDTH;
    rect.h = BALL_HEIGHT;
    
    return rect;
}