
// Created by lukah on 1. 05. 2022.
//


#include "GameOver.h"
#include "../Core/Engine.h"
#include "../Inputs/Input.h"
#include "../MainMenu/Menu.h"
#include "../Collision/CollisionHandler.h"
#include "../Replay/Replay.h"

GameOver *GameOver::instance = nullptr;

GameOver *GameOver::getInstance() {

    if (instance == nullptr)
        instance = new GameOver();
    return instance;
}

void GameOver::init(SDL_Renderer *renderer)
{
    this->renderer = renderer;

    rect_bg = {0, 0, 1920, 1030};
    SDL_Surface *surface = IMG_Load("../assets/menu/victory.webp");
    background = SDL_CreateTextureFromSurface(this->renderer, surface);

    // title
    char tmp_text[60];

    // izbira
    strcpy(tmp_text, "izhod");
    options[0].init_center(renderer, SCREEN_HEIGHT / 2 + 50, 40, tmp_text);

    strcpy(tmp_text, "Replay");
    options[1].init_center(renderer, SCREEN_HEIGHT / 2 + 100, 40, tmp_text);

    rect_arrow = {SCREEN_WIDTH-850, SCREEN_HEIGHT / 2 + 50, 75, 50}; // y start on position 0
    char tmp[40] = "../assets/menu/arrow.png";

    surface = IMG_Load(tmp);
    arrow = SDL_CreateTextureFromSurface(this->renderer, surface);

}

void GameOver::draw(){
    SDL_RenderCopy(this->renderer, background, NULL, &rect_bg);
    title.draw();
    for (int i = 0; i < 2; i++)
        options[i].draw();
    SDL_RenderCopy(this->renderer, arrow, NULL, &rect_arrow);
}


void GameOver::moveDown(){
    if (position != 1){
        position++;
        rect_arrow.y += 50;
    }
    else{
        position = 0;
        rect_arrow.y = SCREEN_HEIGHT / 2 + 50 - 5;
    }
}

void GameOver::moveUp(){
    if (position != 0)
    {
        position--;
        rect_arrow.y -= 50;
    }
    else
    {
        position = 1;
        rect_arrow.y = SCREEN_HEIGHT / 2 + 100;
    }
}

int GameOver::getPosition(){
    return position;
}

void GameOver::update() {

    delayCount++, delay++;
    if (delayCount == 60) {
        delayCount = 0;
        moveArrow = true;
    }
    if (!moveArrow) return;

    if (Input::getInstance()->getKeyDown(SDL_SCANCODE_UP)) {
        moveUp();
        moveArrow = false;
    }
    if (Input::getInstance()->getKeyDown(SDL_SCANCODE_DOWN)) {
        moveDown();
        moveArrow = false;
    }

    if ((Input::getInstance()->getKeyDown(SDL_SCANCODE_SPACE)) && (position == 0) && (delay >= 300)) {
        delay = 0;
        Menu::getInstance()->delay = 0;

        Menu::getInstance()->inGame = false;
        GameOver::displayMenu = false;
        Menu::getInstance()->displayGame = false;
        Menu::getInstance()->displayMenu = true;

    }
    if (Input::getInstance()->getKeyDown(SDL_SCANCODE_SPACE) && (position == 1) && (delay >= 300)){
        delay = 0;
        displayMenu = false;
        stevec = 1;
        displayReplay = true;
        Replay::getInstance()->resetReadCount();
        Replay::getInstance()->displayMovement();
    }
}
