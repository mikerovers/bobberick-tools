#ifndef BOBBERICK_TOOLS_ENEMYFACTORY_H
#define BOBBERICK_TOOLS_ENEMYFACTORY_H

#include "../../../bobberick-framework/src/entity/Entity.h"

class EnemyFactory
{
public:
	Entity* getRandomEnemy(const int level, const std::string type);
};


#endif //BOBBERICK_TOOLS_ENEMYFACTORY_H
