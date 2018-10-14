#ifndef BOBBERICK_TOOLS_BOBBERGAME_H
#define BOBBERICK_TOOLS_BOBBERGAME_H

#include "../bobberick-framework/src/Game.h"

class BobberGame : public Game
{
public:
    bool setup() override;
    void start() override;
};


#endif //BOBBERICK_TOOLS_BOBBERGAME_H
