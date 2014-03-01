//
//  Paddle.cpp
//  Pong
//
//  Created by Nik Klassen on 2012-12-30.
//  Copyright (c) 2012 Nik Klassen. All rights reserved.
//

#include "Paddle.h"

Paddle::Paddle() {
    x = 0;
    y = 0;
    
    vy = 0.0;
    
    images[0] = NULL;
    images[1] = NULL;
}

Paddle::Paddle( int startX, int startY ) {
    
    x = startX;
    y = startY;
    
    vy = 0.0;
    
    images[0] = NULL;
    images[1] = NULL;
}

Paddle::~Paddle() {
    SDL_FreeSurface(images[0]);
    SDL_FreeSurface(images[1]);
}

Paddle& Paddle::operator=(const Paddle& p) {
    
    x = p.x;
    y = p.y;
    
    vy = p.vy;
    
    images[0] = NULL;
    images[1] = NULL;
    
    return *this;
}

void Paddle::handle_event(SDL_Event event) {
    
    if( event.type == SDL_KEYDOWN ) {
        switch( event.key.keysym.sym ) {
            case SDLK_DOWN:
                vy += speed;
                break;
            case SDLK_UP:
                vy -= speed;
            default:
                break;
        }
    } else if( event.type == SDL_KEYUP ) {
        if( event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN ) {
            vy = 0.0;
        }
    }
}

void Paddle::move() {
    
    if( abs(vy) < MAX_SPEED && vy != 0.0 ) {
        if (vy > 0) vy += 0.5;
        else vy -= 0.5;
    }
    y += vy;
    
    if( y < BAR_HEIGHT ) {
        y = BAR_HEIGHT + 1;
    } else if( y > (SCREEN_HEIGHT - images[currentImage]->clip_rect.h) ) {
        y = SCREEN_HEIGHT - images[currentImage]->clip_rect.h - 1;
    }
}

void Paddle::draw(SDL_Surface *src) {
    
    SDL_Rect rect;
    
    rect.x = x;
    rect.y = y;
    
    SDL_BlitSurface(images[currentImage], NULL, src, &rect);
}

SDL_Rect Paddle::getRect() {
    
    SDL_Rect rect;
    
    rect.x = x;
    rect.y = y;
    rect.w = images[currentImage]->clip_rect.w;
    rect.h = images[currentImage]->clip_rect.h;
    
    return rect;
}
