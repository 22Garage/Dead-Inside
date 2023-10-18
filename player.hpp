#ifndef player_hpp
#define player_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class GameProcess{
public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    
    int windowWidth;
    int windowHeight;
    
    int gameWidth;
    int gameHeight;
    
    int frame;
    int currentFrametime;
    int maxFrametime;
    
    int lastTime;
    int newTime;
    int dt;
    
    GameProcess();
    ~GameProcess();
    
    void init();
    void deInit(int error);
    SDL_Texture* loadTexture(const char* filename);
    int frameCounter();
    void renderBackground(SDL_Texture* tex, SDL_Rect src);
    void render(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst);
    
};



class Player: public GameProcess{
public:
    Player();
    ~Player();

    void checkPlayerBoards(GameProcess& g);
    void checkCanAdd();
    void countDstPlayerRect(GameProcess& g);
    void plusTrees();


    int xPlayer, yPlayer; // координаты
    int trees; // здоровье и деревья
    bool canCut;
    bool canAdd;
    SDL_Rect playerRect;
    SDL_Rect dstPlayerRect;
    SDL_Texture* playerTex;

};

class Bonfire: public Player{
public:
    int xBonfire, yBonfire;
    int life;
    int lastTime;
    int lastFrameTime;
    int newTime;
    int newFrameTime;
    int frame;
    int currentFrametime;
    int maxFrametime;
    int dt;
    int dft;
    int k;
    int repeats;
    
    Bonfire();
    ~Bonfire();
    
    void lifeCounter();
    int frameCounter();
    void checkCanPlus();
    
};

class Camera: public Bonfire{
public:
    SDL_Rect cameraRect;
    SDL_Rect dstCameraRect;
    SDL_Rect backgroundRect;
    SDL_Rect dstBonfireRect;
    
    Camera();
    ~Camera();
    
    void countCoords(GameProcess& g, Player& p);
    void checkCameraBoards(GameProcess& g);
    void countDstCameraRect(GameProcess& g, Player& p);
    void countDstBonfireRect(Bonfire& b);
    
};

class Forest: public Camera{
public:
    int firstCut;
    int lastRegen;
    int newRegen;
    int dr;
    Forest();
    ~Forest();
    
    int regenCounter();
};


#endif /* player_hpp */
