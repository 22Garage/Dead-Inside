#include <stdio.h>
#include "player.hpp"
#include <ctime>
#include <math.h>

Forest::Forest(){
    firstCut = 0;
    lastRegen = SDL_GetTicks();
    newRegen = 0;
    dr = 0;
}

Forest::~Forest(){

}

//}
int Forest::regenCounter(){
    newRegen = SDL_GetTicks();
    dr += newRegen - lastRegen;
    lastRegen = newRegen;
    if(dr >= 35000){
        dr -= 35000;
        return 1;
    }
    return 0;
}
