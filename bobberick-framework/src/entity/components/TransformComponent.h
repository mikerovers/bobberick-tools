#ifndef BOBBERICK_TOOLS_TRANSFORMCOMPONENT_H
#define BOBBERICK_TOOLS_TRANSFORMCOMPONENT_H


#include "../Component.h"
#include "../../util/Vector2D.h"

class TransformComponent : public Component
{
public:
    Vector2D position = Vector2D(0, 0);
    Vector2D velocity = Vector2D(0, 0);

    int height = 32;
    int width = 32;
    int scale = 1;

    int speed = 3;

    TransformComponent();
    TransformComponent(int sc);
    TransformComponent(float xPos, float yPos, int h, int w, int sc);

    void update() override;
    void init() override;
};


#endif //BOBBERICK_TOOLS_TRANSFORMCOMPONENT_H