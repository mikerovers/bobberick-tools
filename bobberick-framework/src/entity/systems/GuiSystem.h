#ifndef BOBBERICK_TOOLS_GUISYSTEM_H
#define BOBBERICK_TOOLS_GUISYSTEM_H

#include "System.h"

class GuiSystem : public System
{
public:
    explicit GuiSystem(EntityManager& entityManager);
    void update() override;
};


#endif //BOBBERICK_TOOLS_GUISYSTEM_H
