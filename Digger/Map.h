#pragma once

#include<vector>
#include<fstream>
#include<string>
#include<stdexcept>

#include<SFML/System.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#include"ResourceHolder.hpp"
#include"ResourceIdentifiers.hpp"
#include"StringHelpers.hpp"

#include"Emerald.h"
#include"Bonus.h"
#include"MoneyBag.h"

class Map
{
public:
	//ConstValues
	static const int TUNNEL_WIDTH = 33;
	static const int ENEMY_SPAWN_POSITION_TUNEL_WIDTH = 47;

	static const int BR_ROWS = 48;
	static const int BR_COLLS = 73;

	static const float PIXELS_BETWEEN_TWO_CIRCLES;

private:
	sf::Sprite background;

	//design
	char levelDesign[15][10];
	sf::CircleShape* map[BR_COLLS][BR_ROWS];
	bool** diggedSpots;

	//top left position
	sf::Vector2f topLeftCorner;

	//positions
	sf::Vector2i playerStartPos;
	sf::Vector2i enemySpawnPos;	

	//Textures
	TextureHolder& textures;

	//Emerald and Bags of Gold
	std::vector<Emerald> emeralds;
	std::vector<MoneyBag> moneyBags;
	Bonus* bonus;

	//init
	void initDiggedSpots();
	void initBackground();

	//functions
	void copyMap(const Map& other);
	void deleteMap();

	void reshapeArray(char from[10][15], char to[15][10]);

	void makeStartFormation();

	void readFromFile(int level);
public:

	Map(int level, sf::Vector2f topLeftCorner, TextureHolder& textures);
	Map(const Map& other);
	~Map();

	const Map& operator=(const Map& other);

	void update(sf::Time& elapsedTime);
	void render(sf::RenderTarget* target);

	//get
	sf::Vector2i getPlayerStartPos() const;
	sf::Vector2i getEnemySpawnPos() const;
	const bool** getDiggedSpots() const;
	std::vector<Emerald>& getEmeralds();
	std::vector<MoneyBag>& getMoneyBags();
	Bonus* getBonus();

	void createCircle(int x, int y);
	void spawnBonus();
	void deleteBonus();
	
	void loadMap(int level);
};

