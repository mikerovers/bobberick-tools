#include "Game.h"
#include "services/TextureManager.h"
#include "services/FontManager.h"
#include "services/RectangleManager.h"
#include "entity/EntityManager.h"
#include "services/InputHandler.h"
#include "services/RenderService.h"
#include "services/SettingsService.h"
#include "entity/systems/DrawSystem.h"
#include "entity/systems/InputSystem.h"
#include "services/SoundManager.h"
#include "EmptyState.h"

Game::Game()
{
}

bool Game::running() const
{
	return isRunning;
}

int Game::getGameWidth() const
{
	return gameWidth;
}

int Game::getGameHeight() const
{
	return gameHeight;
}

bool Game::init(const char* title, int xPos, int yPos, int height, int width, int flags)
{
	ServiceManager* serviceManager = ServiceManager::Instance();
	serviceManager->addService<FrameHandler>(60);
	serviceManager->addService<TextureManager>();
	serviceManager->addService<FontManager>();
	serviceManager->addService<RectangleManager>();
	serviceManager->addService<EntityManager>();
	serviceManager->addService<RenderService>();
	serviceManager->addService<SoundManager>();
	serviceManager->addService<InputHandler>();
	serviceManager->addService<SoundManager>();
	serviceManager->addService<StateMachine>();
	serviceManager->addService<SettingsService>();

	serviceManager->getService<InputHandler>().initialiseJoysticks();

	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		TTF_Init();
		serviceManager->getService<FontManager>().init(); // Load in our fonts.
		IMG_Init(IMG_INIT_PNG);
		serviceManager->getService<SettingsService>().gameWidth = width;
		serviceManager->getService<SettingsService>().gameHeight = height;
		window = SDL_WindowPointer(SDL_CreateWindow(title, xPos, yPos, width, height, flags));

		if (window != nullptr)
		{
			serviceManager->getService<RenderService>().createRenderer(window);
			renderer = serviceManager->getService<RenderService>().getRenderer();

			if (renderer != nullptr)
			{
				SDL_SetRenderDrawColor(renderer.get(), 75, 75, 255, 255);
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	SDL_SetWindowInputFocus(window.get());
	SDL_RaiseWindow(window.get());

	isRunning = true;
	gameWidth = width;
	gameHeight = height;

	return true;
}

void Game::update()
{
	// Check if game state machine is empty then exit
	if (ServiceManager::Instance()->getService<StateMachine>().isEmpty() || ServiceManager::Instance()
	                                                                        ->getService<InputHandler>().isWindowEvent(
		                                                                        SDL_WINDOWEVENT_CLOSE)
	)
	{
		isRunning = false;
		return;
	}

	ServiceManager::Instance()->getService<FrameHandler>().updateTicks();

	SDL_RenderClear(renderer.get());
	ServiceManager::Instance()->getService<EntityManager>().refresh();
	ServiceManager::Instance()->getService<StateMachine>().update();
	SDL_RenderPresent(renderer.get());

	const auto frames = ServiceManager::Instance()->getService<FrameHandler>().getCurrentFps();
	//	std::cout << frames << "\n";
	ServiceManager::Instance()->getService<FrameHandler>().handleFrame();
}

void Game::clean()
{
	ServiceManager::Instance()->clean();

	SDL_Quit();
}

void Game::start()
{
	while (running())
	{
		update();
	}
}

bool Game::setup()
{
	if (init("Bobberick The Knight", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 480, 640,
	         static_cast<Uint32>(false)))
	{
		return true;
	}
	else
	{
		std::cout << "Game initialization failure - " << SDL_GetError() << " :( \n";

		return false;
	}
}
