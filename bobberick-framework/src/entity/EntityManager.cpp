//
// Created by Mike Rovers on 08/09/2018.
//

#include "EntityManager.h"

void EntityManager::init()
{

}

void EntityManager::refresh()
{

    for(auto& group : groupedEntities) {
        auto& g(group.second);

        g.erase(
               std::remove_if(std::begin(g), std::end(g), [group](Entity* entity) {
              return entity->isDeleted() || !entity->hasGroup(group.first);
            }), std::end(g));
    }

    entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity> &entity) {
        return entity->isDeleted();
    }), std::end(entities));
}

Entity* EntityManager::addEntity()
{
    std::unique_ptr<Entity> uPtr = std::make_unique<Entity>();
    entities.emplace_back(std::move(uPtr));

    return entities.back().get();
}

void EntityManager::clean()
{

}

void EntityManager::addEntityToGroup(Entity *entity, const Group group)
{
    auto& vectorOfEntities = groupedEntities[group];
    vectorOfEntities.push_back(entity);
    entity->addGroup(group);
}

std::vector<Entity*> &EntityManager::getEntitiesFromGroup(const Group group)
{
    auto& a = groupedEntities[group];
    return groupedEntities.find(group)->second;
}
