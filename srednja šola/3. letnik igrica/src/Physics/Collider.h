

#ifndef BLOJZGAME_COLLIDER_H
#define BLOJZGAME_COLLIDER_H

#include <SDL.h>

class Collider{
private:
    SDL_Rect box;
    SDL_Rect buffer;
public:
    SDL_Rect getBox(){return box;}
    void setBuffer(int x, int y, int w, int h){buffer = {x, y, w, h};}

    void set(int x, int y, int w, int h){
        box = {
                x - buffer.x,
                y - buffer.y,
                w - buffer.w,
                h - buffer.h
        };
    }
};

#endif //BLOJZGAME_COLLIDER_H
