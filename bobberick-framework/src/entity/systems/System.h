#ifndef BOBBERICK_TOOLS_SYSTEM_H
#define BOBBERICK_TOOLS_SYSTEM_H


#include "../EntityManager.h"

class System
{
public:
    explicit System(EntityManager& entityManager);
    virtual void update() = 0;
protected:
    EntityManager& entityManager;
};


#endif //BOBBERICK_TOOLS_SYSTEM_H
