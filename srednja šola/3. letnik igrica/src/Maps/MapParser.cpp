
#include "MapParser.h"
#include "../Collision/CollisionHandler.h"

MapParser *MapParser::instance = nullptr;

MapParser *MapParser::getInstance() {
    if (instance == nullptr) instance = new MapParser();
    return instance;
}

MapParser::MapParser() {
}

 bool MapParser::load() {
    parse("MAP1", "../assets/maps/level1.tmx");
    parse("MAP2", "../assets/maps/level2.tmx");


    return true;
}

void MapParser::clean() {
    std::map<std::string, GameMap*>::iterator it;
    for(it = mapDict.begin(); it != mapDict.end(); it++)
        it->second = nullptr;

    mapDict.clear();
}

bool MapParser::parse(std::string id, std::string source) {
    TiXmlDocument xml;
    xml.LoadFile(source);

    if (xml.Error()){
        SDL_Log("Failed to load: %s", source.c_str());
        return false;
    }

    TiXmlElement *root = xml.RootElement();
    int rowCount, colCount, tileSize = 0;

    root->Attribute("width", &colCount);
    root->Attribute("height", &rowCount);
    root->Attribute("tilewidth", &tileSize);

    //Parse tileSets
    TileSetList tileSets;
    for(TiXmlElement *element = root->FirstChildElement(); element != nullptr; element = element->NextSiblingElement()){
        if (element->Value() == std::string("tileset")){
            tileSets.push_back(parseTileSet(element));
        }
    }

    //Parse layers
    GameMap *gameMap = new GameMap();
    for(TiXmlElement *element = root->FirstChildElement(); element != nullptr; element = element->NextSiblingElement()){
        if (element->Value() == std::string("layer")){
            TileLayer *tileLayer = parseTileLayer(element, tileSets, tileSize, rowCount, colCount);
            gameMap->mapLayers.push_back(tileLayer);
        }
    }

    mapDict[id] = gameMap;
    return true;
}

TileSet MapParser::parseTileSet(TiXmlElement *xmlTileSet) {
    TileSet tileSet;

    tileSet.name = xmlTileSet->Attribute("name");
    xmlTileSet->Attribute("firstgid", &tileSet.firstID);

    xmlTileSet->Attribute("tilecount", &tileSet.tileCount);
    tileSet.lastID = tileSet.firstID + tileSet.tileCount - 1;

    xmlTileSet->Attribute("columns", &tileSet.colCount);
    tileSet.rowCount = tileSet.tileCount/tileSet.colCount;
    xmlTileSet->Attribute("tilewidth", &tileSet.tileSize);

    TiXmlElement *image = xmlTileSet->FirstChildElement();
    tileSet.source = image->Attribute("source");

    return tileSet;
}

TileLayer *MapParser::parseTileLayer(TiXmlElement *xmlLayer, TileSetList tileSets, int tileSize, int rowCount, int colCount) {
    TiXmlElement *data;
    for(TiXmlElement *element = xmlLayer->FirstChildElement(); element != nullptr; element = element->NextSiblingElement()){
        if (element->Value() == std::string("data")){
            data = element;
            break;
        }
    }

    //Parse layer tile map
    std::string matrix(data->GetText());
    std::istringstream iss(matrix);
    std::string id;

    TileMap tileMap(rowCount, std::vector<int>(colCount, 0));

    for(int row = 0; row < rowCount; ++row){
        for(int col = 0; col < colCount; ++col){
            std::getline(iss, id, ',');
            std::stringstream convertor(id);
            convertor >> tileMap[row][col];

            if (!iss.good()) break;
        }
    }

    return new TileLayer(tileSize, rowCount, colCount, tileMap, tileSets);
}
