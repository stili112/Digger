#pragma once

#include<string>
#include<vector>
#include<fstream>

#include"Score.h"

class HighScoreSystem
{
public:
	static const int MAX_BR_SCORES_SAVED = 10;
private:
	//const
	static const std::string FILE_NAME;

	//board
	std::vector<Score> highScores;

	//current score
	int currentScore;

	//functions
	void loadFromFile();
	void saveToFile();

	void sortHighScores();
public:
	HighScoreSystem();
	~HighScoreSystem();
	
	void updateHightScore();

	void reseteCurrentScore();
	void addToCurrentScore(int points);

	std::vector<Score> getScores() const;
	int getCurrentScore() const;
};

