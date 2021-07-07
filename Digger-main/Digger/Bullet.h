#pragma once

#include<SFML/System.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#include"StringHelpers.hpp"
#include"ResourceHolder.hpp"
#include"ResourceIdentifiers.hpp"
#include"AnimatedSprite.h"
#include"Animation.h"
#include"Map.h"
#include"DiggerPlayer.h"

namespace bulletMoving
{
	enum Moving
	{
		RIGHT,
		LEFT,
		UP,
		DOWN
	};
}

class Bullet
{
private:
	static const float OFSET_TOP;
	static const float OFSET_LEFT;

	static const float MOVING_SPEED;

	//start position
	int x;
	int y;
	sf::Vector2f topLeftCorner;

	//hited wall
	bool hitWall;

	//last digged circle pos
	int LastDiggedCircleX;
	int LastDiggedCircleY;
	float xOfset;
	float yOfset;

	//holder
	AnimationHolder& animations;

	//moving Direction
	sf::Vector2f moving;
	bulletMoving::Moving movingDirection;

	//animation
	AnimatedSprite animationSprite;

	//functions
	void getLastDiggedCircle(Map* map);
public:
	Bullet(int x, int y, sf::Vector2f topLeftCorner, AnimationHolder& animations,playerFacing::Facing movingDirection);

	//update
	void update(sf::Time& elapsedTime, Map* map);

	//render
	void render(sf::RenderTarget* target);

	sf::FloatRect getBounds() const;
	bool getHitWall() const;
};

