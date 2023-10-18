#include <stdio.h>
#include "player.hpp"
#include <SDl2/SDL_ttf.h>

void GameProcess::init(){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        printf("Couldn't init SDL! Error: %s", SDL_GetError());
        deInit(1);
    }
    if(IMG_Init(IMG_INIT_PNG) == 0){
        printf("Couldn't init an image! Error: %s", SDL_GetError());
        deInit(1);
    }
    window = SDL_CreateWindow("DeadInside", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if(window == NULL){
        printf("Couldn't create a window! Error: %s", SDL_GetError());
        deInit(1);
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(renderer == NULL){
        printf("Couldn't create a renderer! Error: %s", SDL_GetError());
        deInit(1);
    }
    if(TTF_Init() < 0){
        printf("Couldn't init fonts! Error: %s", SDL_GetError());
        deInit(1);
    }
} // иницализация SDL

void GameProcess::deInit(int error){
    if(renderer != NULL) SDL_DestroyRenderer(renderer);
    if(window != NULL) SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    exit(error);
} // деиницализация SDL

GameProcess::GameProcess(){
    window = NULL;
    renderer = NULL;
    
    windowWidth = 800;
    windowHeight = 600;
    
    gameWidth = 1500;
    gameHeight = 1000;
    
    
    frame = 0;
    currentFrametime = 0;
    maxFrametime = 300;
    
    lastTime = SDL_GetTicks();
    newTime = 0;
    dt = 0;
}

GameProcess::~GameProcess(){}


int GameProcess::frameCounter(){
    newTime = SDL_GetTicks();
    dt = newTime - lastTime;
    lastTime = newTime;
    
    currentFrametime += dt;
    if(currentFrametime >= maxFrametime){
        currentFrametime -= maxFrametime;
        frame = (frame + 1) % 2;
    }
    return frame;
} // счетчик фреймов

SDL_Texture* GameProcess::loadTexture(const char* filename){
    SDL_Surface* surface = IMG_Load(filename);
    if(surface == nullptr){
        printf("Couldn't load image %s! Error: %s ", filename, SDL_GetError());
        deInit(1);
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
} // загружаем текстуры
void GameProcess::renderBackground(SDL_Texture* tex, SDL_Rect src){
    SDL_RenderCopy(renderer, tex, &src, NULL);
}
void GameProcess::render(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst){
    SDL_RenderCopy(renderer, tex, &src, &dst);
}
