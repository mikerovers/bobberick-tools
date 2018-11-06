#include "PlayerInputSystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/services/InputHandler.h"
#include "../../bobberick-framework/src/SoundManager.h"
#include "../components/PlayerMovementComponent.h"
#include "../components/BulletMovementComponent.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../bobberick-framework/src/entity/components/PlayerShootComponent.h"
PlayerInputSystem::PlayerInputSystem(EntityManager &entityManager) : System(entityManager)
{

}

void PlayerInputSystem::update()
{
	for (auto& entity : entityManager.getAllEntitiesWithComponent<PlayerMovementComponent>()) {
		auto& transform = entity->getComponent<TransformComponent>();
		auto& sprite = entity->getComponent<SpriteComponent>();
		auto& playerShoot = entity->getComponent<PlayerShootComponent>();
		auto& inputHandler = ServiceManager::Instance()->getService<InputHandler>();

		//std::cout << "Joystick x: " << inputHandler.xvalue(0, 1) << std::endl;
		//std::cout << "Joystick y: " << inputHandler.xvalue(0, 1) << std::endl;

		bool notGoingX = true;

		if (inputHandler.isKeyDown(SDL_SCANCODE_RIGHT) || inputHandler.isKeyDown(SDL_SCANCODE_D))
		{
			transform.velocity.setX(1);
			sprite.moving = true;
			sprite.flip = false;
			notGoingX = false;
		}
		else if (inputHandler.isKeyDown(SDL_SCANCODE_LEFT) || inputHandler.isKeyDown(SDL_SCANCODE_A)) {
			transform.velocity.setX(-1);
			sprite.moving = true;
			sprite.flip = true;
			notGoingX = false;
		}
		else {
			transform.velocity.setX(0);
		}
		if (inputHandler.isKeyDown(SDL_SCANCODE_UP) || inputHandler.isKeyDown(SDL_SCANCODE_W))
		{
			transform.velocity.setY(-1);
			sprite.moving = true;
		}
		else if (inputHandler.isKeyDown(SDL_SCANCODE_DOWN) || inputHandler.isKeyDown(SDL_SCANCODE_S))
		{
			transform.velocity.setY(1);
			sprite.moving = true;
		}
		else
		{
			if (notGoingX) {
				sprite.moving = false;
			}
			transform.velocity.setY(0);
		}

		if (inputHandler.getMouseButtonState(LEFT)) { // shoot
			if (playerShoot.canShoot()) {
				double playerX = transform.position.getX();
				double playerY = transform.position.getY();

				double playerXCenter = playerX + transform.width / 2;
				double playerYCenter = playerY + transform.height / 2;

				double angleX = inputHandler.getMousePosition()->getX() - playerXCenter;
				double angleY = inputHandler.getMousePosition()->getY() - playerYCenter;

				float vectorLength = sqrt(angleX*angleX + angleY * angleY);
				float dx = angleX / vectorLength;
				float dy = angleY / vectorLength;

				std::shared_ptr<Entity> bullet = ServiceManager::Instance()->getService<EntityManager>().addEntity();
				ServiceManager::Instance()->getService<SoundManager>().playSound("1", 0);
				auto& bulletTransform = bullet->addComponent<TransformComponent>(playerXCenter + (dx * 100), playerYCenter + (dy * 100), 10, 10, 1);
				bullet->addComponent<SpriteComponent>("assets/image/bullet_ball_grey.png", "bullet");
				bullet->addComponent<BulletMovementComponent>();

				bulletTransform.velocity.setX(dx);
				bulletTransform.velocity.setY(dy);
				playerShoot.setShootTimer(500);
			}
		}

		transform.update();
	}
}
