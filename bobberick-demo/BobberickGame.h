//
// Created by Kevin van Rossum on 07/10/2018.
//

#ifndef BOBBERICK_TOOLS_BOBBERICKGAME_H
#define BOBBERICK_TOOLS_BOBBERICKGAME_H


#include "../bobberick-framework/src/Game.h"

class BobberickGame : Game {
public:
    BobberickGame();
    bool init(const char* title, int xPos, int yPos, int height, int width, int flags);
    void render();
    void handleEvents();
    void clean();
    void update();

    bool running();

    std::shared_ptr<StateMachine> getStateMachine();

    int getGameWidth() const;
    int getGameHeight() const;

private:
    SDL_WindowPointer window;
    SDL_RendererPointer renderer;

    int gameHeight;
    int gameWidth;

    bool isRunning;

    std::shared_ptr<StateMachine> stateMachine;
    std::shared_ptr<FrameHandler> frameHandler;
    //TODO Make a interface for system registring. Maybe in the statemachine?
    std::shared_ptr<DrawSystem> drawSystem;
    std::shared_ptr<InputSystem> inputSystem;
};

#endif //BOBBERICK_TOOLS_BOBBERICKGAME_H
