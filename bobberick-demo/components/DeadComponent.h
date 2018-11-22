#pragma once
#include "../../bobberick-framework/src/entity/Component.h"

class DeadComponent : public Component
{
public:
	DeadComponent() = default;
	bool handledDeath = false;
};
