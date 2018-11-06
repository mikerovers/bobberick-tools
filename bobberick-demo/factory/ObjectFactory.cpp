#include "ObjectFactory.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/entity/EntityManager.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"

Entity* ObjectFactory::getObject(const TileObject* object)
{
    if(object->name == "healthkit") {
        std::shared_ptr<Entity> entity = ServiceManager::Instance()->getService<EntityManager>().addEntity();
        entity->addComponent<TransformComponent>(object->position->getX(), object->position->getY(), 92, 64, 1);
        entity->addComponent<SpriteComponent>("assets/image/potion.png", "potion");

        return entity.get();
    }

    return new Entity();
}