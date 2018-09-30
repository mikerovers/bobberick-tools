#ifndef BOBBERICK_TOOLS_MANAGER_H
#define BOBBERICK_TOOLS_MANAGER_H


#include "Entity.h"
#include "SDL.h"
#include "../services/Service.h"

class EntityManager : public Service {
public:
    EntityManager() = default;

    void refresh();
    void init() override;

    template <typename T>
    std::vector<std::shared_ptr<Entity>> getAllEntitiesWithComponent()
    {
        std::vector<std::shared_ptr<Entity>> temp;

        for (auto& entity : entities) {
            if (entity->hasComponent<T>()) {
                temp.push_back(entity);
            }
        }

        return temp;
    }

    std::shared_ptr<Entity> addEntity();
    bool removeEntity(std::shared_ptr<Entity> entity);
private:
    std::vector<std::shared_ptr<Entity>> entities;
};


#endif //BOBBERICK_TOOLS_MANAGER_H
