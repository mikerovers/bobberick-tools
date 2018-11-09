//
// Created by Mike Rovers on 08/09/2018.
//

#include "EntityManager.h"

void EntityManager::init()
{

}

void EntityManager::refresh()
{
    entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::shared_ptr<Entity> &mEntity) {
        return !mEntity->isActive();
    }),
        std::end(entities)
    );
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
    for(auto& group : groupedEntities) {
        auto& groupVector = group.second;
        groupVector.erase(
            std::remove_if(std::begin(groupVector), std::end(groupVector), [group](Entity* entity) {
                return entity->isDeleted() || entity->hasGroup(group.first);
            }), std::end(groupVector)
            );
    }

    entities.erase(std::remove_if(std::begin(entities), std::end(entities),
        [](const std::unique_ptr<Entity> &uEntity) {
            return uEntity->isDeleted();
        }), std::end(entities));
}

void EntityManager::addEntityToGroup(const Entity *entity, const Group group)
{
    groupedEntities[group].emplace_back(entity);
}

std::vector<Entity *> &EntityManager::getGroup(const Group group) const
{
    return groupedEntities[group];
}
