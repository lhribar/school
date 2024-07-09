

#include "Timer.h"

Timer* Timer::instance = nullptr;

Timer *Timer::getInstance() {
    if (instance == nullptr) instance = new Timer();
    return instance;
}

void Timer::tick(){
    deltaTime = (SDL_GetTicks() - lastTime) * (TARGET_FPS / 1000.0f);

    if (deltaTime > TARGET_DELTATIME) deltaTime = TARGET_DELTATIME;

    lastTime = SDL_GetTicks();
}

float Timer::getDeltaTime() const{
    return deltaTime;
}

