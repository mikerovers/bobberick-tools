#ifndef BOBBERICK_TOOLS_ENEMYFACTORY_H
#define BOBBERICK_TOOLS_ENEMYFACTORY_H

#include "../../../bobberick-framework/src/entity/Entity.h"
#include "BaseEnemyFactory.h"
#include <map>

class EnemyFactory
{
public:
	Entity& getRandomEnemy(const int level);
	Entity& getRandomEnemy(const int minLevel, const int maxLevel);
	Entity& getEnemy(const int level, const std::string type);
	Entity& spawnEnemy(const int level, const std::string type, const int spawnerId);
	Entity& getBoss(const int level);
	BaseEnemyFactory& getFactory(const std::string type);
	BaseEnemyFactory& getRandomFactory();

};


#endif //BOBBERICK_TOOLS_ENEMYFACTORY_H
