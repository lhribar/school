#include "TextureManager.h"
#include "../Core/Engine.h"
#include "../Cameras/Camera.h"
#include "../Vendor/tinyxml.h"

TextureManager* TextureManager::instance = nullptr;

TextureManager *TextureManager::getInstance() {
    if (instance == nullptr) instance = new TextureManager();
    return instance;
}

bool TextureManager::loadTexture(std::string id, std::string fileName){
    SDL_Surface* surface = IMG_Load(fileName.c_str());
    if(surface == nullptr){
        SDL_Log("Failed to load texture: %s, %s", fileName.c_str(), SDL_GetError());
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::getInstance()->getRenderer(), surface);
    SDL_FreeSurface(surface); // Free the surface to avoid memory leak
    if(texture == nullptr){
        SDL_Log("Failed to create texture from surface: %s , %s", fileName.c_str(), SDL_GetError());
        return false;
    }

    textureMap[id] = texture;

    return true;
}

void TextureManager::dropTexture(std::string id) {
    SDL_DestroyTexture(textureMap[id]);
    textureMap.erase(id);
}

void TextureManager::drawTexture(std::string id, int x, int y, int width, int height, float scaleX, float scaleY, float scrollRatio, SDL_RendererFlip flip){
    SDL_Rect srcRect = {0, 0, width, height};
    Vector2D cam = Camera::getInstance()->getPosition() * scrollRatio;
    SDL_Rect dstRect = {x - (int) cam.x, y - (int) cam.y, (int) (width * scaleX), (int) (height * scaleY)};
    SDL_RenderCopyEx(Engine::getInstance()->getRenderer(), textureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip){
    SDL_Rect srcRect = {width * frame, height * (row - 1), width, height};
    Vector2D cam = Camera::getInstance()->getPosition();
    SDL_Rect dstRect = {x - (int) cam.x, y - (int) cam.y, width, height};
    SDL_RenderCopyEx(Engine::getInstance()->getRenderer(), textureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::drawTile(std::string tileSetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip) {
    SDL_Rect srcRect = {tileSize * frame, tileSize * row, tileSize, tileSize};
    Vector2D cam = Camera::getInstance()->getPosition();
    SDL_Rect dstRect = {x - (int) cam.x, y - (int) cam.y, tileSize, tileSize};
    SDL_RenderCopyEx(Engine::getInstance()->getRenderer(), textureMap[tileSetID], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::cleanTexture() {
    std::map<std::string, SDL_Texture*>::iterator iterator;
    for(iterator = textureMap.begin(); iterator != textureMap.end(); iterator++) SDL_DestroyTexture(iterator->second);

    textureMap.clear();
    SDL_Log("Texture map cleaned!");
}

bool TextureManager::parseTextures(std::string source) {
    TiXmlDocument xmlDocument;
    xmlDocument.LoadFile(source);
    if (xmlDocument.Error()){
        SDL_Log("Failed to load: %s", source.c_str());
        return false;
    }

    TiXmlElement *root = xmlDocument.RootElement();
    for(TiXmlElement *element = root->FirstChildElement(); element != nullptr; element = element->NextSiblingElement()){
        if (element->Value() == std::string("texture")){
            std::string id = element->Attribute("id");
            std::string src = element->Attribute("source");
            loadTexture(id, src);
        }
    }
    SDL_Log("Textures were successfully loaded!");
    return true;
}