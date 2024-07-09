#include "Menu.h"
#include "../Core/Engine.h"
#include "../Inputs/Input.h"
#include "../Collision/CollisionHandler.h"
#include "../Timer/Timer.h"
#include <iostream>

Menu *Menu::instance = nullptr;

Menu *Menu::getInstance() {

    if (instance == nullptr)
        instance = new Menu();
    return instance;
}


void Menu::init(SDL_Renderer *renderer){
    this->renderer = renderer;
    position = 0;


    // background
    rect_bg = {0, 0, 1920, 1080};
    SDL_Surface *surface = IMG_Load("../assets/maps/menuBackground.jpg");
    background = SDL_CreateTextureFromSurface(this->renderer, surface);

    // title
    char tmp_text[60] = "NE TESTIRANJU NA ZIVALIH";
    title.init_center(renderer, SCREEN_HEIGHT / 2 - 140, 70, tmp_text);

    // izbira
    resumePlay();

    strcpy(tmp_text, "Navodila");
    options[1].init_center(renderer, SCREEN_HEIGHT / 2 + 100, 40, tmp_text);

    strcpy(tmp_text, "leaderboard");
    options[3].init_center(renderer, SCREEN_HEIGHT / 2 + 200, 40, tmp_text);


    strcpy(tmp_text, "Izhod");
    options[4].init_center(renderer, SCREEN_HEIGHT / 2 + 250, 40, tmp_text);

    // arrow
    rect_arrow = {SCREEN_WIDTH-850, SCREEN_HEIGHT / 2 + 50, 75, 50}; // y start on position 0
    char tmp[40] = "../assets/menu/arrow.png";

    // std::cout << tmp << std::endl;
    surface = IMG_Load(tmp);
    arrow = SDL_CreateTextureFromSurface(this->renderer, surface);
}

void Menu::draw(){
    SDL_RenderCopy(this->renderer, background, NULL, &rect_bg);
    title.draw();
    for (int i = 0; i < 5; i++)
        options[i].draw();
    SDL_RenderCopy(this->renderer, arrow, NULL, &rect_arrow);
}

void Menu::move_down(){
    if (position != 4){
        position++;
        rect_arrow.y += 50;
    }
    else{
        position = 0;
        rect_arrow.y = SCREEN_HEIGHT / 2 + 50;
    }
}

void Menu::move_up(){
    if (position != 0)
    {
        position--;
        rect_arrow.y -= 50;
    }
    else
    {
        position = 4;
        rect_arrow.y = SCREEN_HEIGHT / 2 + 250 - 5;
    }
}

int Menu::getPosition(){
    return position;
}

void Menu::change_title(char text[]){
    title.change_text_center(text);
}

void Menu::update() {
    delayCount++, delay++;
    if (delayCount == 60){
        delayCount = 0;
        moveArrow = true;
    }
    if (!moveArrow) return;

    if (Input::getInstance()->getKeyDown(SDL_SCANCODE_UP)) {
        move_up();
        moveArrow = false;
    }
    if (Input::getInstance()->getKeyDown(SDL_SCANCODE_DOWN)) {
        move_down();
        moveArrow = false;
    }
    if (Input::getInstance()->getKeyDown(SDL_SCANCODE_SPACE) && position == 0 && delay >= 300){
        if (!inGame) {
            std::cin>> x;
            CollisionHandler::getInstance()->mapLvl = 1;
            Engine::getInstance()->saved = false;
            Engine::getInstance()->loadLevel();
            CollisionHandler::getInstance()->updateTileMap();
            remove("replay.bin");
            ofstream replayData("Replay.txt");
            replayData << CollisionHandler::getInstance()->mapLvl;
            replayData.close();
        }
        inGame = true;
        displayGame = true;
        displayMenu = false;
    }

    if (Input::getInstance()->getKeyDown(SDL_SCANCODE_SPACE) && position == 1) {
        displayDirections = true;
        displayMenu = false;
    }
    if (Input::getInstance()->getKeyDown(SDL_SCANCODE_SPACE) && position == 2) {
        displayReplay = true;
        displayMenu = false;
    }

    if (Input::getInstance()->getKeyDown(SDL_SCANCODE_SPACE) && position == 2) {
        displayReplay = true;
        displayMenu = false;
    }

    if (Input::getInstance()->getKeyDown(SDL_SCANCODE_SPACE) && position == 3){
        displayMenu = false;
        displayLeaderboard = true;
    }


    if (Input::getInstance()->getKeyDown(SDL_SCANCODE_SPACE) && position == 4 && delay >= 100) {
        delay = 0;
        leave();
    }
}

void Menu::resumePlay(){
    char tmp_text[60];
    if (inGame) {
        strcpy(tmp_text, "Nadaljuj");
        options[0].init_center(renderer, SCREEN_HEIGHT / 2 + 50, 40, tmp_text);
        strcpy(tmp_text, "save");
        options[2].init_center(renderer, SCREEN_HEIGHT / 2 + 150, 40, tmp_text);
    }
    else{
        strcpy(tmp_text, "Nova igra");
        options[0].init_center(renderer, SCREEN_HEIGHT / 2 + 50, 40, tmp_text);
        strcpy(tmp_text, "load");
        options[2].init_center(renderer, SCREEN_HEIGHT / 2 + 150, 40, tmp_text);
    }
}

void Menu::leave() {
    if (inGame) {
        CollisionHandler::getInstance()->mapLvl = 1;
        inGame = false;
        displayMenu = true;
        displayGame = false;
        resumePlay();
    }
    else{
        Engine::getInstance()->clean();
        Engine::getInstance()->quit();
    }
}

void Menu::Leaderboard(){
    ifstream leaderboard("leaderboard.txt");

    if (!leaderboard.is_open()) {
        ofstream leaderboard2("temp.txt");
        leaderboard2 << x << " " << Timer::getInstance()->ingametime << endl;
        leaderboard2.close();
        rename ("temp.txt", "leaderboard.txt");
    }
    else {
            bool found = false;
            ofstream temp("temp.txt");
            int number;
            std::string name;
            while (leaderboard >> name >> number) {
                if (number > Timer::getInstance()->ingametime && !found) {
                    temp << x << " " << Timer::getInstance()->ingametime << endl;
                    found = true;
                }
                temp << name << " " << number << endl;
            }
            if (!found)
                temp << x << " " << Timer::getInstance()->ingametime << endl;
            temp.close();
            leaderboard.close();
            remove("leaderboard.txt");
            rename("temp.txt", "leaderboard.txt");
        }
    }
