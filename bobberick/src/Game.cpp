#include "Game.h"
#include "TextureManager.h"
#include "entity/EntityManager.h"
#include "services/RenderService.h"
#include "entity/components/TransformComponent.h"
#include "entity/components/SpriteComponent.h"

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

    isRunning = true;
    gameWidth = width;
    gameHeight = height;

    return true;
}

void Game::render()
{
    SDL_RenderClear(renderer);

    ServiceManager::Instance()->getService<EntityManager>().render();

    SDL_RenderPresent(renderer);
}

void Game::clean()
{

}

void Game::update()
{

}

void Game::handleEvents()
{

}
