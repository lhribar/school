

#ifndef BLOJZGAME_WARRIOR_H
#define BLOJZGAME_WARRIOR_H

#include "Character.h"
#include "../Animations/SpriteAnimation.h"
#include "../Physics/RigidBody.h"
#include "../Physics/Collider.h"
#include "../Physics/Vector2D.h"

#define JUMP_TIME 15.0f
#define JUMP_FORCE 19.0
#define RUN_FORCE 4.0f


class Warrior: public Character{
private:
    SpriteAnimation *animation;
    RigidBody *rigidBody;
    Vector2D lastSafePosition;

    bool isJumping;
    bool isGrounded;
    bool isFalling;
    bool isRunning;
    bool isHurt;

    float jumpTime;
    float jumpForce;

    int hurt_delay = 0;

public:
    Collider *collider;
    void IsHurt(bool temp){isHurt = temp;}
    int lives = 3;
    int animalsSaved = 0;
    Warrior(Properties* properties);
    virtual void draw();
    virtual void clean();
    virtual void update(float dt);
    void animationState();
    SDL_Rect hitBox(){return collider->getBox();}
};


#endif //BLOJZGAME_WARRIOR_H
