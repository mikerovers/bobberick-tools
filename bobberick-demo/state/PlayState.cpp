#include "PlayState.h"
#include "../systems/PlayerInputSystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/entity/systems/DrawSystem.h"
#include "../../bobberick-framework/src/entity/systems/InputSystem.h"
#include "../components/PlayerMovementComponent.h"
#include "../../bobberick-framework/src/entity/components/RectangleComponent.h"
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
    std::cout << "Entered playstate" << std::endl;

    std::shared_ptr<Entity> player = ServiceManager::Instance()->getService<EntityManager>().addEntity();
    player->addComponent<TransformComponent>();
    player->addComponent<SpriteComponent>("assets/image/spritestrip.png", "character");
    player->addComponent<PlayerMovementComponent>();

	std::shared_ptr<Entity> hudBox = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	hudBox->addComponent<TransformComponent>(0, 0, 50, 640, 1);
	hudBox->addComponent<RectangleComponent>(51, 51, 204, true);

	std::shared_ptr<Entity> box = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	box->addComponent<TransformComponent>(10, 10, 30, 300, 1);
	box->addComponent<RectangleComponent>(0, 0, 0, false);

	std::shared_ptr<Entity> innerBox = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	innerBox->addComponent<TransformComponent>(11, 11, 28, 298, 1);
	innerBox->addComponent<RectangleComponent>(128, 128, 128, true);

	std::shared_ptr<Entity> healthBox = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	healthBox->addComponent<TransformComponent>(11, 11, 28, 198, 1);
	healthBox->addComponent<RectangleComponent>(255, 0, 0, true);

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
