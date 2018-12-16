#include "ParticleSystemComponent.h"
#include "../../services/ServiceManager.h"
#include "../EntityManager.h"
#include "SpriteComponent.h"
#include "../../util/RandomGenerator.h"
#include "../../StateMachine.h"

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
    auto velocityDecrease = Vector2D{0.1, 0.1};
    particle.addComponent<ParticleComponent>(lifeTime, velocityDecrease);
    auto& transform = particle.addComponent<TransformComponent>(x, y, 32, 32, 1);
    auto t = RandomGenerator{}.getRandomNumber(0, textures.size() - 1);
    particle.addComponent<SpriteComponent>(textures[t].c_str(), false);
    ServiceManager::Instance()->getService<EntityManager>().addEntityToGroup(particle, ServiceManager::Instance()->getService<StateMachine>().peekState().getStateID());

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

void ParticleSystemComponent::addTexture(std::string const textureID)
{
    textures.emplace_back(textureID);
}
