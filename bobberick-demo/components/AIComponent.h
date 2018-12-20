#ifndef BOBBERICK_TOOLS_AICOMPONENT_H
#define BOBBERICK_TOOLS_AICOMPONENT_H


#include "../../bobberick-framework/src/entity/Component.h"

class AIComponent : public Component
{
public:
    Entity* entity{};
};


#endif //BOBBERICK_TOOLS_AICOMPONENT_H
