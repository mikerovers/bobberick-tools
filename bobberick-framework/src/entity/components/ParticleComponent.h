#ifndef BOBBERICK_TOOLS_PARTICLECOMPONENT_H
#define BOBBERICK_TOOLS_PARTICLECOMPONENT_H

#include <string>
#include "../Component.h"
#include "../../util/Vector2D.h"

class ParticleComponent : public Component
{
public:
    explicit ParticleComponent(int lifeTime, Vector2D velocityCurve) : lifeLeft(lifeTime), velocityCurve(velocityCurve)
    {}

    void liveLife();
    int getLifeLeft() const;

    Vector2D getVelocityCurve() const;
    void setVelocityCurve(Vector2D v);
private:
    int lifeLeft;
    Vector2D velocityCurve;
};


#endif //BOBBERICK_TOOLS_PARTICLECOMPONENT_H
