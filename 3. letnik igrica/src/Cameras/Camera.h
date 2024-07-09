
#ifndef BLOJZGAME_CAMERA_H
#define BLOJZGAME_CAMERA_H

#include "../Physics/Point.h"
#include "../Physics/Vector2D.h"
#include "../Core/Engine.h"

class Camera {
private:
    static Camera *instance;
    Camera(){
        viewBox = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    };

    Point *target;
    Vector2D position;
    SDL_Rect viewBox;
public:
    static Camera *getInstance();
    void update(float dt);

    SDL_Rect getViewBox() {return viewBox;}
    Vector2D getPosition() {return position;}
    void setTarget(Point *target){ this->target = target;}
};


#endif //BLOJZGAME_CAMERA_H
