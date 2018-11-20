#ifndef BOBBERICK_TOOLS_NULLFACTORY_H
#define BOBBERICK_TOOLS_NULLFACTORY_H

#include "BaseEnemyFactory.h"

class NullFactory : public BaseEnemyFactory
{
    Entity& getEnemy(const int level) override;
    Entity& getEnemy(const int level, const int spawnerId) override;
};


#endif //BOBBERICK_TOOLS_NULLFACTORY_H
