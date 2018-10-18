#include "Game.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "entity/EntityManager.h"
#include "services/InputHandler.h"
#include "services/RenderService.h"
#include "entity/components/TransformComponent.h"
#include "entity/components/SpriteComponent.h"
#include "entity/components/TextComponent.h"
#include "entity/components/FadeComponent.h"
#include "entity/systems/DrawSystem.h"
#include "entity/systems/InputSystem.h"
#include "SoundManager.h"

Game::Game(): frameHandler(new FrameHandler(60))
{

}

bool Game::running()
{
    return isRunning;
}

std::shared_ptr<StateMachine> Game::getStateMachine()
{
    return stateMachine;
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
	serviceManager->addService<FontManager>();
    serviceManager->addService<EntityManager>();
    serviceManager->addService<RenderService>();
	serviceManager->addService<SoundManager>();
	serviceManager->addService<InputHandler>();
	serviceManager->addService<SoundManager>();

	serviceManager->getService<InputHandler>().initialiseJoysticks();

    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
		TTF_Init();
		IMG_Init(IMG_INIT_PNG);
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

	drawSystem = std::shared_ptr<DrawSystem>(new DrawSystem(serviceManager->getService<EntityManager>()));

	auto& entityManager = serviceManager->getService<EntityManager>();
	std::shared_ptr<Entity> logo = entityManager.addEntity();
	logo->addComponent<TransformComponent>(0, 0, 256, 256, 1);
	logo->addComponent<SpriteComponent>("assets/teamcpp_logo.bmp", "logo");
	logo->addComponent<FadeComponent>("logo", -100, 2, 300); // Starting the opacity value below 0 will delay the fade-in.
	std::shared_ptr<Entity> logoText = entityManager.addEntity();
	logoText->addComponent<TransformComponent>(0, 256, 80, 256, 1);
	logoText->addComponent<TextComponent>("assets/font.ttf", "logoText", "Team C++", 56);
	logoText->addComponent<FadeComponent>("logoText", 0, 2, 300);
  
    SDL_SetWindowInputFocus(window.get());
    SDL_RaiseWindow(window.get());

    isRunning = true;
    gameWidth = width;
    gameHeight = height;

    return true;
}

void Game::update()
{
    frameHandler->updateTicks();

    SDL_RenderClear(renderer.get());
    stateMachine->update();
	drawSystem->update();
    SDL_RenderPresent(renderer.get());

    frameHandler->handleFrame();
}

void Game::clean()
{
    ServiceManager::Instance()->clean();

    SDL_Quit();
}

void Game::start()
{
    while (running()) {
        update();
    }
}

bool Game::setup()
{
    if (init("Bobberick The Knight", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 480, 640,
             static_cast<Uint32>(false))) {
        return true;
    } else {
        std::cout << "Game initialization failure - " << SDL_GetError() << " :( \n";

        return false;
    }
}
