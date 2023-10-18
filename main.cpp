#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDl2/SDL_ttf.h>
#include "player.hpp"
#include <random>
#include <math.h>
#include <algorithm>
using namespace std;


GameProcess game; GameProcess& g = game;
Player player; Player& p = player; SDL_Rect playerRect; SDL_Rect dstPlayerRect; SDL_Texture* playerTex;
Camera camera; Camera& c = camera;
Bonfire bonfire; Bonfire& b = bonfire;
Forest forest; Forest& f = forest;
SDL_Rect treeRect1;
SDL_Rect dstTreeRect1;
SDL_Rect treeRect2;
SDL_Rect dstTreeRect2;
SDL_Rect treeRect3;
SDL_Rect dstTreeRect3;
SDL_Rect treeRect4;
SDL_Rect dstTreeRect4;
SDL_Rect treeRect5;
SDL_Rect dstTreeRect5;
SDL_Rect treeRect6;
SDL_Rect dstTreeRect6;
SDL_Rect treeRect7;
SDL_Rect dstTreeRect7;
SDL_Rect treeRect8;
SDL_Rect dstTreeRect8;
SDL_Rect treeRect9;
SDL_Rect dstTreeRect9;
SDL_Rect treeRect10;
SDL_Rect dstTreeRect10;

SDL_Rect backgroundRect = {0, 0, 1500, 1000};
SDL_Texture* bonfireTex;
SDL_Rect bonfireRect;
SDL_Texture* flameTex;
SDL_Texture* fireTex[3];

SDL_Event event;
SDL_Surface* pTrees;
SDL_Surface* bLife;
SDL_Color color = {0, 0, 0};
TTF_Font* font;
SDL_Texture* pTreesTex;
SDL_Texture* bLifeTex;
SDL_Rect pTreesDst;
SDL_Rect bLifeDst;

SDL_Texture* zastavka;
SDL_Texture* menu[4];
SDL_Texture* spravka;
SDL_Texture* records;
SDL_Texture* changeName;
SDL_Texture* total;
SDL_Texture* pause;

int coords[10][2];

bool isRunning = true;
bool isGameRunning = false;
bool isSpravkaRunning = false;
bool isChangeNameRunning = false;
bool isRecordsRunning = false;
bool isTotalRunning = false;
bool isPauseRunning = false;

bool isUpPressed = false;
bool isDownPressed = false;
bool isLeftPressed = false;
bool isRightPressed = false;
bool isSpacePressed = false;
bool nextStep = false;
int playerFrame;
int fireFrame;
int delta;

int totalScore = 0;
int flag = 0;
int pp = 0;
int h = 0;

SDL_Texture* stand[2];
SDL_Texture* leftRun[2];
SDL_Texture* rightRun[2];
SDL_Texture* upRun[2];
SDL_Texture* downRun[2];
SDL_Texture* punch[2];
SDL_Texture* backgroundTex;
SDL_Texture* treeTex1; SDL_Texture* cutTreeTex1;
SDL_Texture* treeTex2; SDL_Texture* cutTreeTex2;
SDL_Texture* treeTex3; SDL_Texture* cutTreeTex3;
SDL_Texture* treeTex4; SDL_Texture* cutTreeTex4;
SDL_Texture* treeTex5; SDL_Texture* cutTreeTex5;
SDL_Texture* treeTex6; SDL_Texture* cutTreeTex6;
SDL_Texture* treeTex7; SDL_Texture* cutTreeTex7;
SDL_Texture* treeTex8; SDL_Texture* cutTreeTex8;
SDL_Texture* treeTex9; SDL_Texture* cutTreeTex9;
SDL_Texture* treeTex10; SDL_Texture* cutTreeTex10;

struct Records{
    char nickname[10];
    int score;
};

Records table[11];

char lastPlayer[11];

void showZastavka();
void showMenu();
void showPause();
void showSpravka();
void showChangeName();
void showRecords();
void showChangeName();
void showTotal();
void updateRecords();
void sortRecords(int n);
void getPushes(SDL_Event event);
void update();
void render();
void makeRandomForest();
void countDstTreeRect();
int cut();
void treeFall(int i);
void cutAnim(int i);
void regenerateForest();
void regenerateTree(int i);
void move();
void destroyTextures();
void loadTexes();
void updateFire();
void addTrees();
void checkTreeCollision();
int checkOrderOfTextures();
SDL_Texture* loadTreeTexture(const char* filename, SDL_Rect* rect);
void loadText();
void initFont();
void createLocation();

int main( int argc, char *argv[] ){
    game.init();
    initFont();
    loadTexes();
    showZastavka();
    while(isRunning == true){
        showMenu();
        createLocation();
        while(isGameRunning){
            if(h == 0){
                flag = 1;
                h = 1;
            }
            while(SDL_PollEvent(&event)){
                getPushes(event);
            }
            update();
            render();
        }
        if(flag){
            showTotal();
            updateRecords();
            totalScore = 0;
            flag = 0;
        }
    }
    destroyTextures();
    game.deInit(0);
    return 0;
}

void getPushes(SDL_Event event){
    switch(event.type){
        case SDL_QUIT:
            isRunning = false;
            isGameRunning = false;
            flag = 0;
            break;
        case SDL_WINDOWEVENT:
            if(event.window.event == SDL_WINDOWEVENT_RESIZED){
                g.windowWidth = event.window.data1;
                g.windowHeight = event.window.data2;
            }
            break;
            
        case SDL_KEYDOWN:
            switch(event.key.keysym.scancode){
                case SDL_SCANCODE_ESCAPE:
                    isRunning = false;
                    isGameRunning = false;
                    flag = 0;
                    break;
                case SDL_SCANCODE_P:
                    showPause();
                    break;
                case SDL_SCANCODE_SPACE:
                    isSpacePressed = true;
                    nextStep = true;
                    break;
                case SDL_SCANCODE_UP:
                    isUpPressed = true;
                    break;
                case SDL_SCANCODE_DOWN:
                    isDownPressed = true;
                    break;
                case SDL_SCANCODE_LEFT:
                    isLeftPressed = true;
                    break;
                case SDL_SCANCODE_RIGHT:
                    isRightPressed = true;
                case SDL_SCANCODE_RETURN:
                    nextStep = true;
                    break;
                default:
                    nextStep = true;
                    break;
            }
            break;
        case SDL_KEYUP:
            switch(event.key.keysym.scancode){
                case SDL_SCANCODE_SPACE:
                    isSpacePressed = false;
                    break;
                case SDL_SCANCODE_UP:
                    isUpPressed = false;
                    break;
                case SDL_SCANCODE_DOWN:
                    isDownPressed = false;
                    break;
                case SDL_SCANCODE_LEFT:
                    isLeftPressed = false;
                    break;
                case SDL_SCANCODE_RIGHT:
                    isRightPressed = false;
                    break;
                default:
                    break;
            }
            break;
    }
}

void update(){
    playerFrame = g.frameCounter();
    fireFrame = b.frameCounter();
    updateFire();
    b.lifeCounter();
    delta = 10 * ((g.windowWidth*g.windowHeight)/(800*600));
    move();
    treeFall(cut());
    if(f.firstCut && f.regenCounter()){
        regenerateForest();
    }
    p.checkCanAdd();
    b.checkCanPlus();
    addTrees();
    p.countDstPlayerRect(g);
    c.countCoords(g, p);
    countDstTreeRect();
    c.countDstBonfireRect(b);
    loadText();
    if(b.life < 1){
        b.life = 0;
        isGameRunning = false;
    }
}

void move(){
    if(!isUpPressed && !isDownPressed && !isLeftPressed && !isRightPressed && !isSpacePressed){
        playerTex = stand[playerFrame];
    }
    if(isUpPressed && !isDownPressed && !isLeftPressed && !isRightPressed){
        p.yPlayer -= delta;
        p.checkPlayerBoards(g);
        checkTreeCollision();
        playerTex = upRun[playerFrame];
    }else if(isUpPressed && !isDownPressed){
        p.yPlayer -= delta;
        p.checkPlayerBoards(g);
        checkTreeCollision();
    }
    if(isDownPressed && !isUpPressed && !isLeftPressed && !isRightPressed){
        p.yPlayer += delta;
        p.checkPlayerBoards(g);
        checkTreeCollision();
        playerTex = downRun[playerFrame];
    }else if(isDownPressed && !isUpPressed){
        p.yPlayer += delta;
        p.checkPlayerBoards(g);
        checkTreeCollision();
    }
    if(isLeftPressed && !isRightPressed){
        p.xPlayer -= delta;
        p.checkPlayerBoards(g);
        checkTreeCollision();
        playerTex = leftRun[playerFrame];
    }
    if(isRightPressed && !isLeftPressed){
        p.xPlayer += delta;
        p.checkPlayerBoards(g);
        checkTreeCollision();
        playerTex = rightRun[playerFrame];
    }
}

void loadTexes(){
    stand[0] = g.loadTexture("покой1.png");
    stand[1] = g.loadTexture("покой2.png");
    leftRun[0] = g.loadTexture("бегвлево1.png");
    leftRun[1] = g.loadTexture("бегвлево2.png");
    rightRun[0] = g.loadTexture("бегвправо1.png");
    rightRun[1] = g.loadTexture("бегвправо2.png");
    upRun[0] = g.loadTexture("спина1.png");
    upRun[1] = g.loadTexture("спина2.png");
    downRun[0] = g.loadTexture("лицо1.png");
    downRun[1] = g.loadTexture("лицо2.png");
    punch[0] = g.loadTexture("удар1.png");
    punch[1] = g.loadTexture("удар2.png");
    backgroundTex = g.loadTexture("грунт.png");
    treeTex1 = loadTreeTexture("дерево.png", &treeRect1);
    treeTex2 = loadTreeTexture("дерево.png", &treeRect2);
    treeTex3 = loadTreeTexture("дерево.png", &treeRect3);
    treeTex4 = loadTreeTexture("дерево.png", &treeRect4);
    treeTex5 = loadTreeTexture("дерево.png", &treeRect5);
    treeTex6 = loadTreeTexture("дерево.png", &treeRect6);
    treeTex7 = loadTreeTexture("дерево.png", &treeRect7);
    treeTex8 = loadTreeTexture("дерево.png", &treeRect8);
    treeTex9 = loadTreeTexture("дерево.png", &treeRect9);
    treeTex10 = loadTreeTexture("дерево.png", &treeRect10);
    bonfireTex = loadTreeTexture("дно.png", &bonfireRect);
    fireTex[0] = g.loadTexture("огонь1.png");
    fireTex[1] = g.loadTexture("огонь2.png");
    fireTex[2] = g.loadTexture("огонь3.png");
    zastavka = g.loadTexture("заставка.png");
    menu[0] = g.loadTexture("меню1.png");
    menu[1] = g.loadTexture("меню2.png");
    menu[2] = g.loadTexture("меню3.png");
    menu[3] = g.loadTexture("меню2.png");
    spravka = g.loadTexture("справка.png");
    records = g.loadTexture("таблица рекордов.png");
    changeName = g.loadTexture("смена игрока.png");
    total = g.loadTexture("итого.png");
    pause = g.loadTexture("меню.png");
}

void createLocation(){
    g.lastTime = SDL_GetTicks();
    b.lastTime = SDL_GetTicks();
    b.lastFrameTime = SDL_GetTicks();
    SDL_QueryTexture(backgroundTex, NULL, NULL, &g.gameWidth, &g.gameHeight);
    backgroundRect = {0, 0, g.gameWidth, g.gameHeight};
    makeRandomForest();
}

void render(){
    game.renderBackground(backgroundTex, c.cameraRect);
    game.render(bonfireTex, bonfireRect, c.dstBonfireRect);
    if(checkOrderOfTextures()){
        game.render(treeTex1, treeRect1, dstTreeRect1);
        game.render(treeTex2, treeRect2, dstTreeRect2);
        game.render(treeTex3, treeRect3, dstTreeRect3);
        game.render(treeTex4, treeRect4, dstTreeRect4);
        game.render(treeTex5, treeRect5, dstTreeRect5);
        game.render(treeTex6, treeRect6, dstTreeRect6);
        game.render(treeTex7, treeRect7, dstTreeRect7);
        game.render(treeTex8, treeRect8, dstTreeRect8);
        game.render(treeTex9, treeRect9, dstTreeRect9);
        game.render(treeTex10, treeRect10, dstTreeRect10);
        game.render(playerTex, p.playerRect, c.dstCameraRect);
    }else{
        game.render(playerTex, p.playerRect, c.dstCameraRect);
        game.render(treeTex1, treeRect1, dstTreeRect1);
        game.render(treeTex2, treeRect2, dstTreeRect2);
        game.render(treeTex3, treeRect3, dstTreeRect3);
        game.render(treeTex4, treeRect4, dstTreeRect4);
        game.render(treeTex5, treeRect5, dstTreeRect5);
        game.render(treeTex6, treeRect6, dstTreeRect6);
        game.render(treeTex7, treeRect7, dstTreeRect7);
        game.render(treeTex8, treeRect8, dstTreeRect8);
        game.render(treeTex9, treeRect9, dstTreeRect9);
        game.render(treeTex10, treeRect10, dstTreeRect10);
    }
    game.render(flameTex, bonfireRect, c.dstBonfireRect);
    SDL_RenderCopy(game.renderer, pTreesTex, NULL, &pTreesDst);
    SDL_RenderCopy(game.renderer, bLifeTex, NULL, &bLifeDst);
    SDL_RenderPresent(game.renderer);
    SDL_Delay(30);
}

SDL_Texture* loadTreeTexture(const char* filename, SDL_Rect* rect){
    SDL_Surface* surface = IMG_Load(filename);
    if(surface == NULL){
        printf("Couldn't load image %s! Error: %s ", filename, SDL_GetError());
        game.deInit(1);
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(game.renderer, surface);
    *rect = {0, 0, surface -> w, surface -> h};
    SDL_FreeSurface(surface);
    return texture;
}

void makeRandomForest(){
    srand((unsigned int)(time(0))*4);
    coords[0][0] = 30 + ((-1 + (rand()%2))*20);
    coords[0][1] = 100 + ((-1 + (rand()%2))*25);
    srand((unsigned int)(time(0))*5);
    coords[1][0] = 750 + ((-1 + (rand()%2))*150);
    coords[1][1] = 100 + ((-1 + (rand()%2))*100);
    srand((unsigned int)(time(0))*179);
    coords[2][0] = 750 + ((-1 + (rand()%2))*150);
    coords[2][1] = 820 + ((-1 + (rand()%2))*100);
    srand((unsigned int)(time(0))*42);
    coords[3][0] = 50 + ((-1 + (rand()%2))*20);
    coords[3][1] = 800 + ((-1 + (rand()%2))*50);
    srand((unsigned int)(time(0))*64);
    coords[4][0] = 250 + ((-1 + (rand()%2))*70);
    coords[4][1] = 700 + ((-1 + (rand()%2))*100);
    srand((unsigned int)(time(0))*99);
    coords[5][0] = 250 + ((-1 + (rand()%2))*70);
    coords[5][0] = 300 + ((-1 + (rand()%2))*100);
    srand((unsigned int)(time(0))*77);
    coords[6][0] = 1400 + ((-1 + (rand()%2))*40);
    coords[6][1] = 100 + ((-1 + (rand()%2))*25);
    srand((unsigned int)(time(0))*3);
    coords[7][0] = 1340 + ((-1 + (rand()%2))*50);
    coords[7][1] = 800 + ((-1 + (rand()%2))*50);
    srand((unsigned int)(time(0))*93);
    coords[8][0] = 1150 + ((-1 + (rand()%2))*70);
    coords[8][1] = 700 + ((-1 + (rand()%2))*100);
    srand((unsigned int)(time(0))*124);
    coords[9][0] = 1250 + ((-1 + (rand()%2))*70);
    coords[9][1] = 300 + ((-1 + (rand()%2))*100);
}

void countDstTreeRect(){
    dstTreeRect1 = {coords[0][0] - c.cameraRect.x, coords[0][1] - c.cameraRect.y, treeRect1.w/2, treeRect1.h/2};
    dstTreeRect2 = {coords[1][0] - c.cameraRect.x, coords[1][1] - c.cameraRect.y, treeRect2.w/2, treeRect2.h/2};
    dstTreeRect3 = {coords[2][0] - c.cameraRect.x, coords[2][1] - c.cameraRect.y, treeRect2.w/2, treeRect2.h/2};
    dstTreeRect4 = {coords[3][0] - c.cameraRect.x, coords[3][1] - c.cameraRect.y, treeRect2.w/2, treeRect2.h/2};
    dstTreeRect5 = {coords[4][0] - c.cameraRect.x, coords[4][1] - c.cameraRect.y, treeRect2.w/2, treeRect2.h/2};
    dstTreeRect6 = {coords[5][0] - c.cameraRect.x, coords[5][1] - c.cameraRect.y, treeRect2.w/2, treeRect2.h/2};
    dstTreeRect7 = {coords[6][0] - c.cameraRect.x, coords[6][1] - c.cameraRect.y, treeRect2.w/2, treeRect2.h/2};
    dstTreeRect8 = {coords[7][0] - c.cameraRect.x, coords[7][1] - c.cameraRect.y, treeRect2.w/2, treeRect2.h/2};
    dstTreeRect9 = {coords[8][0] - c.cameraRect.x, coords[8][1] - c.cameraRect.y, treeRect9.w/2, treeRect9.h/2};
    dstTreeRect10 = {coords[9][0] - c.cameraRect.x, coords[9][1] - c.cameraRect.y, treeRect10.w/2, treeRect10.h/2};
}

void checkTreeCollision(){
    for(int i = 0; i < 10; i++){
        if((abs(p.xPlayer - (coords[i][0]+50)) < 20) && (abs(p.yPlayer - (coords[i][1] + 90)) < 10)){
            p.xPlayer -= 20;
            p.yPlayer -= 15;
        }
    }
}

int checkOrderOfTextures(){
    for(int i = 0; i < 10; i++){
        if((abs(p.xPlayer - (coords[i][0]+50)) < 50) && (p.yPlayer > (coords[i][1]+90)) && ((abs(p.xPlayer - (coords[i][0])) < 250) && (abs(p.yPlayer - (coords[i][1]))< 250))){
            return 1;
        }
    }
    return 0;
}

int cut(){
    for(int i = 0; i < 10; i++){
        if(((abs(p.xPlayer - (coords[i][0]+50)) < 60) && (abs(p.yPlayer - (coords[i][1] + 90)) < 60)) && isSpacePressed){
            cutAnim(i);
            f.firstCut = 1;
            p.plusTrees();
            return i;
        }
    }
    return 777;
}

void treeFall(int i){
    
    if(i != 777){
        coords[i][0] = -200;
    }
}

void cutAnim(int i){
    if(coords[i][0] + 40 >= p.xPlayer){
        playerTex = punch[1];
    }else{
        playerTex = punch[0];
    }
}

void regenerateForest(){
    for(int i = 0; i < 10; i++){
        if(coords[i][0] == -200){
            regenerateTree(i);
        }
    }
}

void regenerateTree(int i){
    if(i == 0){
        srand((unsigned int)(time(0))*4);
        coords[0][0] = 30 + ((-1 + (rand()%2))*20);
        coords[0][1] = 100 + ((-1 + (rand()%2))*25);
    }else if(i == 1){
        srand((unsigned int)(time(0))*5);
        coords[1][0] = 750 + ((-1 + (rand()%2))*150);
        coords[1][1] = 100 + ((-1 + (rand()%2))*100);
    }else if(i == 2){
        srand((unsigned int)(time(0))*179);
        coords[2][0] = 750 + ((-1 + (rand()%2))*150);
        coords[2][1] = 820 + ((-1 + (rand()%2))*100);
    }else if(i == 3){
        srand((unsigned int)(time(0))*42);
        coords[3][0] = 50 + ((-1 + (rand()%2))*20);
        coords[3][1] = 800 + ((-1 + (rand()%2))*50);
    }else if(i == 4){
        srand((unsigned int)(time(0))*64);
        coords[4][0] = 250 + ((-1 + (rand()%2))*150);
        coords[4][1] = 700 + ((-1 + (rand()%2))*100);
    }else if(i == 5){
        srand((unsigned int)(time(0))*99);
        coords[5][0] = 250 + ((-1 + (rand()%2))*150);
        coords[5][0] = 300 + ((-1 + (rand()%2))*100);
    }else if(i == 6){
        srand((unsigned int)(time(0))*77);
        coords[6][0] = 1400 + ((-1 + (rand()%2))*40);
        coords[6][1] = 100 + ((-1 + (rand()%2))*25);
    }else if(i == 7){
        srand((unsigned int)(time(0))*3);
        coords[7][0] = 1340 + ((-1 + (rand()%2))*50);
        coords[7][1] = 800 + ((-1 + (rand()%2))*50);
    }else if(i == 8){
        srand((unsigned int)(time(0))*93);
        coords[8][0] = 1250 + ((-1 + (rand()%2))*150);
        coords[8][1] = 700 + ((-1 + (rand()%2))*100);
    }else if(i == 9){
        srand((unsigned int)(time(0))*124);
        coords[9][0] = 1250 + ((-1 + (rand()%2))*150);
        coords[9][1] = 300 + ((-1 + (rand()%2))*100);
    }
}

void destroyTextures(){
    for(int i = 0; i < 2; i++){
        SDL_DestroyTexture(stand[i]);
        SDL_DestroyTexture(leftRun[i]);
        SDL_DestroyTexture(rightRun[i]);
        SDL_DestroyTexture(upRun[i]);
        SDL_DestroyTexture(downRun[i]);
        SDL_DestroyTexture(punch[i]);
        SDL_DestroyTexture(fireTex[i]);
    }
    SDL_DestroyTexture(fireTex[2]);
    SDL_DestroyTexture(bonfireTex);
    SDL_DestroyTexture(backgroundTex);
    SDL_DestroyTexture(treeTex1);
    SDL_DestroyTexture(treeTex2);
    SDL_DestroyTexture(treeTex3);
    SDL_DestroyTexture(treeTex4);
    SDL_DestroyTexture(treeTex5);
    SDL_DestroyTexture(treeTex6);
    SDL_DestroyTexture(treeTex7);
    SDL_DestroyTexture(treeTex8);
    SDL_DestroyTexture(treeTex9);
    SDL_DestroyTexture(treeTex10);
    SDL_DestroyTexture(pTreesTex);
    SDL_DestroyTexture(bLifeTex);
    SDL_FreeSurface(pTrees);
    SDL_FreeSurface(bLife);
    TTF_CloseFont(font);
    
}

void updateFire(){
    flameTex = fireTex[fireFrame];
}

void addTrees(){
    if(p.canAdd && (p.trees > 0)){
        if(isSpacePressed){
            p.trees--;
            b.life += 10;
            totalScore += 10;
        }
    }
}

void loadText(){
    char bufferTree[2];
    char bufferLife[4];
    sprintf(bufferTree,"%d",p.trees);
    sprintf(bufferLife,"%d",b.life);
    pTrees = TTF_RenderText_Solid(font, bufferTree, color);
    bLife = TTF_RenderText_Solid(font, bufferLife, color);
    if(!pTrees && !bLife) {
        cout << "Failed to render text: " << TTF_GetError() << endl;
        game.deInit(1);
    }
    pTreesTex = SDL_CreateTextureFromSurface(game.renderer, pTrees);
    pTreesDst = {5, 5, 25, 25};
    bLifeTex = SDL_CreateTextureFromSurface(game.renderer, bLife);
    bLifeDst = {760, 5, 40, 40};
}

void initFont(){
    font = TTF_OpenFont("sample.ttf", 24);
    if (!font) {
        cout << "Failed to load font: " << TTF_GetError() << endl;
        game.deInit(1);
    }
}

void showZastavka(){
    while(!nextStep){
        while(SDL_PollEvent(&event)){
            getPushes(event);
        }
        SDL_RenderCopy(game.renderer, zastavka, NULL, NULL);
        SDL_RenderPresent(game.renderer);
    }
    isSpacePressed = false;
}

void showMenu(){
    int lastTime = SDL_GetTicks();
    int newTime = 0;
    int dt = 0;
    int frame = 0;
    int current = 0;
    SDL_Texture* menuTex;
    
    bool isMenuRunning = true;
    while(isMenuRunning){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    isRunning = false;
                    isGameRunning = false;
                    isMenuRunning = false;
                    break;
                case SDL_WINDOWEVENT:
                    if(event.window.event == SDL_WINDOWEVENT_RESIZED){
                        g.windowWidth = event.window.data1;
                        g.windowHeight = event.window.data2;
                    }
                    break;
                    
                case SDL_KEYDOWN:
                    switch(event.key.keysym.scancode){
                        case SDL_SCANCODE_ESCAPE:
                            isRunning = false;
                            isGameRunning = false;
                            isMenuRunning = false;
                            break;
                        case SDL_SCANCODE_P:
                            isGameRunning = true;
                            isMenuRunning = false;
                            break;
                        case SDL_SCANCODE_S:
                            isSpravkaRunning = true;
                            showSpravka();
                            lastTime = SDL_GetTicks();
                            break;
                        case SDL_SCANCODE_R:
                            isRecordsRunning = true;
                            showRecords();
                            lastTime = SDL_GetTicks();
                            break;
                        case SDL_SCANCODE_C:
                            isChangeNameRunning = true;
                            showChangeName();
                            lastTime = SDL_GetTicks();
                            break;
                        default:
                            break;
                    }
                    break;
            }
        }
        FILE* f = fopen("records.txt", "r");
        if (!f){
            perror ("File error: ");
            system ("pause");
            game.deInit(1);
        }
        fscanf(f, "%s", lastPlayer);
        fclose(f);
        SDL_Rect nickRect;
        SDL_Surface* nickSurf;
        SDL_Texture* nickTex;
        SDL_Color col = {245, 237, 237};
        nickSurf = TTF_RenderText_Solid(font, lastPlayer, col);
        nickTex = SDL_CreateTextureFromSurface(game.renderer, nickSurf);
        nickRect = {30, 150, 250, 50};
        
        newTime = SDL_GetTicks();
        dt = newTime - lastTime;
        lastTime = newTime;
        
        current += dt;
        if(current >= 300){
            current -= 300;
            frame = (frame + 1) % 4;
        }
        menuTex = menu[frame];
        SDL_RenderCopy(game.renderer, menuTex, NULL, NULL);
        SDL_RenderCopy(game.renderer, nickTex, NULL, &nickRect);
        SDL_RenderPresent(game.renderer);
        SDL_Delay(30);
    }
}

void showSpravka(){
    while(isSpravkaRunning){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    isRunning = false;
                    isGameRunning = false;
                    isSpravkaRunning = false;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.scancode){
                        case SDL_SCANCODE_ESCAPE:
                            isRunning = false;
                            isGameRunning = false;
                            isSpravkaRunning = false;
                            break;
                        case SDL_SCANCODE_B:
                            isSpravkaRunning = false;
                        default:
                            break;
                    }
            }
        }
        SDL_RenderCopy(game.renderer, spravka, NULL, NULL);
        SDL_RenderPresent(game.renderer);
        SDL_Delay(30);
    }
}

bool compareTwoPlayers(Records a, Records b){
    if (a.score != b.score)
            return a.score > b.score;
    return 1;
}

void sortRecords(int n){
        sort(table, table + n, compareTwoPlayers);
}

void showRecords(){
    int i = 0;
    FILE* f = fopen("records.txt", "r");
    if (!f)
    {
        perror ("File error: ");
        system ("pause");
        game.deInit(1);
    }
    fgets(lastPlayer, 80, f);
    while(fscanf(f, "%s %d", table[i].nickname, &table[i].score) && i < 10){
        i++;
    }
    sortRecords(i);
    while(isRecordsRunning){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    isRunning = false;
                    isGameRunning = false;
                    isRecordsRunning = false;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.scancode){
                        case SDL_SCANCODE_ESCAPE:
                            isRunning = false;
                            isGameRunning = false;
                            isRecordsRunning = false;
                            break;
                        case SDL_SCANCODE_B:
                            isRecordsRunning = false;
                        default:
                            break;
                    }
            }
        }
        SDL_Rect nickRect; SDL_Rect scoreRect;
        SDL_Surface* nickSurf; SDL_Surface* scoreSurf;
        SDL_Texture* nickTex; SDL_Texture* scoreTex;
        char buffer[5];
        SDL_Color col = {245, 237, 237};
        SDL_RenderCopy(game.renderer, records, NULL, NULL);
        for(int i = 0; i < 10; i++){
            sprintf(buffer,"%d",table[i].score);
            if(table[i].score == 0){
                nickSurf = TTF_RenderText_Solid(font, "---", col);
                scoreSurf = TTF_RenderText_Solid(font, buffer, col);
                nickTex = SDL_CreateTextureFromSurface(game.renderer, nickSurf);
                nickRect = {100, 60*(i+1), 100, 50};
                scoreTex = SDL_CreateTextureFromSurface(game.renderer, scoreSurf);
                if(table[i].score > 1000){
                    scoreRect = {300, 60*(i+1), 100, 50};
                }else{
                    scoreRect = {300, 60*(i+1), 50, 50};
                }
            }else{
                nickSurf = TTF_RenderText_Solid(font, table[i].nickname, col);
                scoreSurf = TTF_RenderText_Solid(font, buffer, col);
                if(!nickSurf && !scoreSurf){
                    cout << "Failed to render text: " << TTF_GetError() << endl;
                    game.deInit(1);
                }
                nickTex = SDL_CreateTextureFromSurface(game.renderer, nickSurf);
                nickRect = {100, 60*(i+1), 100, 50};
                scoreTex = SDL_CreateTextureFromSurface(game.renderer, scoreSurf);
                if(table[i].score > 1000){
                    scoreRect = {300, 60*(i+1), 100, 50};
                }else{
                    scoreRect = {300, 60*(i+1), 50, 50};
                }
            }
            SDL_RenderCopy(game.renderer, nickTex, NULL, &nickRect);
            SDL_RenderCopy(game.renderer, scoreTex, NULL, &scoreRect);
        }
        SDL_RenderPresent(game.renderer);
        SDL_Delay(30);
    }
    
    fclose(f);
}

void showTotal(){
    isTotalRunning = true;
    while(isTotalRunning){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    isRunning = false;
                    isGameRunning = false;
                    isTotalRunning = false;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.scancode){
                        case SDL_SCANCODE_ESCAPE:
                            isRunning = false;
                            isGameRunning = false;
                            isTotalRunning = false;
                            break;
                        case SDL_SCANCODE_RETURN:
                            isTotalRunning = false;
                        default:
                            break;
                    }
            }
        }
        char buffer[5];
        sprintf(buffer, "%d", totalScore);
        SDL_Rect scoreRect;
        SDL_Surface* scoreSurf;
        SDL_Texture* scoreTex;
        SDL_Color col = {245, 237, 237};
        SDL_RenderCopy(game.renderer, total, NULL, NULL);
        scoreSurf = TTF_RenderText_Solid(font, buffer, col);
        if(!scoreSurf){
            cout << "Failed to render text: " << TTF_GetError() << endl;
            game.deInit(1);
        }
        scoreTex = SDL_CreateTextureFromSurface(game.renderer, scoreSurf);
        if(totalScore > 1000){
            scoreRect = {350, 260, 100, 50};
        }else{
            scoreRect = {350, 260, 50, 50};
        }
        SDL_RenderCopy(game.renderer, scoreTex, NULL, &scoreRect);
        SDL_RenderPresent(game.renderer);
        SDL_Delay(30);
    }
}

void updateRecords(){
    int i = 0;
    char g[15];
    FILE* fNew = fopen("recordsNew.txt", "w");
    if (!fNew){
        perror ("File error: ");
        system ("pause");
        game.deInit(1);
    }
    FILE* f = fopen("records.txt", "r");
    if (!f){
        perror ("File error: ");
        system ("pause");
        game.deInit(1);
    }
    fprintf(fNew, "%s\n", lastPlayer);
    fgets(g, 15, f);
    while(fscanf(f, "%s %d", table[i].nickname, &table[i].score) && i < 11){
        if(table[i].score != 0){
            fprintf(fNew, "%s %d\n", table[i].nickname, table[i].score);
        }
        i++;
    }
    if(totalScore != 0){
        fprintf(fNew, "%s %d\n", lastPlayer, totalScore);
    }
    fclose(f);
    fclose(fNew);
    remove("records.txt");
    rename("recordsNew.txt", "records.txt");
}

void showChangeName(){
    string in;
    int i = 0;
    int flag = 1;
    SDL_StartTextInput();
    while(isChangeNameRunning){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    isRunning = false;
                    isGameRunning = false;
                    isChangeNameRunning = false;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.scancode){
                        case SDL_SCANCODE_ESCAPE:
                            isRunning = false;
                            isGameRunning = false;
                            isChangeNameRunning = false;
                            break;
                        case SDL_SCANCODE_RETURN:
                            isChangeNameRunning = false;
                        default:
                            break;
                    }
            }
            if(event.type == SDL_TEXTINPUT && i < 10){
                in += event.text.text;
                if(flag){
                    in.pop_back();
                    flag = 0;
                    i--;
                }
                i++;
            }else if (i == 10){
                SDL_StopTextInput();
                break;
            }else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && in.size()){
                in.pop_back();
                i--;
            }
        }
        for (int i = 0; i < 10; i++) {
                lastPlayer[i] = in[i];
            }
        SDL_Rect nickRect;
        SDL_Surface* nickSurf;
        SDL_Texture* nickTex;
        SDL_Color col = {0, 0, 0};
        int k = sizeof(lastPlayer);
        nickSurf = TTF_RenderText_Solid(font, lastPlayer, col);
        nickTex = SDL_CreateTextureFromSurface(game.renderer, nickSurf);
        nickRect = {200, 200, 35*k, 40};
        SDL_RenderCopy(game.renderer, changeName, NULL, NULL);
        SDL_RenderCopy(game.renderer, nickTex, NULL, &nickRect);
        SDL_RenderPresent(game.renderer);
        SDL_Delay(30);
    }
    updateRecords();
}

void showPause(){
    isPauseRunning = true;
    while(isPauseRunning){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    isRunning = false;
                    isGameRunning = false;
                    isPauseRunning = false;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.scancode){
                        case SDL_SCANCODE_ESCAPE:
                            isRunning = false;
                            isGameRunning = false;
                            isPauseRunning = false;
                            break;
                        case SDL_SCANCODE_P:
                            isPauseRunning = false;
                            isGameRunning = true;
                        case SDL_SCANCODE_E:
                            isGameRunning = false;
                            isPauseRunning = false;
                            flag = 1;
                        default:
                            break;
                    }
            }
        }
        SDL_RenderCopy(game.renderer, pause, NULL, NULL);
        SDL_RenderPresent(game.renderer);
        SDL_Delay(30);
    }
}
