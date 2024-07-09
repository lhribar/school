

#include "SpriteAnimation.h"
#include "../Graphics/TextureManager.h"

SpriteAnimation::SpriteAnimation(bool repeat) : Animation(repeat) {

}

void SpriteAnimation::update(float dt) {
    currentFrame = (SDL_GetTicks() / animationSpeed) % frameCount;
}

void SpriteAnimation::draw(float x, float y, int spriteWidth, int spriteHeight, float xScale, float yScale, SDL_RendererFlip flip) {
    TextureManager::getInstance()->drawFrame(textureID, x, y, spriteWidth, spriteHeight, spriteRow, currentFrame, flip);
}

void SpriteAnimation::setProperties(std::string textureID, int spriteRow, int frameCount, int animationSpeed) {
    this->textureID = textureID;
    this->spriteRow = spriteRow;
    this->frameCount = frameCount;
    this->animationSpeed = animationSpeed;
}
