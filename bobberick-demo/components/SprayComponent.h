#pragma once
#include "../../bobberick-framework/src/entity/Component.h"

class SprayComponent : public Component
{
public:
	int sprayTimer{5000}; // ms
};
