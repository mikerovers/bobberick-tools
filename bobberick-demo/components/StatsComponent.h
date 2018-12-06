#ifndef BOBBERICK_TOOLS_STATSCOMPONENT_H
#define BOBBERICK_TOOLS_STATSCOMPONENT_H

#include "../../bobberick-framework/src/entity/Component.h"
#include "../../bobberick-framework/src/util/RandomGenerator.h"

class StatsComponent : public Component
{
public:
	StatsComponent(const double hp, const double hpMax, const double atMin, const double atMax, const double df, const int level);

	void healPoints(const double  points); // Heal HP, up to X fixed points.
	void healPercent(const double percentage); // Heal HP, up to X percent of HPmax.
	virtual void getHit(double attack, const bool pierceDF); // Mitigate attack with DF (unless pierceDF is true), then take the resulting damage.
	int attack() const; // Return a random number between ATmin and ATmax (when hitting an enemy or when generating a bullet).
	
	// Get the value of a stat.
	double getHP() const;
	double getHPmax() const;
	double getATmin() const;
	double getATmax() const;
	double getDF() const;
	int getLevel() const;

	// Permanently upgrade or impair stats by the specified amount.
	void changeHPmax(const double amount);
	void changeATmin(const double amount);
	void changeATmax(const double amount);
	void changeDF(const double amount);
	void changeLevel(const int amount);
protected:
	RandomGenerator generator;
	double hp = 0; // current hit points
	double hpMax = 0; // maximum hit points
	double atMin = 0; // minimum attack
	double atMax = 0; // maximum attack
	double df = 0; // natural defense (in offensive mode)
	int level = 0;
};

#endif //BOBBERICK_TOOLS_STATSCOMPONENT_H