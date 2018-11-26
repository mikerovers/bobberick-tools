#include "AdvertisementSystem.h"
#include "../../bobberick-demo/components/AdvertisementComponent.h"
#include "../../bobberick-demo/components/ShootComponent.h"
#include "../../bobberick-framework/src/entity/components/TimerComponent.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include <sstream>

AdvertisementSystem::AdvertisementSystem(EntityManager &entityManager) : System(entityManager)
{
	maxAds = 5;
}

void AdvertisementSystem::update()
{
	for (auto& entity : entityManager.getAllEntitiesWithComponent<AdvertisementComponent>()) {
		auto& advertisementComponent = entity->getComponent<AdvertisementComponent>();
		if (entity->hasComponent<TimerComponent>()) {
			// reload advertisement through
			auto& timer = entity->getComponent<TimerComponent>();
			if (timer.isTimerFinished())
			{
				auto& spriteComponent = entity->getComponent<SpriteComponent>();

				std::ostringstream sstream;
				sstream << "ad" << advertisementComponent.getNextAd();
				const std::string tmp = sstream.str();
				const char* cstr = tmp.c_str();
				spriteComponent.setTexture(cstr);

				timer.setTimer(5000);
			}
		}
	}
}
