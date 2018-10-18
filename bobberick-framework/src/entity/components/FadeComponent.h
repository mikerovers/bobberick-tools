#ifndef BOBBERICK_TOOLS_FADECOMPONENT_H
#define BOBBERICK_TOOLS_FADECOMPONENT_H
#include "../Component.h"
#include <string>

class FadeComponent : public Component
{
public:
	FadeComponent(std::string textureID, double opacity, double fadeFactor, bool fadeIn, bool fadeOut);
	FadeComponent(std::string textureID, double opacity, double fadeFactor, int reverseDelay); // Will initiate both fadeIn and fadeOut as true.
	void update() override; // Will return false when the FadeComponent is done fading (fadeIn and fadeOut are both false).
	// Then we can use that cue to end the splash screen and go to the menu, destroy a dead monster after it faded out, etcetera. 
	std::string textureID;
	bool fadeIn; // When true, the texture will fade in until opacity is 255.
	bool fadeOut; // When true, the texture will fade out until opacity is 0.
	int reverseDelay; // The delay in ticks (on top of fadeDelay) before the object begins to fade out.
	// When both fadeIn and fadeOut are true, the texture will start fading out right after it's done fading in.
	double opacity; // The current opacity (0 = invisible, 255 = opaque).
	double fadeFactor; // The value by which opacity changes every tick.
};
#endif //BOBBERICK_TOOLS_FADECOMPONENT_H 