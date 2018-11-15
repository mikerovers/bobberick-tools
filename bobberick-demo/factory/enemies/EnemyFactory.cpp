#include "EnemyFactory.h"
#include "OrcFactory.h"
#include "ZombieFactory.h"
#include "FireWizardFactory.h"
#include "../../../bobberick-framework/src/services/ServiceManager.h"
#include "../../../bobberick-framework/src/entity/EntityManager.h"
#include "../../../bobberick-framework/src/entity/components/SpriteComponent.h"

Entity & EnemyFactory::getRandomEnemy(const int level)
{
	const int type = rand() % 3;
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
		// TODO find something for this.
		case 3:
			FireWizardFactory factory = FireWizardFactory{};
			return factory.getEnemy(level);
	}

	FireWizardFactory factory = FireWizardFactory{};
	return factory.getEnemy(level);
}

Entity& EnemyFactory::getRandomEnemy(const int minLevel, const int maxLevel)
{
	const int type = rand() % 3;
	const int level = rand() % (maxLevel-minLevel) + minLevel;
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
	FireWizardFactory factory = FireWizardFactory{};
	return factory.getEnemy(level);
}

Entity & EnemyFactory::getEnemy(const int level, const std::string type)
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

	// TODO replace this with something else
	FireWizardFactory factory = FireWizardFactory{};
	return factory.getEnemy(level);
}
