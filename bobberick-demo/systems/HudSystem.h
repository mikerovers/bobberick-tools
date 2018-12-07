#ifndef BOBBERICK_TOOLS_HUDSYSTEM_H
#define BOBBERICK_TOOLS_HUDSYSTEM_H

#include "../../bobberick-framework/src/entity/systems/System.h"
#include "../components/WeaponComponent.h"

class HudSystem : public System
{
public:
    explicit HudSystem(EntityManager& entityManager);
    void update() override;
	void init() override;
	void startCompare(WeaponComponent oldWeapon, WeaponComponent newWeapon);
	void stopCompare();
private:
	const int barWidth = 300; // The width boundary of the inner bars.
	int fpsMiddlerCount = 0;
	int const fpsMiddlerDivideBy = 20;
	int fpsMiddlerResult = 0;
	std::vector<int> fpsMiddlerVector;
	bool comparing = false;

	Entity& hudBox; // The HUD background rectangle.
	Entity& outerBox; // The outline for the health bar.
	Entity& innerBox; // The background for the health bar.
	Entity& healthBox; // The remaining health bar itself.
	Entity& shieldBox; // The shield bar, inside the health bar.

	Entity& healthText;
	Entity& coinImage;
	Entity& coinText;
	Entity& xpImage;
	Entity& xpText;
	Entity& oldWeaponText;
	Entity& newWeaponText;

	Entity& inventory;
	Entity& inventorySlot1;
	Entity& inventorySlot2;

	Entity& fpsCounter;

		
};


#endif //BOBBERICK_TOOLS_HUDSYSTEM_H
