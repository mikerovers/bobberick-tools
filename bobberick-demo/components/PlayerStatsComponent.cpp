#include "PlayerStatsComponent.h"
#include "StatsComponent.h"

PlayerStatsComponent::PlayerStatsComponent(StatsComponent* stats, const double shdTime, const double shdTimeMax, const double shdRecov, const int gold, const int xp) {
	PlayerStatsComponent::shdTime = shdTime;
	PlayerStatsComponent::shdTimeMax = shdTimeMax;
	PlayerStatsComponent::shdRecov = shdRecov;
	shdActive = false;
	PlayerStatsComponent::gold = gold;
	PlayerStatsComponent::xp = xp;
	PlayerStatsComponent::stats = stats;
}

void PlayerStatsComponent::update() {
	if (stats->getHP() > 0) { // Shield recovery freezes when the player is dead.
		if (shdActive) {
			shdTime -= 1;
			if (shdTime <= 0) {
				shdActive = false;
			}
		} else { // The shield mode only recovers when inactive.
			shdTime += shdRecov;
			if (shdTime > shdTimeMax) {
				shdTime = shdTimeMax;
			}
		}
	} else {
		shdActive = false;
	}
}

void PlayerStatsComponent::toggleShield() {
	if (!shdActive && shdTime / shdTimeMax >= 0.5) {
		shdActive = true;
	} else if (shdActive) {
		shdActive = false;
	}
}

const bool PlayerStatsComponent::shieldActive() const {
	return shdActive;
}

void PlayerStatsComponent::getHit(int attack, const bool pierceDF) {
	if (!shdActive) {
		stats->getHit(attack, pierceDF); // Shield mode not active, get hit normally.
	}
}

PlayerStatsComponent::~PlayerStatsComponent()
{
	//delete stats;
}
