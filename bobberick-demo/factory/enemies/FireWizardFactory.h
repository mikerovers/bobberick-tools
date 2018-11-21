#ifndef BOBBERICK_TOOLS_FIREWIZARDFACTORY_H
#define BOBBERICK_TOOLS_FIREWIZARDFACTORY_H

#include "../../../bobberick-framework/src/entity/Entity.h"
#include "../../../bobberick-demo/factory/enemies/BaseEnemyFactory.h"
class FireWizardFactory : public BaseEnemyFactory
{
public:
    Entity& getEnemy(const int level) override;
    Entity& getEnemy(const int level, const int spawnerId) override;
};


#endif //BOBBERICK_TOOLS_FIREWIZARDFACTORY_H
