#ifndef BOBBERICK_TOOLS_SPRITECOMPONENT_H
#define BOBBERICK_TOOLS_SPRITECOMPONENT_H

#include <SDL.h>
#include <string>
#include "../Component.h"
#include "TransformComponent.h"

class SpriteComponent : public Component
{
public:
    SpriteComponent() = default;
	SpriteComponent(const char * path, const char* textureID, const bool guiLayer = false);
    SpriteComponent(const char * path, const char* textureID, int animCols, int animFrames, int animRate);

    void init() override;
    void update() override;
    void render() override;

	bool guiLayer; // Set this to true to always render this sprite on top of any rectangles and text; used for drawing sprites on a GUI box.
	// This is needed because in-game sprites are normally under the GUI.
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
};


#endif //BOBBERICK_TOOLS_SPRITECOMPONENT_H
