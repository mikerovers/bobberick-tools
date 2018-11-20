#ifndef BOBBERICK_TOOLS_ITEMCOMPONENT_H
#define BOBBERICK_TOOLS_ITEMCOMPONENT_H

#include "../../bobberick-framework/src/entity/Component.h"
#include "PlayerStatsComponent.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include <string>

class ItemComponent : public Component {
public:
	SpriteComponent sprite; // The sprite belonging to this item. Could be used when the item is in the inventory view.
	std::string texture;
	std::string name; // The name for this item. Might be randomly generated as well.
	ItemComponent(SpriteComponent sprite, std::string name) {
		ItemComponent::texture = sprite.getTexture();
		ItemComponent::name = name;
	}
	virtual void use(PlayerStatsComponent* playerStats) { }; // Impart an effect (or equip self) to this PlayerStatsComponent.
};

#endif //BOBBERICK_TOOLS_ITEMCOMPONENT_H