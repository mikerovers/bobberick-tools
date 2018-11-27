#ifndef BOBBERICK_TOOLS_WEAPONCOMPONENT_H
#define BOBBERICK_TOOLS_WEAPONCOMPONENT_H

#include "../../bobberick-framework/src/entity/Component.h"
#include "ItemComponent.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include <string>

class WeaponComponent : public ItemComponent {
public:
	bool isMagic; // Magic weapons (staffs) go into the right mouse button. Non-magic weapons (bows) go into the left mouse button.
	int power; // The modifier to the user's attack strength.
	int fireDelay; // The amount of frames between each bullet and the next. 60 = one bullet per second.
	std::string bulletTexture; // The asset path for the sprite for bullets fired by this weapon.
	WeaponComponent(const std::string texture, const std::string name, const bool isMagic, const int power, const int fireDelay, const std::string bulletTexture) : ItemComponent(texture, name) {
		WeaponComponent::isMagic = isMagic;
		WeaponComponent::power = power;
		WeaponComponent::fireDelay = fireDelay;
		WeaponComponent::bulletTexture = bulletTexture;
	}
	//void use(PlayerStatsComponent* playerStats) override; // Equip self to this PlayerStatsComponent.
};

#endif //BOBBERICK_TOOLS_WEAPONCOMPONENT_H