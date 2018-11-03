#include "PlayerInputSystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/services/InputHandler.h"
#include "../components/PlayerMovementComponent.h"
#include "../components/BulletMovementComponent.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
PlayerInputSystem::PlayerInputSystem(EntityManager &entityManager) : System(entityManager)
{

}

void PlayerInputSystem::update()
{
	for (auto& entity : entityManager.getAllEntitiesWithComponent<PlayerMovementComponent>()) {
		auto& transform = entity->getComponent<TransformComponent>();
		auto& inputHandler = ServiceManager::Instance()->getService<InputHandler>();

		//std::cout << "Joystick x: " << inputHandler.xvalue(0, 1) << std::endl;
		//std::cout << "Joystick y: " << inputHandler.xvalue(0, 1) << std::endl;


		if (inputHandler.isKeyDown(SDL_SCANCODE_RIGHT) || inputHandler.isKeyDown(SDL_SCANCODE_D))
		{
			transform.velocity.setX(1);
		}
		else if (inputHandler.isKeyDown(SDL_SCANCODE_LEFT) || inputHandler.isKeyDown(SDL_SCANCODE_A)) {
			transform.velocity.setX(-1);
		}
		else {
			transform.velocity.setX(0);
		}
		if (inputHandler.isKeyDown(SDL_SCANCODE_UP) || inputHandler.isKeyDown(SDL_SCANCODE_W))
		{
			transform.velocity.setY(-1);
		}
		else if (inputHandler.isKeyDown(SDL_SCANCODE_DOWN) || inputHandler.isKeyDown(SDL_SCANCODE_S))
		{
			transform.velocity.setY(1);
		}
		else
		{
			transform.velocity.setY(0);
		}

		if (inputHandler.getMouseButtonState(LEFT)) { // shoot
			std::cout << "x: " << inputHandler.getMousePosition()->getX() << " y:" << inputHandler.getMousePosition()->getY();
			std::shared_ptr<Entity> bullet = ServiceManager::Instance()->getService<EntityManager>().addEntity();
			auto& bulletTransform = bullet->addComponent<TransformComponent>();
			//bullet->addComponent<SpriteComponent>("assets/image/Simple_Bullet.bmp", "bullet");
			bullet->addComponent<SpriteComponent>("assets/teamcpp_logo.bmp", "bullet");
			bullet->addComponent<BulletMovementComponent>();
			double angle = std::atan2(inputHandler.getMousePosition()->getX() - transform.position.getX(), inputHandler.getMousePosition()->getY() - transform.position.getY());
			double xVel = cos(angle);
			double yVel = sin(angle);

			double angleX = inputHandler.getMousePosition()->getX() - transform.position.getX();
			double angleY = inputHandler.getMousePosition()->getY() - transform.position.getY();

			float vectorLength = sqrt(angleX*angleX + angleY * angleY);
			float dx = angleX / vectorLength;
			float dy = angleY / vectorLength;

			bulletTransform.position.setX(inputHandler.getMousePosition()->getX());
			bulletTransform.position.setY(inputHandler.getMousePosition()->getY());

			bulletTransform.height = 1;
			bulletTransform.width = 1;
			bulletTransform.velocity.setX(dx);
			bulletTransform.velocity.setY(dy);

		}







		//transform.velocity.setX(inputHandler.xvalue(0, 1));

		//transform.velocity.setY(inputHandler.yvalue(0, 1));

		transform.update();
	}
}
