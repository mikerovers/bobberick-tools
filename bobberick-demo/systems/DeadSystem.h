#pragma once
#include "../../bobberick-framework/src/entity/systems/System.h"

class DeadSystem : public System
{
public:
	explicit DeadSystem(EntityManager& entityManager)
		: System(entityManager)
	{
	}

	void init() override;
	void update() override;
};
