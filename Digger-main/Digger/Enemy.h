#pragma once

#include<SFML/System.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#include"StringHelpers.hpp"
#include"ResourceHolder.hpp"
#include"ResourceIdentifiers.hpp"
#include "AnimatedSprite.h"
#include"Animation.h"

#include "Map.h"
#include"DiggerPlayer.h"



namespace enemy
{
	enum Type
	{
		HOBBIN,
		NOBBIN
	};
	enum Facing
	{
		LEFT,
		RIGHT
	};
}


class Enemy
{
private:
	//const
	static const int OFSET_TOP = 9;
	static const int OFSET_LEFT = 9;

	//position
	int x;
	int y;
	sf::Vector2f topLeftCorner;
	enemy::Facing facing;

	//Moving Speed(time before move)
	static const float TIME_BEFORE_MOVE;
	float timerForMovment;

	//Change type
	static const float TIME_BEFORE_CHANGE;
	float timerForChanege;
	enemy::Type type;

	//sprite
	AnimatedSprite animatedSprite;
	Animation* currentAnimation;

	//Resource holder
	TextureHolder& textures;
	AnimationHolder& animations;
	
	//init
	void initAnimation();

	//movements
	void nobbinMove(sf::Time& elapsedTime, Map* map, DiggerPlayer* player);
	void hobbinMove(sf::Time& elapsedTime, Map* map, DiggerPlayer* player);

	//copy
	void copyEnemy(const Enemy& other);

public:
	
	Enemy(int x, int y, sf::Vector2f topLeftCorner, TextureHolder& textures, AnimationHolder& animations);
	const Enemy& operator=(const Enemy& other);

	//update
	void update(sf::Time& elapsedTime, Map* map , DiggerPlayer* player);

	//render
	void render(sf::RenderTarget* target);

	//get
	sf::FloatRect getBound() const;
	enemy::Type getTypeEnemy() const;
};

