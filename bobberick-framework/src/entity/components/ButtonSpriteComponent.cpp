#include "ButtonSpriteComponent.h"

ButtonSpriteComponent::ButtonSpriteComponent(const char *path, const char *textureID, int animCols, int animFrames,
                                             int animRate) : SpriteComponent(path, textureID, animCols, animFrames,
                                                                             animRate)
{

}

void ButtonSpriteComponent::update()
{
    int currentRow = currentFrame / animCols;

    sourceRect.x = transform->width * currentRow;
}
