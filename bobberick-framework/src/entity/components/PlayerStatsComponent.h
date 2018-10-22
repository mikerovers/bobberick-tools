#ifndef BOBBERICK_TOOLS_PLAYERSTATSCOMPONENT_H
#define BOBBERICK_TOOLS_PLAYERSTATSCOMPONENT_H

#include "../Component.h"
#include "StatsComponent.h"

class PlayerStatsComponent : public Component
{
public:
	PlayerStatsComponent(StatsComponent& stats, const int shdHpMax, const int shdCoolMax, const int gold, const int xp);

	void update() override; // The shield is recovered in this function.

	void getHit(int attack, const bool pierceDF); // Mitigate attack with DF in offensive mode or with ShdHP in shield mode.
	// If an entity has a PlayerStatsComponent with a StatsComponent in it, call only the PlayerStatsComponent getHit() in your system.

	StatsComponent& stats; // The Component containing the player's basic stats.
	int shdHp = 0; // Shield HP, the amount of hits the player can still absorb (in shield mode).
	int shdHpMax = 0; // Amount of hits the player can absorb at most.
	int shdCool = 0; // Amount of ticks it takes until the next ShdHP point is recovered.
	int shdCoolMax = 0; // Amount of ticks to recover each ShdHP point.
	bool shdActive = false; // Whether or not shield mode is active.
	int gold;
	int xp;
};

#endif //BOBBERICK_TOOLS_PLAYERSTATSCOMPONENT_H