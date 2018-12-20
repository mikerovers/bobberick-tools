#ifndef BOBBERICK_TOOLS_HIGHSCORESTATE_H
#define BOBBERICK_TOOLS_HIGHSCORESTATE_H
#include "../services/HighscoreService.h"
#include "../../bobberick-framework/src/GameState.h"
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/util/TextFormatter.h"
#include "../../bobberick-framework/src/entity/Entity.h"
#include <vector>

class HighscoreState : public GameState
{
public:
	HighscoreState() {
		for (int i = 0; i < highscoreService.numHighscores; i++) {
			highscoreTexts.emplace_back(&entityManager.addEntity());
			entityManager.addEntityToGroup(*highscoreTexts[i], getStateID());
		}
	}

	bool onEnter() override;
	bool onExit() override;
	void update() override;
	std::string getStateID() const override;
	bool shouldExit() override;

private:
	bool readyForExit = false;
	EntityManager& entityManager = ServiceManager::Instance()->getService<EntityManager>();
	HighscoreService& highscoreService = ServiceManager::Instance()->getService<HighscoreService>();

	void makeClearButton();
	void makeExitButton();
	void makeBackground();

	void makeTitleText();
	void makeHighscoreText();
	void updateHighscoreText();

	TextFormatter textFormatter = TextFormatter();

	std::vector<Entity*> highscoreTexts;
	std::vector<int> highscores;
};

#endif // BOBBERICK_TOOLS_HIGHSCORESTATE_H