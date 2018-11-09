#include "PlayState.h"
#include "../systems/PlayerInputSystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/SoundManager.h"
#include "../../bobberick-framework/src/entity/systems/DrawSystem.h"
#include "../../bobberick-framework/src/entity/systems/InputSystem.h"
#include "../../bobberick-framework/src/entity/components/ShootComponent.h"
#include "../components/PlayerMovementComponent.h"
#include "../../bobberick-framework/src/entity/components/RectangleComponent.h"
#include "../components/StatsComponent.h"
#include "../components/PlayerStatsComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonSpriteComponent.h"
#include "../../bobberick-framework/src/LevelFactory.h"
#include "../../bobberick-framework/src/services/RenderService.h"
#include "../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../factory/ObjectFactory.h"
#include "../factory/enemies/EnemyFactory.h"

std::string PlayState::getStateID() const
{
    return "playing";
}

void PlayState::update()
{
    for (const auto &system : systems) {
        system->update();
    }
}

bool PlayState::onEnter()
{
	EnemyFactory enemyFactory = EnemyFactory{};
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 10; y++) {
			Entity* enemy = enemyFactory.getRandomEnemy(1, 4);

			auto& enemyTransform = enemy->getComponent<TransformComponent>();
			enemyTransform.position.setX(450 + 50 * x);
			enemyTransform.position.setY(50 * y);
		}
	}

	for (const auto &system : systems) {
		system->init();
	}

    std::cout << "Entered playstate" << std::endl;
	ServiceManager::Instance()->getService<SoundManager>().load("assets/music/effects/arrow-swoosh-2.ogg", "arrow", SOUND_SFX);
	ServiceManager::Instance()->getService<SoundManager>().load("assets/music/effects/footsteps_on_gravel.ogg", "footsteps", SOUND_SFX);
	ServiceManager::Instance()->getService<SoundManager>().load("assets/music/effects/magical_zap.ogg", "bolt", SOUND_SFX);

    auto* player = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	player->addComponent<TransformComponent>(200, 200, 64, 32, 2);
    //player->addComponent<SpriteComponent>("assets/image/spritestrip.png", "character", 6, 6, 5);
    auto& spriteComponent = player->addComponent<SpriteComponent>("assets/image/character/character.png", "character", 6, 4, 5);
	spriteComponent.addTexture("assets/image/character/character_casting.png", "character_casting");
	spriteComponent.addTexture("assets/image/character/character_shooting.png", "character_shooting");
	spriteComponent.addTexture("assets/image/character/character_shield.png", "character_shield");
    player->addComponent<PlayerMovementComponent>();
	// 3 seconds (180 ticks) of shield mode, 3/10ths of a second recovered per second.
	player->addComponent<PlayerStatsComponent>(new StatsComponent(100000, 100000, 1, 3, 1), 180, 180, 0.3, 0, 0);
	//player->getComponent<PlayerStatsComponent>().toggleShield(); // For testing purposes
    player->addComponent<ShootComponent>();
    player->addComponent<CollisionComponent>("player");

    auto* level = ServiceManager::Instance()->getService<EntityManager>().addEntity();
    auto* levelFactory = new LevelFactory();
    TilesetComponent* tilesetComponent = levelFactory->Load("assets/maps/map1.tmx", ServiceManager::Instance()->getService<RenderService>().getRenderer());
    level->addExistingComponent<TilesetComponent>(tilesetComponent);
    delete levelFactory;

    auto* box = ServiceManager::Instance()->getService<EntityManager>().addEntity();
    auto* collisionComponent = new CollisionComponent("test", 140, 175, 40);
    box->addExistingComponent<CollisionComponent>(collisionComponent);
    
    auto* objectFactory = new ObjectFactory();
    for(auto* object : tilesetComponent->objects) {
        objectFactory->getObject(object);
    }

    delete objectFactory;

    auto* exitButton = ServiceManager::Instance()->getService<EntityManager>().addEntity();
    auto* exitButtonComponent = new ButtonComponent([this](){
        std::cout << "Exit button clicked." << std::endl;
		_exitPressed = true;
    });
    exitButton->addExistingComponent<ButtonComponent>(exitButtonComponent);
    auto* exitButtonTransformComponent = new TransformComponent();
    exitButtonTransformComponent->position.setX(10);
    exitButtonTransformComponent->position.setY(60);
    exitButtonTransformComponent->height = 64;
    exitButtonTransformComponent->width = 128;
    exitButton->addExistingComponent<TransformComponent>(exitButtonTransformComponent);
    exitButton->addComponent<ButtonSpriteComponent>("assets/image/button/exitbutton.png", "exitbutton", 1, 3, 0);
    exitButton->getComponent<ButtonSpriteComponent>().setStaticAnimation(true);

    ServiceManager::Instance()->getService<SoundManager>().load("assets/music/soundtrack/level_1.wav", "level1", SOUND_MUSIC);
    ServiceManager::Instance()->getService<SoundManager>().playMusic("level1", -1);



    return true;
}

bool PlayState::onExit()
{
    std::cout << "Exited playstate" << std::endl;

    return true;
}

bool PlayState::shouldExit()
{
	return _exitPressed;
}
