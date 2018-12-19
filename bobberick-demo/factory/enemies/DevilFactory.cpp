#include "DevilFactory.h"
#include "../../../bobberick-framework/src/services/ServiceManager.h"
#include "../../../bobberick-framework/src/entity/EntityManager.h"
#include "../../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../../../bobberick-framework/src/entity/components/TimerComponent.h"
#include "../../../bobberick-framework/src/util/RandomGenerator.h"
#include "../../components/StatsComponent.h"
#include "../../components/HealthBarComponent.h"
#include "../../components/AIComponent.h"
#include "../../components/EnemyMovementComponent.h"
#include "../../components/EndBossComponent.h"
#include "../../components/SprayComponent.h"
#include "../../components/SpawnedComponent.h"

Entity& DevilFactory::getEnemy(const int level)
{
	Entity& chicken = ServiceManager::Instance()->getService<EntityManager>().addEntity();	
	auto& transformComponent = chicken.addComponent<TransformComponent>(0, 0, 92, 86, 1);

	chicken.addComponent<SpriteComponent>("devil", 3, 3, 9, 6);


	chicken.addComponent<SprayComponent>();
	chicken.addComponent<EndBossComponent>();
	chicken.addComponent<TimerComponent>();
	chicken.getComponent<SprayComponent>().sprayTimer = 1000;
	chicken.addComponent<HealthBarComponent>();
	chicken.addComponent<AIComponent>();
	chicken.addComponent<EnemyMovementComponent>();
	chicken.addComponent<CollisionComponent>("chicken");

	transformComponent.speed = 2;

	const double random = RandomGenerator{}.getRandomDouble(1, 50);
	const double randMutator = (random + 50) / 100;

	int hp = 1000 * level * randMutator,
	    maxHp = 1000 * level * randMutator,
	    atkMin = 5 * level * randMutator,
	    atkMax = 5 * level * randMutator,
	    df = 0;

	chicken.addComponent<StatsComponent>(hp, maxHp, atkMin, atkMax, df, level);

	return chicken;
}

Entity & DevilFactory::getEnemy(const int level, const int spawnerId)
{
	auto& enemy = getEnemy(level);
	enemy.addComponent<SpawnedComponent>(spawnerId);
	return enemy;
}