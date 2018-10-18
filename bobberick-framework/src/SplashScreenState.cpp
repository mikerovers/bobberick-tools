#include "SplashScreenState.h"
#include "services\ServiceManager.h"
#include "entity/components/TransformComponent.h"
#include "entity/components/SpriteComponent.h"
#include "entity/components/TextComponent.h"
#include "entity/components/FadeComponent.h"

SplashScreenState::~SplashScreenState() {

}

void SplashScreenState::update() {
	for each (std::shared_ptr<System> system in systems) {
		system->update();
	}
}

bool SplashScreenState::onEnter() {
	auto& entityManager = ServiceManager::Instance()->getService<EntityManager>();
	std::shared_ptr<Entity> logo = entityManager.addEntity();
	logo->addComponent<TransformComponent>(0, 0, 256, 256, 1);
	logo->addComponent<SpriteComponent>("assets/teamcpp_logo.bmp", "logo");
	logo->addComponent<FadeComponent>("logo", -100, 2, 300); // Starting the opacity value below 0 will delay the fade-in.
	std::shared_ptr<Entity> logoText = entityManager.addEntity();
	logoText->addComponent<TransformComponent>(0, 256, 80, 256, 1);
	logoText->addComponent<TextComponent>("assets/font.ttf", "logoText", "Team C++", 56);
	logoText->addComponent<FadeComponent>("logoText", 0, 2, 300);
	return true;
}

bool SplashScreenState::onExit() {
	return false;
}

std::string SplashScreenState::getStateID() const {
	return "splashScreen";
}