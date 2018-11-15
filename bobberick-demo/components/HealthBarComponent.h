#ifndef BOBBERICK_TOOLS_HEALTHBARCOMPONENT_H
#define BOBBERICK_TOOLS_HEALTHBARCOMPONENT_H


#include <memory>


#include "../../bobberick-framework/src/entity/Component.h"

class HealthBarComponent : public Component
{
public:
	HealthBarComponent();

    Entity* entity{};
	void init() override;
	Entity& outerBox; // The outline for the health bar.
	Entity& innerBox; // The background for the health bar.
	Entity& healthBox; // The remaining health bar itself.
private:

};


#endif //BOBBERICK_TOOLS_HEALTHBARCOMPONENT_H
