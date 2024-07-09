#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Text
{
private:
    SDL_Renderer *renderer;
    SDL_Texture *message;
    TTF_Font *font;
    SDL_Color color;
    SDL_Rect messageRect;

public:
    void init(SDL_Renderer *renderer, int x, int y, const char text[]);
    void init_center(SDL_Renderer *renderer, int y, int size, char text[]);

    void draw();
    void change_text(char text[]);
    void change_text(char text[], int x);
    void change_text_center(char text[]);
};