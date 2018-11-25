#include "PlayerStatsComponent.h"
#include "StatsComponent.h"
#include "WeaponComponent.h"

PlayerStatsComponent::PlayerStatsComponent(const int hp, const int hpMax, const int atMin, const int atMax, const int df, const int level, const double shdTime, const double shdTimeMax, const double shdRecov, const int gold, const int xp) : StatsComponent(hp, hpMax, atMin, atMax, df, level) {
	PlayerStatsComponent::shdTime = shdTime;
	PlayerStatsComponent::shdTimeMax = shdTimeMax;
	PlayerStatsComponent::shdRecov = shdRecov;
	shdActive = false;
	PlayerStatsComponent::gold = gold;
	PlayerStatsComponent::xp = xp;
}

void PlayerStatsComponent::update() {
	if (gold > 999999) {
		gold = 999999;
	}
	if (xp > 999999) {
		xp = 999999;
	}
	if (getHP() > 0) { // Shield recovery freezes when the player is dead.
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
	}
}

int PlayerStatsComponent::attack(bool magic) const {
	int basePow = generator.getRandomNumber(atMin, atMax);
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
		if (!pierceDF) {
			attack -= df;
			if (attack < 1) {
				attack = 1;
			}
		}
		hp -= attack;
		if (hp < 0) {
			hp = 0;
		}
	}
}
