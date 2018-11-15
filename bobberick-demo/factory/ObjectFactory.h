#ifndef BOBBERICK_TOOLS_OBJECTFACTORY_H
#define BOBBERICK_TOOLS_OBJECTFACTORY_H

#include "../../bobberick-framework/src/entity/Entity.h"
#include "../../bobberick-framework/src/util/Vector2D.h"
#include "../../bobberick-framework/src/entity/components/TileObject.h"

class ObjectFactory
{
public:
    Entity& getObject(const TileObject* object);
};


#endif //BOBBERICK_TOOLS_OBJECTFACTORY_H
