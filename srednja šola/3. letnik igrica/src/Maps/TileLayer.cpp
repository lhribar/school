

#include "TileLayer.h"
#include "../Graphics/TextureManager.h"

TileLayer::TileLayer(int tileSize, int rowCount, int colCount, TileMap tileMap, TileSetList tileSetList)
: tileSize(tileSize), rowCount(rowCount), colCount(colCount), tileMap(tileMap), tileSetList(tileSetList){

    for(int i = 0; i < tileSetList.size(); i++) TextureManager::getInstance()->loadTexture(tileSetList[i].name, "../assets/maps/" + tileSetList[i].source);

}

void TileLayer::render() {

    for(int row = 0; row < rowCount; row++){
        for(int col = 0; col < colCount; col++){
            int tileID = tileMap[row][col];

            if(tileID == 0) continue;
            else {
                int index = 0;
                if (tileSetList.size() > 1){
                    for(int k = 1; k < tileSetList.size(); k++){
                        if (tileID >= tileSetList[k].firstID && tileID <= tileSetList[k].lastID){
                            tileID = tileID + tileSetList[k].tileCount - tileSetList[k].lastID;
                            index = k;
                            break;
                        }
                    }
                }
                TileSet ts = tileSetList[index];
                int tileRow = tileID/ts.colCount;
                int tileCol = tileID - tileRow*ts.colCount - 1;

                //if this tile is on the last column
                if (tileID % ts.colCount == 0){
                    tileRow--;
                    tileCol = ts.colCount - 1;
                }

                TextureManager::getInstance()->drawTile(ts.name, ts.tileSize, col*ts.tileSize, row*ts.tileSize, tileRow, tileCol);
            }
        }
    }
}

void TileLayer::update() {

}
