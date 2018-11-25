#include "SkillsComponent.h"
#include <cmath>

SkillsComponent::SkillsComponent(int totalXP, int hpLv, int atLv, int dfLv, int shdTimeLv, int shdRecovLv) {
	SkillsComponent::totalXP = totalXP;
	SkillsComponent::hpLv = hpLv;
	SkillsComponent::atLv = atLv;
	SkillsComponent::dfLv = dfLv;
	SkillsComponent::shdTimeLv = shdTimeLv;
	SkillsComponent::shdRecovLv = shdRecovLv;
}

int SkillsComponent::getTotalXP() const {
	return totalXP;
}
int SkillsComponent::getHpLevel() const {
	return hpLv;
}
int SkillsComponent::getAtLevel() const {
	return atLv;
}
int SkillsComponent::getDfLevel() const {
	return dfLv;
}
int SkillsComponent::getShdTimeLevel() const {
	return shdTimeLv;
}
int SkillsComponent::getShdRecovLevel() const {
	return shdRecovLv;
}

int SkillsComponent::getHpCost() const {
	if (getHpValue(true) != -1) {
		return getHpValue(true) * 10;
	} else {
		return -1;
	}
}
int SkillsComponent::getAtCost() const {
	if (getAtMinValue(true) != -1) {
		return pow(getAtMinValue(true) * 1000, 1.1);
	}
	else {
		return -1;
	}
}
int SkillsComponent::getDfCost() const {
	if (getDfValue(true) != -1) {
		return pow(getDfValue(true) * 60, 1.8);
	}
	else {
		return -1;
	}
}
int SkillsComponent::getShdTimeCost() const {
	if (getShdTimeValue(true) != -1) {
		return pow(getShdTimeValue(true) / 80, 5);
	}
	else {
		return -1;
	}
}
int SkillsComponent::getShdRecovCost() const {
	if (getShdRecovValue(true) != -1) {
		return getHpValue(true) * 10;
	}
	else {
		return -1;
	}
}

int SkillsComponent::getHpValue(bool next) const {
	if (!next) {
		return __max(100 * (pow(1.1, hpLv)), 500000);
	} else {
		if (getHpValue(false) < 500000) {
			return __max(100 * (pow(1.1, hpLv + 1)), 500000);
		} else {
			return -1;
		}
	}
}
int SkillsComponent::getAtMinValue(bool next) const {
	if (!next) {
		return __max(pow(atLv + 1, 1.3), 400);
	} else {
		if (getHpValue(false) < 400) {
			return __max(pow(atLv + 2, 1.3), 400);
		} else {
			return -1;
		}
	}
}
int SkillsComponent::getAtMaxValue(bool next) const {
	int value = getAtMinValue(next);
	if (value > -1) {
		value = (value * 1.5) + 1;
	}
	return value;
}
int SkillsComponent::getDfValue(bool next) const {
	if (!next) {
		return __max(dfLv, 100);
	} else {
		if (getHpValue(false) < 100) {
			return __max(dfLv + 1, 100);
		} else {
			return -1;
		}
	}
}
int SkillsComponent::getShdTimeValue(bool next) const {
	if (!next) {
		return __max(120 + (10 * pow(shdTimeLv, 0.9)), 999);
	} else {
		if (getShdTimeValue(false) < 999) {
			return __max(120 + (10 * pow(shdTimeLv+1, 0.9)), 999);
		} else {
			return -1;
		}
		
	}
}
double SkillsComponent::getShdRecovValue(bool next) const {
	if (!next) {
		return __max(0.1+((shdRecovLv) * 0.01), 1);
	} else {
		if (getShdTimeValue(false) < 1) {
			return __max(0.1 + ((shdRecovLv + 1) * 0.01), 1);
		} else {
			return -1;
		}
	}
}

bool SkillsComponent::upgradeHpLevel() {
	if (getHpCost() > -1 && totalXP >= getHpCost()) {
		totalXP -= getHpCost();
		hpLv++;
		return true;
	} else {
		return false;
	}
}
bool SkillsComponent::upgradeAtLevel() {
	if (getAtCost() > -1 && totalXP >= getAtCost()) {
		totalXP -= getAtCost();
		atLv++;
		return true;
	} else {
		return false;
	}
}
bool SkillsComponent::upgradeDfLevel() {
	if (getDfCost() > -1 && totalXP >= getDfCost()) {
		totalXP -= getDfCost();
		dfLv++;
		return true;
	} else {
		return false;
	}
}
bool SkillsComponent::upgradeShdTimeLevel() {
	if (getShdTimeCost() > -1 && totalXP >= getShdTimeCost()) {
		totalXP -= getShdTimeCost();
		shdTimeLv++;
		return true;
	} else {
		return false;
	}
}
bool SkillsComponent::upgradeShdRecovLevel() {
	if (getShdRecovCost() > -1 && totalXP >= getShdRecovCost()) {
		totalXP -= getShdRecovCost();
		shdRecovLv++;
		return true;
	} else {
		return false;
	}
}

PlayerStatsComponent SkillsComponent::generateStartingStats() {
	int totalLv = getHpLevel() + getAtLevel() + getDfLevel() + getShdTimeLevel() + getShdRecovLevel();
	return PlayerStatsComponent(
		new StatsComponent(
			getHpValue(false), 
			getHpValue(false), 
			getAtMinValue(false), 
			getAtMaxValue(false), 
			getDfValue(false), 
			totalLv
		), 
		getShdTimeValue(false), 
		getShdTimeValue(false), 
		getShdRecovValue(false), 
		0,
		0
	);
}