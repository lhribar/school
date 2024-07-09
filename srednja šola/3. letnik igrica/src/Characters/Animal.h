//
// Created by lukah on 1. 04. 2022.
//

#ifndef BLOJZGAME_ANIMAL_H
#define BLOJZGAME_ANIMAL_H

#include "Character.h"
#include "../Animations/SpriteAnimation.h"
#include "../Physics/RigidBody.h"
#include "../Physics/Collider.h"
#include "../Physics/Vector2D.h"

class Animal: public Character{
private:
    SpriteAnimation *animation;
    RigidBody *rigidBody;
    Collider *collider;
    Vector2D lastSafePosition;

    bool isFalling;
    bool isGrounded;
public:
    Animal(Properties *properties);
    Animal(){}
    virtual void draw();
    virtual void clean();
    virtual void update(float dt);
    SDL_Rect hitBox(){return collider->getBox();}
    void animationState();

    std::string returnTexture(){
        return textureID;
    }

    float animalOriginX();
    float animalOriginY();
};


#endif //BLOJZGAME_ANIMAL_H
