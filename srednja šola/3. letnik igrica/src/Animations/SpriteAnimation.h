

#ifndef BLOJZGAME_SPRITEANIMATION_H
#define BLOJZGAME_SPRITEANIMATION_H

#include "Animation.h"
#include <SDL.h>
#include <string>

class SpriteAnimation : public Animation{
private:
    int animationSpeed, spriteRow, frameCount;
    std::string textureID;
public:
    SpriteAnimation(bool repeat = true);

    virtual void update(float dt);
    void draw(float x, float y, int spriteWidth, int spriteHeight, float xScale = 1, float yScale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void setProperties(std::string textureID, int spriteRow, int frameCount, int animationSpeed);

    int getCurrentFrame() const {return currentFrame;}
    int getSpriteRow() const {return spriteRow;}
    void setSpriteRow(int row){spriteRow = row;}
    void incrSpriteRow(){++spriteRow;}
    void decrSpriteRow(){--spriteRow;}
};


#endif //BLOJZGAME_SPRITEANIMATION_H
