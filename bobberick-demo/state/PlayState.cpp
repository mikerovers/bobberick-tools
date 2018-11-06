#include "PlayState.h"
#include "../systems/PlayerInputSystem.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/SoundManager.h"
#include "../../bobberick-framework/src/entity/systems/DrawSystem.h"
#include "../../bobberick-framework/src/entity/systems/InputSystem.h"
#include "../../bobberick-framework/src/entity/components/PlayerShootComponent.h"
#include "../components/PlayerMovementComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonComponent.h"
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
	ServiceManager::Instance()->getService<SoundManager>().load("assets/music/effects/arrow-swoosh-2.ogg", "1", SOUND_SFX);

    std::shared_ptr<Entity> player = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	player->addComponent<TransformComponent>(10, 10, 256, 256, 2);
    player->addComponent<SpriteComponent>("assets/image/spritestrip.png", "character", 6, 6, 5);
    player->addComponent<PlayerMovementComponent>();
    player->addComponent<PlayerShootComponent>();

    std::shared_ptr<Entity> level = ServiceManager::Instance()->getService<EntityManager>().addEntity();
    auto* factory = new LevelFactory();
    TilesetComponent* tilesetComponent = factory->Load("assets/maps/map1.tmx", ServiceManager::Instance()->getService<RenderService>().getRenderer());
    level->addExistingComponent<TilesetComponent>(tilesetComponent);

    std::shared_ptr<Entity> exitButton = ServiceManager::Instance()->getService<EntityManager>().addEntity();
    auto* buttonComponent = new ButtonComponent([]() {
        std::cout << "hoi";
    });
    buttonComponent->setCallback([](){
        std::cout << "doei";
    });
    exitButton->addExistingComponent<ButtonComponent>(buttonComponent);
    exitButton->addComponent<TransformComponent>();
    exitButton->addComponent<SpriteComponent>("assets/image/playbutton.bmp", "playbutton", 3, 3, 0);
    exitButton->getComponent<SpriteComponent>().setStaticAnimation(true);

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
