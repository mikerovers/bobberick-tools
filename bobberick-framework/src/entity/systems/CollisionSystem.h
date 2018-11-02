#ifndef BOBBERICK_TOOLS_COLLISIONSYSTEM_H
#define BOBBERICK_TOOLS_COLLISIONSYSTEM_H

#include "System.h"

class CollisionSystem : public System
{
public:
    explicit CollisionSystem(EntityManager& entityManager);
    void update() override;
};


#endif //BOBBERICK_TOOLS_COLLISIONSYSTEM_H
