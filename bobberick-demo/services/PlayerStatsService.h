#ifndef BOBBERICK_TOOLS_PLAYERSTATSSERVICE_H
#define BOBBERICK_TOOLS_PLAYERSTATSSERVICE_H
#include "../../bobberick-framework/src/services/Service.h"
#include "../../bobberick-framework/src/util/RandomGenerator.h"
#include "../components/WeaponComponent.h"

class PlayerStatsService : public Service {
public:
	// Lifecycle events
	void init() override; // Will reset the player based on the current skill levels, meant to be called more than once.
	void setStats(const int hp, const int hpMax, const int atMin, const int atMax, const int df, const double shdTime, const double shdTimeMax, const double shdRecov, const int gold, const int xp); // Set stats when loading a in-progress game.
	void setWeapons(const WeaponComponent normal, const WeaponComponent magic); // Set initial weapons when loading a 'New Game +' save file(?)
	void setMetaStats(const int totalXP, const int hpLv, const int atLv, const int dfLv, const int shdTimeLv, const int shdRecovLv); // Initialize skills when loading a save file.
	void clean() override {};
	void update(); // Call this every frame in an in-game state.

	// In-game events
	void getHit(int attack, const bool pierceDF); // Mitigate attack with DF in offensive mode or absorb it in shield mode.
	void heal(const int amount); // Heal the player by the specified number of points.
	// Generate an attack and modify it based on the power of one of the weapons. Returns -1 if the firing cooldown has not elapsed (do not generate a bullet).
	int attack(const bool magic); // Call this every frame when the player is holding a fire button.
	void toggleShield(); // Activate the shield, if it's charged enough (must be at least 50% charged).

	// Metagame events
	bool upgradeHPlevel();
	bool upgradeATlevel();
	bool upgradeDFlevel();
	bool upgradeSHDlevel();
	bool upgradeSHDrecovLevel();

	// Getters for private stats
	int getHP() const;
	int getHPmax() const;
	int getATmin() const;
	int getATmax() const;
	int getDF() const;
	double getSHD() const;
	double getSHDmax() const;
	double getSHDrecov() const;
	bool getSHDactive() const;

	// Cheats
	void changeHPmax(const int amount);
	void changeATmin(const int amount);
	void changeATmax(const int amount);
	void setSHD(const int amount);

	// Getters for metagame stats
	int getXPtotal() const;

	int getHPlevel() const;
	int getATlevel() const;
	int getDFlevel() const;
	int getSHDlevel() const;
	int getSHDrecovLevel() const;

	int getHPcost() const;
	int getATcost() const;
	int getDFcost() const;
	int getSHDcost() const;
	int getSHDrecovCost() const;

	int getHPvalue(bool next) const;
	int getATminValue(bool next) const;
	int getATmaxValue(bool next) const;
	int getDFvalue(bool next) const;
	int getSHDvalue(bool next) const;
	double getSHDrecovValue(bool next) const;

	// Public in-game stats
	WeaponComponent normalWeapon = WeaponComponent("potion", "Training Bow of Nothing", false, 0, 60, "bullet");
	WeaponComponent magicWeapon = WeaponComponent("potion", "Training Staff of Nothing", false, 5, 120, "bolt");
	int gold;
	int xp; // Earned in the current game.
private:
	// Private in-game stats
	int hp; // current hit points
	int hpMax; // maximum hit points
	int atMin; // minimum attack
	int atMax; // maximum attack
	int df; // natural defense (in offensive mode)
	double shdTime; // The amount of ticks the shield can still be active.
	double shdTimeMax; // The amount of ticks the shield can be active at most.
	double shdRecov; // The amount of shdTime recovered every tick (when shield is inactive).
	bool shdActive;
	int fireCooldown; // The amount of ticks to wait before a weapon can be fired again.

	// Metagame stats (skills and total XP)
	int xpTotal = 0; // Total, spendable experience earned across all games.
	int hpLv = 0;
	int atLv = 0;
	int dfLv = 0;
	int shdTimeLv = 0;
	int shdRecovLv = 0;

	// Internally used
	bool alive; // Whether the player is alive.
	RandomGenerator generator = RandomGenerator();
};

#endif // BOBBERICK_TOOLS_PLAYERSTATSSERVICE_H