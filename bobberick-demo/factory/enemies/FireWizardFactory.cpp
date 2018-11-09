#include "FireWizardFactory.h"
#include "../../../bobberick-framework/src/services/ServiceManager.h"
#include "../../../bobberick-framework/src/entity/EntityManager.h"
#include "../../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../../../bobberick-framework/src/entity/components/ShootComponent.h"
#include "../../components/StatsComponent.h"
#include "../../components/HealthBarComponent.h"
#include "../../components/AIComponent.h"

Entity * FireWizardFactory::getEnemy(const int level)
{
	std::shared_ptr<Entity> fireWizard = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	auto& transformComponent = fireWizard->addComponent<TransformComponent>(-1, -1, 59, 54, 1);
	auto& spriteComponent = fireWizard->addComponent<SpriteComponent>("assets/image/enemies/fire_wizard.png", "fire_wizard", 5, 5, 12);
	spriteComponent.addTexture("assets/image/enemies/fire_wizard_casting.png", "fire_wizard_casting");
	fireWizard->addComponent<HealthBarComponent>();
	fireWizard->addComponent<AIComponent>();
	fireWizard->addComponent<ShootComponent>();
	fireWizard->addComponent<CollisionComponent>("fireWizard");

	transformComponent.speed = 1.5;

	int randMutator = (rand() % 50) / 100;

	int hp = 100 * level * (randMutator + 50),
		maxHp = 100 * level * (randMutator + 50),
		atkMin = 2 * level * (randMutator + 50),
		atkMax = 4 * level * (randMutator + 50),
		df = 1;

	fireWizard->addComponent<StatsComponent>(hp, maxHp, atkMin, atkMax, df);

	return fireWizard.get();
}
