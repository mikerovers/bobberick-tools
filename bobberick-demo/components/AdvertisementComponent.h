#ifndef BOBBERICK_TOOLS_ADVERTISEMENTCOMPONENT_H
#define BOBBERICK_TOOLS_ADVERTISEMENTCOMPONENT_H

#include "../../bobberick-framework/src/entity/Component.h"

class AdvertisementComponent : public Component
{
public:
	explicit AdvertisementComponent(int const startAdvertisement, int const firstAdvertisement, int const lastAdvertisement) : currentAd(startAdvertisement), firstAd(firstAdvertisement), lastAd(lastAdvertisement) {};

	int getNextAd();

private:
	int currentAd;
	int const firstAd;
	int const lastAd;
};


#endif //BOBBERICK_TOOLS_ADVERTISEMENTCOMPONENT_H
