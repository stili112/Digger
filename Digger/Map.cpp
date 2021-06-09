#include "Map.h"
#include <iostream>

//private
//init
void Map::initDiggedSpots()
{
	diggedSpots = new bool* [brColls];
	for (size_t i = 0; i < brColls; i++)
	{
		diggedSpots[i] = new bool[brRows];
		for (size_t j = 0; j < brRows; j++)
		{
			diggedSpots[i][j] = false;
		}
	}
}

//functions
void Map::copyMap(const Map& other)
{
	topLeftCorner = other.topLeftCorner;
	playerStartPos = other.playerStartPos;
	enemySpawnPos = other.enemySpawnPos;
	emeralds = other.emeralds;
	moneyBags = other.moneyBags;

	//levelDesign char[15][10]
	for (size_t i = 0; i < 15; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			levelDesign[i][j] = other.levelDesign[i][j];
		}
	}


	//map and diggedSpots
	diggedSpots = new bool* [brColls];
	for (size_t i = 0; i < brColls; i++)
	{
		diggedSpots[i] = new bool[brRows];
	}

	for (size_t i = 0; i < brColls; i++)
	{
		for (size_t j = 0; j < brRows; j++)
		{
			diggedSpots[i][j] = other.diggedSpots[i][j];
			map[i][j] = new sf::CircleShape(other.map[i][j]->getRadius());
		}
	}
}
void Map::deleteMap()
{
	for (size_t i = 0; i < brColls; i++)
	{
		for (size_t j = 0; j < brRows; j++)
		{
			delete map[i][j];
		}
		delete[] diggedSpots[i];
	}
	delete[] diggedSpots;
}

void Map::reshapeArray(char from[10][15], char to[15][10])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			to[j][i] = from[i][j];
		}
	}	
}

void Map::makeStartFormation()
{
	sf::CircleShape circle(tunnelWidth);
	for (size_t i = 0; i < 15; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			if (levelDesign[i][j] == '.' || levelDesign[i][j] == 'S')
			{
				if (levelDesign[i][j] == '.')
				{
					circle.setPosition(topLeftCorner.x + (1 + i * 5) * 14.f, topLeftCorner.y + (1 + j * 5) * 14.f);
					map[1 + i * 5][1 + j * 5] = new sf::CircleShape(circle);
				}

				if (i > 0)
				{
					if (levelDesign[i - 1][j] == '.' || levelDesign[i - 1][j] == 'S')
					{
						circle.setPosition(topLeftCorner.x + (i * 5) * 14.f, topLeftCorner.y + (1 + j * 5) * 14.f);
						map[i * 5][1 + j * 5] = new sf::CircleShape(circle);

						circle.setPosition(topLeftCorner.x + (-1 + i * 5) * 14.f, topLeftCorner.y + (1 + j * 5) * 14.f);
						map[-1 + i * 5][1 + j * 5] = new sf::CircleShape(circle);
					}
				}
				else
				{
					circle.setPosition(topLeftCorner.x + (i * 5) * 14.f, topLeftCorner.y + (1 + j * 5) * 14.f);
					map[i * 5][1 + j * 5] = new sf::CircleShape(circle);
				}

				if (i < 14)
				{
					if (levelDesign[i + 1][j] == '.' || levelDesign[i + 1][j] == 'S')
					{
						circle.setPosition(topLeftCorner.x + (2 + i * 5) * 14.f, topLeftCorner.y + (1 + j * 5) * 14.f);
						map[2 + i * 5][1 + j * 5] = new sf::CircleShape(circle);

						circle.setPosition(topLeftCorner.x + (3 + i * 5) * 14.f, topLeftCorner.y + (1 + j * 5) * 14.f);
						map[3 + i * 5][1 + j * 5] = new sf::CircleShape(circle);
					}
				}
				else
				{
					circle.setPosition(topLeftCorner.x + (2 + i * 5) * 14.f, topLeftCorner.y + (1 + j * 5) * 14.f);
					map[2 + i * 5][1 + j * 5] = new sf::CircleShape(circle);
				}

				if (j > 0)
				{
					if (levelDesign[i][j - 1] == '.' || levelDesign[i][j - 1] == 'S')
					{
						circle.setPosition(topLeftCorner.x + (1 +i * 5) * 14.f, topLeftCorner.y + (j * 5) * 14.f);
						map[1 +i * 5][ j * 5] = new sf::CircleShape(circle);

						circle.setPosition(topLeftCorner.x + (1 + i * 5) * 14.f, topLeftCorner.y + (-1 + j * 5) * 14.f);
						map[1 + i * 5][-1 + j * 5] = new sf::CircleShape(circle);
					}
				}
				else
				{

				}

				if (j < 9)
				{
					if (levelDesign[i][j + 1] == '.' || levelDesign[i][j + 1] == 'S')
					{
						circle.setPosition(topLeftCorner.x + (1 + i * 5) * 14.f, topLeftCorner.y + (2 + j * 5) * 14.f);
						map[1 + i * 5][2 +j * 5] = new sf::CircleShape(circle);

						circle.setPosition(topLeftCorner.x + (1 + i * 5) * 14.f, topLeftCorner.y + (3 + j * 5) * 14.f);
						map[1 + i * 5][3 + j * 5] = new sf::CircleShape(circle);
					}
				}
				else
				{

				}
			}
			
			if (levelDesign[i][j] == 'E')
			{
				Emerald emerald((1 + i * 5), (1 + j * 5),topLeftCorner,textures,3);
				emeralds.push_back(emerald);
			}
			if (levelDesign[i][j] == 'B')
			{
				MoneyBag moneyBag((1 + i * 5), (1 + j * 5), topLeftCorner, textures, 3);
				moneyBags.push_back(moneyBag);
			}
			if (levelDesign[i][j] == 'S')
			{
				if (j > 0 && levelDesign[i][j - 1] != '.')
				{
					circle.setPosition(topLeftCorner.x + (i * 5) * 14.f, topLeftCorner.y + (1 + j * 5) * 14.f);
					map[1 + i * 5][ j * 5] = new sf::CircleShape(circle);
				}
				if (j < 9 && levelDesign[i][j + 1] != '.')
				{
					circle.setPosition(topLeftCorner.x + (2 + i * 5) * 14.f, topLeftCorner.y + (1 + j * 5) * 14.f);
					map[1 + i * 5][2 + j * 5] = new sf::CircleShape(circle);
				}

				if (i > 0 && levelDesign[i-1][j] != '.')
				{
					circle.setPosition(topLeftCorner.x + (1 + i * 5) * 14.f, topLeftCorner.y + (j * 5) * 14.f);
					map[i * 5][1+ j * 5] = new sf::CircleShape(circle);
				}
				if (i < 14 && levelDesign[i+1][j] != '.')
				{
					circle.setPosition(topLeftCorner.x + (1 + i * 5) * 14.f, topLeftCorner.y + (2 + j * 5) * 14.f);
					map[2 + i * 5][1 + j * 5] = new sf::CircleShape(circle);
				}

				circle.setPosition(topLeftCorner.x + i * 5 * 14.f, topLeftCorner.y + j * 5 * 14.f);
				circle.setRadius(enemySpawnPositionTunelWidth);
				map[1 + i * 5][1 + j * 5] = new sf::CircleShape(circle);
				circle.setRadius(tunnelWidth);

				enemySpawnPos = sf::Vector2i(1 + 5 * i, 1 + 5 * j);
			}
			if (levelDesign[i][j] == 'D')
			{
				playerStartPos = sf::Vector2i(1 + 5 * i, 1 + 5 * j);
			}
		}


	}


	for (size_t i = 0; i < brColls; i++)
	{
		for (size_t j = 0; j < brRows; j++)
		{
			if (map[i][j] != nullptr)
			{
				diggedSpots[i][j] = true;
			}
			else
			{
				diggedSpots[i][j] = false;
			}
		}

	}
}

//public
Map::Map(int level, sf::Vector2f topLeftCorner, TextureHolder& textures) : textures(textures)
{
	this->topLeftCorner = topLeftCorner;

	char start[10][15] = {	'G','G','G','G','.','G','G','G','G','G','G','G','G','G','E',
							'G','G','G','G','.','G','G','G','G','G','.','.','.','S','G',
							'G','G','G','G','.','.','.','.','.','.','.','G','G','G','G',
							'G','G','G','G','G','G','G','.','G','G','G','G','G','G','G',
							'G','G','G','G','G','G','G','G','G','G','G','G','G','G','G',
							'G','B','G','G','G','G','G','G','G','G','G','G','G','G','G',
							'G','B','G','G','G','G','G','G','G','G','G','G','G','G','G',
							'G','.','G','G','G','G','G','G','G','G','G','G','G','G','G',
							'G','.','G','G','G','G','G','G','G','G','G','G','G','G','G',
							'B','G','G','G','G','G','G','G','G','G','G','G','G','G','.' };

	reshapeArray(start, levelDesign);

	for (size_t i = 0; i < brColls; i++)
	{
		for (size_t j = 0; j < brRows; j++)
		{
			map[i][j] = nullptr;
		}
	}

	initDiggedSpots();
	makeStartFormation();

}
Map::Map(const Map& other) : textures(other.textures)
{
	copyMap(other);
}
Map::~Map()
{
	deleteMap();
}

const Map& Map::operator=(const Map& other)
{
	if (this != &other)
	{
		deleteMap();
		copyMap(other);
	}
	return *this;
}

void Map::update(sf::Time& elapsedTime)
{
	for (size_t i = 0; i < moneyBags.size(); i++)
	{
		moneyBags[i].update(elapsedTime,this);
	}
}
void Map::render(sf::RenderTarget* target)
{
	for (size_t i = 0; i < brColls; i++)
	{
		for (size_t j = 0; j < brRows; j++)
		{
			if (map[i][j] != nullptr)
			{
				target->draw(*map[i][j]);
			}
		}
	}

	for (size_t i = 0; i < emeralds.size(); i++)
	{
		emeralds[i].render(target);
	}
	for (size_t i = 0; i < moneyBags.size(); i++)
	{
		moneyBags[i].render(target);
	}
}


sf::Vector2i Map::getPlayerStartPos() const
{
	return playerStartPos;
}
sf::Vector2i Map::getEnemySpawnPos() const
{
	return enemySpawnPos;
}
const bool** Map::getDiggedSpots() const
{
	return const_cast<const bool**>(diggedSpots);
}
const std::vector<Emerald>& Map::getEmeralds() const
{
	return emeralds;
}
const std::vector<MoneyBag>& Map::getMoneyBags() const
{
	return moneyBags;
}


void Map::createCircle(int x, int y)
{
	if (map[x][y] == nullptr)
	{
		
		map[x][y] = new sf::CircleShape(tunnelWidth);
		map[x][y]->setPosition(sf::Vector2f(topLeftCorner.x+x*14,topLeftCorner.y+y*14));
		diggedSpots[x][y] = true;
	}
}