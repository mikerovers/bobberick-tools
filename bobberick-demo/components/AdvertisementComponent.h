#ifndef BOBBERICK_TOOLS_ADVERTISEMENTCOMPONENT_H
#define BOBBERICK_TOOLS_ADVERTISEMENTCOMPONENT_H

#include "../../bobberick-framework/src/entity/Component.h"

class AdvertisementComponent : public Component
{
public:
	explicit AdvertisementComponent(int const startAdvertisement, int const maxAdvertisement) : currentAd(startAdvertisement), maxAd(maxAdvertisement) {};

	int getCurrentAd() const;
	void increaseAd();

private:
	int currentAd;
	int const maxAd;
};


#endif //BOBBERICK_TOOLS_ADVERTISEMENTCOMPONENT_H
