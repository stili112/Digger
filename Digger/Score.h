#pragma once

#include<string>
#include<stdexcept>
#include <ostream>
#include<sstream>

class Score
{
private:
	std::string name;
	int score;
public:
	Score(std::string name, int score);

	friend std::ostream& operator<<(std::ostream& os, const Score& other);
	friend std::istream& operator>>(std::istream& is, Score& other);

	//get
	std::string getName() const;
	int getScore() const;
};

