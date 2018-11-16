#include "ChickenFactory.h"
#include "../../../bobberick-framework/src/services/ServiceManager.h"
#include "../../../bobberick-framework/src/entity/EntityManager.h"
#include "../../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../../components/StatsComponent.h"
#include "../../components/HealthBarComponent.h"
#include "../../components/AIComponent.h"

Entity& ChickenFactory::getEnemy(const int level)
{
	Entity& chicken = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	auto& transformComponent = chicken.addComponent<TransformComponent>(-1, -1, 25, 24, 1);

	chicken.addComponent<SpriteComponent>("assets/image/enemies/chicken_white.png",
	                                      "chicken", 3, 2, 9);

	chicken.addComponent<HealthBarComponent>();
	chicken.addComponent<AIComponent>();
	chicken.addComponent<CollisionComponent>("chicken");

	transformComponent.speed = 2;

	const double random = (rand() % 50);
	const double randMutator = (random + 50) / 100;

	int hp = 10 * level * (randMutator),
	    maxHp = 10 * level * (randMutator),
	    atkMin = 0 * level * (randMutator),
	    atkMax = 0 * level * (randMutator),
	    df = 0;

	chicken.addComponent<StatsComponent>(hp, maxHp, atkMin, atkMax, df);

	return chicken;
}
