#include "PlayState.h"
#include "../systems/PlayerInputSystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/SoundManager.h"
#include "../../bobberick-framework/src/entity/systems/DrawSystem.h"
#include "../../bobberick-framework/src/entity/systems/InputSystem.h"
#include "../../bobberick-framework/src/entity/components/PlayerShootComponent.h"
#include "../components/PlayerMovementComponent.h"
#include "../../bobberick-framework/src/entity/components/RectangleComponent.h"
#include "../components/StatsComponent.h"
#include "../components/PlayerStatsComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonComponent.h"
#include "../../bobberick-framework/src/LevelFactory.h"
#include "../../bobberick-framework/src/services/RenderService.h"
#include "../factory/ObjectFactory.h"

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
	for (const auto &system : systems) {
		system->init();
	}

    std::cout << "Entered playstate" << std::endl;
	ServiceManager::Instance()->getService<SoundManager>().load("assets/music/effects/arrow-swoosh-2.ogg", "arrow", SOUND_SFX);
	ServiceManager::Instance()->getService<SoundManager>().load("assets/music/effects/footsteps_on_gravel.ogg", "footsteps", SOUND_SFX);

    std::shared_ptr<Entity> player = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	player->addComponent<TransformComponent>(10, 10, 64, 32, 2);
    //player->addComponent<SpriteComponent>("assets/image/spritestrip.png", "character", 6, 6, 5);
    player->addComponent<SpriteComponent>("assets/image/vector-sprites-hero-6.png", "character", 6, 4, 5);
    player->addComponent<PlayerMovementComponent>();
	// 3 seconds (180 ticks) of shield mode, 3/10ths of a second recovered per second.
	player->addComponent<PlayerStatsComponent>(new StatsComponent(100000, 100000, 1, 3, 1), 180, 180, 0.3, 0, 0);
	player->getComponent<PlayerStatsComponent>().toggleShield(); // For testing purposes
    player->addComponent<PlayerShootComponent>();

    std::shared_ptr<Entity> level = ServiceManager::Instance()->getService<EntityManager>().addEntity();
    auto* levelFactory = new LevelFactory();
    TilesetComponent* tilesetComponent = levelFactory->Load("assets/maps/map1.tmx", ServiceManager::Instance()->getService<RenderService>().getRenderer());
    level->addExistingComponent<TilesetComponent>(tilesetComponent);
    delete levelFactory;

    auto* objectFactory = new ObjectFactory();
    for(auto* object : tilesetComponent->objects) {
        objectFactory->getObject(object);
    }

    delete objectFactory;

    return true;
}

bool PlayState::onExit()
{
    std::cout << "Exited playstate" << std::endl;

    return true;
}

bool PlayState::shouldExit()
{
    return false;
}
