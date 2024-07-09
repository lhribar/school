

#ifndef BLOJZGAME_TEXTUREMANAGER_H
#define BLOJZGAME_TEXTUREMANAGER_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>

class TextureManager{
private:
    static TextureManager* instance;
    std::map<std::string, SDL_Texture*> textureMap;
public:
    static TextureManager *getInstance();

    bool parseTextures(std::string source);
    bool loadTexture(std::string id, std::string filename);
    void dropTexture(std::string id);
    void cleanTexture();
    void drawTexture(std::string id, int x, int y, int width, int height, float scaleX = 1, float scaleY = 1, float scrollRatio = 0, SDL_RendererFlip flip= SDL_FLIP_NONE);
    void drawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawTile(std::string tileSetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
};

#endif //BLOJZGAME_TEXTUREMANAGER_H
