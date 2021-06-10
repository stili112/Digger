#pragma once

#include<SFML/System.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#include"ResourceHolder.hpp"
#include"ResourceIdentifiers.hpp"
#include"AnimatedSprite.h"
#include"Animation.h"
#include"Map.h"

namespace playerFacing
{
	enum Facing
	{
		Right,
		Left,
		Up,
		Down
	};
}

class DiggerPlayer
{
private:
	//const
	static const int OFSET_TOP;
	static const int OFSET_LEFT;

	//Moving Speed(time before move)
	static const float TIME_BEFORE_MOVE;
	float timerForMovment;

	playerFacing::Facing playerIsFacing;

	//position
	int x;
	int y;
	sf::Vector2f topLeftCorner;

	//sprite
	AnimatedSprite animatedSprite;
	Animation* currentAnimation;

	//Resource holder
	TextureHolder& textures;
	AnimationHolder& animations;

	//init
	void initAnimation();

	//update
	void moving(sf::Time& elapsedTime, Map* map);
	void moveUp(Map* map);
	void moveDown(Map* map);
	void moveLeft(Map* map);
	void moveRight( Map* map);
	
public:
	DiggerPlayer(int x,int y, sf::Vector2f topLeftCorner, TextureHolder& textures, AnimationHolder& animations);

	//update
	void update(sf::Time& elapsedTime, Map* map);

	//render
	void render(sf::RenderTarget* target);

	//get
	sf::FloatRect getBound() const;
};

