#ifndef BOBBERICK_TOOLS_PARTICLECOMPONENT_H
#define BOBBERICK_TOOLS_PARTICLECOMPONENT_H

#include <string>
#include "../Component.h"

class ParticleComponent : public Component
{
public:
    explicit ParticleComponent(int lifeTime): lifeLeft(lifeTime)
    {}

    void liveLife();
    int getLifeLeft() const;
private:
    int lifeLeft;
};


#endif //BOBBERICK_TOOLS_PARTICLECOMPONENT_H
