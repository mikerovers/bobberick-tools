#include "Entity.h"

Entity::Entity() : active(true), deleted(false)
{
}

bool Entity::isActive() const
{
    return active;
}

void Entity::destroy()
{
    deleted = true;
}

bool Entity::isDeleted() const
{
    return deleted;
}

void Entity::setActive(const bool isActive)
{
    active = isActive;
}

void Entity::addGroup(const Group group)
{
    if(std::find(groups.begin(), groups.end(), group) == groups.end()) {
        groups.emplace_back(group);
    }
}

bool Entity::hasGroup(const Group group) const
{
    return std::find(groups.begin(), groups.end(), group) != groups.end();
}

void Entity::removeGroup(const Group group)
{
	const auto it = std::find(groups.begin(), groups.end(), group);;
    if(it != groups.end()) {
        groups.erase(it);
    }
}

std::vector<Group> Entity::getGroups() const
{
	return groups;
}
