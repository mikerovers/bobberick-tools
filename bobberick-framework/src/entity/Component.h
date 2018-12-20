#ifndef BOBBERICK_TOOLS_COMPONENT_H
#define BOBBERICK_TOOLS_COMPONENT_H

#include <iostream>

class Entity;

class Component
{
public:
    Entity* entity{};

    virtual void init() {};
    virtual void update() {};
    virtual void render() {};

    virtual ~Component() = default;
};


#endif //BOBBERICK_TOOLS_COMPONENT_H
