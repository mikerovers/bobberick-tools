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
	SpriteComponent(const char * path, const char* textureID, const bool guiLayer = false);
    SpriteComponent(const char * path, const char* textureID, int animCols, int animFrames, int animRate);

	void addTexture(const char * path, const char * textureID);
	void changeTexture(const char * textureID);

    void setCurrentFrame(const int frame);
    void setStaticAnimation(const bool stan);

    void init() override;
    void update() override;
    void render() override;

	bool guiLayer; // Set this to true to always render this sprite on top of any rectangles and text; used for drawing sprites on a GUI box.
	bool moving;
	bool flip = false;

protected:
    TransformComponent* transform;
    std::string currentTexture;
    SDL_Rect sourceRect{};
    SDL_Rect destinationRect{};
	int animCols; // Amount of columns in spritesheet
	int animFrames; // Amount of frames in spritesheet
	int currentFrame; // Current frame number
	int animRate; // Amount of ticks each frame
	int animTimer; // Amount of ticks remaining to next frame
	bool staticAnimation;
};


#endif //BOBBERICK_TOOLS_SPRITECOMPONENT_H
