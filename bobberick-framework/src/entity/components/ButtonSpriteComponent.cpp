#include "ButtonSpriteComponent.h"

ButtonSpriteComponent::ButtonSpriteComponent(const char *textureID, int animCols, int animFrames,
                                             int animRate, const int zIndex) : SpriteComponent(textureID, animCols, animFrames,
                                                                             animRate, zIndex)
{

}

void ButtonSpriteComponent::update()
{
	const int currentRow = currentFrame / animCols;

    sourceRect.x = transform->width * currentRow;
}


void ButtonSpriteComponent::setTexture(const char * textureID)
{
	if (currentTexture != textureID) {
		currentTexture = textureID;
	}
}