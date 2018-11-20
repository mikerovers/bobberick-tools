#include "HelpScreenState.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/entity/components/ButtonComponent.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonSpriteComponent.h"
#include "../../bobberick-framework/src/entity/components/TextComponent.h"
#include "../../bobberick-framework/src/entity/components/FadeComponent.h"
#include "../../bobberick-framework/src/StateMachine.h"

bool HelpScreenState::shouldExit()
{
    return hasPressedBack;
}

HelpScreenState::HelpScreenState(): hasPressedBack(false)
{

}

std::string HelpScreenState::getStateID() const
{
    return "help_screen";
}

void HelpScreenState::update()
{
    for (auto& system : systems)
    {
        system->update();

        if (exiting) {
            break;
        }
    }
}

bool HelpScreenState::onEnter()
{
    makeGui();
    makeText();

    return true;
}

bool HelpScreenState::onExit()
{
    return true;
}

void HelpScreenState::makeGui()
{
    auto& exitButton = ServiceManager::Instance()->getService<EntityManager>().addEntity();

    auto* exitButtonComponent = new ButtonComponent([this]()
    {
        hasPressedBack = true;
        ServiceManager::Instance()->getService<StateMachine>().popState();
    });

    exitButton.addExistingComponent<ButtonComponent>(exitButtonComponent);
    auto* exitButtonTransformComponent = new TransformComponent();
    exitButtonTransformComponent->position.setX(10);
    exitButtonTransformComponent->position.setY(60);
    exitButtonTransformComponent->height = 64;
    exitButtonTransformComponent->width = 128;
    exitButton.addExistingComponent<TransformComponent>(exitButtonTransformComponent);
    exitButton.addComponent<ButtonSpriteComponent>("assets/image/button/exitbutton.png", "exitbutton", 1, 3, 0);
    exitButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);

    ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(exitButton, getStateID());
}

void HelpScreenState::makeText()
{
    auto& walkText = ServiceManager::Instance()->getService<EntityManager>().addEntity();
    walkText.addComponent<TransformComponent>(10, 120, 80, 400, 1);
    walkText.addComponent<TextComponent>("defaultLarge", "walkText", "WASD : Walk");

    ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(walkText, getStateID());

    auto& shieldText = ServiceManager::Instance()->getService<EntityManager>().addEntity();
    shieldText.addComponent<TransformComponent>(10, 220, 80, 400, 1);
    shieldText.addComponent<TextComponent>("defaultLarge", "shieldText", "SPACE : Shield");

    ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(shieldText, getStateID());

    auto& mouseText = ServiceManager::Instance()->getService<EntityManager>().addEntity();
    mouseText.addComponent<TransformComponent>(10, 320, 80, 400, 1);
    mouseText.addComponent<TextComponent>("defaultLarge", "shootText", "Mouse : Shoot");

    ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(mouseText, getStateID());
}
