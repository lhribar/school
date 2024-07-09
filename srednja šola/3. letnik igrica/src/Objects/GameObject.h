

#ifndef BLOJZGAME_GAMEOBJECT_H
#define BLOJZGAME_GAMEOBJECT_H


#include "../Physics/Transform.h"
#include "../Physics/Point.h"
#include "SDL.h"

class Properties{
public:
    Properties(std::string textureID, float x, float y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE){
        this->x = x;
        this->y = y;
        this->flip = flip;
        this->width = width;
        this->height = height;
        this->textureID = textureID;
    }

    std::string textureID;
    int width, height;
    float x, y;
    SDL_RendererFlip flip;
};

class GameObject{
public:
    GameObject(Properties *properties): textureID(properties->textureID), width(properties->width), height(properties->height), flip(properties->flip){
        transform = new Transform(properties->x, properties->y);
        float px = properties->x + properties->width/2;
        float py = properties->y + properties->height/2;
        origin = new Point(px, py);
    }
    GameObject(){}

    Point *getOrigin() {return origin;}


    virtual void draw() = 0;
    virtual void update(float dt) = 0;
    virtual void clean() = 0;

    Transform* transform;

protected:
    Point *origin;
    int width, height;
    std::string textureID;
    SDL_RendererFlip flip;
};


#endif //BLOJZGAME_GAMEOBJECT_H
