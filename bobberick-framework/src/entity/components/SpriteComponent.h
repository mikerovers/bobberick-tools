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
	explicit SpriteComponent(const std::string textureID, const bool guiLayer = false);
    SpriteComponent(const char* textureID, int animCols, int animFrames, int animRate);

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

	bool guiLayer{}; // Set this to true to always render this sprite on top of any rectangles and text; used for drawing sprites on a GUI box.
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
