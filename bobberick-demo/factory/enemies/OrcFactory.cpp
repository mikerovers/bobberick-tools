#include "OrcFactory.h"
#include "../../../bobberick-framework/src/services/ServiceManager.h"
#include "../../../bobberick-framework/src/entity/EntityManager.h"
#include "../../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../../components/StatsComponent.h"
#include "../../components/AIComponent.h"

Entity * OrcFactory::getEnemy(const int level)
{
	std::shared_ptr<Entity> orc = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	auto& transformComponent = orc->addComponent<TransformComponent>(-1, -1, 49, 64, 1);
	auto& spriteComponent = orc->addComponent<SpriteComponent>("assets/image/enemies/orc_piratess.png", "orc", 9, 9, 3);
	orc->addComponent<AIComponent>();
	orc->addComponent<CollisionComponent>("orc");

	transformComponent.speed = 2;

	int randMutator = (rand() % 50) / 100;

	int hp = 100 * level * (randMutator + 50),
		maxHp = 100 * level * (randMutator + 50),
		atkMin = 2 * level * (randMutator + 50),
		atkMax = 4 * level * (randMutator + 50),
		df = 1;

	orc->addComponent<StatsComponent>(hp, maxHp, atkMin, atkMax, df);

	return orc.get();
}
