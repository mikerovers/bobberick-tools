#ifndef BOBBERICK_TOOLS_SKILLSCOMPONENT_H
#define BOBBERICK_TOOLS_SKILLSCOMPONENT_H
#include "../../bobberick-framework/src/entity/Component.h"
#include "PlayerStatsComponent.h"

class SkillsComponent : public Component {
public:
	SkillsComponent(int totalXP, int hpLv, int atLv, int dfLv, int shdTimeLv, int shdRecovLv);

	// Get the total experience value.
	int getTotalXP() const;

	// Get the current level of each skill.
	int getHpLevel() const;
	int getAtLevel() const;
	int getDfLevel() const;
	int getShdTimeLevel() const;
	int getShdRecovLevel() const;

	// Get the XP cost to upgrade each skill. Returns -1 if the stat value has already been maxed out.
	int getHpCost() const;
	int getAtCost() const;
	int getDfCost() const;
	int getShdTimeCost() const;
	int getShdRecovCost() const;

	// Get the stat value corresponding to each skill level. If 'next' is true, returns what the stat would be after upgrading.
	// Returns -1 if 'next' is true, but the skill is already maxed out.
	int getHpValue(bool next) const;
	int getAtMinValue(bool next) const;
	int getAtMaxValue(bool next) const;
	int getDfValue(bool next) const;
	int getShdTimeValue(bool next) const;
	double getShdRecovValue(bool next) const;

	// Upgrade the level of each skill. Returns true if the upgrade was successful (the skill wasn't maxed out and the player could afford it).
	bool upgradeHpLevel();
	bool upgradeAtLevel();
	bool upgradeDfLevel();
	bool upgradeShdTimeLevel();
	bool upgradeShdRecovLevel();

	// Return a PlayerStatsComponent based on all skill levels.
	PlayerStatsComponent generateStartingStats();
private:
	int totalXP; // The player's total (spendable) XP, used to buy skills. 
	// Upon player death, current XP should be added to this in the save file.

	// The skill levels corresponding to each upgradable base stat.
	int hpLv;
	int atLv;
	int dfLv;
	int shdTimeLv;
	int shdRecovLv;
};

#endif // BOBBERICK_TOOLS_SKILLSCOMPONENT_H
