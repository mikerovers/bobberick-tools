#include "TransformComponent.h"

TransformComponent::TransformComponent()
{
}

TransformComponent::TransformComponent(float xPos, float yPos, int h, int w, int sc)
{
    position.setX(xPos);
    position.setY(yPos);
    height = h;
    width = w;
    scale = sc;
}


TransformComponent::TransformComponent(int sc)
{
    scale = sc;
}


void TransformComponent::update()
{
    position.setX(velocity.getX() * speed);
    position.setY(velocity.getY() * speed);
}

void TransformComponent::init()
{
    velocity.Zero();
}