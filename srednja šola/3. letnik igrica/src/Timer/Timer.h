

#ifndef BLOJZGAME_TIMER_H
#define BLOJZGAME_TIMER_H

#include <SDL.h>

const int TARGET_FPS = 60;
const float TARGET_DELTATIME = 1.5f;

class Timer {
private:
    static Timer* instance;
    float deltaTime, lastTime;
public:
    void loadSave(int Time);
    int ingametime = 0, outsidegame = 0;
    static Timer* getInstance();
    void tick();
    float getDeltaTime() const;
};


#endif //BLOJZGAME_TIMER_H
