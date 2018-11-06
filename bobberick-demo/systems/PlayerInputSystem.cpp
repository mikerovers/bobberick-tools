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

		bool left = inputHandler.isKeyDown(SDL_SCANCODE_LEFT) || inputHandler.isKeyDown(SDL_SCANCODE_A),
			right = inputHandler.isKeyDown(SDL_SCANCODE_RIGHT) || inputHandler.isKeyDown(SDL_SCANCODE_D),
			up = inputHandler.isKeyDown(SDL_SCANCODE_UP) || inputHandler.isKeyDown(SDL_SCANCODE_W),
			down = inputHandler.isKeyDown(SDL_SCANCODE_DOWN) || inputHandler.isKeyDown(SDL_SCANCODE_S);

		if (left || right || up || down) {
			sprite.moving = true;
			if (!ServiceManager::Instance()->getService<SoundManager>().isSoundPlaying()) {
				ServiceManager::Instance()->getService<SoundManager>().playSound("footsteps", 0);
			}
			if ((left && right) || (!left && !right)) {
				transform.velocity.setX(0);
			}
			else if (right) {
				transform.velocity.setX(1);
			}
			else if (left) {
				transform.velocity.setX(-1);
			}

			if ((up && down) || (!up && !down)) {
				transform.velocity.setY(0);
			}
			else if (up) {
				transform.velocity.setY(-1);
			}
			else if (down) {
				transform.velocity.setY(1);
			}
		}
		else {
			sprite.moving = false;
			transform.velocity.setY(0);
			transform.velocity.setX(0);
			ServiceManager::Instance()->getService<SoundManager>().stopSound();
		}

		sprite.flip = left ? true : false;
			   
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
				ServiceManager::Instance()->getService<SoundManager>().playSound("arrow", 0);
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
