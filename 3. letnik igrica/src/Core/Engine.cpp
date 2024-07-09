

#include "Engine.h"
#include <iostream>
#include "SDL.h"
#include "../Graphics/TextureManager.h"
#include <SDL_image.h>
#include "../Characters/Warrior.h"
#include "../Inputs/Input.h"
#include "../Timer/Timer.h"
#include "../Maps/MapParser.h"
#include "../Cameras/Camera.h"
#include "../Characters/Enemy.h"
#include "../Characters/Animal.h"
#include <fstream>
#include "../Collision/CollisionHandler.h"
#include "../MainMenu/Menu.h"
#include "../MainMenu/Text.h"
#include "../MainMenu/GameOver.h"
#include <vector>
#include <cmath>
#include <cstring>
#include "../Characters/boss.h"
#include "../SaveAndLoad/saveAndLoad.h"
#include "../Replay/Replay.h"

using namespace std;


Engine* Engine::instance = nullptr;

Engine *Engine::getInstance() {
    if (instance == nullptr) instance = new Engine;
    return instance;
}

bool Engine::init(){
    if (TTF_Init() == -1){
        SDL_Log("Could not initialize SDL2 ttf, error: %s", TTF_GetError());
        return false;
    }

    //data.open("replay.bin", ios::binary);

    if (SDL_Init(SDL_INIT_VIDEO)!=0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)!= 0){
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    SDL_WindowFlags flags = (SDL_WindowFlags) (SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    window = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, flags);
    if(window == nullptr){
        SDL_Log("Failed to create Window: %s", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr){
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }
    if (!MapParser::getInstance()->load()){

        SDL_Log("failed to load map: %s", SDL_GetError());
        return false;
    }

    levelMap = MapParser::getInstance()->getMaps("MAP1");
    TextureManager::getInstance()->parseTextures("../assets/textures.tml");

    Menu::getInstance()->init(renderer);


    Replay::getInstance()->initReplay(renderer);

    running = true;
    return running;


}

void Engine::update() {

    Timer::getInstance()->ingametime = (SDL_GetTicks() / 1000) + loadTime;
    fullscreenDelay++;
    if (Input::getInstance()->getKeyDown(SDL_SCANCODE_F3) && fullscreenDelay > 100){
        if (!fullscreen){
            SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
            fullscreen = true;
        } else {
            SDL_SetWindowFullscreen(window, 0);
            fullscreen = false;
        }
        fullscreenDelay = 0;
    }

    if (Menu::getInstance()->displayMenu) {
        Menu::getInstance()->update();
    }
    else if (GameOver::getInstance()->displayMenu) {

        GameOver::getInstance()->update();
    }

    else if (GameOver::getInstance()->displayReplay){
        if (Input::getInstance()->getKeyDown(SDL_SCANCODE_ESCAPE)) {
            GameOver::getInstance()->displayMenu = true;
            GameOver::getInstance()->displayReplay = false;
        }
        //SDL_Log("%i", GameOver::getInstance()->stevec);

        Replay::getInstance()->update();
    }

    else if (Menu::getInstance()->displayDirections) {
        if (Input::getInstance()->getKeyDown(SDL_SCANCODE_ESCAPE)) {
            Menu::getInstance()->displayMenu = true;
            Menu::getInstance()->displayDirections = false;
        }
    } else if (Menu::getInstance()->displayReplay) {
        if (Input::getInstance()->getKeyDown(SDL_SCANCODE_ESCAPE)) {
            Menu::getInstance()->displayReplay = false;
            Menu::getInstance()->displayMenu = true;
        }
    }
    else if (Menu::getInstance()->displayLeaderboard) {
        if (Input::getInstance()->getKeyDown(SDL_SCANCODE_ESCAPE)) {
            Menu::getInstance()->displayLeaderboard = false;
            Menu::getInstance()->displayMenu = true;
        }
    }

    if (!Menu::getInstance()->displayMenu && Menu::getInstance()->inGame) {

        if (Input::getInstance()->getKeyDown(SDL_SCANCODE_ESCAPE)) {
            leaveDelay++;

            Menu::getInstance()->displayMenu = true;
            Menu::getInstance()->displayGame = false;

            Menu::getInstance()->resumePlay();

            if ((Input::getInstance()->getKeyDown(SDL_SCANCODE_SPACE)) && (Menu::getInstance()->getPosition() == 4) &&
                (leaveDelay >= 100)) {
                leaveDelay = 0;
                Menu::getInstance()->leave();
            }
        }

        //SDL_Log("%f %f",warrior->getOrigin()->x, warrior->getOrigin()->y);

        float dt = Timer::getInstance()->getDeltaTime();
        for (int i = 0; i != enemy.size(); i++)
            enemy[i]->update(dt);
        warrior->update(dt);
        for (int i = 0; i != animal.size(); i++)
            animal[i]->update(dt);
        Camera::getInstance()->update(dt);

        for (int i = 0; i != boss.size(); i++)
            boss[i]->update(dt);

        levelMap->update();

        SDL_Rect warriorRect = warrior->hitBox();
        if (delayTime >= 100)
            canBeHit = true;
        else {
            canBeHit = false;
            delayTime++;
        }
        for (int i = 0; i < enemy.size() && canBeHit; i++) {
            SDL_Rect enemyRect = enemy[i]->hitBox();
            if (SDL_HasIntersection(&warriorRect, &enemyRect)) {
                warrior->IsHurt(true);
                warrior->lives--;
                delayTime = 0;
            }
        }
        for (int i = 0; i < boss.size(); i++) {
            if (warrior->getOrigin()->x < boss[i]->getOrigin()->x)
                boss[i]->transform->x--;

            else
                boss[i]->transform->x++;


            if (warrior->getOrigin()->y < boss[0]->getOrigin()->y)
                boss[i]->transform->y -= 0.3;
            else
                boss[i]->transform->y += 0.3;
        }

        for (int i = 0; i < boss.size()  && canBeHit; i++) {
            SDL_Rect bossRect = boss[i]->hitBox();
            if (SDL_HasIntersection(&warriorRect, &bossRect)) {
                warrior->IsHurt(true);
                warrior->lives--;
                delayTime = 0;
            }
        }

        for (int i = 0; i < animal.size(); i++) {
            SDL_Rect animalRect = animal[i]->hitBox();
            if (SDL_HasIntersection(&warriorRect, &animalRect)) {
                animal[i]->clean();
                delete (animal[i]);
                animal.erase(animal.begin() + i);
                animalsSaved++;
            }
        }

        if (warrior->lives == 0) {
            Menu::getInstance()->leave();
        }

        if (CollisionHandler::getInstance()->mapLvl == 1) {
            Replay::getInstance()->saveMovement();
            if (animalsSaved == 1) {

                animalsSaved = 0;
                saved = false;
                CollisionHandler::getInstance()->mapLvl = 2;
                loadLevel();
                CollisionHandler::getInstance()->updateTileMap();

                ofstream replayData("Replay.txt");
                replayData << CollisionHandler::getInstance()->mapLvl;
                replayData.close();
                remove("Replay.bin");
            }
        } else if (CollisionHandler::getInstance()->mapLvl == 2) {
            Replay::getInstance()->saveMovement();
            if (animalsSaved == 3) {
                Menu::getInstance()->inGame = false;
                GameOver::getInstance()->displayMenu = true;
                GameOver::getInstance()->init(renderer);
                Menu::getInstance()->Leaderboard();
            }
        }
    }

}

void Engine::events() {
    Input::getInstance()->listen();
}

void Engine::render() {
    SDL_SetRenderDrawColor(renderer, 124, 210, 254, 255);
    SDL_RenderClear(renderer);
    if (!Menu::getInstance()->displayDirections) {

        if (Menu::getInstance()->displayMenu)
            Menu::getInstance()->draw();

        else if (Menu::getInstance()->displayLeaderboard) {
            string x;
            ifstream Leaderboard("leaderboard.txt");

            int count = 0;
            if (!Leaderboard.is_open())
                return;
            int y = 0;
            while (getline(Leaderboard, x)){
                y += 50;
                title.init_center(renderer, SCREEN_HEIGHT / 2 - 220 + y, 35, const_cast<char*>(x.c_str()));
                title.draw();
                count++;
                if (count == 10)
                    break;
            }
        }

        else if (GameOver::getInstance()->displayMenu)
            GameOver::getInstance()->draw();

        else if (GameOver::getInstance()->displayReplay){

            Replay::getInstance()->render();
        }

        else if (Menu::getInstance()->displayReplay) {
            saveLoadDelay++;
            if (Menu::getInstance()->inGame) {
                saved = true;
                rect_bg = {0, 0, 1920, 1030};
                SDL_Surface *surface = IMG_Load("../assets/maps/characterResting.jpg");
                background = SDL_CreateTextureFromSurface(this->renderer, surface);
                SDL_RenderCopy(this->renderer, background, NULL, &rect_bg);

                if (saveLoadDelay >= 100) {
                    SDL_Log("%i", CollisionHandler::getInstance()->mapLvl);
                    saveLoadDelay = 0;

                    Save::getInstance()->saveGameplay();
                }
            } else if (!Menu::getInstance()->inGame && saved) {
                Menu::getInstance()->inGame = true;
                Menu::getInstance()->displayGame = true;
                Menu::getInstance()->displayMenu = false;
                Menu::getInstance()->displayReplay = false;

                //loadSave();
                Save::getInstance()->loadGameplay();

                Camera::getInstance()->setTarget(warrior->getOrigin());
            }

        } else{

            if (CollisionHandler::getInstance()->mapLvl == 1) {
                TextureManager::getInstance()->drawTexture("background1", 0, 0, 3200, 1920, 1, 1, 1);
                levelMap->render();
            } else if (CollisionHandler::getInstance()->mapLvl == 2) {
                TextureManager::getInstance()->drawTexture("background2", 0, 0, 4160, 3200, 1, 1, 1);
                levelMap->render();
            }
            warrior->draw();

            for (int i = 0; i != boss.size(); i++)
                boss[i]->draw();

            for (int i = 0; i != enemy.size(); i++)
                enemy[i]->draw();

            for (int i = 0; i != animal.size(); i++)
                if (((abs(warrior->getOrigin()->x - animal[i]->getOrigin()->x)) < 200) && (abs(warrior->getOrigin()->y - animal[i]->getOrigin()->y)) < 200)
                    animal[i]->draw();

            char tmp_text[30] = "LIVES";
            title.init(renderer, 1800, 0, tmp_text);
            title.draw();

            string tmp_lives = to_string(warrior->lives);
            title.init(renderer, 1750, 0, tmp_lives.c_str());
        }
    }

        else {
            char tmp_text[200] = "Cilj igre je resiti cimvec zivali in uniciti barabe oz. poiskati vse skrite sledi na posamezni stopnji in resiti zivali";
            title.init_center(renderer, SCREEN_HEIGHT / 2 - 140, 35, tmp_text);
            title.draw();
            char tmp_temp[150] = "ce zazenes igro na zacetku in se ne pokaze nic, moras v console vpisati ime";
            title.init_center(renderer, SCREEN_HEIGHT / 2 - 220, 35, tmp_temp);
            title.draw();
        }

    SDL_RenderPresent(renderer);
}

void Engine::clean(){

    for (auto& e : enemy) {
        e->clean();
        delete e;
    }
    enemy.clear();

    for (auto& b : boss) {
        b->clean();
        delete b;
    }
    boss.clear();

    for (auto& a : animal) {
        a->clean();
        delete a;
    }
    animal.clear();

    if (warrior) {
        warrior->clean();
        delete warrior;
        warrior = nullptr;
    }

    TextureManager::getInstance()->cleanTexture();
    MapParser::getInstance()->clean();

    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
    if (instance) {
        delete instance;
        instance = nullptr;
    }
}

void Engine::quit(){

    data.close();
    running = false;
}

void Engine::loadLevel() {

    enemy.clear();
    animal.clear();
    boss.clear();


    if (CollisionHandler::getInstance()->mapLvl == 1) {
        levelMap = MapParser::getInstance()->getMaps("MAP1");
        TextureManager::getInstance()->parseTextures("../assets/textures.tml");
        warrior = new Warrior(new Properties("player_idle", 50, 1000, 50, 50));
        boss.push_back(new Boss(new Properties("boss_idle", 500, 1200, 50, 50)));

        enemy.push_back(new Enemy(new Properties("enemy_idle", 800, 900, 48, 48)));
        enemy.push_back(new Enemy(new Properties("enemy_idle", 1500, 800, 48, 48)));
        if (!saved)
            animal.push_back(new Animal(new Properties("dog1_idle", 2000, 500, 48, 48)));
        //animal.push_back(new Animal(new Properties("dog1_idle", rand()%(500-0)+0, rand()%(500-0)+0, 48, 48))); RANDOM SPAWN
    }

    if (CollisionHandler::getInstance()->mapLvl == 2){
        CollisionHandler::getInstance()->updateTileMap();
        levelMap = MapParser::getInstance()->getMaps("MAP2");
        TextureManager::getInstance()->parseTextures("../assets/textures.tml");
        warrior = new Warrior(new Properties("player_idle", 50, 2500, 50, 50));

        enemy.push_back(new Enemy(new Properties("enemy_idle", 468, 1500, 48, 48)));
        enemy.push_back(new Enemy(new Properties("enemy_idle", 792, 1500, 48, 48)));
        enemy.push_back(new Enemy(new Properties("enemy_idle", 1150, 1500, 48, 48)));
        enemy.push_back(new Enemy(new Properties("enemy_idle", 2250, 2000, 48, 48)));
        enemy.push_back(new Enemy(new Properties("enemy_idle", 2550, 2200, 48, 48)));
        enemy.push_back(new Enemy(new Properties("enemy_idle", 1620, 1200, 48, 48)));
        enemy.push_back(new Enemy(new Properties("enemy_idle", 1050, 1900, 48, 48)));
        enemy.push_back(new Enemy(new Properties("enemy_idle", 2150, 400, 48, 48)));
        enemy.push_back(new Enemy(new Properties("enemy_idle", 90, 1250, 48, 48)));
        enemy.push_back(new Enemy(new Properties("enemy_idle", 1090, 700, 48, 48)));
        enemy.push_back(new Enemy(new Properties("enemy_idle", 90, 700, 48, 48)));
        enemy.push_back(new Enemy(new Properties("enemy_idle", 450, 120, 48, 48)));
        enemy.push_back(new Enemy(new Properties("enemy_idle", 625, 120, 48, 48)));
        enemy.push_back(new Enemy(new Properties("enemy_idle", 800, 120, 48, 48)));
        enemy.push_back(new Enemy(new Properties("enemy_idle", 975, 120, 48, 48)));
        if (!saved){
            animal.push_back(new Animal(new Properties("dog1_idle", 1356, 1600, 48, 48)));
            animal.push_back(new Animal(new Properties("dog2_idle", 3055, 2400, 48, 48)));
            animal.push_back(new Animal(new Properties("cat1_idle", 2935, 450, 48, 48)));
            animal.push_back(new Animal(new Properties("cat2_idle", 1087, 120, 48, 48)));
            animal.push_back(new Animal(new Properties("bird1_idle", 100, 1930, 32, 32)));
        }
    }

    warrior->lives = 5;

    Camera::getInstance()->setTarget(warrior->getOrigin());
}

void Engine::loadSave(int Time) {
    loadTime = Time;
}

void Engine::loadWarrior(int life, float x, float y){
    warrior->lives = life;
    warrior->transform->x = x;
    warrior->transform->y = y;
}

void Engine::loadAnimal(char texture_id[], float x, float y){
    animal.push_back(new Animal(new Properties(texture_id, x, y, 48, 48)));
}

int Engine::warriorLife() {
    return warrior->lives;
}

float Engine::warriorOriginX() {
    return warrior->getOrigin()->x;
}

float Engine::warriorOriginY() {
    return warrior->getOrigin()->y;
}

vector<Animal*> Engine::getAnimals(){
    return animal;
}


void Engine::setRemainingAnimals(int animals){
    animalsSaved = animals;
}

int Engine::remainingAnimals(){
    return animalsSaved;
}
