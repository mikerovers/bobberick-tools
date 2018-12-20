#pragma once


#include "../../../bobberick-framework/src/entity/Entity.h"
#include "../../../bobberick-demo/factory/enemies/BaseEnemyFactory.h"

class EnemyManufactureFactory : public BaseEnemyFactory
{
public:
	Entity& getEnemy(const int level) override;
	Entity& getEnemy(const int level, const int spawnerId) override;
private:
	std::string type;
};
