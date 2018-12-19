#pragma once

#include "../../../bobberick-framework/src/entity/Entity.h"
#include "../../../bobberick-demo/factory/enemies/BaseEnemyFactory.h"

class DevilFactory : public BaseEnemyFactory
{
public:
	Entity& getEnemy(const int level) override;
	Entity& getEnemy(const int level, const int spawnerId) override;
};
