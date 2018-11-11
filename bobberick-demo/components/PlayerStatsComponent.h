#ifndef BOBBERICK_TOOLS_PLAYERSTATSCOMPONENT_H
#define BOBBERICK_TOOLS_PLAYERSTATSCOMPONENT_H

#include "../../bobberick-framework/src/entity/Component.h"
#include "StatsComponent.h"

class WeaponComponent;
class PlayerStatsComponent : public Component
{
public:
	PlayerStatsComponent(StatsComponent* stats, const double shdTime, const double shdTimeMax, const double shdRecov, const int gold, const int xp);

	void update() override; // The shield is recovered in this function.

	void getHit(int attack, const bool pierceDF); // Mitigate attack with DF in offensive mode or with ShdHP in shield mode.
	// If an entity has a PlayerStatsComponent with a StatsComponent in it, call only the PlayerStatsComponent getHit() in your system.

	int attack(bool magic, int seed) const; // Generate an attack and modify it based on the power of one of your weapons.
	void toggleShield(); // Activate the shield, if it's charged enough (currently must be at least 50% charged).
	const bool shieldActive() const; // Returns true if the shield is currently active.

	StatsComponent* stats; // The Component containing the player's basic stats.
	double shdTime; // The amount of ticks the shield can still be active.
	double shdTimeMax; // The amount of ticks the shield can be active at most.
	double shdRecov; // The amount of shdTime recovered every tick (when shield is inactive).
	int gold;
	int xp;

	WeaponComponent* normalWeapon;
	WeaponComponent* magicWeapon;
	
private:
	bool shdActive = false; // Whether or not shield mode is active.
};

#endif //BOBBERICK_TOOLS_PLAYERSTATSCOMPONENT_H