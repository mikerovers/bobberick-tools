#ifndef BOBBERICK_TOOLS_ENEMYFACTORY_H
#define BOBBERICK_TOOLS_ENEMYFACTORY_H

#include "../../../bobberick-framework/src/entity/Entity.h"
#include "BaseEnemyFactory.h"
#include <map>

class EnemyFactory
{
public:
	Entity& getRandomEnemy(const int level) const;
	Entity& getRandomEnemy(const int minLevel, const int maxLevel) const;
	Entity& getEnemy(const int level, const std::string type) const;
	Entity& spawnEnemy(const int level, const std::string type, const int spawnerId) const;
	Entity& getBoss(const int level) const;
	std::unique_ptr<BaseEnemyFactory> getFactory(const std::string type) const;
	std::unique_ptr<BaseEnemyFactory> getRandomFactory() const;

};


#endif //BOBBERICK_TOOLS_ENEMYFACTORY_H
