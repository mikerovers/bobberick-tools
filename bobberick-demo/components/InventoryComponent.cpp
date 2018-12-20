#include "InventoryComponent.h"

ItemComponent* InventoryComponent::getItem(int index) {
	if (index < items.size()) {
		return items[index].get();
	} else {
		return nullptr;
	}
}

bool InventoryComponent::use(int index) {
	if (index < items.size()) {
		items[index]->use();
		items.erase(items.begin() + index);
		return true;
	} else {
		return false;
	}
}

bool InventoryComponent::pickUp(ItemComponent item) {
	if (items.size() < 9) {
		items.emplace_back(std::make_unique<ItemComponent>(item));
		return true;
	} else {
		return false;
	}
}