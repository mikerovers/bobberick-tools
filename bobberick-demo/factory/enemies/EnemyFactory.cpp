#include "EnemyFactory.h"
#include "OrcFactory.h"
#include "ZombieFactory.h"
#include "FireWizardFactory.h"
#include "EndBossFactory.h"
#include "../../../bobberick-framework/src/services/ServiceManager.h"
#include "../../../bobberick-framework/src/entity/EntityManager.h"
#include "../../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "ChickenFactory.h"
#include "EnemyManufactureFactory.h"
#include "../../../bobberick-framework/src/util/RandomGenerator.h"


Entity& EnemyFactory::getRandomEnemy(const int level)
{
	return getRandomFactory().getEnemy(level);
}

Entity& EnemyFactory::getRandomEnemy(const int minLevel, const int maxLevel)
{
	const int level = RandomGenerator{}.getRandomNumber(minLevel, maxLevel);
	return getRandomFactory().getEnemy(level);
}

Entity& EnemyFactory::getEnemy(const int level, const std::string type)
{
	return EnemyFactory::getFactory(type).getEnemy(level);
}

Entity& EnemyFactory::spawnEnemy(const int level, const std::string type, const int spawnerId)
{
	return EnemyFactory::getFactory(type).getEnemy(level, spawnerId);
}

Entity& EnemyFactory::getBoss(const int level)
{
	return EnemyFactory::getFactory("boss").getEnemy(level);
}

BaseEnemyFactory& EnemyFactory::getFactory(std::string type) {
	if (type == "orc")
	{
		return OrcFactory{};
	}

	if (type == "zombie")
	{
		return ZombieFactory{};
	}

	if (type == "fireWizard")
	{
		return FireWizardFactory{};
	}

	if (type == "chicken")
	{
		return ChickenFactory{};
	}

	if (type == "boss")
	{
		return EndBossFactory{};
	}

	if (type == "manufacturer")
	{
		return EnemyManufactureFactory{};
	}

	return FireWizardFactory{}; // default
}

BaseEnemyFactory& EnemyFactory::getRandomFactory() {
	const int type = RandomGenerator{}.getRandomNumber(0, 3);
	switch (type)
	{
	case 0: {
		return getFactory("orc");
	}break;
	case 1: {
		return getFactory("zombie");
	}break;
	case 2: {
		return getFactory("fireWizard");
	}break;
	case 3: {
		return getFactory("chicken");
	}break;
	}
}