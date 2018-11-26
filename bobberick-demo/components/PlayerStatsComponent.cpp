#include "PlayerStatsComponent.h"
#include "StatsComponent.h"
#include "WeaponComponent.h"
#include "../../bobberick-framework/src/StateMachine.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../state/StateFactory.h"

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
		shdTime = 0;
		// Go to the Game Over screen when health reaches 0.
		StateFactory sFactory{};
		ServiceManager::Instance()->getService<StateMachine>().changeState(sFactory.createState("GameOverState"));
	}
}

int PlayerStatsComponent::attack(bool magic, int seed) const {
	int basePow = stats->attack(seed);
	if (magic) {
		return basePow + magicWeapon->power;
	} else {
		return basePow + normalWeapon->power;
	}
}

void PlayerStatsComponent::toggleShield() {
	if (!shdActive && shdTime / shdTimeMax >= 0.5) {
		shdActive = true;
	} else if (shdActive) {
		shdActive = false;
	}
}

void PlayerStatsComponent::equipWeapon(WeaponComponent* weapon) {
	if (weapon->isMagic) {
		*magicWeapon = *weapon;
	} else {
		*normalWeapon = *weapon;
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
