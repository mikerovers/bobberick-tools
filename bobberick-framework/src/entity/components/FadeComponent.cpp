#include "FadeComponent.h"
#include "../../services/ServiceManager.h"
#include "../../TextureManager.h"
#include "../../FontManager.h"

FadeComponent::FadeComponent(std::string textureID, double opacity, double fadeFactor, bool fadeIn, bool fadeOut) {
	FadeComponent::textureID = textureID;
	FadeComponent::opacity = opacity;
	FadeComponent::fadeFactor = fadeFactor;
	FadeComponent::reverseDelay = 0;
	FadeComponent::fadeIn = fadeIn;
	FadeComponent::fadeOut = fadeOut;
	ServiceManager::Instance()->getService<TextureManager>().setOpacity(textureID, opacity);
}
FadeComponent::FadeComponent(std::string textureID, double opacity, double fadeFactor, int reverseDelay) {
	FadeComponent::textureID = textureID;
	FadeComponent::opacity = opacity;
	FadeComponent::fadeFactor = fadeFactor;
	FadeComponent::reverseDelay = reverseDelay;
	FadeComponent::fadeIn = true;
	FadeComponent::fadeOut = true;
	ServiceManager::Instance()->getService<TextureManager>().setOpacity(textureID, opacity);
}

void FadeComponent::update() {
	if (fadeIn) {
		opacity += fadeFactor;
		ServiceManager::Instance()->getService<TextureManager>().setOpacity(textureID, opacity);
		if (opacity >= 255) {
			opacity = 255;
			fadeIn = false;
		}
	}
	else if (fadeOut) {
		if (opacity >= 255) { // Once we reverse direction, we wait for the 'reverse delay' to pass.
			reverseDelay--;
			if (reverseDelay <= 0) {
				reverseDelay = 0;
				opacity -= fadeFactor;
				ServiceManager::Instance()->getService<TextureManager>().setOpacity(textureID, opacity);
			}
		}
		else {
			opacity -= fadeFactor;
			ServiceManager::Instance()->getService<TextureManager>().setOpacity(textureID, opacity);
			if (opacity <= 0) {
				opacity = 0;
				fadeOut = false;
			}
		}
	}
}