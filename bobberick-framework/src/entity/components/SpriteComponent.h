#ifndef BOBBERICK_TOOLS_SPRITECOMPONENT_H
#define BOBBERICK_TOOLS_SPRITECOMPONENT_H

#include <SDL.h>
#include <string>
#include "../Component.h"
#include "TransformComponent.h"

class SpriteComponent : public Component
{
public:
    SpriteComponent();
	SpriteComponent(const char * path, const char* textureID);
    SpriteComponent(const char * path, const char* textureID, int animCols, int animFrames, int animRate);

    void setCurrentFrame(const int frame);
    void setStaticAnimation(const bool stan);

    void init() override;
    void update() override;
    void render() override;

	bool moving;
	bool flip;

private:
    TransformComponent* transform;
    std::string texture;
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
