#include "EndScreenState.h"
#include "../services/HighscoreService.h"
#include "../services/PlayerStatsService.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/entity/components/ButtonComponent.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonSpriteComponent.h"
#include "../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../../bobberick-framework/src/entity/components/TextComponent.h"
#include "../../bobberick-framework/src/StateMachine.h"
#include "StateFactory.h"

bool EndScreenState::onEnter()
{
	auto& playerStats = ServiceManager::Instance()->getService<PlayerStatsService>();
	ServiceManager::Instance()->getService<HighscoreService>().saveScore(playerStats.xp);
	playerStats.init();

    makeExitButton();
    makeText();

    return true;
}

std::string EndScreenState::getStateID() const
{
    return "end_screen_state";
}

bool EndScreenState::onExit()
{
    return true;
}

void EndScreenState::update()
{
    for (const auto& system : systems)
    {
        system->update();
    }
}

void EndScreenState::makeExitButton() const
{
    auto& exitButton = ServiceManager::Instance()->getService<EntityManager>().addEntity();
    auto* exitButtonComponent = new ButtonComponent([]()
                                                    {
                                                        std::unique_ptr<StateFactory> sFactory = std::make_unique<StateFactory>();
                                                        ServiceManager::Instance()->getService<StateMachine>().changeState(sFactory->createState("MainMenuState"));
                                                    });

    exitButton.addExistingComponent<ButtonComponent>(exitButtonComponent);
    auto* exitButtonTransformComponent = new TransformComponent();

    exitButtonTransformComponent->position.x = 420;
    exitButtonTransformComponent->position.y = 400;
    exitButtonTransformComponent->height = 64;
    exitButtonTransformComponent->width = 128;
    exitButton.addExistingComponent<TransformComponent>(exitButtonTransformComponent);
    exitButton.addComponent<ButtonSpriteComponent>("exitButton", 1, 3, 0);
    exitButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);
    exitButton.addComponent<CollisionComponent>("button");

    ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(exitButton, getStateID());
}

bool EndScreenState::shouldExit()
{
    return readyForExit;
}

void EndScreenState::makeText() const
{
    auto& hurrayText = ServiceManager::Instance()->getService<EntityManager>().addEntity();
    hurrayText.addComponent<TransformComponent>(100, 50, 80, 450, 1);
    hurrayText.addComponent<TextComponent>("defaultLarge", "hurrayText", "Congratulations!");

    ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(hurrayText, getStateID());
}
