//
// Created by lukah on 24. 05. 2022.
//

#ifndef BLOJZGAME_SAVEANDLOAD_H
#define BLOJZGAME_SAVEANDLOAD_H

#include <vector>

struct Other{
    int mapLvl;
    int remainingAnimals;
    int Time;
};

struct WarriorData{
    int life;
    float x, y;
};

struct AnimalData{
    char texture_id [32];
    float x, y;
};

class Save {
private:
    static Save *instance;
public:
    static Save *getInstance();

    void saveGameplay();
    void loadGameplay();

    Other getInformationData();
    WarriorData getWarriorData();
    std::vector<AnimalData> getAnimalData();
};


#endif //BLOJZGAME_SAVEANDLOAD_H
