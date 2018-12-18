#ifndef BOBBERICK_TOOLS_PARTICLESYSTEM_H
#define BOBBERICK_TOOLS_PARTICLESYSTEM_H


#include "System.h"
#include "../components/ParticleComponent.h"

class ParticleSystem : public System
{
public:
    explicit ParticleSystem(EntityManager& entityManager);
    void update() override;
};


#endif //BOBBERICK_TOOLS_PARTICLESYSTEM_H
