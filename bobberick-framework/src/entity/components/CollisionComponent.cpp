#include "CollisionComponent.h"
#include <utility>
#include "../../services/ServiceManager.h"
#include "../../TextureManager.h"
#include "../../services/RenderService.h"

CollisionComponent::CollisionComponent(std::string tag) : tag(std::move(tag))
{
	collider = new SDL_Rect();
	collider->x = collider->y = collider->h = collider->w = 0;
}

CollisionComponent::CollisionComponent(std::string tag, int xPos, int yPos, int size) : tag(std::move(tag))
{
	collider = new SDL_Rect();
	collider->x = xPos;
	collider->y = yPos;
	collider->h = collider->w = size;
}

CollisionComponent::CollisionComponent(std::string tag, int xPos, int yPos, int height, int width): tag(std::move(tag))
{
	collider = new SDL_Rect();
	collider->x = xPos;
	collider->y = yPos;
	collider->h = height;
	collider->w = width;
}

void CollisionComponent::init()
{
	if (!entity->hasComponent<TransformComponent>())
	{
		entity->addComponent<TransformComponent>();
	}

	//ServiceManager::Instance()->getService<TextureManager>().load("assets/image/collision.png", "collision", ServiceManager::Instance()->getService<RenderService>().getRenderer());
	texture = "collision";

	sourceRect = {0, 0, 32, 32};
	destinationRect = {collider->x, collider->y, collider->w, collider->h};
}

CollisionComponent::~CollisionComponent()
{
    delete collider;
}
