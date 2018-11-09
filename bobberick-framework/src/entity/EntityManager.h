#ifndef BOBBERICK_TOOLS_MANAGER_H
#define BOBBERICK_TOOLS_MANAGER_H

#include <map>
#include "Entity.h"
#include "SDL.h"
#include "../services/Service.h"

class EntityManager : public Service {
public:
    EntityManager() = default;

    void refresh();
    void init() override;
    void clean() override;

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
    bool removeEntity(const std::shared_ptr<Entity> entity);
    void addEntityToGroup(const Entity* entity, const Group group);
    std::vector<Entity*>& getGroup(const Group group) const;
private:
    std::vector<std::shared_ptr<Entity>> entities;
    std::map<Group, std::vector<Entity*>> groupedEntities;
};


#endif //BOBBERICK_TOOLS_MANAGER_H
