//
// Created by Mike Rovers on 08/09/2018.
//

#include "EntityManager.h"

void EntityManager::init()
{

}

void EntityManager::update()
{
    for (auto& entity : entities) {
        entity->update();
    }
}

void EntityManager::render()
{
    for (auto& entity : entities) {
        entity->render();
    }
}

void EntityManager::refresh()
{
    entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::shared_ptr<Entity> &mEntity) {
        return !mEntity->isActive();
    }),
        std::end(entities)
    );
}

Entity &EntityManager::addEntity()
{
    auto * e = new Entity();
    std::unique_ptr<Entity> uPtr{ e };
    entities.emplace_back(std::move(uPtr));

    return *e;
}
