#pragma once


#include "../../../bobberick-framework/src/entity/Entity.h"
#include "../../../bobberick-demo/factory/enemies/BaseEnemyFactory.h"

class EnemyManufactureFactory : public BaseEnemyFactory
{
public:
	Entity& getEnemy(const int level);
	Entity& getEnemy(const int level, const int spawnerId);
private:
	std::string type;
};
