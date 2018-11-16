#pragma once


#include "../../../bobberick-framework/src/entity/Entity.h"
#include "../../../bobberick-demo/factory/enemies/BaseEnemyFactory.h"

class ChickenFactory : public BaseEnemyFactory
{
public:
	Entity& getEnemy(const int level);
};
