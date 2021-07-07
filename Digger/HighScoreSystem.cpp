#include "HighScoreSystem.h"

//private
const std::string HighScoreSystem::FILE_NAME = "HightScore.txt";

void HighScoreSystem::loadFromFile()
{
	std::ifstream in("HightScore.txt");
	if (in.is_open())
	{
		for (size_t i = 0; i < MAX_BR_SCORES_SAVED; i++)
		{
			Score temp("...", 0);
			in >> temp;
			highScores.push_back(temp);			
		}	

		in.close();
	}
	else
	{
		for (size_t i = 0; i < 10; i++)
		{
			Score temp("...", 0);
			highScores.push_back(temp);
		}
	}
}
void HighScoreSystem::saveToFile()
{
	std::ofstream out("HightScore.txt");
	if (out.is_open())
	{
		for (size_t i = 0; i < MAX_BR_SCORES_SAVED; i++)
		{
			out << highScores[i]<<std::endl;
		}
		out.close();
	}
}
//public
HighScoreSystem::HighScoreSystem() 
{
	reseteCurrentScore();

	loadFromFile();
}
HighScoreSystem::~HighScoreSystem()
{
	saveToFile();
}

void HighScoreSystem::sortHighScores()
{
	int n = highScores.size();
	int max_idx;
	for (int i = 0; i <  n- 1; i++)
	{
		max_idx = i;
		for (int j = i + 1; j < n; j++)
		{
			if (highScores[j].getScore() > highScores[max_idx].getScore())
			{
				max_idx = j;
			}				
		}
		if (max_idx != i)
		{
			std::swap(highScores[i],highScores[max_idx]);
		}
		
	}
}
void HighScoreSystem::updateHightScore()
{
	Score curent("...",currentScore);
	highScores.push_back(curent);
	
	sortHighScores();
}

void HighScoreSystem::reseteCurrentScore()
{
	currentScore = 0;
}
void HighScoreSystem::addToCurrentScore(int points)
{
	if (points >= 0)
	{
		currentScore += points;
	}
	else
	{
		throw std::logic_error("Cant add negative points");
	}
}

std::vector<Score> HighScoreSystem::getScores() const
{
	return highScores;
}
int HighScoreSystem::getCurrentScore() const
{
	return currentScore;
}