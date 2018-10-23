#ifndef BOBBERICK_TOOLS_PLAYERMOVEMENTCOMPONENT_H
#define BOBBERICK_TOOLS_PLAYERMOVEMENTCOMPONENT_H


#include "../../bobberick-framework/src/entity/Component.h"

class PlayerMovementComponent : public Component
{
public:
    Entity* entity{};

    void init() override;
    void update() override;
    void render() override;

};


#endif //BOBBERICK_TOOLS_PLAYERMOVEMENTCOMPONENT_H
