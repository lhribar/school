

#ifndef BLOJZGAME_GAMEMAP_H
#define BLOJZGAME_GAMEMAP_H

#include "Layer.h"

#include <vector>

class GameMap {
private:
    friend class MapParser;
    std::vector<Layer*> mapLayers;
public:
    void render(){
        for(int i = 0; i < mapLayers.size(); i++) mapLayers[i]->render();
    }

    void update(){
        for(int i = 0; i< mapLayers.size(); i++) mapLayers[i]->update();
    }

    std::vector<Layer*> getMapLayers(){return mapLayers;}
};

#endif //BLOJZGAME_GAMEMAP_H
