#include "Game.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "entity/EntityManager.h"
#include "services/RenderService.h"
#include "entity/components/TransformComponent.h"
#include "entity/components/SpriteComponent.h"
#include "entity/components/TextComponent.h"
#include "entity/systems/DrawSystem.h"
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
    drawSystem = std::shared_ptr<DrawSystem>(new DrawSystem(serviceManager->getService<EntityManager>()));
	serviceManager->addService<SoundManager>();

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

    auto& entityManager = serviceManager->getService<EntityManager>();
	std::shared_ptr<Entity> player = entityManager.addEntity();
    player->addComponent<TransformComponent>(0, 0, 256, 256, 1);
    player->addComponent<SpriteComponent>("assets/spritestrip.bmp", "spritestrip", 6, 6, 7);
	player->addComponent<TextComponent>("assets/font.ttf", "font", "sample\ntext", 100);
	std::shared_ptr<Entity> player2 = entityManager.addEntity();
	player2->addComponent<TransformComponent>(256, 0, 150, 130, 1);
	player2->addComponent<SpriteComponent>("assets/dude_animation_sheet.png", "spritestrip2", 7, 27, 3);
	std::shared_ptr<Entity> enemy = entityManager.addEntity();
	enemy->addComponent<TransformComponent>(0, 256, 256, 256, 1);
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

void Game::render()
{
    frameHandler->updateTicks();

    SDL_RenderClear(renderer.get());
    drawSystem->update();
    SDL_RenderPresent(renderer.get());

    frameHandler->handleFrame();
}

void Game::clean()
{
    SDL_Quit();
}

void Game::update()
{

}

void Game::handleEvents()
{

}
