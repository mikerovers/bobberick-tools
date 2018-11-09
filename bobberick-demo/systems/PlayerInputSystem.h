#ifndef BOBBERICK_TOOLS_PLAYERINPUTSYSTEM_H
#define BOBBERICK_TOOLS_PLAYERINPUTSYSTEM_H


#include "../../bobberick-framework/src/entity/systems/System.h"

class PlayerInputSystem : public System
{

public:
    explicit PlayerInputSystem(EntityManager& entityManager);
    void update() override;
private: 
	void handleKeyInput(std::shared_ptr<Entity> entity);
	void handleMouseInput(std::shared_ptr<Entity> entity);
};


#endif //BOBBERICK_TOOLS_PLAYERINPUTSYSTEM_H
