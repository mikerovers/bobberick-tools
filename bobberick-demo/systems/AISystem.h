#ifndef BOBBERICK_TOOLS_AISYSTEM_H
#define BOBBERICK_TOOLS_AISYSTEM_H


#include "../../bobberick-framework/src/entity/systems/System.h"
#include "../../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../../bobberick-framework/src/entity/components/ShootComponent.h"
#include "../../bobberick-demo/components/PlayerStatsComponent.h"
class AISystem : public System
{
public:
	explicit AISystem(EntityManager& entityManager);
	void update() override;
	void init() override;

private:
	std::string addSpaces(std::string string, const int goalChars, const bool leading);
	void executeShoot(std::shared_ptr<Entity> entity, int &channelCounter);
	void applyHealthBar(std::shared_ptr<Entity> entity);
	void applyMovement(std::shared_ptr<Entity> entity);
};


#endif //BOBBERICK_TOOLS_AISYSTEM_H
