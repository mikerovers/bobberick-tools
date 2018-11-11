#ifndef BOBBERICK_TOOLS_WEAPONCOMPONENT_H
#define BOBBERICK_TOOLS_WEAPONCOMPONENT_H

#include "../../bobberick-framework/src/entity/Component.h"
#include "ItemComponent.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include <string>

class PlayerStatsComponent;
class WeaponComponent : public ItemComponent {
public:
	bool isMagic; // Magic weapons (staffs) go into the right mouse button. Non-magic weapons (bows) go into the left mouse button.
	int power; // The modifier to the user's attack strength. Can also be negative as a trade-off to, for instance, a very high firing rate.
	int fireDelay; // The amount of frames between each bullet and the next. 60 = one bullet per second.
	SpriteComponent bulletSprite; // The sprite used for bullets fired by this weapon.
	WeaponComponent(SpriteComponent sprite, std::string name, bool isMagic, int power, int fireDelay, SpriteComponent bulletSprite) : ItemComponent(sprite, name) {
		WeaponComponent::isMagic = isMagic;
		WeaponComponent::power = power;
		WeaponComponent::fireDelay = fireDelay;
		WeaponComponent::bulletSprite = bulletSprite;
	}
	void use(PlayerStatsComponent* playerStats) override; // Equip self to this PlayerStatsComponent.
};

#endif //BOBBERICK_TOOLS_WEAPONCOMPONENT_H