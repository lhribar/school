
#include "Enemy.h"
#include "../Collision/CollisionHandler.h"
#include "../Cameras/Camera.h"
#include "Warrior.h"
#include "../Graphics/TextureManager.h"

Enemy::Enemy(Properties *properties) : Character(properties) {
    collider = new Collider();
    collider->setBuffer(-1, -12, 120, 60);

    rigidBody = new RigidBody();
    rigidBody->setGravity(3.0f);

    animation = new SpriteAnimation();
    animation->setProperties(textureID, 1, 4, 100);
}

void Enemy::draw() {
    animation->draw(transform->x, transform->y, width, height, 1, 1, flip);

    Vector2D cam = Camera::getInstance()->getPosition();
    SDL_Rect box = collider->getBox();
    box.x -= cam.x;
    box.y -= cam.y;
    //SDL_RenderDrawRect(Engine::getInstance()->getRenderer(), &box);
}

void Enemy::clean() {
    TextureManager::getInstance()->dropTexture(textureID);
}

void Enemy::update(float dt) {
    rigidBody->update(dt);
    lastSafePosition.x = transform->x;
    transform->x += rigidBody->getPosition().x;
    collider->set(transform->x, transform->y, 140, 100);

    if (CollisionHandler::getInstance()->mapCollision(collider->getBox())) transform->x = lastSafePosition.x;

    animation->update(dt);

    lastSafePosition.y = transform->y;
    transform->y += rigidBody->getPosition().y;
    collider->set(transform->x, transform->y, 140, 100);

    //Fall
    if (rigidBody->getVelocity().y > 0 && !isGrounded) {
        isFalling = true;
    } else isFalling = false;


    if (CollisionHandler::getInstance()->mapCollision(collider->getBox())) transform->y = lastSafePosition.y;

    if (isGrounded) {
        isRunning = true;
        if (walking < 220 && moveRight) {
            walking+= 2;
            transform->x += 2;
        } else {
            if (walking == 0)
                moveRight = true;
            else
                moveRight = false;
            walking-=2;
            transform->x-=2;
        }
    }

    if (CollisionHandler::getInstance()->mapCollision(collider->getBox())){
        isGrounded = true;
        transform->y = lastSafePosition.y;
    } else isGrounded = false;

    origin->x = transform->x + width / 2;
    origin->y = transform->y + height / 2;

    animationState();
    animation->update(dt);
}

void Enemy::animationState() {

    //Falling
    if (isFalling) animation->setProperties("enemy_fall", 1, 4, 100);

    //Walk
    if (isRunning) animation->setProperties("enemy_walk", 1, 6, 100);

}