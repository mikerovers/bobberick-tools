#include "StatsComponent.h"
#include <random>

StatsComponent::StatsComponent(const int hp, const int hpmax, const int atmin, const int atmax, const int df) {
	changeHPmax(hpmax);
	healPoints(hp);
	changeATmax(atmax);
	changeATmin(atmin);
	changeDF(df);
}

void StatsComponent::healPoints(const int points) {
	if (points > 0) {
		hp += points;
		if (hp > hpmax) {
			hp = hpmax;
		}
	}
}

void StatsComponent::healPercent(const int percent) {
	if (percent > 0) {
		const int points = (double)((hpmax / 100) * percent);
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

int StatsComponent::attack() {
	std::default_random_engine generator;
	generator.seed(time(0));
	std::uniform_int_distribution<int> dist(atmin, atmax);
	return dist(generator);
}

const int StatsComponent::getHP() {
	return hp;
}
const int StatsComponent::getHPmax() {
	return hpmax;
}
const int StatsComponent::getATmin() {
	return atmin;
}
const int StatsComponent::getATmax() {
	return atmax;
}
const int StatsComponent::getDF() {
	return df;
}

void StatsComponent::changeHPmax(const int amount) {
	hpmax += amount;
	if (hpmax < 1) {
		hpmax = 1;
	}
	if (hp > hpmax) {
		hp = hpmax;
	}
}

void StatsComponent::changeATmin(const int amount) {
	atmin += amount;
	if (atmin < 0) {
		atmin = 0;
	}
	if (atmin > atmax) {
		atmin = atmax;
	}
}

void StatsComponent::changeATmax(const int amount) {
	atmax += amount;
	if (atmax < 1) {
		atmax = 1;
	}
	if (atmin > atmax) {
		atmin = atmax;
	}
}

void StatsComponent::changeDF(const int amount) {
	df += amount;
	if (df < 0) {
		df = 0;
	}
}