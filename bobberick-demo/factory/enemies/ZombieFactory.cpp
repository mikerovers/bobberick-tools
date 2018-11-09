#include "ZombieFactory.h"
#include "../../../bobberick-framework/src/services/ServiceManager.h"
#include "../../../bobberick-framework/src/entity/EntityManager.h"
#include "../../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../../components/StatsComponent.h"
#include "../../components/HealthBarComponent.h"
#include "../../components/AIComponent.h"

Entity * ZombieFactory::getEnemy(const int level)
{
	std::shared_ptr<Entity> zombie = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	auto& transformComponent = zombie->addComponent<TransformComponent>(-1, -1, 51, 51, 1);
	auto& spriteComponent = zombie->addComponent<SpriteComponent>("assets/image/enemies/zombie.png", "zombie", 6, 4, 10);
	zombie->addComponent<HealthBarComponent>();
	zombie->addComponent<AIComponent>();
	zombie->addComponent<CollisionComponent>("zombie");

	transformComponent.speed = 0.8;

	double random = (rand() % 50);
	double randMutator = (random + 50) / 100;

	int hp = 175 * level * (randMutator),
		maxHp = 200 * level * (randMutator),
		atkMin = 1 * level * (randMutator),
		atkMax = 3 * level * (randMutator),
		df = 1;

	zombie->addComponent<StatsComponent>(hp, maxHp, atkMin, atkMax, df);

	return zombie.get();
}
