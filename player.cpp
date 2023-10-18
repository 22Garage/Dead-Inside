#include "player.hpp"

Player::Player(){
    xPlayer = 750;
    yPlayer = 600;
    trees = 0;
    canCut = false;
    playerRect = {0, 0, 50, 50};
    dstPlayerRect = {0, 0, 50, 50};
    playerTex = NULL;
}

Player::~Player(){

}

void Player::countDstPlayerRect(GameProcess& g){
    dstPlayerRect = {xPlayer, yPlayer, g.windowWidth/8, g.windowWidth/8};
} // считаем позицию на экране

//void Player::move(){
//    if(!isUpPressed && !isDownPressed && !isLeftPressed && !isRightPressed && !isSpacePressed){
//        playerTex = stand[frame];
//    }
//    if(isUpPressed && !isDownPressed && !isLeftPressed && !isRightPressed){
//        yPlayer -= 10;
//        checkPlayerBoards();
//        playerTex = upRun[frame];
//    }else if(isUpPressed && !isDownPressed){
//        yPlayer -= 10;
//        checkPlayerBoards();
//    }
//    if(isDownPressed && !isUpPressed && !isLeftPressed && !isRightPressed){
//        yPlayer += 10;
//        checkPlayerBoards();
//        playerTex = downRun[frame];
//    }else if(isDownPressed && !isUpPressed){
//        yPlayer += 10;
//        checkPlayerBoards();
//    }
//    if(isLeftPressed && !isRightPressed){
//        printf("left\n");
//        xPlayer -= 10;
//        checkPlayerBoards();
//        playerTex = leftRun[frame];
//    }
//    if(isRightPressed && !isLeftPressed){
//        xPlayer += 10;
//        checkPlayerBoards();
//        playerTex = rightRun[frame];
//    }
//    if(isSpacePressed){
//        playerTex = punch[0];
//    }
//} // движение

void Player::checkPlayerBoards(GameProcess& g){
    if(g.windowWidth == 800 && g.windowHeight == 600){
        if(xPlayer > g.gameWidth-20){
            xPlayer = g.gameWidth-20;
        }
        if(yPlayer > g.gameHeight-45){
            yPlayer = g.gameHeight-45;
        }
        if(xPlayer < 5){
            xPlayer = 6;
        }
        if(yPlayer < 5){
            yPlayer = 6;
        }
    }else{
        if(xPlayer > g.gameWidth+600){
            xPlayer = g.gameWidth+600;
        }
        if(yPlayer > g.gameHeight+200){
            yPlayer = g.gameHeight+200;
        }
        if(xPlayer < 0){
            xPlayer = 0;
        }
        if(yPlayer < 0){
            yPlayer = 0;
        }
    }
    if((xPlayer > 670 && yPlayer > 480) && (xPlayer <= 830 && yPlayer < 600)){
        if(xPlayer > 800 && yPlayer >= 480 && yPlayer <= 570){
            xPlayer = 830;
        }else if(xPlayer < 700 && yPlayer > 480 && yPlayer < 570){
            xPlayer = 670;
        }else if(yPlayer < 500 && xPlayer >= 670 && xPlayer <= 830){
            yPlayer = 480;
        }else if(yPlayer > 500 && xPlayer > 670 && xPlayer < 830){
            yPlayer = 600;
        }
    }
} // проверка на границы

void Player::plusTrees(){
    trees++;
    if(trees > 3){
        trees = 3;
    }
}

void Player::checkCanAdd(){
//    double h = hypot((xPlayer - 650), (yPlayer - 350));
//    if(h < 200){
//        canAdd = true;
//        printf("%d %d\n", xPlayer, yPlayer);
//    }
    if(xPlayer >= 600 && xPlayer <= 900 && yPlayer >= 400 && yPlayer <= 650){
        canAdd = true;
    }else{
        canAdd = false;
    }
}
