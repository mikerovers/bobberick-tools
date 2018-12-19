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
    makeBackground();

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
	exitButton.addComponent<TransformComponent>(10, 10, 64, 128, 1);
    exitButton.addComponent<ButtonSpriteComponent>("exitButton", 1, 3, 0, 1).setStaticAnimation(true);

    ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(exitButton, getStateID());
}

void HelpScreenState::makeText() const
{
	makeHeaderTexts();
	makeMoveTexts();
    makeActivateShieldText();
    makeShootTexts();
	makePauseText();
	makeGoalText();
}

void HelpScreenState::makeHeaderTexts() const
{
	// Game goal header
	auto& goalText = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	goalText.addComponent<TransformComponent>(100, 220, 50, 250, 1);
	goalText.addComponent<TextComponent>("monoMedium", "goalHeaderText", "Game goal:");

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(goalText, getStateID());

	// Controls header
	auto& controlsText = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	controlsText.addComponent<TransformComponent>(550, 220, 50, 250, 1);
	controlsText.addComponent<TextComponent>("monoMedium", "controlsHeaderText", "Controls:");

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(controlsText, getStateID());
}

void HelpScreenState::makeGoalText() const
{
	auto& goalTextPt1 = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	goalTextPt1.addComponent<TransformComponent>(100, 290, 17, 350, 1);
	goalTextPt1.addComponent<TextComponent>("monoSmall", "goalTextPt1", "To win the game, you will have to");

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(goalTextPt1, getStateID());

	auto& goalTextPt2 = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	goalTextPt2.addComponent<TransformComponent>(100, 310, 17, 350, 1);
	goalTextPt2.addComponent<TextComponent>("monoSmall", "goalTextPt2", "destroy all the Wells and the Bosses");

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(goalTextPt2, getStateID());

	auto& goalTextPt3 = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	goalTextPt3.addComponent<TransformComponent>(100, 330, 17, 100, 1);
	goalTextPt3.addComponent<TextComponent>("monoSmall", "goalTextPt3", "they spawn.");

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(goalTextPt3, getStateID());
}

void HelpScreenState::makeMoveTexts() const
{
	// Move left
	std::string moveLeftString = "Move left: ";
	moveLeftString = moveLeftString.append(settings.getHumanReadableScancode(settings.left1)).append(" or ").append(settings.getHumanReadableScancode(settings.left2));
	auto& moveLeftText = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	moveLeftText.addComponent<TransformComponent>(550, 290, 17, 200, 1);
	moveLeftText.addComponent<TextComponent>("monoSmall", "moveLeftText", moveLeftString);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(moveLeftText, getStateID());

	// Move right
	std::string moveRightString = "Move right: ";
	moveRightString = moveRightString.append(settings.getHumanReadableScancode(settings.right1)).append(" or ").append(settings.getHumanReadableScancode(settings.right2));
	auto& moveRightText = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	moveRightText.addComponent<TransformComponent>(550, 310, 17, 200, 1);
	moveRightText.addComponent<TextComponent>("monoSmall", "moveRightText", moveRightString);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(moveRightText, getStateID());

	// Move up
	std::string moveUpString = "Move up: ";
	moveUpString = moveUpString.append(settings.getHumanReadableScancode(settings.up1)).append(" or ").append(settings.getHumanReadableScancode(settings.up2));
	auto& moveUpText = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	moveUpText.addComponent<TransformComponent>(550, 330, 17, 160, 1);
	moveUpText.addComponent<TextComponent>("monoSmall", "moveUpText", moveUpString);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(moveUpText, getStateID());

	// Move down
	std::string moveDownString = "Move down: ";
	moveDownString = moveDownString.append(settings.getHumanReadableScancode(settings.down1)).append(" or ").append(settings.getHumanReadableScancode(settings.down2));
	auto& moveDownText = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	moveDownText.addComponent<TransformComponent>(550, 350, 17, 200, 1);
	moveDownText.addComponent<TextComponent>("monoSmall", "moveDownText", moveDownString);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(moveDownText, getStateID());
}

void HelpScreenState::makeActivateShieldText() const
{
	std::string activateShieldString = "Activate shield: ";
	activateShieldString.append(settings.getHumanReadableScancode(settings.activateShield));
	auto& shieldText = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	shieldText.addComponent<TransformComponent>(550, 370, 17, 200, 1);
	shieldText.addComponent<TextComponent>("monoSmall", "shieldText", activateShieldString);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(shieldText, getStateID());
}

void HelpScreenState::makeShootTexts() const
{
	// Shoot normal
	auto& shootNormalText = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	shootNormalText.addComponent<TransformComponent>(550, 390, 17, 280, 1);
	shootNormalText.addComponent<TextComponent>("monoSmall", "shootNormalText", "Shoot normal: Left Mouse Button");

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(shootNormalText, getStateID());

	// Shoot magic
	auto& shootMagicText = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	shootMagicText.addComponent<TransformComponent>(550, 410, 17, 280, 1);
	shootMagicText.addComponent<TextComponent>("monoSmall", "shootMagicText", "Shoot magic: Right Mouse Button");

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(shootMagicText, getStateID());
}

void HelpScreenState::makePauseText() const
{
	std::string pauseString = "Pause: ";
	pauseString.append(settings.getHumanReadableScancode(settings.pauseGame1));
	auto& pauseText = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	pauseText.addComponent<TransformComponent>(550, 430, 17, 115, 1);
	pauseText.addComponent<TextComponent>("monoSmall", "pauseText", pauseString);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(pauseText, getStateID());
}

void HelpScreenState::makeBackground() const
{
    auto& background = ServiceManager::Instance()->getService<EntityManager>().addEntity();
    background.addComponent<TransformComponent>(0, 0, 704, 960, 1);
    background.addComponent<SpriteComponent>("menuBackground", 0);

    ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(background, getStateID());
}
