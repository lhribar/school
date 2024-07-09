

#ifndef BLOJZGAME_INPUT_H
#define BLOJZGAME_INPUT_H

#include <SDL.h>

enum Axis {HORIZONTAL, VERTICAL};

class Input{
private:
    Input();
    static Input* instance;

    void keyDown();
    void keyUp();

    const Uint8* keyStates;
public:
    static Input* getInstance();

    void listen();
    bool getKeyDown(SDL_Scancode key);
    int getAxisKey(Axis axis);
};

#endif //BLOJZGAME_INPUT_H
