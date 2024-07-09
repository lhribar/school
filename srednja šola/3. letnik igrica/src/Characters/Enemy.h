

#ifndef BLOJZGAME_ENEMY_H
#define BLOJZGAME_ENEMY_H

#include "Character.h"
#include "../Physics/RigidBody.h"

#include "../Animations/SpriteAnimation.h"
#include "../Physics/Collider.h"

class Enemy : public Character {
private:
    Collider *collider;
    RigidBody *rigidBody;
    SpriteAnimation *animation;
    Vector2D lastSafePosition;

    int walking = 0;
    bool moveRight;

    bool isFalling;
    bool isRunning;
    bool isGrounded;
public:
    Enemy(Properties *properties);

    virtual void draw();
    virtual void clean();
    virtual void update(float dt);
    void animationState();
    SDL_Rect hitBox(){return collider->getBox();}

};


#endif //BLOJZGAME_ENEMY_H
