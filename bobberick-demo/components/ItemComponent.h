#ifndef BOBBERICK_TOOLS_ITEMCOMPONENT_H
#define BOBBERICK_TOOLS_ITEMCOMPONENT_H

#include "../../bobberick-framework/src/entity/Component.h"
#include "../../bobberick-framework/src/entity/components/SpriteComponent.h"
#include <string>

class ItemComponent : public Component {
public:
	std::string textureID; // The asset path for the texture belonging to this item. Could be used when the item is in the inventory view.
	std::string name; // The name for this item. Might be randomly generated as well.
	ItemComponent(std::string const textureID, std::string const name) {
		ItemComponent::textureID = textureID;
		ItemComponent::name = name;
	}
	virtual void use() { }; // Impart an effect to the player stats.
};

#endif //BOBBERICK_TOOLS_ITEMCOMPONENT_H