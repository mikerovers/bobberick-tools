#include "WeaponComponent.h"
#include "PlayerStatsComponent.h"

void WeaponComponent::use(PlayerStatsComponent* playerStats) {
	if (isMagic) {
		playerStats->magicWeapon = this;
	} else {
		playerStats->normalWeapon = this;
	}
}