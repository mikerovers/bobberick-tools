#include "EndBossFactory.h"
#include "../../../bobberick-framework/src/services/ServiceManager.h"
#include "../../../bobberick-framework/src/entity/EntityManager.h"
#include "../../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../../../bobberick-framework/src/entity/components/ShootComponent.h"
#include "../../../bobberick-framework/src/entity/components/TimerComponent.h"
#include "../../components/StatsComponent.h"
#include "../../components/HealthBarComponent.h"
#include "../../components/AIComponent.h"
#include "../../components/SpawnMinionsSpellComponent.h"

Entity & EndBossFactory::getEnemy(const int level)
{
	auto& endBoss = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	auto& transformComponent = endBoss.addComponent<TransformComponent>(-1, -1, 91, 128, 1);
	auto& spriteComponent = endBoss.addComponent<SpriteComponent>("assets/image/enemies/end_boss.png", "end_boss", 7, 7, 12);
	//spriteComponent.addTexture("assets/image/enemies/fire_wizard_casting.png", "fire_wizard_casting");
	auto* collisionComponent = new HealthBarComponent();
	endBoss.addExistingComponent<HealthBarComponent>(collisionComponent);
	//endBoss.addComponent<HealthBarComponent>();
	endBoss.addComponent<AIComponent>();
	endBoss.addComponent<TimerComponent>();
	endBoss.addComponent<SpawnMinionsSpellComponent>();
	//endBoss.addComponent<ShootComponent>();
	endBoss.addComponent<CollisionComponent>("endBoss");

	transformComponent.speed = 1;

	double random = (rand() % 50);
	double randMutator = (random + 50) / 100;

	int hp = 500 * level * (randMutator),
		maxHp = 500 * level * (randMutator),
		atkMin = 40 * level * (randMutator),
		atkMax = 60 * level * (randMutator),
		df = 1;

	endBoss.addComponent<StatsComponent>(hp, maxHp, atkMin, atkMax, df);

	return endBoss;
}