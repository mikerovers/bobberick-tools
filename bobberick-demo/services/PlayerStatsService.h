#ifndef BOBBERICK_TOOLS_PLAYERSTATSSERVICE_H
#define BOBBERICK_TOOLS_PLAYERSTATSSERVICE_H
#include "../../bobberick-framework/src/services/Service.h"
#include "../../bobberick-framework/src/util/RandomGenerator.h"
#include "../components/WeaponComponent.h"

class PlayerStatsService : public Service {
public:
	// Lifecycle events
	void init() override; // Will reset the player based on the current skill levels, meant to be called more than once.
	void setStats(const int hp, const int hpMax, const int atMin, const int atMax, const double shdTime, const double shdTimeMax, const double shdRecov, const int xp); // Set stats when loading a in-progress game.
	void setWeapons(const WeaponComponent normal, const WeaponComponent magic); // Set initial weapons when loading a 'New Game +' save file(?)
	void setMetaStats(const int totalXP, const int hpLv, const int atLv, const int shdTimeLv, const int shdRecovLv); // Initialize skills when loading the game.
	void clean() override { };
	void update(); // Call this every frame in an in-game state.

	// In-game events
	void getHit(double attack); // Mitigate attack with DF in offensive mode or absorb it in shield mode.
	void heal(const int amount); // Heal the player by the specified number of points.
	// Generate an attack and modify it based on the power of one of the weapons. Returns -1 if the firing cooldown has not elapsed (do not generate a bullet).
	int attack(const bool magic); // Call this every frame when the player is holding a fire button.
	void toggleShield(); // Activate the shield, if it's charged enough (must be at least 50% charged).
	void setNormalWeapon(const WeaponComponent weapon);
	void setMagicWeapon(const WeaponComponent weapon);
	void equipComparingWeapon(); // Confirm equipping the currently compared weapon.

	// Metagame events
	bool upgradeHPlevel();
	bool upgradeATlevel();
	bool upgradeSHDlevel();
	bool upgradeSHDrecovLevel();

	// Getters for private stats
	int getHP() const;
	int getHPmax() const;
	int getATmin() const;
	int getATmax() const;
	double getSHD() const;
	int getSHDmax() const;
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
	int getSHDlevel() const;
	int getSHDrecovLevel() const;

	int getHPcost() const;
	int getATcost() const;
	int getSHDcost() const;
	int getSHDrecovCost() const;

	int getHPvalue(bool next) const;
	int getATminValue(bool next) const;
	int getATmaxValue(bool next) const;
	int getSHDvalue(bool next) const;
	double getSHDrecovValue(bool next) const;

	// Public in-game stats
	WeaponComponent normalWeapon = WeaponComponent("", "Training Bow of Nothing", false, 0, 30, "bullet", "characterShooting");
	WeaponComponent magicWeapon = WeaponComponent("", "Training Staff of Nothing", true, 5, 60, "bolt", "characterCasting");
	WeaponComponent comparingWeapon = WeaponComponent("", "", false, 0, 0, "", "");
	int compareTime = 0; // When >0, the hud system should show the compared weapon. Depicts the amount of frames the compared weapon is valid.
	bool compareConfirmed = false; // When true, this is a message to the collision system to destroy the colliding weapon and set this back to false when done.
	int xp{}; // Earned in the current game.

	void save(); // Save current game stats
	void load(); // Load current game stats
	bool validateSave() const;

	void saveMeta(); // Save skills and total XP
	void loadMeta(); // Load skills and total XP
	void wipeMeta();
	bool validateSaveMeta() const;
private:
	// Private in-game stats
	double hp{}; // current hit points
	double hpMax{}; // maximum hit points
	double atMin{}; // minimum attack
	double atMax{}; // maximum attack
	double shdTime{}; // The amount of ticks the shield can still be active.
	double shdTimeMax{}; // The amount of ticks the shield can be active at most.
	double shdRecov{}; // The amount of shdTime recovered every tick (when shield is inactive).
	bool shdActive{};
	int fireCooldown{}; // The amount of ticks to wait before a weapon can be fired again.

	// Metagame stats (skills and total XP)
	int xpTotal{0}; // Total, spendable experience earned across all games.
	int hpLv{0};
	int atLv{0};
	int shdTimeLv{0};
	int shdRecovLv{0};

	// Internally used
	RandomGenerator generator{};
};

#endif // BOBBERICK_TOOLS_PLAYERSTATSSERVICE_H