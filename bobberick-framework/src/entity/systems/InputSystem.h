#ifndef BOBBERICK_TOOLS_INPUTSYSTEM_H
#define BOBBERICK_TOOLS_INPUTSYSTEM_H

#include "System.h"

class InputSystem : public System
{
public:
	InputSystem(EntityManager& entityManager);

    void update() override;
    void clean();
};


#endif //BOBBERICK_TOOLS_INPUTSYSTEM_H
