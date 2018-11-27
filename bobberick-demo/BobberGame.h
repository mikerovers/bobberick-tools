#ifndef BOBBERICK_TOOLS_BOBBERGAME_H
#define BOBBERICK_TOOLS_BOBBERGAME_H

#include "../bobberick-framework/src/Game.h"
#include "state/StateFactory.h"

class BobberGame : public Game
{
public:
    bool setup() override;
    void start() override;

private:
	std::shared_ptr<StateFactory> stateFactory;
	void preloadTextures();
	void preloadMusicAndSounds();
};


#endif //BOBBERICK_TOOLS_BOBBERGAME_H
