#include "PlayerInputSystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/services/SettingsService.h"
#include "../../bobberick-framework/src/services/InputHandler.h"
#include "../../bobberick-framework/src/services/SoundManager.h"
#include "../services/PlayerStatsService.h"
#include "../components/PlayerMovementComponent.h"
#include "../components/BulletMovementComponent.h"
#include "../components/ShootComponent.h"
#include "../components/DamageComponent.h"
#include "../components/PlayerComponent.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../bobberick-framework/src/entity/components/TimerComponent.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../../bobberick-framework/src/services/FrameHandler.h"
#include "../../bobberick-framework/src/StateMachine.h"
#include "../state/StateFactory.h"
#include "../components/InventoryComponent.h"
#include "../components/InventorySlotComponent.h"

PlayerInputSystem::PlayerInputSystem(EntityManager& entityManager) : System(entityManager)
{
}

void PlayerInputSystem::update()
{
	for (auto& entity : entityManager.getAllEntitiesWithComponent<PlayerMovementComponent>())
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			continue;
		}

		auto& transform = entity->getComponent<TransformComponent>();

		handleKeyInput(entity);
		handleMouseInput(entity);

		transform.update();
	}
}

void PlayerInputSystem::handleKeyInput(Entity* entity)
{
	if (skipForRepeat > 600) {
		skipForRepeat = 0;
	}
	else {
		skipForRepeat++;
	}
	auto& transform = entity->getComponent<TransformComponent>();
	auto& sprite = entity->getComponent<SpriteComponent>();
	auto& inputHandler = ServiceManager::Instance()->getService<InputHandler>();
	auto& playerStats = ServiceManager::Instance()->getService<PlayerStatsService>();

	double speedModifier = playerStats.getSHDactive() ? 0.5 : 1;

	if (inputHandler.isKeyDown(SDL_SCANCODE_SPACE))
	{
		if (!playerStats.getSHDactive())
		{
			playerStats.toggleShield();
		}
	}

	bool left = inputHandler.isKeyDown(SDL_SCANCODE_LEFT) || inputHandler.isKeyDown(SDL_SCANCODE_A),
	     right = inputHandler.isKeyDown(SDL_SCANCODE_RIGHT) || inputHandler.isKeyDown(SDL_SCANCODE_D),
	     up = inputHandler.isKeyDown(SDL_SCANCODE_UP) || inputHandler.isKeyDown(SDL_SCANCODE_W),
	     down = inputHandler.isKeyDown(SDL_SCANCODE_DOWN) || inputHandler.isKeyDown(SDL_SCANCODE_S),
	     z = inputHandler.isKeyDown(SDL_SCANCODE_Z),
	     x = inputHandler.isKeyDown(SDL_SCANCODE_X),
	     c = inputHandler.isKeyDown(SDL_SCANCODE_C),
		 ret = inputHandler.isKeyDown(SDL_SCANCODE_RETURN) || inputHandler.isKeyDown(SDL_SCANCODE_RETURN2),
		 esc = inputHandler.isKeyDown(SDL_SCANCODE_ESCAPE);
	
	if (left || right || up || down)
	{
		const int gameWidth = ServiceManager::Instance()->getService<SettingsService>().gameWidth;
		const int gameHeight = ServiceManager::Instance()->getService<SettingsService>().gameHeight;

		if (transform.position.x < 0)
		{
			left = false;
		}
		if (transform.position.x > gameWidth - 30)
		{
			right = false;
		}
		if (transform.position.y < 0 + 50)
		{
			up = false;
		}
		if (transform.position.y > gameHeight - transform.height)
		{
			down = false;
		}

		sprite.moving = true;
		if (!ServiceManager::Instance()->getService<SoundManager>().isSoundPlaying(1))
		{
			ServiceManager::Instance()->getService<SoundManager>().playSound(1, "footsteps", 0);
		}
		if (left && right || !left && !right)
		{
			transform.velocity.x = 0;
		}
		else if (right)
		{
			transform.velocity.x = 1 * speedModifier;
		}
		else if (left)
		{
			transform.velocity.x = -1 * speedModifier;
		}

		if (up && down || !up && !down)
		{
			transform.velocity.y = 0;
		}
		else if (up)
		{
			transform.velocity.y = -1 * speedModifier;
		}
		else if (down)
		{
			transform.velocity.y = 1 * speedModifier;
		}
	}
	else
	{
		sprite.moving = false;
		transform.velocity.y = 0;
		transform.velocity.x = 0;
		ServiceManager::Instance()->getService<SoundManager>().stopSound(1);
	}

	if (z)
	{
		ServiceManager::Instance()->getService<FrameHandler>().setTarget(
			ServiceManager::Instance()->getService<FrameHandler>().getTarget() - 10);
	}
	else if (x)
	{
		ServiceManager::Instance()->getService<FrameHandler>().setTarget(
			ServiceManager::Instance()->getService<FrameHandler>().getTarget() + 10);
	}
	else if (c)
	{
		ServiceManager::Instance()->getService<FrameHandler>().setTarget(60);
	}

	if (ret)
	{
		std::unique_ptr<StateFactory> sFactory = std::make_unique<StateFactory>();
		ServiceManager::Instance()->getService<StateMachine>().popState();
		ServiceManager::Instance()->getService<StateMachine>().pushState(sFactory->createState("EndScreen"));
		// if (ServiceManager::Instance()->getService<StateMachine>().peekState()->getStateID() == "playing")
		// {
		// 	std::unique_ptr<StateFactory> sFactory = std::make_unique<StateFactory>();
		// 	ServiceManager::Instance()->getService<StateMachine>().pushState(sFactory->createState("PauseScreenState"));
		// }
		// else
		// {
		// 	ServiceManager::Instance()->getService<StateMachine>().popState();
		// }
	}

	if (esc)
	{
		// if (ServiceManager::Instance()->getService<StateMachine>().peekState()->getStateID() == "playing")
		// {
			std::unique_ptr<StateFactory> sFactory = std::make_unique<StateFactory>();

			ServiceManager::Instance()->getService<StateMachine>().pushState(sFactory->createState("PauseScreenState"));
		// }
		// else
		// {
		// 	ServiceManager::Instance()->getService<StateMachine>().popState();
		// }
	}

	sprite.flip = inputHandler.getMousePosition()->x < transform.position.x;

	auto& collisionComponent = entity->getComponent<CollisionComponent>();
	collisionComponent.collider.x = transform.position.x;
	collisionComponent.collider.y = transform.position.y;
	collisionComponent.collider.w = transform.width;
	collisionComponent.collider.h = transform.height;
}

void PlayerInputSystem::handleMouseInput(Entity* entity)
{
	auto& transform = entity->getComponent<TransformComponent>();
	auto& sprite = entity->getComponent<SpriteComponent>();
	//auto& timer = entity->getComponent<TimerComponent>();
	auto& inputHandler = ServiceManager::Instance()->getService<InputHandler>();
	auto& playerStats = ServiceManager::Instance()->getService<PlayerStatsService>();

	if (inputHandler.getMouseButtonState(LEFT) || inputHandler.getMouseButtonState(RIGHT))
	{
		// shoot
		if (/*timer.isTimerFinished() && */!playerStats.getSHDactive())
		{
			double playerAttack;
			if (inputHandler.getMouseButtonState(LEFT)) {
				playerAttack = playerStats.attack(false);
			} else {
				playerAttack = playerStats.attack(true);
			}

			if (playerAttack == -1) {
				return;
			}

			const auto playerX = transform.position.x;
			const auto playerY = transform.position.y;

			const auto playerXCenter = playerX + transform.width / 2;
			const auto playerYCenter = playerY + transform.height / 2;

			const double angleX = inputHandler.getMousePosition()->x - playerXCenter;
			const double angleY = inputHandler.getMousePosition()->y - playerYCenter;

			const float vectorLength = sqrt(angleX * angleX + angleY * angleY);
			float dx = angleX / vectorLength;
			float dy = angleY / vectorLength;

			Entity& projectile = ServiceManager::Instance()->getService<EntityManager>().addEntity();
			projectile.addComponent<BulletMovementComponent>();
			projectile.addComponent<DamageComponent>(playerAttack);
			auto& projectileTransform = projectile.addComponent<TransformComponent>(
				playerXCenter + dx * 25, playerYCenter + dy * 25, 10, 10, 1);
			projectileTransform.velocity.x = dx;
			projectileTransform.velocity.y = dy;

			auto& playerComponent = entity->getComponent<PlayerComponent>();

			if (inputHandler.getMouseButtonState(LEFT))
			{
				auto& weapon = playerStats.normalWeapon;
				sprite.setTexture(weapon.attackingTextureID.c_str());
				ServiceManager::Instance()->getService<SoundManager>().playSound(2, "arrow", 0);
				projectile.addComponent<SpriteComponent>("bullet");
				projectile.addComponent<CollisionComponent>("arrow");
				//timer.setTimer(playerComponent.shootingTimeout);
			}

			if (inputHandler.getMouseButtonState(RIGHT))
			{
				auto& weapon = playerStats.magicWeapon;
				sprite.setTexture(weapon.attackingTextureID.c_str());
				ServiceManager::Instance()->getService<SoundManager>().playSound(2, "bolt", 0);
				projectile.addComponent<SpriteComponent>("bolt");
				projectile.addComponent<CollisionComponent>("bolt");
				//timer.setTimer(playerComponent.shootingTimeout * 2);
			}

			for (const auto& group : entity->getGroups())
			{
				ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(projectile, group);
			}
		}
	}
	else
	{
		sprite.setTexture("character");
	}
}
