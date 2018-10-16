#include "PlayerStatsComponent.h"
#include "StatsComponent.h"

PlayerStatsComponent::PlayerStatsComponent(StatsComponent& stats, const int shdhpmax, const int shdcoolmax, const int gold, const int xp) {
	shdhp = this.shdhpmax = shdhpmax;
	shdcool = this.shdcoolmax = shdcoolmax;
	shdactive = false;
	this.gold = gold;
	this.xp = xp;
	this.stats = stats;
}

void PlayerStatsComponent::update() {
	if (shdactive) {
		shdcool = shdcoolmax;
		if (shdhp <= 0) { // ShdHP reached 0, get kicked out of shield mode.
			shdactive = false;
		}
	} else if (shdhp < shdhpmax) { // The shield mode only recovers when inactive.
		shdcool--;
		if (shdcool == 0) { // Shield cooldown reached 0, replenish one Shield HP.
			shdcool = shdcoolmax;
			shdhp++;
		}
	}
}

void PlayerStatsComponent::getHit(int attack, const bool pierceDF) {
	if (shdactive) {
		shdhp--; // Block this attack in shield mode.
		if (shdhp <= 0) {
			shdhp = 0; // ShdHP reached 0, get kicked out of shield mode.
			shdactive = false;
		}
	} else {
		stats.getHit(attack, pierceDF); // Shield mode not active, get hit normally.
	}
}