//
//  main.cpp
//  Pong
//
//  Created by Nik Klassen on 2012-12-30.
//  Copyright (c) 2012 Nik Klassen. All rights reserved.
//

#include "main.h"

// Basic screen variables
SDL_Surface *screen = NULL;

// Rect that represents that score bar
SDL_Rect score_rect;

// Timer variables
const int fps = 32;

SDL_Surface *background = NULL;

// Scoring variables
SDL_Surface *my_scoreSurface = NULL, *op_scoreSurface = NULL;
SDL_Rect score_offsets[2];
int my_score = 0, op_score = 0;

// Game pieces
Paddle my_paddle(20, 50);
Paddle op_paddle(605,50);
Ball b;

SDL_Surface *big_paddle = NULL;

// Font
TTF_Font *font = NULL;
SDL_Color fontColour = {255,255,255};

// Event handler
SDL_Event event;

int main( int argc, char* args[] )
{
    // Loop control variables
    bool quit = false;
    Timer fps;
    
    // Init all core functions (SDL, TTF, etc.)
    init();
    
    // Init variables with images, co ordinates, etc
    load();
    
    // Draw images
    draw();
    
    // Load the ball initially
    b.spawn(my_paddle.x + 25, my_paddle.y + 25);
    
    while (!quit) {
        
        fps.start();
        
        while (SDL_PollEvent(&event)) {
            
            // Two conditions to quit the app, x out the window or type Command-Q
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                
                if ((SDL_GetModState() & KMOD_META) && event.key.keysym.sym == SDLK_q) {
                    quit = true;
                }
                
                // "Serve" the ball with the space bar
                else if (event.key.keysym.sym == SDLK_SPACE && !b.isMoving()) {
                    b.serve();
                }
                
                else if (event.key.keysym.sym == SDLK_c) {
                    if (!my_paddle.currentImage) my_paddle.currentImage = 1;
                    else my_paddle.currentImage = 0;
                }
            }
            
            // Handle the movement of your paddle within the class
            my_paddle.handle_event(event);
        }
        
        // Adjust position co-ordinates
        my_paddle.move();
        
        b.move();
        
        op_movement();
        
        Paddle p;
        
        int c = COLLISION_NONE;
        
        if (collides(b.getRect(), my_paddle.getRect())) {
            p = my_paddle;
            c = collides(b.getRect(), my_paddle.getRect());
        }
        else if (collides(b.getRect(), op_paddle.getRect())) {
            p = op_paddle;
            c = collides(b.getRect(), op_paddle.getRect());
        }
        
        // Check if the ball has hit a paddle
        if (c != COLLISION_NONE) {
            
            std::cout << c << std::endl;
            
            // Check which way to actually bounce the ball
            if (c == COLLISION_CORNER) {
                b.bounce('y', p.vy);
                b.bounce('x');
            } else if (c == COLLISION_TB) {
                b.bounce('y', p.vy);
            } else if (c == COLLISION_LR) {
                b.bounce('x');
                b.vy += p.vy;
                
                // If the ball is moving too quickly slow it down to the maximum speed
                if (abs(b.vy) > b.MAX_SPEED) {
                    // Make sure the ball's velocity is in the same direction it was already moving
                    b.vy = (b.vy/abs(b.vy)) * b.MAX_SPEED;
                }
                
                // If the ball isn't going at it's max speed speed it up
                if (abs(b.vx) < b.MAX_SPEED) {
                    b.vx += 0.5;
                }
            }
            
        }
        
        // Check if the ball has gone off the edge of the screen and change the score
        if (b.x < 0 || b.x > SCREEN_WIDTH - b.BALL_WIDTH) {
            
            if (b.x < SCREEN_WIDTH/2) op_score++;
            else my_score++;
            
            update_score();
            
            b.spawn(my_paddle.x + 25, my_paddle.y + 15);
            
        }
        
        // If the ball would go off the top or bottom bounce it back
        if (b.y > SCREEN_HEIGHT - b.BALL_HEIGHT || collides(b.getRect(), score_rect)) {
            std::cout << "Bouncing off the top/bottom\n";
            b.bounce('y');
        }
        
        draw();
        
        // Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) SDL_Delay((1000/FRAMES_PER_SECOND) - fps.get_ticks());
        
    }
    
    // Perform deletion operations
    close();
    
    return 0;
}

SDL_Surface *load_image (std::string s, int r, int g, int b) {
    
    // Get the desired image
    SDL_Surface *temp = IMG_Load(s.c_str());
    
    // Format the image
    SDL_Surface *returnImage = SDL_DisplayFormat(temp);
    
    SDL_FreeSurface(temp);
    
    // If the colour mapping is not the default (-1,-1,-1) use that colour key on the image
    if (r >= 0 && g >= 0 && b >= 0) {
        SDL_SetColorKey(returnImage, SDL_SRCCOLORKEY, SDL_MapRGB(returnImage->format, r, g, b));
    }
    
    return returnImage;
}

int collides (SDL_Rect rectA, SDL_Rect rectB) {
    
    int x = 0, y = 0;
    
    // Left side of rectA
    if ( rectA.x <= rectB.x + rectB.w && rectA.x >= rectB.x ) x++;
    
    // Right side of rectA
    if ( rectA.x + rectA.w <= rectB.x + rectB.w && rectA.x + rectA.w >= rectB.x ) x++;
    
    // Top side of rectA
    if ( rectA.y <= rectB.y + rectB.h && rectA.y >= rectB.y ) y++;
    
    // Bottom side of rectA
    if ( rectA.y + rectA.h <= rectB.y + rectB.h && rectA.y + rectA.h >= rectB.y ) y++;
    
    // For a collision to occur both an x and y component (a corner) have to be in the other rectangle
    if (x && y) {
        
        // If the first box collides with the top or bottom of the second
        if (x == 2) return COLLISION_TB;
        
        // If the boxes collide side on
        else if (y == 2) return COLLISION_LR;
        
        // If the boxes' corners intersect
        else return COLLISION_CORNER;
        
    }
    
    return COLLISION_NONE;
}

void update_score () {
    
    std::stringstream s;
    
    s << my_score;
    my_scoreSurface = TTF_RenderText_Solid(font, s.str().c_str(), fontColour);
    
    // Clear the string stream
    s.str("");
    
    s << op_score;
    op_scoreSurface = TTF_RenderText_Solid(font, s.str().c_str(), fontColour);
    
}

void op_movement () {
    
    
    static int r;
    static int randomDelay;
    
    // Only update the movement after a random delay has occured
    if (r > randomDelay) {
        // If the ball is below the paddle and heading towards it move it down
        if (b.y > op_paddle.y + op_paddle.PADDLE_HEIGHT && b.vx > 0) {
            
            op_paddle.vy = op_paddle.MAX_SPEED/3.0;
            r = 0;
            // If the ball is aboce the paddle and headings towards it move it up
        } else if (b.y < op_paddle.y && b.vx > 0) {
            
            op_paddle.vy = -op_paddle.MAX_SPEED/3.0;
            r = 0;
        }
        // Move the paddle towards the center if the ball is heading away from it
        else if (b.vx < 0){
            
            if (op_paddle.y < SCREEN_HEIGHT/2 - op_paddle.PADDLE_HEIGHT/2) {
                op_paddle.vy = op_paddle.MAX_SPEED/3.0;
            } else if (op_paddle.y > SCREEN_HEIGHT/2 - op_paddle.PADDLE_HEIGHT/2) {
                op_paddle.vy = -op_paddle.MAX_SPEED/3.0;
            } else {
                op_paddle.vy = 0;
            }
            
            r = 0;
        }
    }
    
    if (randomDelay == 0) {
        randomDelay = arc4random() % 15;
    }
    
    r++;
    
    op_paddle.move();
}

void init () {
    
    SDL_Init(SDL_INIT_EVERYTHING);
    
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    
    TTF_Init();
    
    SDL_WM_SetCaption("Paddle Battle", NULL);
}

void load () {
    
    //Open the font
    font = TTF_OpenFont( "arial.ttf", 28 );
    
    background = load_image("Background.png");
    
    // Set the paddle images
    my_paddle.images[0] = load_image("Paddle.png");
    op_paddle.images[0] = load_image("Paddle.png");
    
    my_paddle.images[1] = load_image("paddle_big.png");
    op_paddle.images[1] = load_image("paddle_big.png");
    
    // Set the ball image
    b.setImage(load_image("Ball.png", 0xFF, 0xFF, 0xFF));
    
    update_score();
    
    // Declare the co-ordinates for the score labels
    score_offsets[0].x = 25;
    score_offsets[0].y = 5;
    
    score_offsets[1].x = 610;
    score_offsets[1].y = 5;
    
    // Define that bounds of the score bar
    score_rect.x = 0;
    score_rect.y = 0;
    score_rect.w = SCREEN_WIDTH;
    score_rect.h = 40;
}

void draw () {
    
    // Draw background
    SDL_BlitSurface(background, NULL, screen, NULL);
    
    // Draw score text
    SDL_BlitSurface(my_scoreSurface, NULL, screen, &score_offsets[0]);
    SDL_BlitSurface(op_scoreSurface, NULL, screen, &score_offsets[1]);
    
    // Draw paddles at appropriate co ordinates
    my_paddle.draw(screen);
    op_paddle.draw(screen);
    
    if (b.isMoving()) {
        b.draw(screen);
    } else {
        b.x = my_paddle.x + 25;
        b.y = my_paddle.y + 25;
        b.draw(screen);
    }
    
    // Update screen
    SDL_Flip(screen);
    
}

void close () {
    
    SDL_FreeSurface(background);
    SDL_FreeSurface(my_scoreSurface);
    SDL_FreeSurface(op_scoreSurface);
    
    // Close font objects
    TTF_CloseFont(font);
    TTF_Quit();
    
    SDL_Quit();
    
}


