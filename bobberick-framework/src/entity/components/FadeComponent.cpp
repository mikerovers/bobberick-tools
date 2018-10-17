#include "FadeComponent.h"
#include "../../services/ServiceManager.h"
#include "../../TextureManager.h"

FadeComponent::FadeComponent(std::string textureID, int opacity, int fadeDelay, bool fadeIn, bool fadeOut) {
	FadeComponent::textureID = textureID;
	FadeComponent::opacity = opacity;
	FadeComponent::fadeDelay = fadeDelayMax = fadeDelay;
	FadeComponent::reverseDelay = 0;
	FadeComponent::fadeIn = fadeIn;
	FadeComponent::fadeOut = fadeOut;

	ServiceManager::Instance()->getService<TextureManager>().setOpacity(textureID, opacity);
}

FadeComponent::FadeComponent(std::string textureID, int opacity, int fadeDelay, int reverseDelay) {
	FadeComponent::textureID = textureID;
	FadeComponent::opacity = opacity;
	FadeComponent::fadeDelay = fadeDelayMax = fadeDelay;
	FadeComponent::reverseDelay = reverseDelay;
	FadeComponent::fadeIn = true;
	FadeComponent::fadeOut = true;

	ServiceManager::Instance()->getService<TextureManager>().setOpacity(textureID, opacity);
}

void FadeComponent::update() {
	if (fadeIn || fadeOut) {
		fadeDelay--;
		if (fadeDelay <= 0) {
			if (fadeIn) {
				opacity++;
				fadeDelay = fadeDelayMax;
				ServiceManager::Instance()->getService<TextureManager>().setOpacity(textureID, opacity);
				if (opacity >= 255) {
					opacity = 255;
					fadeIn = false;
				}
			} else if (fadeOut) {
				if (fadeDelay <= 0) {
					if (opacity >= 255) { // Once the fade delay passes in this case, we wait for the extra reverse delay to pass too.
						reverseDelay--;
						if (reverseDelay <= 0) {
							reverseDelay = 0;
							opacity--;
							fadeDelay = fadeDelayMax;
							ServiceManager::Instance()->getService<TextureManager>().setOpacity(textureID, opacity);
						}
					} else {
						opacity--;
						fadeDelay = fadeDelayMax;
						ServiceManager::Instance()->getService<TextureManager>().setOpacity(textureID, opacity);
						if (opacity <= 0) {
							opacity = 0;
							fadeOut = false;
						}
					}
				}
			}
		}
	}
	
}