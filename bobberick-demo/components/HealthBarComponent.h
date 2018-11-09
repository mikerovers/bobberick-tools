#ifndef BOBBERICK_TOOLS_HEALTHBARCOMPONENT_H
#define BOBBERICK_TOOLS_HEALTHBARCOMPONENT_H


#include <memory>


#include "../../bobberick-framework/src/entity/Component.h"

class HealthBarComponent : public Component
{
public:
    Entity* entity{};
	void init() override;
	std::shared_ptr<Entity> outerBox; // The outline for the health bar.
	std::shared_ptr<Entity> innerBox; // The background for the health bar.
	std::shared_ptr<Entity> healthBox; // The remaining health bar itself.
private:

};


#endif //BOBBERICK_TOOLS_HEALTHBARCOMPONENT_H
