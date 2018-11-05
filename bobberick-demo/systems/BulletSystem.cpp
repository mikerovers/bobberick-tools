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

		double maxWidth = 640.00; //change this
		double maxHeight = 480.00; //change this
		//std::cout << transform.position.getX() << "\n";
		if (transform.position.getX() > 640 || transform.position.getY() > 480) {

			//entity->destroy();
			//delete &entity;
			//entity.reset();
			//entity = nullptr;

		}
		else {
			transform.update();

		}
	}
}
