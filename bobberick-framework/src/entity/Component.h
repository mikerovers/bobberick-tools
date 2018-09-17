#ifndef BOBBERICK_TOOLS_COMPONENT_H
#define BOBBERICK_TOOLS_COMPONENT_H

class Entity;

class Component
{
public:
    Entity* entity{};

    virtual void init() {};
    virtual void update() {};
    virtual void render() {};

    virtual ~Component() {};
};


#endif //BOBBERICK_TOOLS_COMPONENT_H
