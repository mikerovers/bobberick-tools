#include "Game.h"
#include "TextureManager.h"
#include "entity/EntityManager.h"
#include "services/RenderService.h"
#include "entity/components/TransformComponent.h"
#include "entity/components/SpriteComponent.h"
#include "entity/systems/DrawSystem.h"

bool Game::running()
{
    return isRunning;
}

StateMachine *Game::getStateMachine()
{
    return stateMachine;
}

SDL_Renderer *Game::getRenderer() const
{
    return renderer;
}

int Game::getGameWidth() const
{
    return gameWidth;
}

int Game::getGameHeight() const
{
    return gameHeight;
}

bool Game::init(const char *title, int xPos, int yPos, int height, int width, int flags)
{
    ServiceManager* serviceManager = ServiceManager::Instance();
    serviceManager->addService<TextureManager>();
    serviceManager->addService<EntityManager>();
    serviceManager->addService<RenderService>();
    drawSystem = new DrawSystem(serviceManager->getService<EntityManager>());

    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
        window = SDL_CreateWindow(title, xPos, yPos, height, width, false);

        if (window != nullptr) {
            serviceManager->getService<RenderService>().createRenderer(window);
            renderer = serviceManager->getService<RenderService>().getRenderer();

            if (renderer != nullptr) {
                SDL_SetRenderDrawColor(renderer, 75, 75, 255, 255);
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }

    stateMachine = new StateMachine();

    auto& entityManager = serviceManager->getService<EntityManager>();
    auto& player = entityManager.addEntity();
    player.addComponent<TransformComponent>();
    player.addComponent<SpriteComponent>("assets/spritestrip.bmp", "spritestrip");
    auto& enemy = entityManager.addEntity();
    enemy.addComponent<SpriteComponent>("assets/mountain_landscape.png", "mountains");

    SDL_SetWindowInputFocus(window);
    SDL_RaiseWindow(window);

    isRunning = true;
    gameWidth = width;
    gameHeight = height;

    return true;
}

void Game::render()
{
    SDL_RenderClear(renderer);

    drawSystem->update();

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Game::update()
{

}

void Game::handleEvents()
{

}
