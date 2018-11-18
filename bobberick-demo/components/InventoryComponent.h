#ifndef BOBBERICK_TOOLS_INVENTORYCOMPONENT_H
#define BOBBERICK_TOOLS_INVENTORYCOMPONENT_H

#include "../../bobberick-framework/src/entity/Component.h"
#include "ItemComponent.h"
#include "PlayerStatsComponent.h"
#include <vector>
#include <memory>

class InventoryComponent : public Component {
public:
	InventoryComponent(PlayerStatsComponent* stats) {
		InventoryComponent::playerStats = stats;
	}

	bool pickUp(ItemComponent item); // Add an ItemComponent to the inventory. Returns false if there is no room (consider not destroying the collided item in the game world).
	ItemComponent* getItem(int index); // Get an item from the inventory. You may need this when printing item stats. Returns null if there is no item.
	bool use(int index); // Use the item at the specified inventory index. Returns false if there is no item.
private:
	PlayerStatsComponent* playerStats; // The PlayerStatsComponent to use items on.
	std::vector<std::unique_ptr<ItemComponent>> items; // The list of items in the inventory. Limited to 9 items (think number keys).
};

#endif //BOBBERICK_TOOLS_INVENTORYCOMPONENT_H