#include "PlayState.h"
#include "../systems/PlayerInputSystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/entity/systems/DrawSystem.h"
#include "../../bobberick-framework/src/entity/systems/InputSystem.h"
#include "../components/PlayerMovementComponent.h"
#include "../../bobberick-framework/src/entity/components/RectangleComponent.h"
#include "../../bobberick-framework/src/entity/components/StatsComponent.h"
#include "../../bobberick-framework/src/entity/components/PlayerStatsComponent.h"
#include "../../bobberick-framework/src/LevelFactory.h"
#include "../../bobberick-framework/src/services/RenderService.h"

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

    std::shared_ptr<Entity> player = ServiceManager::Instance()->getService<EntityManager>().addEntity();
    player->addComponent<TransformComponent>();
    player->addComponent<SpriteComponent>("assets/image/spritestrip.png", "character");
    player->addComponent<PlayerMovementComponent>();
	// 2 seconds of shield mode, 2/10ths of a second recovered per second
	player->addComponent<PlayerStatsComponent>(new StatsComponent(60, 100, 1, 3, 1), 120, 120, 0.2, 0, 0);
	player->getComponent<PlayerStatsComponent>().toggleShield();

    std::shared_ptr<Entity> level = ServiceManager::Instance()->getService<EntityManager>().addEntity();
    auto* factory = new LevelFactory();
    TilesetComponent* tilesetComponent = factory->Load("assets/maps/map1.tmx", ServiceManager::Instance()->getService<RenderService>().getRenderer());
    level->addExistingComponent<TilesetComponent>(tilesetComponent);

    delete factory;

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
