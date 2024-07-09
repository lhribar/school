

#ifndef BLOJZGAME_COLLISIONHANDLER_H
#define BLOJZGAME_COLLISIONHANDLER_H

#include "../Maps/TileLayer.h"
#include "../Maps/GameMap.h"
#include "../Core/Engine.h"
#include <SDL.h>
#include <vector>

class CollisionHandler {
private:
    CollisionHandler();
    static CollisionHandler *instance;


    TileMap collisionTileMap;
    TileLayer *collisionLayer;
public:
    int mapLvl = 1;
    static  CollisionHandler *getInstance();
    void updateTileMap();

    bool checkCollision(SDL_Rect a, SDL_Rect b);
    bool mapCollision(SDL_Rect a);
    int getColCount();
    int getRowCount();

};


#endif //BLOJZGAME_COLLISIONHANDLER_H
