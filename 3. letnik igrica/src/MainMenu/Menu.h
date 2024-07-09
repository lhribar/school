#ifndef BLOJZGAME_MENU_H
#define BLOJZGAME_MENU_H

#pragma once

#include <SDL2/SDL.h>
#include "Text.h"
#include <cstring>
#include <iostream>

class Menu{
private:
    std::string x;
    SDL_Renderer *renderer;
    static Menu *instance;
    SDL_Texture *background, *arrow;
    SDL_Rect rect_bg, rect_arrow;
    SDL_Surface *surface;

    Text title, options[5];
    int position;
    bool moveArrow;
    float delayCount = 0;

public:
    bool displayLeaderboard = false;
    float delay = 0;
    bool gameOver = false;
    bool displayReplay = false;
    bool displayGame = false;
    bool displayMenu = true;
    bool inGame = false;
    bool saveLoad = true;
    bool displayDirections = false;


    static Menu *getInstance();
    void init(SDL_Renderer *renderer);
    void draw();
    void update();
    void move_down();
    void move_up();
    int getPosition();
    void change_title(char text[]);
    void resumePlay();
    void leave();
    void Leaderboard();
};

#endif //BLOJZGAME_MENU_H