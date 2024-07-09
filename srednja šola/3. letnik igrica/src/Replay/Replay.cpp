//
// Created by lukah on 25. 05. 2022.
//

#include <fstream>
#include "Replay.h"
#include "../Maps/MapParser.h"
#include "../Graphics/TextureManager.h"
#include "../MainMenu/Menu.h"
#include <fstream>
#include "../Core/Engine.h"
#include "../MainMenu/Text.h"
#include "../Timer/Timer.h"
#include "../Collision/CollisionHandler.h"
#include "../Cameras/Camera.h"
#include "../Characters/Warrior.h"

using namespace std;

Replay *Replay::instance = nullptr;

Replay *Replay::getInstance() {
    if (instance == nullptr)
        instance = new Replay;
    return instance;
}

void Replay::saveMovement(){
    ofstream data("replay.bin", ios::app | ios::binary);
    Position position = Position();
    position.x = Engine::getInstance()->warriorOriginX();
    position.y = Engine::getInstance()->warriorOriginY();
    data.write((char *) &position, sizeof(position));
    data.close();
}

void Replay::displayMovement(){

    ifstream data("replay.bin", ios::binary);
    if (!data.is_open()){
        return;
    }

    data.seekg(sizeof(Position) * readCount, ios::beg);
    struct Position position = Position();

    data.read((char *) &position, sizeof (position));
    readCount++;

   // position.y -= 10;

    player->transform->x = position.x - 25;
    player->transform->y = position.y - 25;

    //player->collider->set(position.x - 25, position.y - 25, 96, 96);
    player->getOrigin()->x = position.x - 25;
    player->getOrigin()->y = position.y - 25;

    data.seekg(sizeof(Position) * readCount, ios::beg);
    data.read((char *) &position, sizeof (position));

    if (position.x != 0 && position.y != -10.0) {
        safeX = position.x;
        safeY = position.y;

    } else {

        player->transform->x = safeX - 25;
        player->transform->y = safeY - 25;
        player->collider->set(safeX, safeY, 96, 96);
        player->getOrigin()->x = safeX + 25;
        player->getOrigin()->y = safeY + 25;
    }

    data.close();

}

void Replay::initReplay(SDL_Renderer *sdlRenderer){
    readCount = 0;

    player = new Warrior(new Properties("player_idle", 50, 2500, 50, 50));

    MapParser::getInstance()->load();


    std::ifstream data("Replay.txt");
    data >> lvl;
    data.close();

    levelMap = MapParser::getInstance()->getMaps("MAP2");



    //CollisionHandler::getInstance()->setCollisionMap(collisionLayer->getTileMap(), tileSize);

    TextureManager::getInstance()->parseTextures("../assets/textures.tml");
}


void Replay::render(){

    TextureManager::getInstance()->drawTexture("background2", 0, 0, 4160, 3200, 1, 1, 1);
    levelMap->render();
    player->draw();
}

void Replay::update(){
    //Menu::getInstance()->checkMenu(renderer);
    float dt = Timer::getInstance()->getDeltaTime();
    displayMovement();
    player->animationState();
    Camera::getInstance()->setTarget(player->getOrigin());
    Camera::getInstance()->update(dt);
    levelMap->update();
}

void Replay::clean(){
    delete player;
    delete levelMap;
}

void Replay::resetReadCount(){
    readCount = 0;
}
