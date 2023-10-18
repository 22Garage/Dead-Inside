#include <stdio.h>
#include "player.hpp"

Bonfire::Bonfire(){
    xBonfire = 650;
    yBonfire = 350;
    life = 100;
    lastTime = SDL_GetTicks();
    lastFrameTime = SDL_GetTicks();
    newTime = 0;
    newFrameTime = 0;
    frame = 0;
    currentFrametime = 0;
    maxFrametime = 200;
    dt = 0;
    dft = 0;
    k = 1;
    repeats = 0;
}
Bonfire::~Bonfire(){
    
}


void Bonfire::lifeCounter(){
    newTime = SDL_GetTicks();
    dt += newTime - lastTime;
    lastTime = newTime;
    if(dt >= 1000){
        dt -= 1000;
        repeats++;
        life -= 1 * k;
    }
    if(repeats > 60 && k < 4){
        k++;
        repeats = 0;
    }
}

int Bonfire::frameCounter(){
    newFrameTime = SDL_GetTicks();
    dft = newFrameTime - lastFrameTime;
    lastFrameTime = newFrameTime;
    
    currentFrametime += dft;
    if(currentFrametime >= maxFrametime){
        currentFrametime -= maxFrametime;
        frame = (frame + 1) % 3;
    }
    return frame;
}

void Bonfire::checkCanPlus(){
    if(life > 100){
        life = 100;
    }
}
