#include "AdvertisementComponent.h"

int AdvertisementComponent::getNextAd() {
	if (currentAd < lastAd) {
		currentAd++;
	}
	else {
		currentAd = firstAd;
	}
	return currentAd;
}
