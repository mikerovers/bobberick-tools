#include "Entity.h"

void Entity::update()
{
    for (auto& c : components) {
        c->update();
    }

    for (auto& c: components) {
        c->render();
    }
}

bool Entity::isActive() const
{
    return active;
}

void Entity::destroy()
{
    active = false;
}

void Entity::render()
{
    for (auto& c: components) {
        c->render();
    }
}

