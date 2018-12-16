#include "ParticleSystemComponent.h"
#include "../../services/ServiceManager.h"
#include "../EntityManager.h"
#include "SpriteComponent.h"
#include "../../util/RandomGenerator.h"

void ParticleSystemComponent::init()
{
    Component::init();
}

void ParticleSystemComponent::update()
{
    Component::update();
}

void ParticleSystemComponent::render()
{
    Component::render();
}

Entity &ParticleSystemComponent::createParticle(int x, int y) const
{
    auto& particle = ServiceManager::Instance()->getService<EntityManager>().addEntity();
    particle.addComponent<ParticleComponent>(lifeTime);
    auto& transform = particle.addComponent<TransformComponent>(x, y, 32, 32, 1);
    particle.addComponent<SpriteComponent>(textureID.c_str(), 1);

    const int moveAngle = RandomGenerator{}.getRandomNumber(0, 360);
    const double xVel = transform.speed * cos(moveAngle);
    const double yVel = transform.speed * sin(moveAngle);
    transform.velocity.x = xVel;
    transform.velocity.y = yVel;

    return particle;
}

void ParticleSystemComponent::spawnParticles(int x, int y)
{
    auto amountToSpawn = particlesToSpawn / spawnDuration;
    if (amountToSpawn < 1) {
        amountToSpawn = 1;
    }

    for (auto i = 0; i < amountToSpawn; ++i) {
        createParticle(x, y);
    }

    particlesToSpawn -= amountToSpawn;
}

int ParticleSystemComponent::getParticlesToSpawn() const
{
    return particlesToSpawn;
}
