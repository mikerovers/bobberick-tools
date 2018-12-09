#ifndef BOBBERICK_TOOLS_SPRITECOMPONENT_H
#define BOBBERICK_TOOLS_SPRITECOMPONENT_H

#include <SDL.h>
#include <string>
#include "../Component.h"
#include "TransformComponent.h"
#include <map>

class SpriteComponent : public Component
{
public:
    SpriteComponent();
	SpriteComponent(const char* textureID, int zIndex = 1);
    SpriteComponent(const char* textureID, int animCols, int animFrames, int animRate, int zIndex = 1);

	void setTexture(const char * textureID);
    void setCurrentFrame(const int frame);
    void setStaticAnimation(const bool stan);
	void processScale(const int scale);
	SDL_Rect& getSourceRect();
	SDL_Rect& getDestinationRect();
	std::string& getTexture();

    void init() override;
    void update() override;
    void render() override;

	int zIndex{}; // Higher number means further to the back
	bool moving{};
	bool flip = false;
protected:
    TransformComponent* transform{};
    std::string currentTexture;
    SDL_Rect sourceRect{};
    SDL_Rect destinationRect{};
	int animCols{}; // Amount of columns in spritesheet
	int animFrames{}; // Amount of frames in spritesheet
	int currentFrame; // Current frame number
	int animRate{}; // Amount of ticks each frame
	int animTimer{}; // Amount of ticks remaining to next frame
	bool staticAnimation;
};


#endif //BOBBERICK_TOOLS_SPRITECOMPONENT_H
