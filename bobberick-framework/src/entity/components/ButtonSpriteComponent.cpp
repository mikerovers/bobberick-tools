#include "ButtonSpriteComponent.h"

ButtonSpriteComponent::ButtonSpriteComponent(const char *textureID, int animCols, int animFrames,
                                             int animRate) : SpriteComponent(textureID, animCols, animFrames,
                                                                             animRate)
{

}

void ButtonSpriteComponent::update()
{
    int currentRow = currentFrame / animCols;

    sourceRect.x = transform->width * currentRow;
}


void ButtonSpriteComponent::setTexture(const char * textureID)
{
	if (currentTexture != textureID) {
		currentTexture = textureID;
	}
}