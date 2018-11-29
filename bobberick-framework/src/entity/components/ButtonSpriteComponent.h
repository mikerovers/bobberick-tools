#ifndef BOBBERICK_TOOLS_BUTTONSPRITECOMPONENT_H
#define BOBBERICK_TOOLS_BUTTONSPRITECOMPONENT_H


#include "SpriteComponent.h"

class ButtonSpriteComponent : public SpriteComponent
{
public:
    ButtonSpriteComponent(const char* textureID, int animCols, int animFrames, int animRate);
    void update() override;
	void setTexture(const char * textureID);
};


#endif //BOBBERICK_TOOLS_BUTTONSPRITECOMPONENT_H
