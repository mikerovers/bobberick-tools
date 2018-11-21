#ifndef BOBBERICK_TOOLS_WEAPONFACTORY_H
#define BOBBERICK_TOOLS_WEAPONFACTORY_H
#include "../components/WeaponComponent.h"
#include <map>
#include <string>
#include <array>
#include "../../bobberick-framework/src/util/RandomGenerator.h"

class WeaponFactory {
public: 
	// Rank is a number between 0 and 10, giving a general idea of a weapon's strength.
	// Higher ranking weapons may show up later in the game or as special treasures.

	// Balance is a number between -9 and +9, determining a weapon's playstyle.
	// Weapons with a positive balance focus on raw power at the expense of firing rate.
	// Weapons with a negative balance have a high firing rate, but far less power.
	std::unique_ptr<WeaponComponent> generateWeapon(bool magic, int minRank, int maxRank, int minBalance, int maxBalance);

private:
	// Weapons have a prefixing word, according to their rank. (May also affect their sprite?)
	const std::map<int, std::string> rankPrefixes{
		{0, "Cursed "},
		{1, "Damaged "},
		{2, "Rusty "},
		{3, "Wooden "},
		{4, "Iron "},
		{5, "Blacksmith's "},
		{6, "Enchanted "},
		{7, "Diamond "},
		{8, "Dragonscale "},
		{9, "Divine Avansian "},
		{10,"Ultimate "},
	};

	// Weapons have a base name, according to their type. (May also affect their sprite?)
	const std::array<std::string, 2> normalNames{
		"Bow", "Crossbow"
	};
	const std::array<std::string, 2> magicNames{
		"Staff", "Wand"
	};

	// Weapons have an affixing word, according to their balance.
	const std::array<int, 8> balanceAffixLimits{
		7,
		5,
		3,
		1,
		-1,
		-3,
		-5,
		-7
		// If the balance isn't above any of these values, use the final entry in balanceAffixes.
	};
	const std::array<std::string, 9> balanceAffixes{
		" of Annihilation",
		" of Destruction",
		" of Flames",
		" of Power",
		" of Balance",
		" of Speed",
		" of Storms",
		" of Tempest",
		" of Infinity",
	};

	bool seeded = false;
};

#endif // BOBBERICK_TOOLS_WEAPONFACTORY_H