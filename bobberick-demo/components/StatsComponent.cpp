#include "StatsComponent.h"
#include <random>

StatsComponent::StatsComponent(const double hp, const double hpMax, const double atMin, const double atMax, const double df,
                               const int level)
{
	changeHPmax(hpMax);
	healPoints(hp);
	changeATmax(atMax);
	changeATmin(atMin);
	changeDF(df);
	changeLevel(level);

	generator = RandomGenerator();
}

void StatsComponent::healPoints(const double points)
{
	if (points > 0)
	{
		hp += points;
		if (hp > hpMax)
		{
			hp = hpMax;
		}
	}
}

void StatsComponent::healPercent(const double percent)
{
	if (percent > 0)
	{
		const int points = double(hpMax / 100 * percent);
		healPoints(points);
	}
}

void StatsComponent::getHit(double attack, const bool pierceDF)
{
	if (!pierceDF)
	{
		// Is this what we want, or do we want a more complex algorithm for mitigating an attack with DF?
		// For that matter, should natural defense (in offensive mode) even exist for the player/enemies?
		attack -= df;
		if (attack < 0)
		{
			attack = 0;
		}
	}
	hp -= attack;
	if (hp < 0)
	{
		hp = 0;
	}
}

int StatsComponent::attack() const
{
	return generator.getRandomNumber(atMin, atMax);
}

double StatsComponent::getHP() const
{
	return hp;
}

double StatsComponent::getHPmax() const
{
	return hpMax;
}

double StatsComponent::getATmin() const
{
	return atMin;
}

double StatsComponent::getATmax() const
{
	return atMax;
}

double StatsComponent::getDF() const
{
	return df;
}

int StatsComponent::getLevel() const
{
	return level;
}

void StatsComponent::changeHPmax(const double amount)
{
	hpMax += amount;
	if (hpMax < 1)
	{
		hpMax = 1;
	}
	if (hpMax > 999999)
	{
		hpMax = 999999;
	}
	if (hp > hpMax)
	{
		hp = hpMax;
	}
}

void StatsComponent::changeATmin(const double amount)
{
	atMin += amount;
	if (atMin < 0)
	{
		atMin = 0;
	}
	if (atMin > atMax)
	{
		atMin = atMax;
	}
}

void StatsComponent::changeATmax(const double amount)
{
	atMax += amount;
	if (atMax < 1)
	{
		atMax = 1;
	}
	if (atMin > atMax)
	{
		atMin = atMax;
	}
}

void StatsComponent::changeDF(const double amount)
{
	df += amount;
	if (df < 0)
	{
		df = 0;
	}
}

void StatsComponent::changeLevel(const int amount)
{
	level += amount;
	if (level < 0)
	{
		level = 0;
	}
}
