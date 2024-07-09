

#ifndef BLOJZGAME_VECTOR2D_H
#define BLOJZGAME_VECTOR2D_H

#include <SDL.h>
#include <string>

class Vector2D {
public:
    float x, y;

    Vector2D(float x = 0, float y = 0) : x(x), y(y) {};
    Vector2D operator+(const Vector2D &v2) const {return Vector2D(x + v2.x, y + v2.y);}
    Vector2D operator-(const Vector2D &v2) const {return Vector2D(x - v2.x, y - v2.y);}
    Vector2D operator*(const float scalar) const {return Vector2D(x*scalar, y*scalar);}
    void log(const std::string& message = "") const { SDL_Log("%s (x y) = (%f %f)", message.c_str(), x, y);}
};

#endif //BLOJZGAME_VECTOR2D_H
