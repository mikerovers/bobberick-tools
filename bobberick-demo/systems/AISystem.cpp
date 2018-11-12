#include "AISystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/SoundManager.h"
#include "../../bobberick-framework/src/services/InputHandler.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../bobberick-framework/src/entity/components/TextComponent.h"
#include "../../bobberick-framework/src/entity/components/ShootComponent.h"
#include "../../bobberick-framework/src/entity/components/RectangleComponent.h"
#include "../../bobberick-demo/components/AIComponent.h"
#include "../../bobberick-demo/components/BulletMovementComponent.h"
#include "../../bobberick-demo/components/PlayerStatsComponent.h"
#include "../../bobberick-demo/components/HealthBarComponent.h"

#include <thread>
#include <chrono>
AISystem::AISystem(EntityManager &entityManager) : System(entityManager)
{

}

void AISystem::init() {
	for (auto& entity : entityManager.getAllEntitiesWithComponent<AIComponent>()) {
		auto& healthBar = entity->getComponent<HealthBarComponent>();
		auto& transform = entity->getComponent<TransformComponent>();
		if (entity->hasComponent<HealthBarComponent>()) {
			int width = transform.width / 2;
			healthBar.outerBox = ServiceManager::Instance()->getService<EntityManager>().addEntity();
			healthBar.innerBox = ServiceManager::Instance()->getService<EntityManager>().addEntity();
			healthBar.healthBox = ServiceManager::Instance()->getService<EntityManager>().addEntity();

			healthBar.outerBox->addComponent<TransformComponent>(-1, -1, 12, width + 2, 1);
			healthBar.outerBox->addComponent<RectangleComponent>(0, 0, 0, false);

			healthBar.innerBox->addComponent<TransformComponent>(-1, -1, 10, width, 1);
			healthBar.innerBox->addComponent<RectangleComponent>(128, 128, 128, true);

			healthBar.healthBox->addComponent<TransformComponent>(-1, -1, 10, width, 1);
			healthBar.healthBox->addComponent<RectangleComponent>(255, 0, 0, true);
		}
	}
}


void AISystem::update()
{
	int channelCounter = 0;
	for (auto& entity : entityManager.getAllEntitiesWithComponent<AIComponent>()) {
		auto& transform = entity->getComponent<TransformComponent>();

		// todo
		// check which directions are clear
		// adjust possible movements accordingly 
		// delete properly
		// make shooting dependant on enemy type (cast/shoot/change of sprite)
		// make smoother

		executeShoot(entity, channelCounter);
		applyHealthBar(entity);
		applyMovement(entity);

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

void AISystem::executeShoot(std::shared_ptr<Entity> entity, int &channelCounter) {
	if (entity->hasComponent<ShootComponent>()) {
		auto& shoot = entity->getComponent<ShootComponent>();
		if (shoot.canShoot()) {
			auto& transform = entity->getComponent<TransformComponent>();
			auto& sprite = entity->getComponent<SpriteComponent>();
			auto& collision = entity->getComponent<CollisionComponent>();

			auto& stats = entity->getComponent<StatsComponent>();
			auto& healthBar = entity->getComponent<HealthBarComponent>();

			double enemyX = transform.position.getX();
			double enemyY = transform.position.getY();

			for (auto& player : entityManager.getAllEntitiesWithComponent<PlayerStatsComponent>()) {
				channelCounter++;
				auto& playerTransform = player->getComponent<TransformComponent>();

				double enemyXCenter = enemyX + transform.width / 2;
				double enemyYCenter = enemyY + transform.height / 2;

				double angleX = playerTransform.position.getX() - enemyXCenter;
				double angleY = playerTransform.position.getY() - enemyYCenter;

				if ((angleX < 300 && angleX > -300) && (angleY < 300 && angleY > -300)) {
					if (angleX < 0) {
						sprite.flip = true;
					}
					else if (angleX > 0) {
						sprite.flip = false;
					}

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
					projectile->addComponent<SpriteComponent>("assets/image/projectiles/bolt.png", "bolt");
					shoot.setShootTimer(980);

				}
				else {
					sprite.changeTexture("fire_wizard");
				}
			}
		}
	}
}

void AISystem::applyHealthBar(std::shared_ptr<Entity> entity) {
	auto& transform = entity->getComponent<TransformComponent>();
	auto& stats = entity->getComponent<StatsComponent>();
	auto& healthBar = entity->getComponent<HealthBarComponent>();

	double enemyX = transform.position.getX();
	double enemyY = transform.position.getY();

	if (entity->hasComponent<HealthBarComponent>()) {
		auto& outBox = healthBar.outerBox->getComponent<TransformComponent>();
		auto& inBox = healthBar.innerBox->getComponent<TransformComponent>();
		auto& healBox = healthBar.healthBox->getComponent<TransformComponent>();

		if (stats.getHP() != stats.getHPmax()) {
			outBox.visible = true;
			inBox.visible = true;
			healBox.visible = true;

			auto& x = healthBar.outerBox;
			outBox.position.setY(enemyY - 10);
			outBox.position.setX(enemyX + 15);

			inBox.position.setY(enemyY - 9);
			inBox.position.setX(enemyX + 16);

			healBox.position.setY(enemyY - 9);
			healBox.position.setX(enemyX + 16);

			double healthWidth = ((double)stats.getHP() / (double)stats.getHPmax()) * 30;
			healthBar.healthBox->getComponent<TransformComponent>().width = healthWidth;

		}
		else {
			outBox.visible = false;
			inBox.visible = false;
			healBox.visible = false;
		}
	}
}

void AISystem::applyMovement(std::shared_ptr<Entity> entity) {
	auto& transform = entity->getComponent<TransformComponent>();
	auto& sprite = entity->getComponent<SpriteComponent>();


	double speed = 0.2 * transform.speed;
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
}

std::string AISystem::addSpaces(std::string string, const int goalChars, const bool leading) {
	std::string spaces = "";
	for (int i = string.length(); i < goalChars; i++) {
		spaces += " ";
	}
	if (leading) {
		return spaces + string;
	}
	else {
		return string + spaces;
	}
}