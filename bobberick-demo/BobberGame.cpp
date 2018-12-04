#include "BobberGame.h"
#include "state/Level1State.h"
#include "services/PlayerStatsService.h"
#include "../bobberick-framework/src/services/RenderService.h"
#include "../bobberick-framework/src/services/TextureManager.h"
#include "../bobberick-framework/src/services/SettingsService.h"
#include "../bobberick-framework/src/services/SoundManager.h"
#include <experimental/filesystem>
#include <regex>

using std::experimental::filesystem::recursive_directory_iterator;

bool BobberGame::setup()
{
	if (Game::setup()) {
		ServiceManager::Instance()->addService<PlayerStatsService>();
		ServiceManager::Instance()->getService<PlayerStatsService>().init();

		preloadTextures();
		preloadMusicAndSounds();

		stateFactory = std::make_unique<StateFactory>();

		ServiceManager::Instance()->getService<StateMachine>().pushState(stateFactory->createState("MainMenuState"));

		return true;
	}
	return false;
}

void BobberGame::start()
{
    Game::start();
}

void BobberGame::preloadMusicAndSounds() {
	ServiceManager::Instance()->getService<SoundManager>().load("assets/music/soundtrack/menu.wav", "menu",
		SOUND_MUSIC);
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
	t.load("assets/image/button/resumebutton.png", "resumeGameButton", renderer);
	t.load("assets/image/button/loadbutton.png", "loadGameButton", renderer);
	t.load("assets/image/button/savebutton.png", "saveGameButton", renderer);
	t.load("assets/image/button/healthbutton.png", "healthButton", renderer);
	t.load("assets/image/button/attackbutton.png", "attackButton", renderer);
	t.load("assets/image/button/defensebutton.png", "defenseButton", renderer);
	t.load("assets/image/button/shieldbutton.png", "shieldButton", renderer);
	t.load("assets/image/button/recovbutton.png", "recoveryButton", renderer);
	t.load("assets/image/button/togglemusicbutton.png", "toggleMusicButton", renderer);
	t.load("assets/image/button/blank_green_button.png", "blankGreenButton", renderer);
	t.load("assets/image/button/blank_red_button.png", "blankRedButton", renderer);

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
	t.load("assets/image/Enemies/blood/blood1.png", "blood1", renderer);
	t.load("assets/image/Enemies/blood/blood2.png", "blood2", renderer);
	t.load("assets/image/Enemies/blood/blood3.png", "blood3", renderer);
	t.load("assets/image/Enemies/blood/blood4.png", "blood4", renderer);
	t.load("assets/image/Enemies/blood/blood5.png", "blood5", renderer);

	// gui
	t.load("assets/image/gui/hud_gold.png", "hudGold", renderer);
	t.load("assets/image/gui/hud_xp.png", "hudXp", renderer);
	t.load("assets/image/gui/playbutton.bmp", "playButton", renderer);

	// items
	t.load("assets/image/items/potion.png", "potion", renderer);

	// projectiles
	t.load("assets/image/projectiles/bolt.png", "bolt", renderer);
	t.load("assets/image/projectiles/bullet_ball_grey.png", "bullet", renderer);

	// advertisements
	int advertisementCounter = 0;
	for (auto& dirEntry : recursive_directory_iterator("assets/image/advertisements")) {
		std::regex rx(".*\\.(?:jpg|png)$");
		bool match = std::tr1::regex_match(dirEntry.path().string().c_str(), rx);
		if (match) {
			std::cout << dirEntry.path().string().c_str() << std::endl;
			t.load(dirEntry.path().string().c_str(), "ad" + std::to_string(advertisementCounter), renderer);
			advertisementCounter++;
		}
	}

	ServiceManager::Instance()->getService<SettingsService>().advertisementCount = advertisementCounter;

}
