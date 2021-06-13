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
	static const int ofsetTop;
	static const int ofsetLeft;
	//moving left right down
	static const float movingEvrySeconds;
	static const float timeBeforeStartFalling;

	//position
	int x;
	int y;

	//move
	bool movingLeft;
	bool movingRight;
	float timerForMovment;
	float timerBeforeFaling;
	int brTunelMoneyBagFallen;
	bool moneyBagIsBrocken;

	TextureHolder& textures;
	sf::Sprite sprite;
	bool falling;

	sf::Vector2f topLeftPos;
public:
	MoneyBag(int x, int y, sf::Vector2f topLeftPos, TextureHolder& textures, float scale);

	const MoneyBag& operator=(const MoneyBag& other);

	void update(sf::Time& elapsedTime, Map* diggedSpots);
	void render(sf::RenderTarget* target);

	//move
	void moveLeft();
	void moveRight();

	//get
	sf::FloatRect getBounds() const;
	sf::Vector2i getPosition() const;
	bool moneyBagIsFalling() const;
	bool getMoneyBagIsBrocken() const;
};

