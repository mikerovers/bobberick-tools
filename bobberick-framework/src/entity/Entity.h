#ifndef BOBBERICK_TOOLS_ENTITY_H
#define BOBBERICK_TOOLS_ENTITY_H

#include "ECS.h"

class Entity
{
public:
    Entity();
    bool isActive() const;
    void setActive(const bool isActive);
    bool isDeleted() const;
    void destroy();

    void addGroup(const Group group);
    bool hasGroup(const Group group) const;
    void removeGroup(const Group group);

    template <typename T> bool hasComponent() const
    {
        return componentBitSet[getComponentTypeID<T>()];
    }

    template <typename T, typename ... TArgs> T& addComponent(TArgs&&... mArgs)
    {
        T *c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;
        std::unique_ptr<Component> uPtr{c};

        if (components.size() < getComponentTypeID<T>()) {
            unsigned int difference = getComponentTypeID<T>() - components.size();
            for (int i = 0 ; i < difference; i++) {
                components.push_back(nullptr);
            }
        }

        components.emplace_back(std::move(uPtr));

        componentArray[getComponentTypeID<T>()] = c;
        componentBitSet[getComponentTypeID<T>()] = true;

        c->init();

        return *c;
    }

    template <typename T, typename... TArgs> void addExistingComponent(Component* component)
    {
        component->entity = this;
        std::unique_ptr<Component> uPtr{component};
        if (components.size() < getComponentTypeID<T>()) {
            unsigned int difference = getComponentTypeID<T>() - components.size();
            for (int i = 0 ; i < difference; i++) {
                components.push_back(nullptr);
            }
        }
        components.emplace_back(std::move(uPtr));
        componentArray[getComponentTypeID<T>()] = component;
        componentBitSet[getComponentTypeID<T>()] = true;
    }

    template <typename T> bool removeComponent()
    {
        auto typeID = getComponentTypeID<T>();
        components[getComponentTypeID<T>()] = nullptr;
        componentBitSet[typeID] = false;

        return true;
    };

    template <typename T> T& getComponent() const
    {
        auto ptr(componentArray[getComponentTypeID<T>()]);

        return *static_cast<T*>(ptr);
    }

private:
    bool active;
    bool deleted;
    std::vector<Group> groups;
    std::vector<std::shared_ptr<Component>> components;

    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
};

#endif //BOBBERICK_TOOLS_ENTITY_H
