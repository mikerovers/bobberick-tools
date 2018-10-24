#include "CreditScreenState.h"
#include "../../../bobberick-framework/src/services/ServiceManager.h"
#include "../../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../../bobberick-framework/src/entity/components/FadeComponent.h"
#include "../../../bobberick-framework/src/entity/components/TextComponent.h"

CreditScreenState::CreditScreenState() = default;

void CreditScreenState::update()
{
	for (const auto& system : systems)
	{
		system->update();
	}
}

bool CreditScreenState::onEnter()
{
	auto& entityManager = ServiceManager::Instance()->getService<EntityManager>();
	auto logo = entityManager.addEntity();
	auto logoText = entityManager.addEntity();
	logoText->addComponent<TransformComponent>(192, 328, 80, 256, 1);
	logoText->addComponent<TextComponent>("assets/font.ttf", "TitleText", "Credits", 56);
	logoText->addComponent<FadeComponent>("logoText", -50, 2, 300);
	fadeEntities = ServiceManager::Instance()->getService<EntityManager>().getAllEntitiesWithComponent<FadeComponent>();
	return true;
}

bool CreditScreenState::onExit()
{
	return true;
}

bool CreditScreenState::shouldExit()
{
	for (const auto& entity : fadeEntities)
	{
		if (entity->getComponent<FadeComponent>().fadeOut)
		{
			return false;
		}
	}
	return true;
}

std::string CreditScreenState::getStateID() const
{
	return "splashScreen";
}
