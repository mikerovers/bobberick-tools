#include "AdvertisementComponent.h"

int AdvertisementComponent::getCurrentAd() const {
	return currentAd;
}

void AdvertisementComponent::increaseAd() {
	if (currentAd < maxAd) {
		currentAd++;
	}
	else {
		currentAd = 1;
	}
}