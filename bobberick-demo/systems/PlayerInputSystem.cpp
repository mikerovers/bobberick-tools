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
	auto& settings = ServiceManager::Instance()->getService<SettingsService>();

	double speedModifier = playerStats.getSHDactive() ? 0.5 : 1;

	if (inputHandler.isKeyDown(settings.activateShield))
	{
		if (!playerStats.getSHDactive())
		{
			playerStats.toggleShield();
		}
	}

	bool left = inputHandler.isKeyDown(settings.left1) || inputHandler.isKeyDown(settings.left2),
	     right = inputHandler.isKeyDown(settings.right1) || inputHandler.isKeyDown(settings.right2),
	     up = inputHandler.isKeyDown(settings.up1) || inputHandler.isKeyDown(settings.up2),
	     down = inputHandler.isKeyDown(settings.down1) || inputHandler.isKeyDown(settings.down2),
	     z = inputHandler.isKeyDown(settings.fpsSpdDown),
	     x = inputHandler.isKeyDown(settings.fpsSpdUp),
	     c = inputHandler.isKeyDown(settings.fpsSpdReset),
		 shift = inputHandler.isKeyDown(settings.equipWeapon1),
		 esc = inputHandler.isKeyDown(settings.pauseGame1),
		 fpsShow = inputHandler.isKeyDown(settings.fpsShow),
		 fpsHide = inputHandler.isKeyDown(settings.fpsHide);
	
	if (left || right || up || down)
	{
		const int gameWidth = settings.gameWidth;
		const int gameHeight = settings.gameHeight;

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

	if (shift) 
	{
		ServiceManager::Instance()->getService<PlayerStatsService>().equipComparingWeapon();
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
	
	if (fpsHide)
	{
		settings.fps = false;
	}

	if (fpsShow)
	{
		settings.fps = true;
	}

	sprite.flip = inputHandler.getMousePosition()->x < transform.position.x;

	auto& collisionComponent = entity->getComponent<CollisionComponent>();
	collisionComponent.collider.x = transform.position.x;
	collisionComponent.collider.y = transform.position.y;
	collisionComponent.collider.w = transform.width;
	collisionComponent.collider.h = transform.height;
}

void PlayerInputSystem::handleMouseInput(Entity* entity) const
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
				std::cout << weapon.power << "\n";
				sprite.setTexture(weapon.attackingTextureID.c_str());
				ServiceManager::Instance()->getService<SoundManager>().playSound(2, "arrow", 0);
				projectile.addComponent<SpriteComponent>("bullet", 4);
				projectile.addComponent<CollisionComponent>("arrow");
				//timer.setTimer(playerComponent.shootingTimeout);
			}
			else if (inputHandler.getMouseButtonState(RIGHT))
			{
				auto& weapon = playerStats.magicWeapon;
				sprite.setTexture(weapon.attackingTextureID.c_str());
				ServiceManager::Instance()->getService<SoundManager>().playSound(2, "bolt", 0);
				projectile.addComponent<SpriteComponent>("bolt", 4);
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
