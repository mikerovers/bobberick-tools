#include "AISystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/services/InputHandler.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../bobberick-demo/components/AIComponent.h"
AISystem::AISystem(EntityManager &entityManager) : System(entityManager)
{

}

void AISystem::update()
{
	for (auto& entity : entityManager.getAllEntitiesWithComponent<AIComponent>()) {
		auto& transform = entity->getComponent<TransformComponent>();
		auto& sprite = entity->getComponent<SpriteComponent>();

		double const speed = 0.2 * transform.speed;

		int move = rand() % 60;
		if (move == 0) {
			int v1 = rand() % 9;
			switch (v1) {
			case 0: {
				transform.velocity.setX(speed);
				transform.velocity.setY(0);
				sprite.flip = false;
			}break;
			case 1: {
				transform.velocity.setX(-speed);
				transform.velocity.setY(0);
				sprite.flip = true;
			}break;
			case 2: {
				transform.velocity.setY(speed);
				transform.velocity.setX(0);
			}break;
			case 3: {
				transform.velocity.setY(-speed);
				transform.velocity.setX(0);
			}break;
			case 4: {
				transform.velocity.setX(speed);
				transform.velocity.setY(speed);
				sprite.flip = false;
			}break;
			case 5: {
				transform.velocity.setX(-speed);
				transform.velocity.setY(-speed);
				sprite.flip = true;
			}break;
			case 6: {
				transform.velocity.setX(-speed);
				transform.velocity.setY(speed);
				sprite.flip = true;
			}break;
			case 7: {
				transform.velocity.setX(speed);
				transform.velocity.setY(-speed);
				sprite.flip = false;
			}break;
			case 8: {
				transform.velocity.setX(0);
				transform.velocity.setY(0);
				sprite.flip = false;
			}break;
			}
		}
		
		sprite.moving = (transform.velocity.getX() == 0 && transform.velocity.getY() == 0) ? false : true;

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
