#include "OrcFactory.h"
#include "../../../bobberick-framework/src/services/ServiceManager.h"
#include "../../../bobberick-framework/src/entity/EntityManager.h"
#include "../../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../../../bobberick-framework/src/util/RandomGenerator.h"
#include "../../components/StatsComponent.h"
#include "../../components/HealthBarComponent.h"
#include "../../components/AIComponent.h"
#include "../../components/EnemyMovementComponent.h"
#include "../../components/SpawnedComponent.h"
#include "../../components/DeadComponent.h"

Entity &OrcFactory::getEnemy(const int level)
{
	Entity& orc = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	auto& transformComponent = orc.addComponent<TransformComponent>(-1, -1, 49, 64, 1);
	auto& spriteComponent = orc.addComponent<SpriteComponent>("orc", 9, 9, 3);
	orc.addComponent<HealthBarComponent>();
	orc.addComponent<EnemyMovementComponent>();
	orc.addComponent<AIComponent>();
	orc.addComponent<CollisionComponent>("orc");
	orc.addComponent<DeadComponent>();

	transformComponent.speed = 2;

	const double random = RandomGenerator{}.getRandomDouble(1, 50);

	double randMutator = (random + 50) / 100;

	int hp = 100 * level * randMutator,
		maxHp = 100 * level * randMutator,
		atkMin = 2 * level * randMutator,
		atkMax = 4 * level * randMutator,
		df = 1;

	orc.addComponent<StatsComponent>(hp, maxHp, atkMin, atkMax, df, level);

	return orc;
}

Entity & OrcFactory::getEnemy(const int level, const int spawnerId)
{
	auto& enemy = getEnemy(level);
	enemy.addComponent<SpawnedComponent>(spawnerId);
	return enemy;
}