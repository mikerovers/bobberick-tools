#ifndef BOBBERICK_TOOLS_ENEMYFACTORY_H
#define BOBBERICK_TOOLS_ENEMYFACTORY_H

#include "../../../bobberick-framework/src/entity/Entity.h"
#include "BaseEnemyFactory.h"
#include <map>
#include <memory>

class EnemyFactory
{
public:
	Entity& getRandomEnemy(const int level);
	Entity& getRandomEnemy(const int minLevel, const int maxLevel);
	Entity& getEnemy(const int level, const std::string type);
	Entity& getEnemy(const int level, const int maxLevel, const std::string type);
	Entity& spawnEnemy(const int level, const std::string type, const int spawnerId);
	Entity& spawnEnemy(const int level, const int maxLevel, const std::string type, const int spawnerId);
	Entity& getBoss(const int level);
	std::unique_ptr<BaseEnemyFactory> getFactory(const std::string type) const;
	std::unique_ptr<BaseEnemyFactory> getRandomFactory() const;

};


#endif //BOBBERICK_TOOLS_ENEMYFACTORY_H
