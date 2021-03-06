#ifndef BOBBERICK_TOOLS_PLAYSTATE_H
#define BOBBERICK_TOOLS_PLAYSTATE_H

#include "../../bobberick-framework/src/GameState.h"

class Level1State : public GameState
{
public:
    void update() override;
    bool onEnter() override;
    bool onExit() override;

    bool shouldExit() override;

    std::string getStateID() const override;

private:
	bool _exitPressed = false;
	Entity &makeTileMap() const;
	void makePlayer() const;
	void makeEnemies() const;
	void makeGui();
	void instantiateSystems() const;
};


#endif //BOBBERICK_TOOLS_PLAYSTATE_H
