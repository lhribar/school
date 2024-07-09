//
// Created by lukah on 23. 05. 2022.
//

#include "boss.h"
#include "Enemy.h"
#include "../Collision/CollisionHandler.h"
#include "../Cameras/Camera.h"
#include "Warrior.h"
#include "../Graphics/TextureManager.h"

Boss::Boss(Properties *properties) : Character(properties) {
    collider = new Collider();
    collider->setBuffer(-15, -12, 120, 70);

    rigidBody = new RigidBody();
    rigidBody->setGravity(0.0f);

    animation = new SpriteAnimation();
    animation->setProperties(textureID, 1, 4, 100);
}

void Boss::draw() {

    animation->draw(transform->x, transform->y, width, height, 1, 1, flip);
    Vector2D cam = Camera::getInstance()->getPosition();
    SDL_Rect box = collider->getBox();
    box.x -= cam.x;
    box.y -= cam.y;
    SDL_RenderDrawRect(Engine::getInstance()->getRenderer(), &box);
}

void Boss::clean() {
    TextureManager::getInstance()->dropTexture(textureID);
}

void Boss::update(float dt) {
    rigidBody->update(dt);
    lastSafePosition.x = transform->x;
    transform->x += rigidBody->getPosition().x;

    collider->set(transform->x, transform->y, 140, 100);

    if (CollisionHandler::getInstance()->mapCollision(collider->getBox())) transform->x = lastSafePosition.x;



    animation->update(dt);

    lastSafePosition.y = transform->y;
    transform->y += rigidBody->getPosition().y;
    collider->set(transform->x, transform->y, 140, 100);

    /*if (rigidBody->getVelocity().y > 0 && !isGrounded) {
        isFalling = true;
    } else isFalling = false;
*/

    if (CollisionHandler::getInstance()->mapCollision(collider->getBox())) transform->y = lastSafePosition.y;

    if (CollisionHandler::getInstance()->mapCollision(collider->getBox())){
        isGrounded = true;
        transform->y = lastSafePosition.y;
    } else isGrounded = false;



    origin->x = transform->x + width / 2;
    origin->y = transform->y + height / 2;

    animationState();
    animation->update(dt);
}

void Boss::animationState() {

    //if (isFalling) animation->setProperties("boss_fall", 1, 16, 100);

    //if (isRunning) animation->setProperties("boss_walk", 1, 6, 100);

}