#pragma once

#include "../../bobberick-framework/src/GameState.h"

class Level4State : public GameState
{
public:
    void update() override;
    bool onEnter() override;
    bool onExit() override;

    bool shouldExit() override;

    std::string getStateID() const override;

private:
    Entity& makeTileMap() const;
    void makePlayer() const;
	std::vector<Vector2D> spawnPoints{};
	RandomGenerator random{};
};