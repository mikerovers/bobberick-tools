#include "PlayerStatsService.h"

void PlayerStatsService::init() {
	// normalWeapon = WeaponComponent("characterShooting", "Training Bow of Nothing", false, 0, 60, "bullet");
	// magicWeapon = WeaponComponent("characterCasting", "Training Staff of Nothing", false, 5, 120, "bolt");
	gold = 0;
	xp = 0;
	shdActive = false;
	fireCooldown = 0;
	alive = true;

	// TODO calculate all of this based on skills
	hp = hpMax = 100;
	atMin = 5;
	atMax = 10;
	df = 0;
	shdTime = shdTimeMax = 120;
	shdRecov = 0.1;
}

void PlayerStatsService::setStats(const int hp, const int hpMax, const int atMin, const int atMax, const int df, const double shdTime, const double shdTimeMax, const double shdRecov, const int gold, const int xp) {
	PlayerStatsService::hp = hp;
	PlayerStatsService::hpMax = hpMax;
	PlayerStatsService::atMin = atMin;
	PlayerStatsService::atMax = atMax;
	PlayerStatsService::df = df;
	PlayerStatsService::shdTime = shdTime;
	PlayerStatsService::shdTimeMax = shdTimeMax;
	PlayerStatsService::shdRecov = shdRecov;
	PlayerStatsService::gold = gold;
	PlayerStatsService::xp = xp;
}

void PlayerStatsService::setWeapons(WeaponComponent normal, WeaponComponent magic) {
	normalWeapon = normal;
	magicWeapon = magic;
}

void PlayerStatsService::setMagicWeapon(WeaponComponent weapon)
{
	magicWeapon = weapon;
}

void PlayerStatsService::setNormalWeapon(WeaponComponent weapon)
{
	normalWeapon = weapon;
}

void PlayerStatsService::update() {
	if (gold > 999999) {
		gold = 999999;
	}
	if (xp > 999999) {
		xp = 999999;
	}
	if (hp > 0) { // Shield recovery freezes when the player is dead.
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
		if (fireCooldown > 0) {
			fireCooldown--;
		}
	} else {
		shdActive = false;
		shdTime = 0;
		hp = 0;
		if (alive) {
			xpTotal += xp;
			alive = false;
		}
	}
}

void PlayerStatsService::getHit(int attack, const bool pierceDF) {
	if (!shdActive) {
		if (!pierceDF) {
			attack -= df;
			if (attack < 1) {
				attack = 1; // Attacks will always do damage.
			}
		}
		hp -= attack;
		if (hp < 0) {
			hp = 0;
		}
	}
}

void PlayerStatsService::heal(const int amount) {
	hp += amount;
	if (hp > hpMax) {
		hp = hpMax;
	}
}

int PlayerStatsService::attack(const bool magic) {
	if (fireCooldown <= 0) {
		int basePow = generator.getRandomNumber(atMin, atMax);
		if (magic) {
			fireCooldown = magicWeapon.fireDelay;
			return basePow + magicWeapon.power;
		} else {
			fireCooldown = normalWeapon.fireDelay;
			return basePow + normalWeapon.power;
		}
	} else {
		return -1; // Cannot fire a bullet yet.
	}
}

void PlayerStatsService::toggleShield() {
	if (!shdActive && shdTime / shdTimeMax >= 0.5) {
		shdActive = true;
	} else if (shdActive) {
		shdActive = false;
	}
}

// Getters
int PlayerStatsService::getHP() const {
	return hp;
}
int PlayerStatsService::getHPmax() const {
	return hpMax;
}
int PlayerStatsService::getATmin() const {
	return atMin;
}
int PlayerStatsService::getATmax() const {
	return atMax;
}
int PlayerStatsService::getDF() const {
	return df;
}
double PlayerStatsService::getSHD() const {
	return shdTime;
}
double PlayerStatsService::getSHDmax() const {
	return shdTimeMax;
}
double PlayerStatsService::getSHDrecov() const {
	return shdRecov;
}
bool PlayerStatsService::getSHDactive() const {
	return shdActive;
}
int PlayerStatsService::getXPtotal() const {
	return xpTotal;
}

void PlayerStatsService::changeHPmax(const int amount) {
	hpMax += amount;
	if (hpMax < 1) {
		hpMax = 1;
	}
	if (hpMax > 999999) {
		hpMax = 999999;
	}
	if (hp > hpMax) {
		hp = hpMax;
	}
}

void PlayerStatsService::changeATmin(const int amount) {
	atMin += amount;
	if (atMin < 0) {
		atMin = 0;
	}
	if (atMin > atMax) {
		atMin = atMax;
	}
}

void PlayerStatsService::changeATmax(const int amount) {
	atMax += amount;
	if (atMax < 1) {
		atMax = 1;
	}
	if (atMin > atMax) {
		atMin = atMax;
	}
}

void PlayerStatsService::setSHD(const int amount) {
	shdTime = amount;
}
