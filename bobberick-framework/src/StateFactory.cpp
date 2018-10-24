#include "StateFactory.h"
#include "entity/systems/DrawSystem.h"
#include "services/ServiceManager.h"
#include "../../bobberick-demo/src/states/CreditScreenState.h"

GameState* StateFactory::createState(const std::string& type) const
{
	if (type == "SplashScreenState") {
		return createSplashScreenState();
	}
	if (type == "CreditScreenState")
	{
		return createCreditScreenState();
	}
	return nullptr;
}

//privates
SplashScreenState* StateFactory::createSplashScreenState() const
{
	auto splashScreen = new SplashScreenState();
	splashScreen->addSystem(std::make_shared<DrawSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	return splashScreen;
}

GameState* StateFactory::createCreditScreenState() const
{
	auto creditScreen =  new CreditScreenState();
	creditScreen->addSystem(std::make_shared<DrawSystem>(ServiceManager::Instance()->getService<EntityManager>()));
	return creditScreen;
}
