#include "BulletSystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/services/SettingsService.h"
#include "../../bobberick-framework/src/services/InputHandler.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../bobberick-demo/components/BulletMovementComponent.h"
BulletSystem::BulletSystem(EntityManager &entityManager) : System(entityManager)
{

}

void BulletSystem::update()
{
	for (auto& entity : entityManager.getAllEntitiesWithComponent<BulletMovementComponent>()) {
		auto& transform = entity->getComponent<TransformComponent>();

		const int maxWidth = ServiceManager::Instance()->getService<SettingsService>().gameWidth;
		const int maxHeight = ServiceManager::Instance()->getService<SettingsService>().gameHeight;
		//std::cout << transform.position.getX() << "\n";
		if (transform.position.x > maxHeight || transform.position.y > maxWidth || transform.position.x < 0 || transform.position.y < 0) {

			entity->destroy();
			//delete &entity;
			//entity.reset();
			//entity = nullptr;

		}
		else {
			transform.update();

		}
	}
}
