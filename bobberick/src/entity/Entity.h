#ifndef BOBBERICK_TOOLS_ENTITY_H
#define BOBBERICK_TOOLS_ENTITY_H

#include "ECS.h"

class Entity
{
public:
    void update();
    void render();
    bool isActive() const;
    void destroy();

    template <typename T> bool hasComponent() const
    {
        return componentBitSet[getComponentTypeID<T>()];
    }

    template <typename T, typename ... TArgs> T& addComponent(TArgs&&... mArgs)
    {
        T *c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;
        std::unique_ptr<Component> uPtr{c};
        components.emplace_back(std::move(uPtr));

        componentArray[getComponentTypeID<T>()] = c;
        componentBitSet[getComponentTypeID<T>()] = true;

        c->init();

        return *c;
    }

    template <typename T> T& getComponent() const
    {
        auto ptr(componentArray[getComponentTypeID<T>()]);

        return *static_cast<T*>(ptr);
    }

private:
    bool active = true;
    std::vector<std::shared_ptr<Component>> components;

    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
};

#endif //BOBBERICK_TOOLS_ENTITY_H
