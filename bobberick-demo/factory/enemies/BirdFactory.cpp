#include "BirdFactory.h"
#include "../../../bobberick-framework/src/services/ServiceManager.h"
#include "../../../bobberick-framework/src/entity/EntityManager.h"
#include "../../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../../bobberick-framework/src/entity/components/TimerComponent.h"
#include "../../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../../../bobberick-framework/src/util/RandomGenerator.h"
#include "../../components/StatsComponent.h"
#include "../../components/HealthBarComponent.h"
#include "../../components/AIComponent.h"
#include "../../components/ChaseComponent.h"
#include "../../components/EnemyMovementComponent.h"
#include "../../components/SpawnedComponent.h"

Entity &BirdFactory::getEnemy(const int level)
{
	Entity& bird = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	auto& transformComponent = bird.addComponent<TransformComponent>(-1, -1, 53, 81, 1);
	auto& spriteComponent = bird.addComponent<SpriteComponent>("bird", 6, 6, 12, 6);
	bird.addComponent<HealthBarComponent>();
	bird.addComponent<EnemyMovementComponent>();
	bird.addComponent<TimerComponent>();
	bird.addComponent<AIComponent>();
	bird.addComponent<ChaseComponent>();
	bird.addComponent<CollisionComponent>("bird");

	transformComponent.speed = 2;

	const double random = RandomGenerator{}.getRandomDouble(1, 50);

	double randMutator = (random + 50) / 100;

	int hp = 50 * level * randMutator,
		maxHp = 50 * level * randMutator,
		atkMin = 2 * level * randMutator,
		atkMax = 4 * level * randMutator,
		df = 1;

	bird.addComponent<StatsComponent>(hp, maxHp, atkMin, atkMax, df, level);

	return bird;
}

Entity & BirdFactory::getEnemy(const int level, const int spawnerId)
{
	auto& enemy = getEnemy(level);
	enemy.addComponent<SpawnedComponent>(spawnerId);
	return enemy;
}