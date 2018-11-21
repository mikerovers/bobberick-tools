#include "ObjectFactory.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/entity/EntityManager.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../bobberick-framework/src/entity/components/CollisionComponent.h"

Entity& ObjectFactory::getObject(const TileObject* object)
{
	if (object->name == "healthkit")
	{
		auto& entity = ServiceManager::Instance()->getService<EntityManager>().addEntity();
		entity.addComponent<TransformComponent>(object->position->x, object->position->y, 48, 32, 1);
		entity.addComponent<SpriteComponent>("potion");
		entity.addComponent<CollisionComponent>(object->name, object->position->x, object->position->y, 48,
		                                        32);

		return entity;
	}

	if (object->name == "water")
	{
		auto& entity = ServiceManager::Instance()->getService<EntityManager>().addEntity();
		entity.addComponent<TransformComponent>(object->position->x, object->position->y, object->aabb.height,
		                                        object->aabb.width, 1);
		entity.addComponent<CollisionComponent>(object->name, object->position->x, object->position->y,
		                                        object->aabb.height, object->aabb.width);


		return entity;
	}	
	
	if (object->name == "aabb_rectangle")
	{
		auto& entity = ServiceManager::Instance()->getService<EntityManager>().addEntity();
		entity.addComponent<TransformComponent>(object->position->x, object->position->y, object->aabb.height,
		                                        object->aabb.width, 1);
		entity.addComponent<CollisionComponent>(object->name, object->position->x, object->position->y,
		                                        object->aabb.height, object->aabb.width);


		return entity;
	}



	return *new Entity();
}
