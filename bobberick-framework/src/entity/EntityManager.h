#ifndef BOBBERICK_TOOLS_MANAGER_H
#define BOBBERICK_TOOLS_MANAGER_H

#include <map>
#include "Entity.h"
#include "SDL.h"
#include "../services/Service.h"

class EntityManager : public Service
{
public:
	EntityManager() = default;

	void refresh();
	void init() override;
	void clean() override;

	template <typename T>
	std::vector<Entity*> getAllEntitiesWithComponent()
	{
		std::vector<Entity*> temp;

		for (auto& entity : entities)
		{
			if (entity->isActive() && entity->hasComponent<T>())
			{
				temp.emplace_back(entity.get());
			}
		}

		return temp;
	}

	Entity& addEntity();
	void addEntityToGroup(Entity& entity, const Group group);
	std::vector<Entity*>& getEntitiesFromGroup(const Group group);
	void activateEntitiesFromGroup(const Group group, const bool active);
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::map<Group, std::vector<Entity*>> groupedEntities;
};


#endif //BOBBERICK_TOOLS_MANAGER_H
