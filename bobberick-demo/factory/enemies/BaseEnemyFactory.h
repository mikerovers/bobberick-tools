#ifndef BOBBERICK_TOOLS_BASEENEMYFACTORY_H
#define BOBBERICK_TOOLS_BASEENEMYFACTORY_H

#include "../../../bobberick-framework/src/entity/Entity.h"

class BaseEnemyFactory
{
public:
	virtual Entity * getEnemy(const int level) = 0;
};


#endif //BOBBERICK_TOOLS_BASEENEMYFACTORY_H
