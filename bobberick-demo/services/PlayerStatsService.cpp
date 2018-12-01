#include "PlayerStatsService.h"

void PlayerStatsService::init() {
	normalWeapon = WeaponComponent("potion", "Training Bow of Nothing", false, 0, 60, "bullet");
	magicWeapon = WeaponComponent("potion", "Training Staff of Nothing", false, 5, 120, "bolt");
	gold = 0;
	if (xp > 0) {
		xpTotal += xp;
	}
	xp = 0;
	shdActive = false;
	fireCooldown = 0;

	// TODO calculate all of this based on skills
	hp = hpMax = getHPvalue(false);
	atMin = getATminValue(false);
	atMax = getATmaxValue(false);
	df = getDFvalue(false);
	shdTime = shdTimeMax = getSHDvalue(false);
	shdRecov = getSHDrecovValue(false);
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

void PlayerStatsService::setMetaStats(const int xpTotal, const int hpLv, const int atLv, const int dfLv, const int shdTimeLv, const int shdRecovLv) {
	PlayerStatsService::xpTotal = xpTotal;
	PlayerStatsService::hpLv = hpLv;
	PlayerStatsService::atLv = atLv;
	PlayerStatsService::dfLv = dfLv;
	PlayerStatsService::shdTimeLv = shdTimeLv;
	PlayerStatsService::shdRecovLv = shdRecovLv;
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

bool PlayerStatsService::upgradeHPlevel() {
	if (getHPcost() > -1 && xpTotal >= getHPcost()) {
		xpTotal -= getHPcost();
		hpLv++;
		init();
		return true;
	}
	else {
		return false;
	}
}
bool PlayerStatsService::upgradeATlevel() {
	if (getATcost() > -1 && xpTotal >= getATcost()) {
		xpTotal -= getATcost();
		atLv++;
		init();
		return true;
	}
	else {
		return false;
	}
}
bool PlayerStatsService::upgradeDFlevel() {
	if (getDFcost() > -1 && xpTotal >= getDFcost()) {
		xpTotal -= getDFcost();
		dfLv++;
		init();
		return true;
	}
	else {
		return false;
	}
}
bool PlayerStatsService::upgradeSHDlevel() {
	if (getSHDcost() > -1 && xpTotal >= getSHDcost()) {
		xpTotal -= getSHDcost();
		shdTimeLv++;
		init();
		return true;
	}
	else {
		return false;
	}
}
bool PlayerStatsService::upgradeSHDrecovLevel() {
	if (getSHDrecovCost() > -1 && xpTotal >= getSHDrecovCost()) {
		xpTotal -= getSHDrecovCost();
		shdRecovLv++;
		init();
		return true;
	}
	else {
		return false;
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

int PlayerStatsService::getHPlevel() const {
	return hpLv;
}
int PlayerStatsService::getATlevel() const {
	return atLv;
}
int PlayerStatsService::getDFlevel() const {
	return dfLv;
}
int PlayerStatsService::getSHDlevel() const {
	return shdTimeLv;
}
int PlayerStatsService::getSHDrecovLevel() const {
	return shdRecovLv;
}

int PlayerStatsService::getHPcost() const {
	if (getHPvalue(true) != -1) {
		return getHPvalue(true) * 10;
	}
	else {
		return -1;
	}
}
int PlayerStatsService::getATcost() const {
	if (getATminValue(true) != -1) {
		return pow(getATminValue(true) * 1000, 1.1);
	}
	else {
		return -1;
	}
}
int PlayerStatsService::getDFcost() const {
	if (getDFvalue(true) != -1) {
		return pow(getDFvalue(true) * 60, 1.7);
	}
	else {
		return -1;
	}
}
int PlayerStatsService::getSHDcost() const {
	if (getSHDvalue(true) != -1) {
		return pow((getSHDlevel() + 1) * 90, 1.6);
	}
	else {
		return -1;
	}
}
int PlayerStatsService::getSHDrecovCost() const {
	if (getSHDrecovValue(true) != -1) {
		return pow((getSHDrecovLevel()+1) * 120, 1.6);
	}
	else {
		return -1;
	}
}

int PlayerStatsService::getHPvalue(bool next) const {
	if (!next) {
		return __min(100 * (pow(1.1, hpLv)), 500000);
	}
	else {
		if (getHPvalue(false) < 500000) {
			return __min(100 * (pow(1.1, hpLv + 1)), 500000);
		}
		else {
			return -1;
		}
	}
}
int PlayerStatsService::getATminValue(bool next) const {
	if (!next) {
		return __min(pow(atLv + 1, 1.3), 400);
	}
	else {
		if (getATminValue(false) < 400) {
			return __min(pow(atLv + 2, 1.3), 400);
		}
		else {
			return -1;
		}
	}
}
int PlayerStatsService::getATmaxValue(bool next) const {
	int value = getATminValue(next);
	if (value > -1) {
		value = (value * 1.5) + 1;
	}
	return __min(value, 600);
}
int PlayerStatsService::getDFvalue(bool next) const {
	if (!next) {
		return __min(dfLv, 100);
	}
	else {
		if (getDFvalue(false) < 100) {
			return __min(dfLv + 1, 100);
		}
		else {
			return -1;
		}
	}
}
int PlayerStatsService::getSHDvalue(bool next) const {
	if (!next) {
		return __min(120 + (10 * pow(shdTimeLv, 0.9)), 999);
	}
	else {
		if (getSHDvalue(false) < 999) {
			return __min(120 + (10 * pow(shdTimeLv + 1, 0.9)), 999);
		}
		else {
			return -1;
		}

	}
}
double PlayerStatsService::getSHDrecovValue(bool next) const {
	if (!next) {
		return __min(0.1 + ((shdRecovLv) * 0.01), 1);
	}
	else {
		if (getSHDrecovValue(false) < 1) {
			return __min(0.1 + ((shdRecovLv + 1) * 0.01), 1);
		}
		else {
			return -1;
		}
	}
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
