#ifndef BOBBERICK_TOOLS_BULLETMOVEMENTCOMPONENT_H
#define BOBBERICK_TOOLS_BULLETMOVEMENTCOMPONENT_H


#include "../../bobberick-framework/src/entity/Component.h"

class BulletMovementComponent : public Component
{
public:
	Entity* entity{};

	void init() override;
	void update() override;
	void render() override;

};


#endif //BOBBERICK_TOOLS_BULLETMOVEMENTCOMPONENT_H
