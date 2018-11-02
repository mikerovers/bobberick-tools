#ifndef BOBBERICK_TOOLS_HUDSYSTEM_H
#define BOBBERICK_TOOLS_HUDSYSTEM_H

#include "../../bobberick-framework/src/entity/systems/System.h"

class HudSystem : public System
{
public:
    explicit HudSystem(EntityManager& entityManager);
    void update() override;
	void init() override;
private:
	const int barWidth = 300; // The width boundary of the inner bars.

	std::shared_ptr<Entity> hudBox; // The HUD background rectangle.
	std::shared_ptr<Entity> outerBox; // The outline for the health bar.
	std::shared_ptr<Entity> innerBox; // The background for the health bar.
	std::shared_ptr<Entity> healthBox; // The remaining health bar itself.
	std::shared_ptr<Entity> shieldBox; // The shield bar, inside the health bar.

	std::shared_ptr<Entity> coinImage; // The image representing the amount of gold.
	std::shared_ptr<Entity> coinText; // The text representing the amount of gold.
	std::shared_ptr<Entity> xpImage; // The image representing the amount of XP.
	std::shared_ptr<Entity> xpText; // The text representing the amount of XP.
};


#endif //BOBBERICK_TOOLS_HUDSYSTEM_H
