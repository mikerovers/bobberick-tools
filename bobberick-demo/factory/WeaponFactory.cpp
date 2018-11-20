#include "WeaponFactory.h"
#include <ctime>
#include <cmath>
#include <iostream>

WeaponComponent* WeaponFactory::generateWeapon(bool magic, int minRank, int maxRank, int minBalance, int maxBalance) {
	if (!seeded) {
		generator.seed(time(nullptr));
		seeded = true;
	}

	// Check all conditions required to generate a valid weapon.
	if (minRank >= 0 && maxRank <= 10 && minBalance >= -9 && maxBalance <= 9 && minRank <= maxRank && minBalance <= maxBalance) {
		// Determine core numbers
		std::uniform_real_distribution<double> rndRank(minRank, maxRank);
		std::uniform_real_distribution<double> rndBalance(minBalance, maxBalance);
		double rank = rndRank(generator);
		double balance = rndBalance(generator);

		// Build weapon name
		std::string name = "";
		name += rankPrefixes.at(rank);
		if (magic) {
			std::uniform_int_distribution<int> rndType(0, magicNames.size() - 1);
			name += magicNames[rndType(generator)];
		} else {
			std::uniform_int_distribution<int> rndType(0, normalNames.size() - 1);
			name += normalNames[rndType(generator)];
		}
		for (int i = 0; i <= balanceAffixLimits.size(); i++) {
			if (i == balanceAffixLimits.size() || balance >= balanceAffixLimits[i]) {
				name += balanceAffixes[i];
				break;
			}
		}

		// Base stats: Magic weapons of equal rank are twice as powerful as a normal weapon, but fire at half the speed.
		// Fire rate is only slightly affected by rank, the bigger changes to it happen by balance.
		int power;
		int fireDelay;
		if (magic) {
			power = 10 * std::pow(1.5, rank);
			fireDelay = 60 - (2 * rank);
		} else {
			power = 5 * std::pow(1.5, rank);
			fireDelay = 30 - (1 * rank);
		}

		// Stats modified by balance: 1 positive balance increases the weapon's power by 20%. 1 negative balance decreases it by 10%.
		// 1 positive balance increases the firing delay by 20% (which is bad). 1 negative balance decreases it by 10% (which is good).
		// So, weapons of equal rank and type deal equal DPS, but different balances facilitate different playing styles.
		double powerUnit = 0;
		double fireDelayUnit = 0;
		if (balance > 0) {
			powerUnit = power * 0.2;
			fireDelayUnit = fireDelay * 0.2;
		} else if (balance < 0) {
			powerUnit = power * 0.1;
			fireDelayUnit = fireDelay * 0.1;
		}
		power += powerUnit * balance;
		fireDelay += fireDelayUnit * balance;

		// Debug: test calculation and randomness.
		std::cout << "Magic: " << magic << std::endl;
		std::cout << "Rank: " << rank << std::endl;
		std::cout << "Balance: " << balance << std::endl;
		std::cout << "Name: " << name.c_str() << std::endl;
		std::cout << "Power: " << power << std::endl;
		std::cout << "Fire Delay: " << fireDelay << std::endl;

		// Assign sprites: these might vary depending on weapon type and weapon rank.
		std::string sprite = "assets/items/potion.png"; // TODO: assign based on core numbers
		std::string bulletSprite;
		if (magic) {
			bulletSprite = "assets/projectiles/bolt.png";
		} else {
			bulletSprite = "assets/projectiles/bullet_ball_grey.png";
		}

		return new WeaponComponent(sprite, name, magic, power, fireDelay, bulletSprite);
	} else {
		return nullptr;
	}
}