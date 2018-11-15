#ifndef BOBBERICK_TOOLS_TRANSFORMCOMPONENT_H
#define BOBBERICK_TOOLS_TRANSFORMCOMPONENT_H


#include "../Component.h"
#include "../../util/Vector2D.h"

class TransformComponent : public Component
{
public:
	TransformComponent();
	explicit TransformComponent(int sc);
	explicit TransformComponent(float xPos, float yPos, int h, int w, int sc);

    Vector2D position = Vector2D(0, 0);
    Vector2D velocity = Vector2D(0, 0);

    int height = 256;
    int width = 256;

    double speed = 3;

	bool visible = true;

    void update() override;
    void init() override;

    int getScale() const;
    void setScale(const int nScale);

protected:
	int scale;
};


#endif //BOBBERICK_TOOLS_TRANSFORMCOMPONENT_H
