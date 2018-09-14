//
// Created by Mike Rovers on 08/09/2018.
//

#ifndef BOBBERICK_TOOLS_MANAGER_H
#define BOBBERICK_TOOLS_MANAGER_H


#include "Entity.h"
#include "../services/Service.h"

class EntityManager : public Service {
public:
    EntityManager() = default;

    void update();
    void render();
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

    Entity& addEntity();
private:
    std::vector<std::shared_ptr<Entity>> entities;
};


#endif //BOBBERICK_TOOLS_MANAGER_H
