#include "StateFactory.h"
#include "entity/systems/DrawSystem.h"
#include "services/ServiceManager.h"

GameState* StateFactory::createState(const std::string type) {
	if (type == "SplashScreenState") {
		return createSplashScreenState();
	}
	return nullptr;
}

//privates
SplashScreenState* StateFactory::createSplashScreenState() {
	SplashScreenState* splashScreen = new SplashScreenState();
	splashScreen->addSystem(std::shared_ptr<DrawSystem>(new DrawSystem(ServiceManager::Instance()->getService<EntityManager>())));
	return splashScreen;
}