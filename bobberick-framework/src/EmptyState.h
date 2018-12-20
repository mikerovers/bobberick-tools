#ifndef BOBBERICK_TOOLS_EMPTYSTATE_H
#define BOBBERICK_TOOLS_EMPTYSTATE_H


#include "GameState.h"

class EmptyState : public GameState
{
public:
    EmptyState() = default;;
    ~EmptyState() = default;;

    void update() override;

    bool onEnter() override;
    bool onExit() override;

    bool shouldExit() override;

    std::string getStateID() const override;
};


#endif //BOBBERICK_TOOLS_EMPTYSTATE_H
