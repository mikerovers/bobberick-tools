#include "CollisionComponent.h"
#include <utility>
#include "../../services/ServiceManager.h"
#include "../../services/TextureManager.h"
#include "../../services/RenderService.h"

CollisionComponent::CollisionComponent(std::string tag) : tag(std::move(tag))
{
	collider.x = collider.y = collider.h = collider.w = 0;
}

CollisionComponent::CollisionComponent(std::string tag, int xPos, int yPos, int size) : tag(std::move(tag))
{
	collider.x = xPos;
	collider.y = yPos;
	collider.h = collider.w = size;
}

CollisionComponent::CollisionComponent(std::string tag, int xPos, int yPos, int height, int width): tag(std::move(tag))
{
	collider.x = xPos;
	collider.y = yPos;
	collider.h = height;
	collider.w = width;
}

void CollisionComponent::init()
{
	if (tag == "monster_projectile")
	{
		std::cout << "init aangeroepen" << std::endl;
	}

	if (!entity->hasComponent<TransformComponent>())
	{
		entity->addComponent<TransformComponent>();
	}

	//ServiceManager::Instance()->getService<TextureManager>().load("assets/image/collision.png", "collision", ServiceManager::Instance()->getService<RenderService>().getRenderer());
	texture = "collision";

	sourceRect = {0, 0, 32, 32};
	destinationRect = {collider.x, collider.y, collider.w, collider.h};
}

CollisionComponent::~CollisionComponent()
{
	
}
