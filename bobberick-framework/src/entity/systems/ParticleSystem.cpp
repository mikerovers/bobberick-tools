#include "ParticleSystem.h"
#include "../components/ParticleSystemComponent.h"
#include "../components/TransformComponent.h"

ParticleSystem::ParticleSystem(EntityManager &entityManager) : System(entityManager)
{

}

void ParticleSystem::update()
{
    for(auto& entity : entityManager.getAllEntitiesWithComponent<ParticleSystemComponent>()) {
        auto& particleSystem = entity->getComponent<ParticleSystemComponent>();
        auto& transformComponent = entity->getComponent<TransformComponent>();
        particleSystem.spawnParticles(transformComponent.position.x, transformComponent.position.y);
        if (particleSystem.getParticlesToSpawn() <= 0) {
            entity->destroy();
        }
    }

    for(auto& entity : entityManager.getAllEntitiesWithComponent<ParticleComponent>()) {
        auto& particle = entity->getComponent<ParticleComponent>();
        auto& transform = entity->getComponent<TransformComponent>();
        transform.update();
        particle.liveLife();

        if (particle.getLifeLeft() <= 0) {
            entity->destroy();
        }
    }
}

