#include "PlayerInputSystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/services/InputHandler.h"
#include "../../bobberick-framework/src/services/SoundManager.h"
#include "../components/PlayerMovementComponent.h"
#include "../components/BulletMovementComponent.h"
#include "../components/PlayerStatsComponent.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../bobberick-framework/src/entity/components/ShootComponent.h"
#include "../../bobberick-framework/src/entity/components/CollisionComponent.h"

PlayerInputSystem::PlayerInputSystem(EntityManager &entityManager) : System(entityManager)
{

}

void PlayerInputSystem::update()
{
	for (auto& entity : entityManager.getAllEntitiesWithComponent<PlayerMovementComponent>()) {
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

void PlayerInputSystem::handleKeyInput(Entity* entity) {
	auto& transform = entity->getComponent<TransformComponent>();
	auto& sprite = entity->getComponent<SpriteComponent>();
	auto& inputHandler = ServiceManager::Instance()->getService<InputHandler>();
	auto& playerStats = entity->getComponent<PlayerStatsComponent>();

	double speedModifier = playerStats.shieldActive() ? 0.5 : 1;

	if (inputHandler.isKeyDown(SDL_SCANCODE_SPACE)) {
		if (!playerStats.shieldActive()) {
			playerStats.toggleShield();
		}
	}

	bool left = inputHandler.isKeyDown(SDL_SCANCODE_LEFT) || inputHandler.isKeyDown(SDL_SCANCODE_A),
		right = inputHandler.isKeyDown(SDL_SCANCODE_RIGHT) || inputHandler.isKeyDown(SDL_SCANCODE_D),
		up = inputHandler.isKeyDown(SDL_SCANCODE_UP) || inputHandler.isKeyDown(SDL_SCANCODE_W),
		down = inputHandler.isKeyDown(SDL_SCANCODE_DOWN) || inputHandler.isKeyDown(SDL_SCANCODE_S);

	if (left || right || up || down) {
		sprite.moving = true;
		if (!ServiceManager::Instance()->getService<SoundManager>().isSoundPlaying(1)) {
			ServiceManager::Instance()->getService<SoundManager>().playSound(1, "footsteps", 0);
		}
		if ((left && right) || (!left && !right)) {
			transform.velocity.setX(0);
		}
		else if (right) {
			transform.velocity.setX(1 * speedModifier);
		}
		else if (left) {
			transform.velocity.setX(-1 * speedModifier);
		}

		if ((up && down) || (!up && !down)) {
			transform.velocity.setY(0);
		}
		else if (up) {
			transform.velocity.setY(-1 * speedModifier);
		}
		else if (down) {
			transform.velocity.setY(1 * speedModifier);
		}
	}
	else {
		sprite.moving = false;
		transform.velocity.setY(0);
		transform.velocity.setX(0);
		ServiceManager::Instance()->getService<SoundManager>().stopSound(1);
	}

	sprite.flip = inputHandler.getMousePosition()->getX() < transform.position.getX() ? true : false;

	auto& collisionComponent = entity->getComponent<CollisionComponent>();
	collisionComponent.collider->x = transform.position.getX();
	collisionComponent.collider->y = transform.position.getY();
	collisionComponent.collider->w = transform.width;
	collisionComponent.collider->h = transform.height;
}

void PlayerInputSystem::handleMouseInput(Entity* entity) {
	auto& transform = entity->getComponent<TransformComponent>();
	auto& sprite = entity->getComponent<SpriteComponent>();
	auto& playerShoot = entity->getComponent<ShootComponent>();
	auto& inputHandler = ServiceManager::Instance()->getService<InputHandler>();
	auto& playerStats = entity->getComponent<PlayerStatsComponent>();

	if (inputHandler.getMouseButtonState(LEFT) || inputHandler.getMouseButtonState(RIGHT)) { // shoot
		if (playerShoot.canShoot() && !playerStats.shieldActive()) {
			double playerX = transform.position.getX();
			double playerY = transform.position.getY();

			double playerXCenter = playerX + transform.width / 2;
			double playerYCenter = playerY + transform.height / 2;

			double angleX = inputHandler.getMousePosition()->getX() - playerXCenter;
			double angleY = inputHandler.getMousePosition()->getY() - playerYCenter;

			float vectorLength = sqrt(angleX*angleX + angleY * angleY);
			float dx = angleX / vectorLength;
			float dy = angleY / vectorLength;

			Entity* projectile = ServiceManager::Instance()->getService<EntityManager>().addEntity();
			projectile->addComponent<BulletMovementComponent>();
			auto& projectileTransform = projectile->addComponent<TransformComponent>(playerXCenter + (dx * 25), playerYCenter + (dy * 25), 10, 10, 1);
			projectileTransform.velocity.setX(dx);
			projectileTransform.velocity.setY(dy);

			if (inputHandler.getMouseButtonState(LEFT)) {
				sprite.changeTexture("character_shooting");
				ServiceManager::Instance()->getService<SoundManager>().playSound(2, "arrow", 0);
				projectile->addComponent<SpriteComponent>("assets/image/projectiles/bullet_ball_grey.png", "arrow");
				playerShoot.setShootTimer(500);
			}
			else {
				sprite.changeTexture("character_casting");
				ServiceManager::Instance()->getService<SoundManager>().playSound(2, "bolt", 0);
				projectile->addComponent<SpriteComponent>("assets/image/projectiles/bolt.png", "bolt");
				playerShoot.setShootTimer(1000);
			}
		}
	}
	else {
		sprite.changeTexture("character");
	}
}
