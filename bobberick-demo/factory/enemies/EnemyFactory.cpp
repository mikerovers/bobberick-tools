#include "EnemyFactory.h"
#include "OrcFactory.h"
#include "ZombieFactory.h"
#include "FireWizardFactory.h"
#include "../../../bobberick-framework/src/services/ServiceManager.h"
#include "../../../bobberick-framework/src/entity/EntityManager.h"
#include "../../../bobberick-framework/src/entity/components/SpriteComponent.h"

Entity * EnemyFactory::getRandomEnemy(const int level)
{
	int type = rand() % 3;
	switch (type) {
		case 0: {
			OrcFactory factory = OrcFactory{};
			return factory.getEnemy(level);
		}
		case 1: {
			ZombieFactory factory = ZombieFactory{};
			return factory.getEnemy(level);
		}
		case 2: {
			FireWizardFactory factory = FireWizardFactory{};
			return factory.getEnemy(level);
		}
	}
	return nullptr;
}

Entity * EnemyFactory::getRandomEnemy(const int minLevel, const int maxLevel)
{
	int type = rand() % 3;
	int level = rand() % (maxLevel-minLevel) + minLevel;
	switch (type) {
	case 0: {
		OrcFactory factory = OrcFactory{};
		return factory.getEnemy(level);
	}
	case 1: {
		ZombieFactory factory = ZombieFactory{};
		return factory.getEnemy(level);
	}
	case 2: {
		FireWizardFactory factory = FireWizardFactory{};
		return factory.getEnemy(level);
	}
	}
	return nullptr;
}

Entity * EnemyFactory::getEnemy(const int level, const std::string type)
{
	if (type == "orc") {
		OrcFactory factory = OrcFactory{};
		return factory.getEnemy(level);
	}

	if (type == "zombie") {
		ZombieFactory factory = ZombieFactory{};
		return factory.getEnemy(level);
	}

	if (type == "fireWizard") {
		FireWizardFactory factory = FireWizardFactory{};
		return factory.getEnemy(level);
	}

	return nullptr;
}
