#include "OrcFactory.h"
#include "../../../bobberick-framework/src/services/ServiceManager.h"
#include "../../../bobberick-framework/src/entity/EntityManager.h"
#include "../../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../../components/StatsComponent.h"
#include "../../components/HealthBarComponent.h"
#include "../../components/AIComponent.h"

Entity * OrcFactory::getEnemy(const int level)
{
	Entity* orc = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	auto& transformComponent = orc->addComponent<TransformComponent>(-1, -1, 49, 64, 1);
	auto& spriteComponent = orc->addComponent<SpriteComponent>("assets/image/enemies/orc_piratess.png", "orc", 9, 9, 3);
	orc->addComponent<HealthBarComponent>();
	orc->addComponent<AIComponent>();
	orc->addComponent<CollisionComponent>("orc");

	transformComponent.speed = 2;

	double random = (rand() % 50);
	double randMutator = (random + 50) / 100;

	const int const hp = 100 * level * (randMutator),
		const maxHp = 100 * level * (randMutator),
		const atkMin = 2 * level * (randMutator),
		const atkMax = 4 * level * (randMutator),
		const df = 1;

	orc->addComponent<StatsComponent>(hp, maxHp, atkMin, atkMax, df);

	return orc;
}
