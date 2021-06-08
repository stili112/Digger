#pragma once

#include<SFML/System.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#include"ResourceHolder.hpp"
#include"ResourceIdentifiers.hpp"

class Map;

class MoneyBag
{
private:
	//const
	static const int ofsetTop = 0;
	static const int ofsetLeft = 0;
	//moving left right down
	static const float movingEvrySeconds;

	//position
	int x;
	int y;

	//move
	bool movingLeft;
	bool movingRight;

	sf::Sprite sprite;
	bool falling;

	sf::Vector2f topLeftPos;
public:
	MoneyBag(int x, int y, sf::Vector2f topLeftPos, TextureHolder textures, float scale);

	void update(sf::Time& elapsedTime, Map* diggedSpots);
	void render(sf::RenderTarget* target);

	void moveLeft();
	void moveRight();

	sf::FloatRect getBounds() const;
};

