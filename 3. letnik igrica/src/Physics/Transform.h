

#ifndef BLOJZGAME_TRANSFORM_H
#define BLOJZGAME_TRANSFORM_H

#include "Vector2D.h"

class Transform{
public:
    float x, y;

    Transform(float x = 0, float y = 0): x(x), y(y){}

    void Log(std::string message = ""){
        SDL_Log("%s (x y) = (%f %f)", message.c_str(), x, y);
    }

    void translateX(float x) { this->x += x;}
    void translateY(float y) { this->y += y;}
    void translate(Vector2D tempV){ this->x += tempV.x; this->y += tempV.y;}
};

#endif //BLOJZGAME_TRANSFORM_H
