#ifndef BOBBERICK_TOOLS_PARTICLESYSTEMCOMPONENT_H
#define BOBBERICK_TOOLS_PARTICLESYSTEMCOMPONENT_H


#include "../Component.h"
#include "ParticleComponent.h"

class ParticleSystemComponent : public Component
{
public:
    explicit ParticleSystemComponent(std::string textureID, int lifeTime, int particlesToSpawn, int spawnDuration): textureID(textureID), lifeTime(lifeTime), particlesToSpawn(particlesToSpawn), spawnDuration(spawnDuration)
    {};

    void init() override;
    void update() override;
    void render() override;

    Entity &createParticle(int x, int y) const;
    void spawnParticles(int x, int y);
    int getParticlesToSpawn() const;
private:
    std::string textureID;
    int lifeTime;
    int particlesToSpawn;
    int spawnDuration;
};


#endif //BOBBERICK_TOOLS_PARTICLESYSTEMCOMPONENT_H
