#ifndef BOBBERICK_TOOLS_INVENTORYSLOTCOMPONENT
#define BOBBERICK_TOOLS_INVENTORYSLOTCOMPONENT
#include "../../bobberick-framework/src/entity/Component.h"

class InventorySlotComponent : public Component
{
public:
	std::string textureID;

	explicit InventorySlotComponent(std::string textureID);
};

#endif //BOBBERICK_TOOLS_INVENTORYSLOTCOMPONENT