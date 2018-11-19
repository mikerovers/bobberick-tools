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
	static std::string addSpaces(const std::string& string, const int goalChars, const bool leading);
	void executeShoot(Entity& entity, int &channelCounter);
	static void executeSpell(Entity& entity);
	static void executeSpawner(Entity& entity);
	static void initHealthBar(Entity& entity);
	static void applyHealthBar(Entity& entity);
	static void applyMovement(Entity& entity);
	static void kill(Entity& entity);
};


#endif //BOBBERICK_TOOLS_AISYSTEM_H
