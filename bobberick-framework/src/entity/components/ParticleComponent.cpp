#include "ParticleComponent.h"

void ParticleComponent::liveLife()
{
    --lifeLeft;
}

int ParticleComponent::getLifeLeft() const
{
    return lifeLeft;
}

Vector2D ParticleComponent::getVelocityCurve() const
{
    return velocityCurve;
}

void ParticleComponent::setVelocityCurve(Vector2D v)
{
    velocityCurve = v;
}
