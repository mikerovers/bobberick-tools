#include "SettingsScreenState.h"
#include "../../bobberick-framework/src/entity/components/CollisionComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonSpriteComponent.h"
#include "../../bobberick-framework/src/entity/components/ButtonComponent.h"
#include "StateFactory.h"
#include "../../bobberick-framework/src/StateMachine.h"
#include "../../bobberick-framework/src/services/SoundManager.h"
#include "../../bobberick-framework/src/services/SettingsService.h"
#include "../../bobberick-framework/src/entity/components/TextComponent.h"
#include "../../bobberick-demo/components/ButtonSettingComponent.h"

bool SettingsScreenState::shouldExit()
{
    return hasPressedBack;
}

SettingsScreenState::SettingsScreenState(): hasPressedBack(false)
{

}

std::string SettingsScreenState::getStateID() const
{
    return "help_screen";
}

void SettingsScreenState::update()
{
    for (auto& system : systems)
    {
        system->update();

        if (exiting) {
            break;
        }
    }
}

bool SettingsScreenState::onEnter()
{
	createTexts();

	// createSaveButton();
	// createLoadButton();
	createMusicToggleButton();
	createExitButton();

    return true;
}

bool SettingsScreenState::onExit()
{
    return true;
}


void SettingsScreenState::createTexts() const
{
	auto& headerText = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	headerText.addComponent<TransformComponent>(235, 50, 80, 450, 1);
	headerText.addComponent<TextComponent>("defaultLarge", "settingsText", "Settings");

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(headerText, getStateID());

	auto& musicText = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	musicText.addComponent<TransformComponent>(200, 180, 30, 100, 1);
	musicText.addComponent<TextComponent>("monoMedium", "musicText", "Music");

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(musicText, getStateID());
}

void SettingsScreenState::createMusicToggleButton() const
{
	auto& musicToggleButton = ServiceManager::Instance()->getService<EntityManager>().addEntity();
	auto* musicToggleButtonComponent = new ButtonComponent([this]()
	{
		auto& soundManager = ServiceManager::Instance()->getService<SoundManager>();
		auto& settings = ServiceManager::Instance()->getService<SettingsService>();
		if (settings.music) {
			soundManager.pauseMusic();
		}
		else {
			soundManager.resumeMusic();
		}

		settings.music = !settings.music;
	});

	musicToggleButton.addExistingComponent<ButtonComponent>(musicToggleButtonComponent);
	musicToggleButton.addComponent<TransformComponent>(560, 165, 64, 128, 1);
	musicToggleButton.addComponent<ButtonSpriteComponent>("blank_green_button", 1, 3, 0);
	musicToggleButton.addComponent<ButtonSettingComponent>("music");
	musicToggleButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(musicToggleButton, getStateID());
}
void SettingsScreenState::createExitButton()
{
	auto& exitButton = ServiceManager::Instance()->getService<EntityManager>().addEntity();

	auto* exitButtonComponent = new ButtonComponent([this]()
	{
		hasPressedBack = true;
		ServiceManager::Instance()->getService<StateMachine>().popState();
	});

	exitButton.addExistingComponent<ButtonComponent>(exitButtonComponent);
	auto* exitButtonTransformComponent = new TransformComponent();
	exitButtonTransformComponent->position.x = 410;
	exitButtonTransformComponent->position.y = 420;
	exitButtonTransformComponent->height = 64;
	exitButtonTransformComponent->width = 128;
	exitButton.addExistingComponent<TransformComponent>(exitButtonTransformComponent);
	exitButton.addComponent<ButtonSpriteComponent>("exitButton", 1, 3, 0);
	exitButton.getComponent<ButtonSpriteComponent>().setStaticAnimation(true);

	ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(exitButton, getStateID());
}
