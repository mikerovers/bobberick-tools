#ifndef BOBBERICK_TOOLS_FADECOMPONENT_H
#define BOBBERICK_TOOLS_FADECOMPONENT_H
#include "../Component.h"
#include <string>

class FadeComponent : public Component
{
public:
	FadeComponent(std::string textureID, double opacity, double fadeFactor, bool fadeIn, bool fadeOut);
	FadeComponent(std::string textureID, double opacity, double fadeFactor, int reverseDelay); // Will initiate both fadeIn and fadeOut as true.
	void update() override;
	std::string textureID;
	bool fadeIn; // When true, the texture will fade in until opacity is 255.
	bool fadeOut; // When true, the texture will fade out until opacity is 0.
	// When both fadeIn and fadeOut are true, the texture will start fading out after it's done fading in.
	int reverseDelay; // The delay in ticks before the object begins to fade out after it's done fading in.
	double opacity; // The current opacity (0 = invisible, 255 = opaque).
	double fadeFactor; // The value by which opacity changes every tick.
};
#endif //BOBBERICK_TOOLS_FADECOMPONENT_H 