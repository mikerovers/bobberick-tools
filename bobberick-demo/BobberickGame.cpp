//
// Created by Kevin van Rossum on 07/10/2018.
//

#include "BobberickGame.h"
#include "../bobberick-framework/src/TextureManager.h"
#include "../bobberick-framework/src/FontManager.h"
#include "../bobberick-framework/src/entity/EntityManager.h"
#include "../bobberick-framework/src/services/InputHandler.h"
#include "../bobberick-framework/src/services/RenderService.h"
#include "../bobberick-framework/src/entity/components/TransformComponent.h"
#include "../bobberick-framework/src/entity/components/SpriteComponent.h"
#include "../bobberick-framework/src/entity/components/TextComponent.h"
#include "../bobberick-framework/src/entity/systems/DrawSystem.h"
#include "../bobberick-framework/src/entity/systems/InputSystem.h"
#include "../bobberick-framework/src/SoundManager.h"
BobberickGame::BobberickGame(): frameHandler(new FrameHandler(60))
{

}

bool BobberickGame::running()
{
    return isRunning;
}

std::shared_ptr<StateMachine> BobberickGame::getStateMachine()
{
    return stateMachine;
}

int BobberickGame::getGameWidth() const
{
    return gameWidth;
}

int BobberickGame::getGameHeight() const
{
    return gameHeight;
}

bool BobberickGame::init(const char *title, int xPos, int yPos, int height, int width, int flags)
{
    // TheInputHandler::Instance()->initialiseJoysticks();
    ServiceManager* serviceManager = ServiceManager::Instance();
    serviceManager->addService<TextureManager>();
    serviceManager->addService<FontManager>();
    serviceManager->addService<EntityManager>();
    serviceManager->addService<RenderService>();
    drawSystem = std::shared_ptr<DrawSystem>(new DrawSystem(serviceManager->getService<EntityManager>()));
    serviceManager->addService<SoundManager>();
    serviceManager->addService<InputHandler>();

    drawSystem = std::shared_ptr<DrawSystem>(new DrawSystem(serviceManager->getService<EntityManager>()));
    inputSystem = std::shared_ptr<InputSystem>(new InputSystem(serviceManager->getService<EntityManager>()));
    serviceManager->addService<SoundManager>();


    serviceManager->getService<InputHandler>().initialiseJoysticks();

    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
        TTF_Init();
        window = SDL_WindowPointer(SDL_CreateWindow(title, xPos, yPos, width, height, flags));

        if (window != nullptr) {
            serviceManager->getService<RenderService>().createRenderer(window);
            renderer = serviceManager->getService<RenderService>().getRenderer();

            if (renderer != nullptr) {
                SDL_SetRenderDrawColor(renderer.get(), 75, 75, 255, 255);
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }

    stateMachine = std::shared_ptr<StateMachine>(new StateMachine());

    auto& entityManager = serviceManager->getService<EntityManager>();
    std::shared_ptr<Entity> player = entityManager.addEntity();
    player->addComponent<TransformComponent>();
    player->addComponent<SpriteComponent>("assets/spritestrip.png", "spritestrip");
    std::shared_ptr<Entity> enemy = entityManager.addEntity();
    enemy->addComponent<SpriteComponent>("assets/mountain_landscape.png", "mountains");

    auto& soundManager = serviceManager->getService<SoundManager>();

    entityManager.removeEntity(enemy);

    soundManager.load("assets/test-background-music.wav", "testMusic", SOUND_MUSIC);
    soundManager.load("assets/arrow-swoosh-2.ogg", "testSound", SOUND_SFX);
    soundManager.playMusic("testMusic", 0);
    soundManager.playSound("testSound", 1);

    SDL_SetWindowInputFocus(window.get());
    SDL_RaiseWindow(window.get());

    isRunning = true;
    gameWidth = width;
    gameHeight = height;

    return true;
}

void BobberickGame::render()
{
    frameHandler->updateTicks();
    frameHandler->updateTicks();

    inputSystem->update();

    SDL_RenderClear(renderer.get());
    drawSystem->update();
    SDL_RenderPresent(renderer.get());

    frameHandler->handleFrame();
}

void BobberickGame::clean()
{
    inputSystem->clean();
    SDL_Quit();
}

void BobberickGame::update()
{

}

void BobberickGame::handleEvents()
{

}