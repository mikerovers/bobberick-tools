#include "BobberGame.h"
#include "state/Level1State.h"
#include "services/PlayerStatsService.h"
#include "services/HighscoreService.h"
#include "../bobberick-framework/src/services/RenderService.h"
#include "../bobberick-framework/src/services/TextureManager.h"
#include "../bobberick-framework/src/services/SettingsService.h"
#include "../bobberick-framework/src/services/SoundManager.h"
#include <regex>
#include "../bobberick-framework/src/util/tinydir.h"

bool BobberGame::setup()
{
	if (Game::setup()) {
		ServiceManager::Instance()->addService<PlayerStatsService>();
		ServiceManager::Instance()->getService<PlayerStatsService>().init();
		ServiceManager::Instance()->addService<HighscoreService>();
		ServiceManager::Instance()->getService<HighscoreService>().init();

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
	ServiceManager::Instance()->getService<SoundManager>().load("assets/music/soundtrack/boss.wav", "boss",
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
	t.load("assets/image/button/scoresbutton.png", "scoresButton", renderer);
	t.load("assets/image/button/clearbutton.png", "clearButton", renderer);
	t.load("assets/image/button/togglemusicbutton.png", "toggleMusicButton", renderer);
	t.load("assets/image/button/blank_green_button.png", "blankGreenButton", renderer);
	t.load("assets/image/button/blank_red_button.png", "blankRedButton", renderer);

	// character
	t.load("assets/image/character/character.png", "character", renderer);
	t.load("assets/image/character/character_casting.png", "characterCasting", renderer);
	t.load("assets/image/character/character_casting_1.png", "characterCasting_1", renderer);
	t.load("assets/image/character/character_casting_2.png", "characterCasting_2", renderer);
	t.load("assets/image/character/character_shield.png", "characterShield", renderer);
	t.load("assets/image/character/character_shooting.png", "characterShooting", renderer);
	t.load("assets/image/character/character_shooting_1.png", "characterShooting_1", renderer);
	t.load("assets/image/character/character_shooting_2.png", "characterShooting_2", renderer);
	t.load("assets/image/character/character_shooting_3.png", "characterShooting_3", renderer);

	// enemies
	t.load("assets/image/Enemies/birds1.png", "birds", renderer);
	t.load("assets/image/Enemies/chicken_brown.png", "chickenBrown", renderer);
	t.load("assets/image/Enemies/chicken_white.png", "chickenWhite", renderer);
	t.load("assets/image/Enemies/end_boss.png", "endBoss", renderer);
	t.load("assets/image/Enemies/factory.png", "factory", renderer);
	t.load("assets/image/Enemies/fire_wizard.png", "fireWizard", renderer);
	t.load("assets/image/Enemies/fire_wizard_casting.png", "fireWizardCasting", renderer);
	t.load("assets/image/Enemies/ice_wizard.png", "iceWizard", renderer);
	t.load("assets/image/Enemies/ice_wizard_casting.png", "iceWizardCasting", renderer);
	t.load("assets/image/Enemies/metal_wizard.png", "metalWizard", renderer);
	t.load("assets/image/Enemies/metal_wizard_casting.png", "metalWizardCasting", renderer);
	t.load("assets/image/Enemies/house.png", "house", renderer);
	t.load("assets/image/Enemies/magic_circle.png", "magicCircle", renderer);
	t.load("assets/image/Enemies/orc_piratess.png", "orc", renderer);
	t.load("assets/image/Enemies/bird.png", "bird", renderer);
	t.load("assets/image/Enemies/zombie.png", "zombie", renderer);
	t.load("assets/image/teleportCircle.png", "spawnCircle", renderer);
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
	// staffs
	t.load("assets/image/items/staff_1.png", "staff_1", renderer);
	t.load("assets/image/items/staff_2.png", "staff_2", renderer);
	// bows
	t.load("assets/image/items/bow_1.png", "bow_1", renderer);
	t.load("assets/image/items/bow_2.png", "bow_2", renderer);
	t.load("assets/image/items/bow_3.png", "bow_3", renderer);

	// projectiles
	t.load("assets/image/projectiles/bolt.png", "bolt", renderer);
	t.load("assets/image/projectiles/bullet_ball_grey.png", "bullet", renderer);

	// advertisements
	int advertisementCounter = 0;
	tinydir_dir dir;
	tinydir_open(&dir, "assets/image/advertisements");

	while (dir.has_next)
	{
		tinydir_file file;
		tinydir_readfile(&dir, &file);
		std::regex rx(".*\\.(?:jpg|png)$");

		bool match = std::regex_match(file.path, rx);
		if (match) {
			t.load(file.path, "ad" + std::to_string(advertisementCounter), renderer);
			advertisementCounter++;
		}
		printf("%s", file.name);
		if (file.is_dir)
		{
			printf("/");
		}
		printf("\n");

		tinydir_next(&dir);
	}

	tinydir_close(&dir);

	ServiceManager::Instance()->getService<SettingsService>().advertisementCount = advertisementCounter;

}
