

#ifndef BLOJZGAME_ANIMATION_H
#define BLOJZGAME_ANIMATION_H


#include <SDL.h>
#include <string>

class Animation {
protected:
    bool repeat;
    bool isEnded;
    int currentFrame;
public:
    Animation(bool repeat = true) : repeat(repeat){
        isEnded = false;
    }

    virtual void update(float dt) = 0;
    bool getIsEnded(){return isEnded;}
};


#endif //BLOJZGAME_ANIMATION_H
