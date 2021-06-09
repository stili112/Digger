#pragma once

#include<vector>

#include<SFML/System.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#include"ResourceHolder.hpp"
#include"ResourceIdentifiers.hpp"

#include"Emerald.h"
#include"MoneyBag.h"

class Map
{
public:
	//ConstValues
	static const int tunnelWidth = 33;
	static const int enemySpawnPositionTunelWidth = 47;

	static const int brRows = 48;
	static const int brColls = 73;

private:

	//design
	char levelDesign[15][10];
	sf::CircleShape* map[brColls][brRows];
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

	//init
	void initDiggedSpots();

	//functions
	void copyMap(const Map& other);
	void deleteMap();

	void reshapeArray(char from[10][15], char to[15][10]);

	void makeStartFormation();
public:
	Map(int level, sf::Vector2f topLeftCorner, TextureHolder& textures);
	Map(const Map& other);
	~Map();

	const Map& operator=(const Map& other);

	void update(sf::Time& elapsedTime);
	void render(sf::RenderTarget* target);

	sf::Vector2i getPlayerStartPos() const;
	sf::Vector2i getEnemySpawnPos() const;
	const bool** getDiggedSpots() const;
	const std::vector<Emerald>& getEmeralds() const;
	const std::vector<MoneyBag>& getMoneyBags() const;

	void createCircle(int x, int y);
	
};

