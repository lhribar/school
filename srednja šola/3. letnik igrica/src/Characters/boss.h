//
// Created by lukah on 23. 05. 2022.
//

#ifndef BLOJZGAME_BOSS_H
#define BLOJZGAME_BOSS_H


#include "Character.h"
#include "../Physics/RigidBody.h"

#include "../Animations/SpriteAnimation.h"
#include "../Physics/Collider.h"

class Boss : public Character {
private:
    Collider *collider;
    RigidBody *rigidBody;
    SpriteAnimation *animation;
    Vector2D lastSafePosition;


    bool isRunning;
    bool isFalling;
    bool isGrounded;

public:
    Boss(Properties *properties);

    virtual void draw();
    virtual void clean();
    virtual void update(float dt);
    void animationState();
    SDL_Rect hitBox(){return collider->getBox();}

};

#endif //BLOJZGAME_BOSS_H
