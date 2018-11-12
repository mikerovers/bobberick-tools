#include "RectangleComponent.h"
#include "../Entity.h"
#include "../../services/ServiceManager.h"
#include "../../services/RectangleManager.h"
#include "../../services/RenderService.h"

void RectangleComponent::init()
{
    transform = &entity->getComponent<TransformComponent>();

	destinationRect.w = transform->width;
	destinationRect.h = transform->height;
	destinationRect.x = transform->position.getX();
	destinationRect.y = transform->position.getY();
}

void RectangleComponent::update()
{
	destinationRect.w = transform->width;
	destinationRect.h = transform->height;
	destinationRect.x = transform->position.getX();
	destinationRect.y = transform->position.getY();
}

void RectangleComponent::render()
{
    ServiceManager::Instance()->getService<RectangleManager>().draw(&destinationRect, ServiceManager::Instance()->getService<RenderService>().getRenderer(), red, green, blue, filled);
}

RectangleComponent::RectangleComponent()
{
	red = 0;
	green = 0;
	blue = 0;
	filled = true;
}

RectangleComponent::RectangleComponent(const int red, const int green, const int blue, const bool filled)
{
	RectangleComponent::red = red;
	RectangleComponent::green = green;
	RectangleComponent::blue = blue;
	RectangleComponent::filled = filled;
}
