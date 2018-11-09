#include "FireWizardFactory.h"
#include "../../../bobberick-framework/src/services/ServiceManager.h"
#include "../../../bobberick-framework/src/entity/EntityManager.h"
#include "../../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../../components/StatsComponent.h"
#include "../../components/AIComponent.h"

Entity * FireWizardFactory::getEnemy(const int level)
{
	std::shared_ptr<Entity> fireWizard = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	auto& transformComponent = fireWizard->addComponent<TransformComponent>(-1, -1, 59, 54, 1);
	auto& spriteComponent = fireWizard->addComponent<SpriteComponent>("assets/image/enemies/fire_wizard.png", "fireWizard", 5, 5, 8);
	fireWizard->addComponent<AIComponent>();
	fireWizard->addComponent<CollisionComponent>("fireWizard");

	transformComponent.speed = 1;

	int randMutator = (rand() % 50) / 100;

	int hp = 100 * level * (randMutator + 50),
		maxHp = 100 * level * (randMutator + 50),
		atkMin = 2 * level * (randMutator + 50),
		atkMax = 4 * level * (randMutator + 50),
		df = 1;

	fireWizard->addComponent<StatsComponent>(hp, maxHp, atkMin, atkMax, df);

	return fireWizard.get();
}
