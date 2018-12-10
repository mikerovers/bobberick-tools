#include "ParticleComponent.h"

void ParticleComponent::liveLife()
{
    --lifeLeft;
}

int ParticleComponent::getLifeLeft() const
{
    return lifeLeft;
}
