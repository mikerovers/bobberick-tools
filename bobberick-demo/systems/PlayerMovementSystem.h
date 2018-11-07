#ifndef BOBBERICK_TOOLS_PLAYERMOVEMENTSYSTEM_H
#define BOBBERICK_TOOLS_PLAYERMOVEMENTSYSTEM_H

#include "../../bobberick-framework/src/entity/systems/System.h"

class PlayerMovementSystem : System
{
public:
    explicit PlayerMovementSystem(EntityManager& entityManager);

    void update() override;
private:
    EntityManager* entityManager;
};


#endif //BOBBERICK_TOOLS_PLAYERMOVEMENTSYSTEM_H
