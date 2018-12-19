#ifndef BOBBERICK_TOOLS_RECTANGLECOMPONENT_H
#define BOBBERICK_TOOLS_RECTANGLECOMPONENT_H

#include <SDL.h>
#include "../Component.h"
#include "TransformComponent.h"

class RectangleComponent : public Component
{
public:
	RectangleComponent();
	RectangleComponent(const int red, const int green, const int blue, const bool filled);

    void init() override;
    void update() override;
    void render() override;

	int red;
	int green;
	int blue;
	bool filled;
	bool overlay; // For transitions, will be drawn over everything else.
private:
    TransformComponent* transform;
    SDL_Rect destinationRect{};

};


#endif //BOBBERICK_TOOLS_RECTANGLECOMPONENT_H
