#ifndef BOBBERICK_TOOLS_MENUSYSTEM_H
#define BOBBERICK_TOOLS_MENUSYSTEM_H


#include "../../bobberick-framework/src/entity/systems/System.h"

class MenuSystem : public System
{
public:
	explicit MenuSystem(EntityManager& entityManager);
	void update() override;
private:
};


#endif //BOBBERICK_TOOLS_MENUSYSTEM_H
