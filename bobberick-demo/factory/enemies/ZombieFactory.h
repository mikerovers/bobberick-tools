#ifndef BOBBERICK_TOOLS_ZOMBIEFACTORY_H
#define BOBBERICK_TOOLS_ZOMBIEFACTORY_H

#include "../../../bobberick-framework/src/entity/Entity.h"

class ZombieFactory
{
public:
    Entity* getEnemy(const int level);
};


#endif //BOBBERICK_TOOLS_ZOMBIEFACTORY_H
