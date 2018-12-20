#ifndef BOBBERICK_TOOLS_BASEENEMYFACTORY_H
#define BOBBERICK_TOOLS_BASEENEMYFACTORY_H

#include "../../../bobberick-framework/src/entity/Entity.h"
#include <random>
#include <functional>

class BaseEnemyFactory
{
public:
	virtual ~BaseEnemyFactory() = default;
	virtual Entity& getEnemy(const int level) = 0;
	virtual Entity& getEnemy(const int level, const int spawnerId) = 0;

	bool randomBool()
	{
		static auto gen = std::bind(std::uniform_int_distribution<>(0, 1), std::default_random_engine());
		return gen();
	}
};


#endif //BOBBERICK_TOOLS_BASEENEMYFACTORY_H
