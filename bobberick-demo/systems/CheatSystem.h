#ifndef BOBBERICK_TOOLS_CHEATSYSTEM_H
#define BOBBERICK_TOOLS_CHEATSYSTEM_H


#include "../../bobberick-framework/src/entity/systems/System.h"

class CheatSystem : public System
{
public:
	explicit CheatSystem(EntityManager& entityManager);
	void update() override;
private:
	void handleKeyInput(Entity* entity);
};


#endif //BOBBERICK_TOOLS_CHEATSYSTEM_H
