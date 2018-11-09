#include "TransformComponent.h"

TransformComponent::TransformComponent() = default;

TransformComponent::TransformComponent(int sc)
{
	scale = sc;
}

TransformComponent::TransformComponent(float xPos, float yPos, int h, int w, int sc)
{
	if (xPos >= 0) position.setX(xPos);
	if (yPos >= 0) position.setY(yPos);
	height = h;
	width = w;
	scale = sc;
}

void TransformComponent::update()
{
    position.setX(position.getX() + (velocity.getX() * speed));
    position.setY(position.getY() + (velocity.getY() * speed));
}

void TransformComponent::init()
{
    velocity.Zero();
}