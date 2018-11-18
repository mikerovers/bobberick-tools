#include "StatsComponent.h"
#include <random>

StatsComponent::StatsComponent(const int hp, const int hpMax, const int atMin, const int atMax, const int df) {
	changeHPmax(hpMax);
	healPoints(hp);
	changeATmax(atMax);
	changeATmin(atMin);
	changeDF(df);
}

void StatsComponent::healPoints(const int points) {
	if (points > 0) {
		hp += points;
		if (hp > hpMax) {
			hp = hpMax;
		}
	}
}

void StatsComponent::healPercent(const int percent) {
	if (percent > 0) {
		const int points = (double)(hpMax / 100 * percent);
		healPoints(points);
	}
}

void StatsComponent::getHit(int attack, const bool pierceDF) {
	if (!pierceDF) {
		// Is this what we want, or do we want a more complex algorithm for mitigating an attack with DF?
		// For that matter, should natural defense (in offensive mode) even exist for the player/enemies?
		attack -= df;
		if (attack < 0) {
			attack = 0;
		}
	}
	hp -= attack;
	if (hp < 0) {
		hp = 0;
	}
}

int StatsComponent::attack(int seed) {
	std::default_random_engine generator;
	generator.seed(seed);
	std::uniform_int_distribution<int> dist(atMin, atMax);
	return dist(generator);
}

const int StatsComponent::getHP() {
	return hp;
}
const int StatsComponent::getHPmax() {
	return hpMax;
}
const int StatsComponent::getATmin() {
	return atMin;
}
const int StatsComponent::getATmax() {
	return atMax;
}
const int StatsComponent::getDF() {
	return df;
}

void StatsComponent::changeHPmax(const int amount) {
	hpMax += amount;
	if (hpMax < 1) {
		hpMax = 1;
	}
	if (hp > hpMax) {
		hp = hpMax;
	}
}

void StatsComponent::changeATmin(const int amount) {
	atMin += amount;
	if (atMin < 0) {
		atMin = 0;
	}
	if (atMin > atMax) {
		atMin = atMax;
	}
}

void StatsComponent::changeATmax(const int amount) {
	atMax += amount;
	if (atMax < 1) {
		atMax = 1;
	}
	if (atMin > atMax) {
		atMin = atMax;
	}
}

void StatsComponent::changeDF(const int amount) {
	df += amount;
	if (df < 0) {
		df = 0;
	}
}