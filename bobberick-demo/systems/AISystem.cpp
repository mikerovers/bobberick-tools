#include "AISystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/SoundManager.h"
#include "../../bobberick-framework/src/services/InputHandler.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../bobberick-framework/src/entity/components/ShootComponent.h"
#include "../../bobberick-demo/components/AIComponent.h"
#include "../../bobberick-demo/components/BulletMovementComponent.h"
#include "../../bobberick-demo/components/PlayerStatsComponent.h"

#include <thread>
#include <chrono>
AISystem::AISystem(EntityManager &entityManager) : System(entityManager)
{

}

void AISystem::update()
{
	int channelCounter = 0;
	for (auto& entity : entityManager.getAllEntitiesWithComponent<AIComponent>()) {
		auto& transform = entity->getComponent<TransformComponent>();
		auto& sprite = entity->getComponent<SpriteComponent>();
		auto& collision = entity->getComponent<CollisionComponent>();
		auto& shoot = entity->getComponent<ShootComponent>();
		// check which directions are clear
		// adjust possible movements accordingly 


		double speed = 0.2 * transform.speed;

		if (entity->hasComponent<ShootComponent>()) {
			if (shoot.canShoot()) {

				for (auto& player : entityManager.getAllEntitiesWithComponent<PlayerStatsComponent>()) {
					channelCounter++;
					auto& playerTransform = player->getComponent<TransformComponent>();
					double enemyX = transform.position.getX();
					double enemyY = transform.position.getY();

					double enemyXCenter = enemyX + transform.width / 2;
					double enemyYCenter = enemyY + transform.height / 2;

					double angleX = playerTransform.position.getX() - enemyXCenter;
					double angleY = playerTransform.position.getY() - enemyYCenter;

					if ((angleX < 300 && angleX > -300) && (angleY < 300 && angleY > -300)) {
						if (angleX < 300) {
							sprite.flip = true;
						}
						else if (angleX > -300) {
							sprite.flip = false;
						}
						// TODO change flip wether the player is in front or back from the enemy
						float vectorLength = sqrt(angleX*angleX + angleY * angleY);
						float dx = angleX / vectorLength;
						float dy = angleY / vectorLength;

						std::shared_ptr<Entity> projectile = ServiceManager::Instance()->getService<EntityManager>().addEntity();
						projectile->addComponent<BulletMovementComponent>();
						auto& projectileTransform = projectile->addComponent<TransformComponent>(enemyXCenter + (dx * 25), enemyYCenter + (dy * 25), 10, 10, 1);
						projectileTransform.velocity.setX(dx);
						projectileTransform.velocity.setY(dy);

						sprite.changeTexture("fire_wizard_casting"); // change to set entity to casting state (and change sprite accordingly)

						transform.velocity.setX(0);
						transform.velocity.setY(0);

						ServiceManager::Instance()->getService<SoundManager>().playSound(channelCounter, "bolt", 0);
						projectile->addComponent<SpriteComponent>("assets/image/bolt.png", "bolt");
						shoot.setShootTimer(980);

					}
					else {
						sprite.changeTexture("fire_wizard");
					}
				}
			}

		}

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
