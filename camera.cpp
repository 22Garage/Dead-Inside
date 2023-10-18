#include <stdio.h>
#include "player.hpp"


Camera::Camera(){
    cameraRect.x = xPlayer - windowWidth/2;
    cameraRect.y = yPlayer - windowHeight/2;
    cameraRect.w = windowWidth;
    cameraRect.h = windowHeight;
    dstBonfireRect = {0, 0, 0, 0};
}
Camera::~Camera(){
} // удаляем текстуру фона

void Camera::countCoords(GameProcess& g, Player& p){
    cameraRect.x = p.xPlayer - windowWidth/2;
    cameraRect.y = p.yPlayer - windowHeight/2;
    checkCameraBoards(g);
    countDstCameraRect(g, p);
} // считаем координаты

void Camera::checkCameraBoards(GameProcess& g){
    if(cameraRect.x < 0){
        cameraRect.x = 0;
    }
    if(cameraRect.y < 0){
        cameraRect.y = 0;
    }
    if(cameraRect.x + cameraRect.w > g.gameWidth){
        cameraRect.x = g.gameWidth - cameraRect.w;
    }
    if(cameraRect.y + cameraRect.h > g.gameHeight){
        cameraRect.y = g.gameHeight - cameraRect.h;
    }
} // проверка на границы

void Camera::countDstCameraRect(GameProcess& g, Player& p){
    dstCameraRect = {p.dstPlayerRect.x - cameraRect.x - g.windowWidth/16, p.dstPlayerRect.y - cameraRect.y - g.windowHeight/20, p.dstPlayerRect.w, p.dstPlayerRect.h};
} // cчитаем позицию камеры к игроку

void Camera::countDstBonfireRect(Bonfire& b){
    dstBonfireRect = {b.xBonfire - cameraRect.x, b.yBonfire - cameraRect.y, 200, 300};
}
