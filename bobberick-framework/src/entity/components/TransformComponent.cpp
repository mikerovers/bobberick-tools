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

double TransformComponent::getScale() const
{
	return scale;
}

void TransformComponent::setScale(const double nScale)
{
	scale = nScale;
}
