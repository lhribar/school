

#include "CollisionHandler.h"
#include "../Core/Engine.h"

CollisionHandler *CollisionHandler::instance = nullptr;

CollisionHandler::CollisionHandler() {
    collisionLayer = (TileLayer*) Engine::getInstance()->getGameMap()->getMapLayers().front();
    collisionTileMap = collisionLayer->getTileMap();
}

CollisionHandler *CollisionHandler::getInstance() {

    if (instance == nullptr)
        instance = new CollisionHandler();
    return instance;
}

void CollisionHandler::updateTileMap() {
    collisionLayer = (TileLayer*) Engine::getInstance()->getGameMap()->getMapLayers().front();
    collisionTileMap = collisionLayer->getTileMap();
}

bool CollisionHandler::checkCollision(SDL_Rect a, SDL_Rect b) {
    bool overLapX = (a.x < b.x + b.w) && (a.x + a.w > b.x);
    bool overLapY = (a.y < b.y + b.h) && (a.y + a.h > b.y);

    return (overLapX && overLapY);
}


bool CollisionHandler::mapCollision(SDL_Rect a) {
    int tileSize = 32,  rowCount = 100, colCount = 130;
    /*if (mapLvl == 1) {
        rowCount = 60;
        colCount = 100;
    }
    else if (mapLvl == 2){
        rowCount = 100;
        colCount = 130;
    }*/


    int leftTile = a.x/tileSize;
    int rightTile = (a.x + a.w)/tileSize;

    int topTile = a.y / tileSize;
    int bottomTile = (a.y + a.h) / tileSize;

    if (leftTile < 0) leftTile = 0;
    if (rightTile > colCount) rightTile = colCount;

    if (topTile < 0) topTile = 0;
    if (bottomTile > rowCount) bottomTile = rowCount;

    for(int i = leftTile; i <= rightTile; ++i){
        for(int j = topTile; j <= bottomTile; j++){
            if (collisionTileMap[j][i] > 0) return true;
        }
    }
    return false;
}
