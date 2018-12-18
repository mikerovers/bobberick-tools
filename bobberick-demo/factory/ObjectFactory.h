#ifndef BOBBERICK_TOOLS_OBJECTFACTORY_H
#define BOBBERICK_TOOLS_OBJECTFACTORY_H

#include "../../bobberick-framework/src/entity/Entity.h"
#include "../../bobberick-framework/src/util/Vector2D.h"
#include "../../bobberick-framework/src/entity/components/TileObject.h"
#include "../components/SpawnComponent.h"
#include "enemies/EnemyFactory.h"

class ObjectFactory
{
public:
	ObjectFactory(int const level) : level(level), enemyFactory(std::make_unique<EnemyFactory>()) {};
    Entity& getObject(const TileObject* object);

private:
    std::unique_ptr<EnemyFactory> enemyFactory;
	int const level;
};


#endif //BOBBERICK_TOOLS_OBJECTFACTORY_H
