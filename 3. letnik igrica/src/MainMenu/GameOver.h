//
// Created by lukah on 1. 05. 2022.
//

#ifndef BLOJZGAME_GAMEOVER_H
#define BLOJZGAME_GAMEOVER_H


#pragma once

#include <fstream>
#include <iostream>

#include <SDL2/SDL.h>
#include "Text.h"

class GameOver
{
private:
    SDL_Renderer *renderer;
    static GameOver *instance;
    Text title, options[5];
    SDL_Texture *background, *arrow;
    SDL_Rect rect_bg, rect_arrow;
    int position;
    bool moveArrow;
    float delay = 100, delayCount = 0;


public:
    int stevec = 0;
    static GameOver *getInstance();
    void update();
    bool displayMenu = false;
    bool displayReplay = false;
    void init(SDL_Renderer *renderer);
    void draw();
    int getPosition();

    void moveDown();
    void moveUp();
};

#endif //BLOJZGAME_GAMEOVER_H
