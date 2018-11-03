#include "BulletSystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
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
		auto& inputHandler = ServiceManager::Instance()->getService<InputHandler>();

		transform.update();
	}
}
