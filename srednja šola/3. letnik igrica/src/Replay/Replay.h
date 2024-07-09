//
// Created by lukah on 25. 05. 2022.
//

#ifndef BLOJZGAME_REPLAY_H
#define BLOJZGAME_REPLAY_H


#include "../Characters/Warrior.h"
#include <SDL_render.h>
#include "../Maps/GameMap.h"
#include "../MainMenu/Text.h"

struct Position{
    float x, y;
};

class Replay {
private:
    static Replay *instance;
    Warrior *player;
    GameMap *levelMap;
    float safeX, safeY;
    SDL_Renderer *renderer;
    unsigned int readCount;
    Text replayText;
    int initialized;
    int lvl;
public:
    static Replay *getInstance();

    void saveMovement();
    void displayMovement();

    void initReplay(SDL_Renderer *sdlRenderer);

    void render();
    void update();
    void clean();

    void resetReadCount();
};

#endif //BLOJZGAME_REPLAY_H
