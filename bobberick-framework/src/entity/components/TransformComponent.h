#ifndef BOBBERICK_TOOLS_TRANSFORMCOMPONENT_H
#define BOBBERICK_TOOLS_TRANSFORMCOMPONENT_H


#include "../Component.h"
#include "../../util/Vector2D.h"

class TransformComponent : public Component
{
public:
    Vector2D position = Vector2D(0, 0);
    Vector2D velocity = Vector2D(0, 0);

    int height = 256;
    int width = 256;
    int scale = 1;

    double speed = 3;

	bool visible = true;

    TransformComponent();
    explicit TransformComponent(int sc);
    explicit TransformComponent(float xPos, float yPos, int h, int w, int sc);

    void update() override;
    void init() override;
};


#endif //BOBBERICK_TOOLS_TRANSFORMCOMPONENT_H
