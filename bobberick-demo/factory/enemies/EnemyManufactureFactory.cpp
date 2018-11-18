#include "EnemyManufactureFactory.h"
#include "../../../bobberick-framework/src/services/ServiceManager.h"
#include "../../../bobberick-framework/src/entity/EntityManager.h"
#include "../../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../../../bobberick-framework/src/entity/components/TimerComponent.h"
#include "../../../bobberick-framework/src/util/RandomGenerator.h"
#include "../../components/StatsComponent.h"
#include "../../components/HealthBarComponent.h"
#include "../../components/SpawnComponent.h"
#include "../../components/AIComponent.h"
#include "../../components/SpawnedComponent.h"

Entity& EnemyManufactureFactory::getEnemy(const int level)
{
	std::string type = "fireWizard";
	int spawnerCount = 0;
	for (auto& entity : ServiceManager::Instance()->getService<EntityManager>().getAllEntitiesWithComponent<SpawnComponent>()) {
		spawnerCount++;

	}
	Entity& manufacture = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	auto& transformComponent = manufacture.addComponent<TransformComponent>(-1, -1, 100, 91, 1);

	manufacture.addComponent<SpriteComponent>("assets/image/enemies/house.png", "factory", 1, 1, 10);
	manufacture.addComponent<HealthBarComponent>();
	manufacture.addComponent<TimerComponent>();
	manufacture.addComponent<AIComponent>();
	manufacture.addComponent<SpawnComponent>(spawnerCount, type, 1, 5, 2500);
	manufacture.addComponent<CollisionComponent>("manufacturer");

	transformComponent.speed = 0;

	const double random = RandomGenerator{}.getRandomDouble(1, 50);
	const double randMutator = (random + 50) / 100;

	int hp = 1000 * level * (randMutator),
	    maxHp = 1000 * level * (randMutator),
	    atkMin = 0 * level * (randMutator),
	    atkMax = 0 * level * (randMutator),
	    df = 0;

	manufacture.addComponent<StatsComponent>(hp, maxHp, atkMin, atkMax, df, level);

	return manufacture;
}

Entity & EnemyManufactureFactory::getEnemy(const int level, const int spawnerId)
{
	auto& enemy = getEnemy(level);
	enemy.addComponent<SpawnedComponent>(spawnerId);
	return enemy;
}