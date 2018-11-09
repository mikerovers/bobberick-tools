#include "EnemyFactory.h"
#include "OrcFactory.h"
#include "ZombieFactory.h"
#include "../../../bobberick-framework/src/services/ServiceManager.h"
#include "../../../bobberick-framework/src/entity/EntityManager.h"
#include "../../../bobberick-framework/src/entity/components/SpriteComponent.h"

Entity * EnemyFactory::getRandomEnemy(const int level, const std::string type)
{
	if (type == "orc") {
		OrcFactory factory = OrcFactory{};
		return factory.getEnemy(level);
	}

	if (type == "zombie") {
		ZombieFactory factory = ZombieFactory{};
		return factory.getEnemy(level);
	}

	return nullptr;
}
