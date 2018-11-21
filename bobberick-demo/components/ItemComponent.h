#ifndef BOBBERICK_TOOLS_ITEMCOMPONENT_H
#define BOBBERICK_TOOLS_ITEMCOMPONENT_H

#include "../../bobberick-framework/src/entity/Component.h"
#include "PlayerStatsComponent.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include <string>

class ItemComponent : public Component {
public:
	std::string texture; // The asset path for the texture belonging to this item. Could be used when the item is in the inventory view.
	std::string name; // The name for this item. Might be randomly generated as well.
	ItemComponent(std::string const texture, std::string const name) {
		ItemComponent::texture = texture;
		ItemComponent::name = name;
	}
	virtual void use(PlayerStatsComponent* playerStats) { }; // Impart an effect (or equip self) to this PlayerStatsComponent.
};

#endif //BOBBERICK_TOOLS_ITEMCOMPONENT_H