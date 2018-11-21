#include "EndBossFactory.h"
#include "../../../bobberick-framework/src/services/ServiceManager.h"
#include "../../../bobberick-framework/src/entity/EntityManager.h"
#include "../../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../../../bobberick-framework/src/entity/components/TimerComponent.h"
#include "../../../bobberick-framework/src/util/RandomGenerator.h"
#include "../../components/StatsComponent.h"
#include "../../components/HealthBarComponent.h"
#include "../../components/AIComponent.h"
#include "../../components/EndBossComponent.h"
#include "../../components/SpawnMinionsSpellComponent.h"
#include "../../components/EnemyMovementComponent.h"
#include "../../components/ShootComponent.h"
#include "../../components/SpawnedComponent.h"

Entity & EndBossFactory::getEnemy(const int level)
{
	auto& endBoss = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	auto& transformComponent = endBoss.addComponent<TransformComponent>(-1, -1, 91, 128, 1);
	auto& spriteComponent = endBoss.addComponent<SpriteComponent>("endBoss", 7, 7, 12);
	//spriteComponent.addTexture("assets/image/enemies/fire_wizard_casting.png", "fire_wizard_casting");
	auto* collisionComponent = new HealthBarComponent();
	endBoss.addExistingComponent<HealthBarComponent>(collisionComponent);
	//endBoss.addComponent<HealthBarComponent>();
	endBoss.addComponent<EnemyMovementComponent>();
	endBoss.addComponent<AIComponent>();
	endBoss.addComponent<TimerComponent>();
	endBoss.addComponent<SpawnMinionsSpellComponent>();
	//endBoss.addComponent<ShootComponent>();
	endBoss.addComponent<CollisionComponent>("endBoss");
	endBoss.addComponent<EndBossComponent>();

	transformComponent.speed = 1;

	const double random = RandomGenerator{}.getRandomDouble(1, 50);
	double randMutator = (random + 50) / 100;

	int hp = 500 * level * randMutator,
		maxHp = 500 * level * randMutator,
		atkMin = 40 * level * randMutator,
		atkMax = 60 * level * randMutator,
		df = 1;

	endBoss.addComponent<StatsComponent>(hp, maxHp, atkMin, atkMax, df, level);

	return endBoss;
}

Entity & EndBossFactory::getEnemy(const int level, const int spawnerId)
{
	auto& enemy = getEnemy(level);
	enemy.addComponent<SpawnedComponent>(spawnerId);
	return enemy;
}