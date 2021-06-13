#include "Score.h"

//public
Score::Score(std::string name, int score)
{
	if (name.size() == 3)
	{
		this->name = name;
		this->score = score;
	}
	else
	{
		throw std::length_error("The name has to be 3 symbols.");
	}
}

std::ostream& operator<<(std::ostream& os, const Score& other)
{
	os << other.name << " " << other.score;
	return os;
}
std::istream& operator>>(std::istream& is, Score& other)
{
	is >> other.name;

	std::string scoreStr;
	is >> scoreStr;

	std::stringstream stream(scoreStr);

	stream >> other.score;
	return is;
}

std::string Score::getName() const
{
	return name;
}
int Score::getScore() const
{
	return score;
}