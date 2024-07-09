
#include "Warrior.h"
#include "../Graphics/TextureManager.h"
#include "SDL.h"
#include "../Inputs/Input.h"
#include "../Cameras/Camera.h"
#include "../Collision/CollisionHandler.h"

#define FORWARD 1
#define BACKWARD -1

Warrior::Warrior(Properties* properties): Character(properties) {
    isHurt = false;
    jumpTime = JUMP_TIME;
    jumpForce = JUMP_FORCE;

    collider = new Collider();
    collider->setBuffer(-15, -12, 78, 70);

    rigidBody = new RigidBody();
    rigidBody->setGravity(8.0f);

    animation = new SpriteAnimation();
    animation->setProperties(textureID, 1, 6, 100);
}

void Warrior::draw() {
    animation->draw(transform->x, transform->y, width, height, 1, 1, flip);

    Vector2D cam = Camera::getInstance()->getPosition();
    SDL_Rect box = collider->getBox();
    box.x -= cam.x;
    box.y -= cam.y;
    //SDL_RenderDrawRect(Engine::getInstance()->getRenderer(), &box);

}

void Warrior::clean() {
    TextureManager::getInstance()->dropTexture(textureID);
}

void Warrior::update(float dt) {
    isRunning = false;

    rigidBody->unSetForce();

    //Run forward
    if (Input::getInstance()->getAxisKey(HORIZONTAL) == FORWARD){
        rigidBody->applyForceX(FORWARD*RUN_FORCE*3);
        flip = SDL_FLIP_NONE;
        isRunning = true;
    }

    //Run backward
    if (Input::getInstance()->getAxisKey(HORIZONTAL) == BACKWARD){
        rigidBody->applyForceX(BACKWARD*RUN_FORCE*3);
        flip = SDL_FLIP_HORIZONTAL;

        isRunning = true;
    }


    //Jump

    if(Input::getInstance()->getKeyDown(SDL_SCANCODE_SPACE) && isGrounded){

        isJumping = true;
        isGrounded = false;
        rigidBody->applyForceY(UPWARD*jumpForce*(-1));

    }
    if (Input::getInstance()->getKeyDown(SDL_SCANCODE_SPACE) && isJumping && jumpTime > 0){
        jumpTime -= dt;
        rigidBody->applyForceY(UPWARD*jumpForce);
    } else {
        isJumping = false;
        jumpTime = JUMP_TIME;
    }

    //Fall
        if (rigidBody->getVelocity().y > 0 && !isGrounded) {
            isFalling = true;
        } else isFalling = false;


    //Move on X axis
    rigidBody->update(dt);
    lastSafePosition.x = transform->x;
    transform->x += rigidBody->getPosition().x;
    collider->set(transform->x, transform->y, 96, 96);

    if (CollisionHandler::getInstance()->mapCollision(collider->getBox())) transform->x = lastSafePosition.x;



    //move on Y axis
    rigidBody->update(dt);
    lastSafePosition.y = transform->y;
    transform->y += rigidBody->getPosition().y;
    collider->set(transform->x, transform->y, 96, 96);


    if (CollisionHandler::getInstance()->mapCollision(collider->getBox())){
        isGrounded = true;
        isJumping = false;
        transform->y = lastSafePosition.y;
    } else isGrounded = false;


    origin->x = transform->x + width / 2;
    origin->y = transform->y + height / 2;

    //preden je lahko ponovno zadet
    if (isHurt){
        hurt_delay++;
        if (hurt_delay >= 100){
            isHurt = false;
            hurt_delay = 0;
        }
    }

    animationState();
    animation->update(dt);


}

void Warrior::animationState() {
    //Idling
    animation->setProperties("player_idle", 1, 4, 100);

    //Running
    if (isRunning) animation->setProperties("player_run", 1, 6, 100);

    //Jumping
    if (isJumping) animation->setProperties("player_jump", 1, 2, 100);

    //Falling
    if (isFalling) animation->setProperties("player_fall", 1, 2, 100);

    //hurt
    if (isHurt) animation->setProperties("player_hurt", 1, 4, 100);
}