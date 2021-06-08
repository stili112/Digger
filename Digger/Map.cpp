#include "Map.h"

//private
//init
void Map::initDiggedSpots()
{
	diggedSpots = new bool* [brRows];
	for (size_t i = 0; i < brRows; i++)
	{
		diggedSpots[i] = new bool[brColls];
		for (size_t j = 0; j < brColls; j++)
		{
			diggedSpots[i][j] = false;
		}
	}
}

//functions
void Map::copyMap(const Map& other)
{
	for (size_t i = 0; i < brRows; i++)
	{
		for (size_t j = 0; j < brColls; j++)
		{
			diggedSpots[i][j] = other.diggedSpots[i][j];
			map[i][j] = new sf::CircleShape(other.map[i][j]->getRadius());
		}
	}
}
void Map::deleteMap()
{
	for (size_t i = 0; i < brRows; i++)
	{
		for (size_t j = 0; j < brColls; j++)
		{
			delete map[i][j];
		}
		delete[] diggedSpots[i];
	}
	delete[] diggedSpots;
}

void Map::makeStartFormation()
{
	sf::CircleShape circle(tunnelWidth);
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 15; j++)
		{
			if (levelDesign[i][j] == '.')
			{
				circle.setPosition((1 + j * 5) * 14.f, (1 + i * 5) * 14.f);
				map[1 + i * 5][1 + j * 5] = new sf::CircleShape(circle);

				if (i > 0)
				{
					if (levelDesign[i - 1][j] == '.')
					{
						circle.setPosition((1 + j * 5) * 14.f, (i * 5) * 14.f);
						map[i * 5][1 + j * 5] = new sf::CircleShape(circle);

						circle.setPosition((1 + j * 5) * 14.f, (-1 + i * 5) * 14.f);
						map[-1 + i * 5][1 + j * 5] = new sf::CircleShape(circle);
					}
				}
				if (i < 9)
				{
					if (levelDesign[i + 1][j] == '.')
					{
						circle.setPosition((1 + j * 5) * 14.f, (2 + i * 5) * 14.f);
						map[2 + i * 5][1 + j * 5] = new sf::CircleShape(circle);

						circle.setPosition((1 + j * 5) * 14.f, (3 + i * 5) * 14.f);
						map[3 + i * 5][1 + j * 5] = new sf::CircleShape(circle);
					}
				}

				if (j == 0)
				{
					circle.setPosition((j * 5) * 14.f, (1 + i * 5) * 14.f);
					map[1 + i * 5][j * 5] = new sf::CircleShape(circle);

					circle.setPosition((2 + j * 5) * 14.f, (1 + i * 5) * 14.f);
					map[1 + i * 5][2 + j * 5] = new sf::CircleShape(circle);

					circle.setPosition((3 + j * 5) * 14.f, (1 + i * 5) * 14.f);
					map[1 + i * 5][3 + j * 5] = new sf::CircleShape(circle);
				}
				else
				{
					if (j == 14)
					{
						circle.setPosition((2 + j * 5) * 14.f, (1 + i * 5) * 14.f);
						map[1 + i * 5][2 + j * 5] = new sf::CircleShape(circle);

						circle.setPosition((j * 5) * 14.f, (1 + i * 5) * 14.f);
						map[1 + i * 5][j * 5] = new sf::CircleShape(circle);

						circle.setPosition((-1 + j * 5) * 14.f, (1 + i * 5) * 14.f);
						map[1 + i * 5][-1 + j * 5] = new sf::CircleShape(circle);
					}
					else
					{
						if (levelDesign[i][j + 1] == '.')
						{
							circle.setPosition((2 + j * 5) * 14.f, (1 + i * 5) * 14.f);
							map[1 + i * 5][2 + j * 5] = new sf::CircleShape(circle);

							circle.setPosition((3 + j * 5) * 14.f, (1 + i * 5) * 14.f);
							map[1 + i * 5][3 + j * 5] = new sf::CircleShape(circle);
						}
						if (levelDesign[i][j - 1] == '.')
						{
							circle.setPosition((j * 5) * 14.f, (1 + i * 5) * 14.f);
							map[1 + i * 5][j * 5] = new sf::CircleShape(circle);

							circle.setPosition((-1 + j * 5) * 14.f, (1 + i * 5) * 14.f);
							map[1 + i * 5][-1 + j * 5] = new sf::CircleShape(circle);
						}
					}
				}


			}
		}

	}


	for (size_t i = 0; i < brRows; i++)
	{
		for (size_t j = 0; j < brColls; j++)
		{
			if (map[i][j] != nullptr)
			{
				diggedSpots[i][j] = true;
			}
		}

	}
}

//public
Map::Map(int level, sf::Vector2f topLeftCorner, TextureHolder& textures)
{
	this->topLeftCorner = topLeftCorner;

	char a[10][15] = { '.', '.', 'G', '.', '.', '.', 'G', '.', '.', '.', 'G', '.', '.', '.', 'G',
						'G', '.', '.', '.', 'G', '.', '.', '.', 'G', '.', '.', '.', 'G', '.', '.',
						'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G',
						'.', '.', 'G', '.', '.', '.', 'G', '.', '.', '.', 'G', '.', '.', '.', 'G',
						'G', '.', '.', '.', 'G', '.', '.', '.', 'G', '.', '.', '.', 'G', '.', '.',
						'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G',
						'.', '.', 'G', '.', '.', '.', 'G', '.', '.', '.', 'G', '.', '.', '.', 'G',
						'G', '.', '.', '.', 'G', '.', '.', '.', 'G', '.', '.', '.', 'G', '.', '.',
						'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G', 'G',
						'.', '.', 'G', '.', '.', '.', 'G', '.', '.', '.', 'G', '.', '.', '.', 'G',
	};

	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 15; j++)
		{
			levelDesign[i][j] = a[i][j];
		}
	}

	for (size_t i = 0; i < brRows; i++)
	{
		for (size_t j = 0; j < brColls; j++)
		{
			map[i][j] = nullptr;
		}
	}

	initDiggedSpots();
	makeStartFormation();

}
Map::Map(const Map& other)
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

}
void Map::render(sf::RenderTarget* target)
{
	for (size_t i = 0; i < 48; i++)
	{
		for (size_t j = 0; j < 73; j++)
		{
			if (map[i][j] != nullptr)
			{
				target->draw(*map[i][j]);
			}
		}
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