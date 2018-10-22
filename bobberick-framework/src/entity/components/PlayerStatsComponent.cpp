#include "PlayerStatsComponent.h"
#include "StatsComponent.h"

PlayerStatsComponent::PlayerStatsComponent(StatsComponent& stats, const int shdHpMax, const int shdCoolMax, const int gold, const int xp) {
	shdHp = this.shdHpMax = shdHpMax;
	shdCool = this.shdCoolMax = shdCoolMax;
	shdActive = false;
	this.gold = gold;
	this.xp = xp;
	this.stats = stats;
}

void PlayerStatsComponent::update() {
	if (shdActive) {
		shdCool = shdCoolMax;
		if (shdHp <= 0) { // ShdHP reached 0, get kicked out of shield mode.
			shdActive = false;
		}
	} else if (shdHp < shdHpMax) { // The shield mode only recovers when inactive.
		shdCool--;
		if (shdCool == 0) { // Shield cooldown reached 0, replenish one Shield HP.
			shdCool = shdCoolMax;
			shdHp++;
		}
	}
}

void PlayerStatsComponent::getHit(int attack, const bool pierceDF) {
	if (shdActive) {
		shdHp--; // Block this attack in shield mode.
		if (shdHp <= 0) {
			shdHp = 0; // ShdHP reached 0, get kicked out of shield mode.
			shdActive = false;
		}
	} else {
		stats.getHit(attack, pierceDF); // Shield mode not active, get hit normally.
	}
}