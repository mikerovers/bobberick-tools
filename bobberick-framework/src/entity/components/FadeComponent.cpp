#include "FadeComponent.h"
#include "../../services/ServiceManager.h"
#include "../../services/TextureManager.h"
#include "../../services/FontManager.h"

FadeComponent::FadeComponent(std::string textureID, double opacity, double fadeFactor, bool fadeIn, bool fadeOut) {
	FadeComponent::textureID = textureID;
	FadeComponent::opacity = opacity;
	FadeComponent::fadeFactor = fadeFactor;
	FadeComponent::reverseDelay = 0;
	FadeComponent::fadeIn = fadeIn;
	FadeComponent::fadeOut = fadeOut;
	
}
FadeComponent::FadeComponent(std::string textureID, double opacity, double fadeFactor, int reverseDelay) {
	FadeComponent::textureID = textureID;
	FadeComponent::opacity = opacity;
	FadeComponent::fadeFactor = fadeFactor;
	FadeComponent::reverseDelay = reverseDelay;
	FadeComponent::fadeIn = true;
	FadeComponent::fadeOut = true;
}

void FadeComponent::update() {
	if (fadeIn) {
		opacity += fadeFactor;
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
			}
		}
		else {
			opacity -= fadeFactor;
			if (opacity <= 0) {
				opacity = 0;
				fadeOut = false;
			}
		}
	}
	ServiceManager::Instance()->getService<TextureManager>().setOpacity(textureID, opacity);
}