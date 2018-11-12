#include "ObjectFactory.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/entity/EntityManager.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"

Entity* ObjectFactory::getObject(const TileObject* object)
{
    if(object->name == "healthkit") {
        std::shared_ptr<Entity> entity = ServiceManager::Instance()->getService<EntityManager>().addEntity();
        entity->addComponent<TransformComponent>(object->position->getX(), object->position->getY(), 48, 32, 1);
        entity->addComponent<SpriteComponent>("assets/image/items/potion.png", "potion");

        return entity.get();
    }

    return new Entity();
}
