#ifndef BOBBERICK_TOOLS_STATSCOMPONENT_H
#define BOBBERICK_TOOLS_STATSCOMPONENT_H

#include "../Component.h"

// StatsComponent represents the stats that both the player and all enemies have.
// There will also be a class for all the extra stats the player has in-game
// and a class for the experience/levels/upgrades/currency the player has out-of-game.
// Perhaps the out-of-game stats class can generate the required in-game stats components.
class StatsComponent : public Component
{
public:
	StatsComponent(const int hp, const int hpMax, const int atMin, const int atMax, const int df);

	void healPoints(const int points); // Heal HP, up to X fixed points.
	void healPercent(const int percentage); // Heal HP, up to X percent of HPmax.
	void getHit(int attack, const bool pierceDF); // Mitigate attack with DF (unless pierceDF is true), then take the resulting damage.
	int attack(); // Return a random number between ATmin and ATmax (when hitting an enemy or when generating a bullet).
	
	// Get the value of a stat.
	const int getHP();
	const int getHPmax();
	const int getATmin();
	const int getATmax();
	const int getDF();

	// Permanently upgrade or impair stats by the specified amount.
	void changeHPmax(const int amount);
	void changeATmin(const int amount);
	void changeATmax(const int amount);
	void changeDF(const int amount);


private:
	int hp = 0; // current hit points
	int hpMax = 0; // maximum hit points
	int atMin = 0; // minimum attack
	int atMax = 0; // maximum attack
	int df = 0; // natural defense (in offensive mode)
};

#endif //BOBBERICK_TOOLS_STATSCOMPONENT_H