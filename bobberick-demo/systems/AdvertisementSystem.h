#ifndef BOBBERICK_TOOLS_ADVERTISEMENTSYSTEM_H
#define BOBBERICK_TOOLS_ADVERTISEMENTSYSTEM_H


#include "../../bobberick-framework/src/entity/systems/System.h"

class AdvertisementSystem : public System
{
public:
	explicit AdvertisementSystem(EntityManager& entityManager);
	void update() override;
private:
};


#endif //BOBBERICK_TOOLS_ADVERTISEMENTSYSTEM_H
