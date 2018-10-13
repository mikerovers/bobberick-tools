#ifndef BOBBERICK_TOOLS_CHAINSHAPECOMPONENT_H
#define BOBBERICK_TOOLS_CHAINSHAPECOMPONENT_H

#include "../../Component.h"
#include "Collision/Shapes/b2ChainShape.h"

class ChainShapeComponent : public Component
{
private:
	b2ChainShape chainShape;
};

#endif // BOBBERICK_TOOLS_CHAINSHAPECOMPONENT_H