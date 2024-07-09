//
// Created by lukah on 24. 05. 2022.
//

#include "saveAndLoad.h"

#include "../Timer/Timer.h"
#include <fstream>
//#include <sys/stat.h>
#include "../Collision/CollisionHandler.h"
#include "../Core/Engine.h"
#include "../Maps/MapParser.h"
#include "../MainMenu/Menu.h"
#include "../Characters/Animal.h"
#include "../Objects/GameObject.h"

Save *Save::instance = nullptr;

Save *Save::getInstance() {
    if (instance == nullptr) instance = new Save();
    return instance;
}

void Save::saveGameplay() {

    struct Other Other = getInformationData();
    ofstream data("save.bin", ios::binary);
    data.write((char *) &Other, sizeof Other);
    data.close();

    struct WarriorData warriorData = getWarriorData();
    ofstream warriorBin("WarriorSave.bin", ios::binary);
    warriorBin.write((char *) &warriorData, sizeof warriorData);
    warriorBin.close();

    vector<AnimalData> animal = getAnimalData();
    ofstream animalSave("AnimalSave.bin", ios::binary);
    for(int i = 0; i < animal.size(); i++)
        animalSave.write((char *) &animal[i], sizeof animal[i]);

    animalSave.close();

}

void Save::loadGameplay() {
    struct Other Other;
    std::ifstream data("save.bin", std::ios::binary);
    if (!data.is_open()){
        SDL_Log("Couldn't open file!");
        return;
    }

    data.read((char *) &Other, sizeof Other);
    data.close();

    CollisionHandler::getInstance()->mapLvl = Other.mapLvl;
    Engine::getInstance()->setRemainingAnimals(Other.mapLvl);
    //Engine::getInstance()->setLevel(saveInformation.level);

    if (Other.mapLvl == 1) {
        MapParser::getInstance()->getMaps("MAP1");

        Engine::getInstance()->loadAnimal("dog1_idle", 2000, 500);
    }
    else if (Other.mapLvl == 2){
        MapParser::getInstance()->getMaps("MAP2");

        vector<AnimalData> animal;
        ifstream animalSave("AnimalSave.bin", ios::binary);
        struct AnimalData animalTemp = AnimalData();
        while (animalSave.read((char *) &animalTemp, sizeof animalTemp))
            animal.push_back(animalTemp);
        animalSave.close();
        for(int i = 0; i < animal.size(); i++)
            Engine::getInstance()->loadAnimal(animal[i].texture_id, animal[i].x, animal[i].y);

    }

    Menu::getInstance()->inGame = true;

    Engine::getInstance()->loadSave(Other.Time);

    //Engine::getInstance()->loadClean();

    struct WarriorData warriorData = WarriorData();
    ifstream warriorBin("WarriorSave.bin", ios::binary);
    warriorBin.read((char *) &warriorData, sizeof warriorData);
    warriorBin.close();

    //Play::getInstance()->loadPlayerData(playerInformation.health, playerInformation.x - 16, playerInformation.y - 45);
    Engine::getInstance()->loadWarrior(warriorData.life, warriorData.x - 16, warriorData.y - 45);
}

Other Save::getInformationData(){
    struct Other save = Other();
    save.mapLvl = CollisionHandler::getInstance()->mapLvl;
    save.Time = Timer::getInstance()->getDeltaTime();
    save.remainingAnimals = Engine::getInstance()->remainingAnimals();

    return save;
}

WarriorData Save::getWarriorData(){
    struct WarriorData temp = WarriorData();
    temp.life = Engine::getInstance()->warriorLife();
    temp.x = Engine::getInstance()->warriorOriginX();
    temp.y = Engine::getInstance()->warriorOriginY();

    return temp;
}

vector<AnimalData> Save::getAnimalData(){
    std::vector<Animal*> animals = Engine::getInstance()->getAnimals();
    std::vector<AnimalData> temp(animals.size());
    for(int i = 0; i < animals.size(); i++){
        temp[i].x = animals[i]->animalOriginX();
        temp[i].y = animals[i]->animalOriginY();
    }

    return temp;
}

