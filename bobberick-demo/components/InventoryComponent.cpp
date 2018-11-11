#include "InventoryComponent.h"

ItemComponent* InventoryComponent::getItem(int index) {
	if (index <= items.size()) {
		return &items[index];
	} else {
		return nullptr;
	}
}

bool InventoryComponent::use(int index) {
	if (index <= items.size()) {
		items[index].use(playerStats);
		items.erase(items.begin() + index - 1);
		return true;
	} else {
		return false;
	}
}

bool InventoryComponent::pickUp(ItemComponent item) {
	if (items.size() < 9) {
		items.emplace_back(item);
		return true;
	} else {
		return false;
	}
}