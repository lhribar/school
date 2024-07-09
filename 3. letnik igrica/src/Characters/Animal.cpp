//
// Created by lukah on 1. 04. 2022.
//

#include "Animal.h"
#include "../Collision/CollisionHandler.h"
#include "../Cameras/Camera.h"
#include "../Graphics/TextureManager.h"
#include "../Objects/GameObject.h"

Animal::Animal(Properties *properties) : Character(properties) {
    collider = new Collider();
    collider->setBuffer(-4, -12, 100, 60);

    rigidBody = new RigidBody();
    rigidBody->setGravity(3.0f);

    animation = new SpriteAnimation();
    animation->setProperties(textureID, 1, 4, 100);
}

void Animal::draw() {
    animation->draw(transform->x, transform->y, width, height, 1, 1, flip);

    Vector2D cam = Camera::getInstance()->getPosition();
    SDL_Rect box = collider->getBox();
    box.x -= cam.x;
    box.y -= cam.y;
    //SDL_RenderDrawRect(Engine::getInstance()->getRenderer(), &box);
}

void Animal::clean() {
    TextureManager::getInstance()->dropTexture(textureID);

}

void Animal::update(float dt) {
    rigidBody->update(dt);
    lastSafePosition.x = transform->x;
    transform->x += rigidBody->getPosition().x;
    collider->set(transform->x, transform->y, 140, 100);

    if (CollisionHandler::getInstance()->mapCollision(collider->getBox())) transform->x = lastSafePosition.x;

    animation->update(dt);

    lastSafePosition.y = transform->y;
    transform->y += rigidBody->getPosition().y;
    collider->set(transform->x, transform->y, 140, 100);

    if (CollisionHandler::getInstance()->mapCollision(collider->getBox())) transform->y = lastSafePosition.y;

    origin->x = transform->x + width / 2;
    origin->y = transform->y + height / 2;

    animationState();
    animation->update(dt);
}

void Animal::animationState() {

    /*//Falling
    if (isFalling) animation->setProperties("animal_fall", 1, 4, 100);

    //idle
    if (isGrounded) animation->setProperties("animal_idle", 1, 4, 100);
*/
}


float Animal::animalOriginX() {
    return origin->x;
}

float Animal::animalOriginY(){
    return origin->y;
}