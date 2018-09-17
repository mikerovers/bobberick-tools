#include "Entity.h"

bool Entity::isActive() const
{
    return active;
}

void Entity::destroy()
{
    active = false;
}
