#include "Map.h"

//private
const float Map::PIXELS_BETWEEN_TWO_CIRCLES = 14.f;
 
//init
void Map::initDiggedSpots()
{
	diggedSpots = new bool* [BR_COLLS];
	for (size_t i = 0; i < BR_COLLS; i++)
	{
		diggedSpots[i] = new bool[BR_ROWS];
		for (size_t j = 0; j < BR_ROWS; j++)
		{
			diggedSpots[i][j] = false;
		}
	}
}
void Map::initBackground()
{
	background.setPosition(topLeftCorner.x, topLeftCorner.y);
	background.setTexture(textures.get(Textures::BACKGROUND));
	background.scale(3, 3);
	background.setTextureRect(sf::IntRect(0,0,1280, 720));
}

//functions
void Map::copyMap(const Map& other)
{
	background = background;
	topLeftCorner = other.topLeftCorner;
	playerStartPos = other.playerStartPos;
	enemySpawnPos = other.enemySpawnPos;
	emeralds = other.emeralds;
	moneyBags = other.moneyBags;

	if (other.bonus != nullptr)
	{
		bonus = new Bonus(*other.bonus);
	}
	else
	{
		bonus = nullptr;
	}

	//levelDesign char[15][10]
	for (size_t i = 0; i < 15; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			levelDesign[i][j] = other.levelDesign[i][j];
		}
	}


	//map and diggedSpots
	diggedSpots = new bool* [BR_COLLS];
	for (size_t i = 0; i < BR_COLLS; i++)
	{
		diggedSpots[i] = new bool[BR_ROWS];
	}

	for (size_t i = 0; i < BR_COLLS; i++)
	{
		for (size_t j = 0; j < BR_ROWS; j++)
		{
			diggedSpots[i][j] = other.diggedSpots[i][j];
			map[i][j] = new sf::CircleShape(other.map[i][j]->getRadius());
			map[i][j]->setFillColor(sf::Color::Black);
		}
	}
}
void Map::deleteMap()
{
	delete bonus;
	bonus = nullptr;

	for (size_t i = 0; i < BR_COLLS; i++)
	{
		for (size_t j = 0; j < BR_ROWS; j++)
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
	sf::CircleShape circle(TUNNEL_WIDTH);
	circle.setFillColor(sf::Color::Black);
	for (size_t i = 0; i < 15; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			makeTunels(circle, i, j);
			makeEmeralds(i, j);
			makeMoneyBags(i, j);
			makeEnemyStartPosition(circle, i, j);
			makePlayerStartPosition(i, j);
		}
	}

	for (size_t i = 0; i < BR_COLLS; i++)
	{
		for (size_t j = 0; j < BR_ROWS; j++)
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
void Map::makeTunels(sf::CircleShape& circle, int i, int j)
{
	if (!(i >= 0 && i <= 14 && j >= 0 && j <= 9))
	{
		return;
	}
	if (levelDesign[i][j] == '.' || levelDesign[i][j] == 'S' || levelDesign[i][j] == 'D')
	{
		if (levelDesign[i][j] == '.' || levelDesign[i][j] == 'D')
		{
			circle.setPosition(topLeftCorner.x + (1 + i * 5) * PIXELS_BETWEEN_TWO_CIRCLES, topLeftCorner.y + (1 + j * 5) * PIXELS_BETWEEN_TWO_CIRCLES);
			map[1 + i * 5][1 + j * 5] = new sf::CircleShape(circle);
		}

		if (i > 0)
		{
			if (levelDesign[i - 1][j] == '.' || levelDesign[i - 1][j] == 'S' || levelDesign[i - 1][j] == 'D')
			{
				circle.setPosition(topLeftCorner.x + (i * 5) * PIXELS_BETWEEN_TWO_CIRCLES, topLeftCorner.y + (1 + j * 5) * PIXELS_BETWEEN_TWO_CIRCLES);
				map[i * 5][1 + j * 5] = new sf::CircleShape(circle);

				circle.setPosition(topLeftCorner.x + (-1 + i * 5) * PIXELS_BETWEEN_TWO_CIRCLES, topLeftCorner.y + (1 + j * 5) * PIXELS_BETWEEN_TWO_CIRCLES);
				map[-1 + i * 5][1 + j * 5] = new sf::CircleShape(circle);
			}
		}
		else
		{
			if ( (j > 0 && levelDesign[i][j - 1] != '.' && levelDesign[i][j - 1] != 'S') && (j < 14 && levelDesign[i][j + 1] != '.' || levelDesign[i][j + 1] != 'S'))
			{
				circle.setPosition(topLeftCorner.x + (i * 5) * PIXELS_BETWEEN_TWO_CIRCLES, topLeftCorner.y + (1 + j * 5) * PIXELS_BETWEEN_TWO_CIRCLES);
				map[i * 5][1 + j * 5] = new sf::CircleShape(circle);
			}
			
		}

		if (i < 14)
		{
			if (levelDesign[i + 1][j] == '.' || levelDesign[i + 1][j] == 'S' || levelDesign[i + 1][j] == 'D')
			{
				circle.setPosition(topLeftCorner.x + (2 + i * 5) * PIXELS_BETWEEN_TWO_CIRCLES, topLeftCorner.y + (1 + j * 5) * PIXELS_BETWEEN_TWO_CIRCLES);
				map[2 + i * 5][1 + j * 5] = new sf::CircleShape(circle);

				circle.setPosition(topLeftCorner.x + (3 + i * 5) * PIXELS_BETWEEN_TWO_CIRCLES, topLeftCorner.y + (1 + j * 5) * PIXELS_BETWEEN_TWO_CIRCLES);
				map[3 + i * 5][1 + j * 5] = new sf::CircleShape(circle);
			}
		}
		else
		{
			circle.setPosition(topLeftCorner.x + (2 + i * 5) * PIXELS_BETWEEN_TWO_CIRCLES, topLeftCorner.y + (1 + j * 5) * PIXELS_BETWEEN_TWO_CIRCLES);
			map[2 + i * 5][1 + j * 5] = new sf::CircleShape(circle);
		}

		if (j > 0)
		{
			if (levelDesign[i][j - 1] == '.' || levelDesign[i][j - 1] == 'S' || levelDesign[i][j - 1] == 'D')
			{
				circle.setPosition(topLeftCorner.x + (1 + i * 5) * PIXELS_BETWEEN_TWO_CIRCLES, topLeftCorner.y + (j * 5) * PIXELS_BETWEEN_TWO_CIRCLES);
				map[1 + i * 5][j * 5] = new sf::CircleShape(circle);

				circle.setPosition(topLeftCorner.x + (1 + i * 5) * PIXELS_BETWEEN_TWO_CIRCLES, topLeftCorner.y + (-1 + j * 5) * PIXELS_BETWEEN_TWO_CIRCLES);
				map[1 + i * 5][-1 + j * 5] = new sf::CircleShape(circle);
			}
		}

		if (j < 9)
		{
			if (levelDesign[i][j + 1] == '.' || levelDesign[i][j + 1] == 'S' || levelDesign[i][j + 1] == 'D')
			{
				circle.setPosition(topLeftCorner.x + (1 + i * 5) * PIXELS_BETWEEN_TWO_CIRCLES, topLeftCorner.y + (2 + j * 5) * PIXELS_BETWEEN_TWO_CIRCLES);
				map[1 + i * 5][2 + j * 5] = new sf::CircleShape(circle);

				circle.setPosition(topLeftCorner.x + (1 + i * 5) * PIXELS_BETWEEN_TWO_CIRCLES, topLeftCorner.y + (3 + j * 5) * PIXELS_BETWEEN_TWO_CIRCLES);
				map[1 + i * 5][3 + j * 5] = new sf::CircleShape(circle);
			}
		}
	}

}
void Map::makeEmeralds(int i, int j)
{
	if (levelDesign[i][j] == 'E')
	{
		Emerald emerald((1 + i * 5), (1 + j * 5), topLeftCorner, textures, 3);
		emeralds.push_back(emerald);
	}
}
void Map::makeMoneyBags(int i, int j)
{
	if (levelDesign[i][j] == 'B')
	{
		MoneyBag moneyBag((1 + i * 5), (1 + j * 5), topLeftCorner, textures, 3);
		moneyBags.push_back(moneyBag);
	}
}
void Map::makeEnemyStartPosition(sf::CircleShape& circle, int i, int j)
{
	if (levelDesign[i][j] == 'S')
	{
		if (j > 0 && levelDesign[i][j - 1] != '.')
		{
			circle.setPosition(topLeftCorner.x + (i * 5) * PIXELS_BETWEEN_TWO_CIRCLES, topLeftCorner.y + (1 + j * 5) * PIXELS_BETWEEN_TWO_CIRCLES);
			map[1 + i * 5][j * 5] = new sf::CircleShape(circle);
		}
		if (j < 9 && levelDesign[i][j + 1] != '.')
		{
			circle.setPosition(topLeftCorner.x + (2 + i * 5) * PIXELS_BETWEEN_TWO_CIRCLES, topLeftCorner.y + (1 + j * 5) * PIXELS_BETWEEN_TWO_CIRCLES);
			map[1 + i * 5][2 + j * 5] = new sf::CircleShape(circle);
		}

		if (i > 0 && levelDesign[i - 1][j] != '.')
		{
			circle.setPosition(topLeftCorner.x + (1 + i * 5) * PIXELS_BETWEEN_TWO_CIRCLES, topLeftCorner.y + (j * 5) * PIXELS_BETWEEN_TWO_CIRCLES);
			map[i * 5][1 + j * 5] = new sf::CircleShape(circle);
		}
		if (i < 14 && levelDesign[i + 1][j] != '.')
		{
			circle.setPosition(topLeftCorner.x + (1 + i * 5) * PIXELS_BETWEEN_TWO_CIRCLES, topLeftCorner.y + (2 + j * 5) * PIXELS_BETWEEN_TWO_CIRCLES);
			map[2 + i * 5][1 + j * 5] = new sf::CircleShape(circle);
		}

		circle.setPosition(topLeftCorner.x + i * 5 * PIXELS_BETWEEN_TWO_CIRCLES, topLeftCorner.y + j * 5 * PIXELS_BETWEEN_TWO_CIRCLES);
		circle.setRadius(ENEMY_SPAWN_POSITION_TUNEL_WIDTH);
		map[1 + i * 5][1 + j * 5] = new sf::CircleShape(circle);
		circle.setRadius(TUNNEL_WIDTH);

		enemySpawnPos = sf::Vector2i(1 + 5 * i, 1 + 5 * j);
	}
}
void Map::makePlayerStartPosition(int i, int j)
{
	if (levelDesign[i][j] == 'D')
	{
		playerStartPos = sf::Vector2i(1 + 5 * i, 1 + 5 * j);
	}
}

void Map::readFromFile(int level)
{
	char temp[10][15];

	std::string fileName="Maps/level";
	fileName.append(toString(level));
	fileName.append(".txt");

	std::ifstream in(fileName);
	if (in.is_open())
	{
		for (size_t i = 0; i < 10; i++)
		{
			for (size_t j = 0; j < 15; j++)
			{
				in >> temp[i][j];
			}
		}

		reshapeArray(temp, levelDesign);

		in.close();
	}
	else
	{
		throw std::logic_error("Cant open: " + fileName);
	}
}

//public
Map::Map(int level, sf::Vector2f topLeftCorner, TextureHolder& textures) : textures(textures)
{
	this->topLeftCorner = topLeftCorner;

	bonus = nullptr;

	readFromFile(level);

	for (size_t i = 0; i < BR_COLLS; i++)
	{
		for (size_t j = 0; j < BR_ROWS; j++)
		{
			map[i][j] = nullptr;
		}
	}

	initDiggedSpots();
	initBackground();
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
	target->draw(background);

	for (size_t i = 0; i < BR_COLLS; i++)
	{
		for (size_t j = 0; j < BR_ROWS; j++)
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

	if (bonus != nullptr)
	{
		bonus->render(target);
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
std::vector<Emerald>& Map::getEmeralds()
{
	return emeralds;
}
std::vector<MoneyBag>& Map::getMoneyBags()
{
	return moneyBags;
}
Bonus* Map::getBonus()
{
	return bonus;
}


void Map::createCircle(int x, int y)
{
	if (map[x][y] == nullptr)
	{
		
		map[x][y] = new sf::CircleShape(TUNNEL_WIDTH);
		map[x][y]->setFillColor(sf::Color::Black);
		map[x][y]->setPosition(sf::Vector2f(topLeftCorner.x+x* PIXELS_BETWEEN_TWO_CIRCLES ,topLeftCorner.y+y* PIXELS_BETWEEN_TWO_CIRCLES));
		diggedSpots[x][y] = true;
	}
}
void Map::spawnBonus()
{
	if (bonus == nullptr)
	{
		bonus = new Bonus(enemySpawnPos.x, enemySpawnPos.y, topLeftCorner, textures, 3);
	}	
}
void Map::deleteBonus()
{
	if (bonus != nullptr)
	{
		delete bonus;
		bonus = nullptr;
	}
}
