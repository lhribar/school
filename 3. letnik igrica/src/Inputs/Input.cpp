
#include "Input.h"
#include "../Core/Engine.h"

Input* Input::instance = nullptr;

Input::Input(){
    keyStates = SDL_GetKeyboardState(nullptr);
}

Input *Input::getInstance() {
    if (instance == nullptr) instance = new Input();
    return instance;
}

void Input::listen() {
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                Engine::getInstance()->quit();
                break;
            case SDL_KEYDOWN:
                keyDown();
                break;
            case SDL_KEYUP:
                keyUp();
                break;
        }
    }
}

bool Input::getKeyDown(SDL_Scancode key){
    if(keyStates[key] == 1)
        return true;
    return false;
}

void Input::keyUp() {
    keyStates = SDL_GetKeyboardState(nullptr);
}

void Input::keyDown() {
    keyStates = SDL_GetKeyboardState(nullptr);
}


int Input::getAxisKey(Axis axis) {
    switch (axis) {
        case HORIZONTAL:
            if (getKeyDown(SDL_SCANCODE_D) || getKeyDown(SDL_SCANCODE_RIGHT)) return 1;
            if (getKeyDown(SDL_SCANCODE_A) || getKeyDown(SDL_SCANCODE_LEFT)) return -1;
            break;
        case VERTICAL:
            if (getKeyDown(SDL_SCANCODE_W) || getKeyDown(SDL_SCANCODE_UP)) return 1;
            if (getKeyDown(SDL_SCANCODE_S) || getKeyDown(SDL_SCANCODE_DOWN)) return -1;
            break;
        default:
            return 0;
    }
    return 0;
}
