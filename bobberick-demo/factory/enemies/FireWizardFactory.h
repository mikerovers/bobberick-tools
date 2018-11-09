#ifndef BOBBERICK_TOOLS_FIREWIZARDFACTORY_H
#define BOBBERICK_TOOLS_FIREWIZARDFACTORY_H

#include "../../../bobberick-framework/src/entity/Entity.h"
class FireWizardFactory
{
public:
    Entity* getEnemy(const int level);
};


#endif //BOBBERICK_TOOLS_FIREWIZARDFACTORY_H
