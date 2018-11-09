#ifndef BOBBERICK_TOOLS_AISYSTEM_H
#define BOBBERICK_TOOLS_AISYSTEM_H


#include "../../bobberick-framework/src/entity/systems/System.h"

class AISystem : public System
{
public:
	explicit AISystem(EntityManager& entityManager);
	void update() override;
	void init() override;
	void stopMoving();
private:
	std::string addSpaces(std::string string, const int goalChars, const bool leading);

};


#endif //BOBBERICK_TOOLS_AISYSTEM_H
