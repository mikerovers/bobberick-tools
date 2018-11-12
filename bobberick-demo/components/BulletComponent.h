#ifndef BOBBERICK_TOOLS_BULLETCOMPONENT_H
#define BOBBERICK_TOOLS_BULLETCOMPONENT_H


#include "../../bobberick-framework/src/entity/Component.h"

class BulletComponent : public Component
{
public:
	Entity* entity{};
	BulletComponent(const double damage) : damage(damage) {};


	void init() override;
	void update() override;
	void render() override;

	double damage = 0;
};


#endif //BOBBERICK_TOOLS_BULLETCOMPONENT_H
