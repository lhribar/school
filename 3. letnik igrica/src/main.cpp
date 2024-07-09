#include "Core/Engine.h"
#include "Timer/Timer.h"

int main(int argc, char* argv[]) {

    Engine::getInstance()->init();

    while (Engine::getInstance()->isRunning()){
        Engine::getInstance()->events();
        Engine::getInstance()->update();
        Engine::getInstance()->render();
        Timer::getInstance()->tick();
    }

    Engine::getInstance()->clean();

    return 0;
}