#include "TransformComponent.h"

TransformComponent::TransformComponent(): scale(1)
{

}

TransformComponent::TransformComponent(int sc)
{
	scale = sc;
}

TransformComponent::TransformComponent(float xPos, float yPos, int h, int w, double sc)
{
	if (xPos >= 0) position.x  = xPos;
	if (yPos >= 0) position.y = yPos;
	height = h;
	width = w;
	scale = sc;
}

void TransformComponent::update()
{
    position.x = position.x + velocity.x * speed;
    position.y = position.y + velocity.y * speed;
}

void TransformComponent::init()
{
    velocity.zero();
}

double TransformComponent::getScale() const
{
	return scale;
}

void TransformComponent::setScale(const double nScale)
{
	scale = nScale;
}
