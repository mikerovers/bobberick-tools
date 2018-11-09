#include "SplashScreenState.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../bobberick-framework/src/entity/components/TextComponent.h"
#include "../../bobberick-framework/src/entity/components/FadeComponent.h"
#include <SDL.h>

SplashScreenState::~SplashScreenState() = default;

void SplashScreenState::update() {
	for (const std::shared_ptr<System> &system : systems) {
		system->update();
	}
}

bool SplashScreenState::onEnter() {
	auto &entityManager = ServiceManager::Instance()->getService<EntityManager>();
	std::shared_ptr<Entity> logo = entityManager.addEntity();
	logo->addComponent<TransformComponent>(192, 72, 256, 256, 1);
	logo->addComponent<SpriteComponent>("assets/teamcpp_logo.bmp", "logo");
	logo->addComponent<FadeComponent>("logo", -150, 2, 300); // Starting the opacity value below 0 will delay the fade-in.
	std::shared_ptr<Entity> logoText = entityManager.addEntity();
	logoText->addComponent<TransformComponent>(192, 328, 80, 256, 1);
	logoText->addComponent<TextComponent>("defaultLarge", "logoText", "Team C++");
	logoText->addComponent<FadeComponent>("logoText", -50, 2, 300);
	fadeEntities = ServiceManager::Instance()->getService<EntityManager>().getAllEntitiesWithComponent<FadeComponent>();

	return true;
}

bool SplashScreenState::onExit() {
	return true;
}

bool SplashScreenState::shouldExit() {
	for (const std::shared_ptr<Entity> &entity : fadeEntities) {
		// We are only done when all of our FadeComponent entities are done fading out.
		if (entity->getComponent<FadeComponent>().fadeOut) {
			return false;
		}
	}

	return true;
}

std::string SplashScreenState::getStateID() const {
	return "splashScreen";
}