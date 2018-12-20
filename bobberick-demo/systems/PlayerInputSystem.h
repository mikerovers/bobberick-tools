#ifndef BOBBERICK_TOOLS_PLAYERINPUTSYSTEM_H
#define BOBBERICK_TOOLS_PLAYERINPUTSYSTEM_H


#include "../../bobberick-framework/src/entity/systems/System.h"

class PlayerInputSystem : public System
{
public:
	explicit PlayerInputSystem(EntityManager& entityManager);
	void update() override;
private:
	void handleKeyInput(Entity* entity);
	void handleMouseInput(Entity* entity) const;
	int skipForRepeat = 0;
};


#endif //BOBBERICK_TOOLS_PLAYERINPUTSYSTEM_H
