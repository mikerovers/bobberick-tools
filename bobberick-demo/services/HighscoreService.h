#ifndef BOBBERICK_TOOLS_HIGHSCORESERVICE_H
#define BOBBERICK_TOOLS_HIGHSCORESERVICE_H
#include "../../bobberick-framework/src/services/Service.h"
#include <vector>

class HighscoreService : public Service {
public:
	void init() override; // Load and initialize our highscore list.
	void clean() override {};
	const int saveScore(const int score); // Returns 0 if you didn't place, or a number between 1 and numHighscores if you did.
	void resetScores(); // Set all scores on the highscore list to zero.
	const std::vector<int> getScores() const; // Get our highscore list, gauranteed to always be numHighscores long after calling init();
	const int numHighscores = 10;
private:
	void saveList() const; // Save our local highscore list externally.
	std::vector<int> scores;
};

#endif // BOBBERICK_TOOLS_HIGHSCORESERVICE_H