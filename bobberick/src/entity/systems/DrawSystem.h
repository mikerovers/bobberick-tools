#ifndef BOBBERICK_TOOLS_DRAWSYSTEM_H
#define BOBBERICK_TOOLS_DRAWSYSTEM_H

#include "System.h"
#include "../components/SpriteComponent.h"

class DrawSystem : public System
{
public:
    DrawSystem(EntityManager& entityManager);

    void update() override;
};


#endif //BOBBERICK_TOOLS_DRAWSYSTEM_H
