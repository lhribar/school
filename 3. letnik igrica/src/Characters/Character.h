

#ifndef BLOJZGAME_CHARACTER_H
#define BLOJZGAME_CHARACTER_H

#include <string>

#include "../Objects/GameObject.h"

class Character: public GameObject{
public:
    Character(){}
    Character(Properties *properties): GameObject(properties){}
    virtual void draw() = 0;
    virtual void clean() = 0;
    virtual void update(float dt) = 0;
protected:
    std::string name;
};


#endif //BLOJZGAME_CHARACTER_H
