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

    // TODO remove shared pointer.
    entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::shared_ptr<Entity> &entity) {
        return entity->isDeleted();
    }), std::end(entities));
}

std::shared_ptr<Entity> EntityManager::addEntity()
{
    std::shared_ptr<Entity> uPtr{ new Entity };
    entities.emplace_back(uPtr);

    return uPtr;
}

bool EntityManager::removeEntity(const std::shared_ptr<Entity> entity)
{
    auto it = std::find(entities.begin(), entities.end(), entity);
    if (it != entities.end()) {
        entities.erase(it);
    } else {
        SDL_Log("An entity that would be deleted could not be found.");
        return false;
    }

    return true;
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
