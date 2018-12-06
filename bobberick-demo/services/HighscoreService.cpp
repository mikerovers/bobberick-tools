#include "HighscoreService.h"
#include <algorithm>
#include <string>
#include "../../bobberick-framework/src/services/ServiceManager.h"
#include "../../bobberick-framework/src/services/SaveService.h"

void HighscoreService::init() {
	auto& save = ServiceManager::Instance()->getService<SaveService>();
	save.load();
	scores = {};

	// We only need to call init() and load our highscores once, at the beginning of our program.
	// From that moment on, we expect our local 'scores' vector to always equal our saved list,
	// because when we update our 'scores' vector, we update our saved list in the same way.
	for (int i = 0; i < numHighscores; i++) {
		if (save.has("highscore_" + std::to_string( i + 1 ))) {
			scores.emplace_back(save.get<int>("highscore_" + std::to_string(i + 1)));
		} else {
			scores.emplace_back(0);
		}
	}
}

const int HighscoreService::saveScore(const int score) {
	int highscorePos = 0;
	if (score > 0) {
		int i;
		for (i = 0; i < scores.size() && i < numHighscores; i++) {
			if (score > scores[i]) {
				scores.insert(scores.begin() + i, score);
				highscorePos = i + 1;
				break;
			}
		}
		if (i < numHighscores) { // The loop was broken because we don't have the maximum amount of recorded scores.
			scores.emplace_back(score);
			highscorePos = i + 1;
		}
		if (highscorePos > 0) { // If we placed in the highscore board, update our saved highscores.
			saveList();
		}
	}
	return highscorePos;
}

void HighscoreService::resetScores() {
	for (int i = 0; i < numHighscores; i++) {
		scores[i] = 0;
	}
	saveList();
}

const std::vector<int> HighscoreService::getScores() const {
	return scores;
}

void HighscoreService::saveList() const {
	auto& save = ServiceManager::Instance()->getService<SaveService>();
	for (int i = 0; i < numHighscores; i++) {
		save.keep<int>("highscore_" + std::to_string(i + 1), scores[i]);
	}
	save.flush();
}
