#include "BobberGame.h"
#include "state/PlayState.h"
#include "../bobberick-framework/src/services/RenderService.h"
#include "../bobberick-framework/src/services/TextureManager.h"

bool BobberGame::setup()
{
	if (Game::setup()) {
		preloadTextures();

		stateFactory = std::make_shared<StateFactory>();

		ServiceManager::Instance()->getService<StateMachine>().pushState(stateFactory->createState("MainMenuState"));
		//getStateMachine()->pushState(stateFactory->createState("MainMenuState"));
		//getStateMachine()->pushState(stateFactory->createState("SplashScreenState"));
        //getStateMachine()->peekState()->onEnter();
		//getStateMachine()->pushState(stateFactory->createState("TestState"));
        //ServiceManager::Instance()->getService<StateMachine>().peekState()->onEnter();

		return true;
	}
	return false;
}

void BobberGame::start()
{
    Game::start();
}

void BobberGame::preloadTextures()
{
	SDL_RendererPointer renderer = ServiceManager::Instance()->getService<RenderService>().getRenderer();
	TextureManager& t = ServiceManager::Instance()->getService<TextureManager>();

	// misc
	t.load("assets/teamcpp_logo.bmp", "logo", renderer);
	t.load("assets/image/collision.png", "collisionBox", renderer);

	// button
	t.load("assets/image/button/exitbutton.png", "exitButton", renderer);
	t.load("assets/image/button/helpbutton.png", "helpButton", renderer);
	t.load("assets/image/button/optionsbutton.png", "optionsButton", renderer);
	t.load("assets/image/button/startgamebutton.png", "startGameButton", renderer);

	// character
	t.load("assets/image/character/character.png", "character", renderer);
	t.load("assets/image/character/character_casting.png", "characterCasting", renderer);
	t.load("assets/image/character/character_shield.png", "characterShield", renderer);
	t.load("assets/image/character/character_shooting.png", "characterShooting", renderer);

	// enemies
	t.load("assets/image/Enemies/birds1.png", "birds", renderer);
	t.load("assets/image/Enemies/chicken_brown.png", "chickenBrown", renderer);
	t.load("assets/image/Enemies/chicken_white.png", "chickenWhite", renderer);
	t.load("assets/image/Enemies/end_boss.png", "endBoss", renderer);
	t.load("assets/image/Enemies/factory.png", "factory", renderer);
	t.load("assets/image/Enemies/fire_wizard.png", "fireWizard", renderer);
	t.load("assets/image/Enemies/fire_wizard_casting.png", "fireWizardCasting", renderer);
	t.load("assets/image/Enemies/house.png", "house", renderer);
	t.load("assets/image/Enemies/magic_circle.png", "magicCircle", renderer);
	t.load("assets/image/Enemies/orc_piratess.png", "orc", renderer);
	t.load("assets/image/Enemies/zombie.png", "zombie", renderer);

	// gui
	t.load("assets/image/gui/hud_gold.png", "hudGold", renderer);
	t.load("assets/image/gui/hud_xp.png", "hudXp", renderer);
	t.load("assets/image/gui/playbutton.bmp", "playButton", renderer);

	// items
	t.load("assets/image/items/potion.png", "potion", renderer);

	// projectiles
	t.load("assets/image/projectiles/bolt.png", "bolt", renderer);
	t.load("assets/image/projectiles/bullet_ball_grey.png", "bullet", renderer);
}
