

#ifndef BLOJZGAME_ENGINE_H
#define BLOJZGAME_ENGINE_H

#include "SDL.h"
#include "SDL_image.h"
#include "../Maps/GameMap.h"
#include "../Objects/GameObject.h"
#include "../Characters/Enemy.h"
#include "../Characters/Animal.h"
#include "../Characters/Warrior.h"
#include "../Characters/boss.h"

#include "fstream"
#include "../MainMenu/Text.h"

using namespace std;


#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1030

class Engine {
private:
    //int maplevel = 1;
    float fullscreenDelay = 0;
    bool fullscreen = false;
    int stevec = 0;
    ofstream data;
    bool running;
    GameMap* levelMap;
    SDL_Window* window;
    SDL_Renderer* renderer;
    static Engine* instance;
    Text title;
    Warrior *warrior;
    std::vector<Boss*> boss;
    std::vector<Enemy*> enemy;
    std::vector<Animal*> animal;
    SDL_Rect rect_bg;
    SDL_Texture *background;
    SDL_Rect a;

    float delayTime = 100, leaveDelay = 0, saveLoadDelay = 200, loadTime = 0;
    int animalsSaved = 0;
    bool canBeHit;


public:
    bool saved;
    static Engine* getInstance();
    GameMap *getGameMap() {return levelMap;}

    bool init();
    void clean();
    void quit();
    void update();
    void render();
    void events();
    void loadLevel();

    void loadSave(int Time);
    void loadWarrior(int life, float x, float y);
    void loadAnimal(char texture_id[], float x, float y);
    int warriorLife();
    float warriorOriginX();
    float warriorOriginY();
    vector<Animal*> getAnimals();

    void setRemainingAnimals(int animals);
    int remainingAnimals();



    inline bool isRunning() const{return running;}
    inline SDL_Renderer* getRenderer() const{return renderer;}
};


#endif //BLOJZGAME_ENGINE_H
