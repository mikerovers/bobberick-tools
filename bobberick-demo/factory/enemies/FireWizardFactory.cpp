#include "FireWizardFactory.h"
#include "../../../bobberick-framework/src/services/ServiceManager.h"
#include "../../../bobberick-framework/src/entity/EntityManager.h"
#include "../../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../../bobberick-framework/src/entity/components/TimerComponent.h"
#include "../../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../../../bobberick-framework/src/util/RandomGenerator.h"
#include "../../components/StatsComponent.h"
#include "../../components/HealthBarComponent.h"
#include "../../components/AIComponent.h"
#include "../../components/EnemyMovementComponent.h"
#include "../../components/SpawnedComponent.h"
#include "../../components/ShootComponent.h"

Entity & FireWizardFactory::getEnemy(const int level)
{
	auto& fireWizard = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	auto& transformComponent = fireWizard.addComponent<TransformComponent>(-1, -1, 59, 54, 1);
	fireWizard.addComponent<HealthBarComponent>();
	fireWizard.addComponent<EnemyMovementComponent>();
	fireWizard.addComponent<AIComponent>();
	fireWizard.addComponent<ShootComponent>();
	fireWizard.addComponent<TimerComponent>();
	fireWizard.addComponent<CollisionComponent>("fireWizard");
	if (level < 6) {
		auto& spriteComponent = fireWizard.addComponent<SpriteComponent>("fireWizard", 5, 5, 12);
	}
	else if (level < 9) {
		auto& spriteComponent = fireWizard.addComponent<SpriteComponent>("iceWizard", 5, 5, 12);
	}
	else {
		auto& spriteComponent = fireWizard.addComponent<SpriteComponent>("metalWizard", 5, 5, 12);
	}

	transformComponent.speed = 1.5;

	const double random = RandomGenerator{}.getRandomDouble(1, 50);
	double randMutator = (random + 50) / 100;

	int hp = 50 * level * randMutator,
		maxHp = 50 * level * randMutator,
		atkMin = 4 * level * randMutator,
		atkMax = 6 * level * randMutator,
		df = 1;

	fireWizard.addComponent<StatsComponent>(hp, maxHp, atkMin, atkMax, df, level);

	return fireWizard;
}

Entity & FireWizardFactory::getEnemy(const int level, const int spawnerId)
{ 
	auto& enemy = getEnemy(level);
	enemy.addComponent<SpawnedComponent>(spawnerId);
	return enemy;
}