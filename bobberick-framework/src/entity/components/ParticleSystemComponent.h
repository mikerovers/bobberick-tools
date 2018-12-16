#ifndef BOBBERICK_TOOLS_PARTICLESYSTEMCOMPONENT_H
#define BOBBERICK_TOOLS_PARTICLESYSTEMCOMPONENT_H

#include "../Component.h"
#include <vector>
#include "ParticleComponent.h"

class ParticleSystemComponent : public Component
{
public:
    explicit ParticleSystemComponent(std::string textureID, int lifeTime, int particlesToSpawn, int spawnDuration): lifeTime(lifeTime), particlesToSpawn(particlesToSpawn), spawnDuration(spawnDuration)
    {
        textures.emplace_back(textureID);
    };

    void init() override;
    void update() override;
    void render() override;

    Entity &createParticle(int x, int y) const;
    void addTexture(std::string const textureID);
    void spawnParticles(int x, int y);
    int getParticlesToSpawn() const;
private:
    std::vector<std::string> textures;
    int lifeTime;
    int particlesToSpawn;
    int spawnDuration;
};


#endif //BOBBERICK_TOOLS_PARTICLESYSTEMCOMPONENT_H
