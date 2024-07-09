

#ifndef BLOJZGAME_TILELAYER_H
#define BLOJZGAME_TILELAYER_H

#include "Layer.h"

#include <string>
#include <vector>

struct TileSet{
    int firstID, lastID;
    int rowCount, colCount;
    int tileCount, tileSize;
    std::string name, source;
};

using TileSetList = std::vector<TileSet>;
using TileMap = std::vector<std::vector<int> >;

class TileLayer : public Layer{
private:
    int tileSize;
    int rowCount, colCount;
    TileMap tileMap;
    TileSetList tileSetList;
public:
    TileLayer(int tileSize, int rowCount, int colCount, TileMap tileMap, TileSetList tileSetList);
    virtual void render();
    virtual void update();
    TileMap getTileMap() {return tileMap;}
};


#endif //BLOJZGAME_TILELAYER_H
