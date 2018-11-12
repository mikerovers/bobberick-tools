#include "BulletSystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/services/InputHandler.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../bobberick-demo/components/BulletComponent.h"
#include "../../bobberick-demo/components/PlayerStatsComponent.h"
BulletSystem::BulletSystem(EntityManager &entityManager) : System(entityManager)
{

}

void BulletSystem::update()
{
	for (auto& entity : entityManager.getAllEntitiesWithComponent<BulletComponent>()) {
		auto& transform = entity->getComponent<TransformComponent>();
		auto& collision = entity->getComponent<CollisionComponent>();

		auto& collisionComponent = entity->getComponent<CollisionComponent>();
		collisionComponent.collider->x = transform.position.getX();
		collisionComponent.collider->y = transform.position.getY();
		collisionComponent.collider->w = transform.width;
		collisionComponent.collider->h = transform.height;

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
