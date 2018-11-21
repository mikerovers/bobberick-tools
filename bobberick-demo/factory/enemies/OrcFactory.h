#ifndef BOBBERICK_TOOLS_ORCFACTORY_H
#define BOBBERICK_TOOLS_ORCFACTORY_H

#include "../../../bobberick-framework/src/entity/Entity.h"
#include "../../../bobberick-demo/factory/enemies/BaseEnemyFactory.h"
class OrcFactory : public BaseEnemyFactory
{
public:
    Entity& getEnemy(const int level) override;
	Entity& getEnemy(const int level, const int spawnerId) override;
};


#endif //BOBBERICK_TOOLS_ORCFACTORY_H
