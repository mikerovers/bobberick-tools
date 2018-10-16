#ifndef BOBBERICK_TOOLS_PLAYERSTATSCOMPONENT_H
#define BOBBERICK_TOOLS_PLAYERSTATSCOMPONENT_H

#include "../Component.h"
#include "StatsComponent.h"

class PlayerStatsComponent : public Component
{
public:
	PlayerStatsComponent(StatsComponent& stats, const int shdhpmax, const int shdcoolmax, const int gold, const int xp);

	void update() override;

	void getHit(int attack, const bool pierceDF); // Mitigate attack with DF in offensive mode or with ShdHP in defensive mode.
	// This method must be called instead of the StatsComponent getHit() when the player is hit.

	StatsComponent& stats; // The Component containing the player's basic stats.
	int shdhp = 0; // Shield HP, the amount of hits the player can still absorb (in shield mode).
	int shdhpmax = 0; // Amount of hits the player can absorb at most.
	int shdcool = 0; // Amount of ticks it takes until the next ShdHP point is recovered.
	int shdcoolmax = 0; // Amount of ticks to recover each ShdHP point.
	bool shdactive = 0; // Whether or not shield mode is active.
	int gold;
	int xp;
};

#endif //BOBBERICK_TOOLS_PLAYERSTATSCOMPONENT_H