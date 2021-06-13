#include "Enemy.h"
#include <iostream>


//private
const float Enemy::TIME_BEFORE_MOVE=0.115f;
const float Enemy::TIME_BEFORE_CHANGE=15.f;


//init
void Enemy::initAnimation()
{
	currentAnimation = &animations.get(Animations::NOBBIN_ANIMATION);
	animatedSprite = AnimatedSprite();
	animatedSprite.play(*currentAnimation);
	animatedSprite.scale(3, 3);
	animatedSprite.setPosition(topLeftCorner.x + x * Map::PIXELS_BETWEEN_TWO_CIRCLES + OFSET_LEFT, topLeftCorner.y + y * Map::PIXELS_BETWEEN_TWO_CIRCLES + OFSET_TOP);
}

//movements
void Enemy::nobbinMove(sf::Time& elapsedTime, Map* map, DiggerPlayer* player)
{
	timerForMovment += elapsedTime.asSeconds();
	currentAnimation = &animations.get(Animations::NOBBIN_ANIMATION);
	if (timerForMovment >= TIME_BEFORE_MOVE)
	{
		const bool** diggedSpots = map->getDiggedSpots();
		bool flag = true;
		while (flag)
		{
			int randNumber = rand() % 4;
			//move up
			if (randNumber == 0)
			{
				if ((y > 1 && diggedSpots[x][y - 1]) || (y > 2 && diggedSpots[x][y - 2]) || (y > 3 && diggedSpots[x][y - 3]) || (y > 4 && diggedSpots[x][y - 4]))
				{
					timerForMovment = 0.f;
					flag = false;
					y--;
				}
			}
			//move Right
			if (randNumber == 1)
			{
				if ((x < Map::BR_COLLS - 1 && diggedSpots[x+1][y]) || (x < Map::BR_COLLS - 2 && diggedSpots[x +2][y]) || (x < Map::BR_COLLS - 3 && diggedSpots[x + 3][y]) || (x < Map::BR_COLLS - 4 && diggedSpots[x+4][y]))
				{
					timerForMovment = 0.f;
					flag = false;
					x++;
				}
			}
			//move Down
			if (randNumber == 2)
			{
				if ((y <Map::BR_ROWS-1 && diggedSpots[x][y + 1]) || (y < Map::BR_ROWS - 2 && diggedSpots[x][y + 2]) || (y < Map::BR_ROWS - 3 && diggedSpots[x][y + 3]) || (y < Map::BR_ROWS - 4 && diggedSpots[x][y + 4]))
				{
					timerForMovment = 0.f;
					flag = false;
					y++;
				}
			}
			//move left
			if (randNumber == 3)
			{
				if ((x >1 && diggedSpots[x - 1][y]) || (x > 2 && diggedSpots[x - 2][y]) || (x > 3 && diggedSpots[x - 3][y]) || (x > 4 && diggedSpots[x - 4][y]))
				{
					timerForMovment = 0.f;
					flag = false;
					x--;
				}				
			}
		}
		animatedSprite.setPosition(OFSET_LEFT + topLeftCorner.x + x * Map::PIXELS_BETWEEN_TWO_CIRCLES, OFSET_TOP + topLeftCorner.y + y * Map::PIXELS_BETWEEN_TWO_CIRCLES);
	}
	animatedSprite.play(*currentAnimation);
}
void Enemy::hobbinMove(sf::Time& elapsedTime, Map* map, DiggerPlayer* player)
{
	timerForMovment += elapsedTime.asSeconds();
	currentAnimation = &animations.get(Animations::HOBBIN_MOVE_RIGHR);
	if (timerForMovment >= TIME_BEFORE_MOVE)
	{
		if (y % 5 == 1 && player->getPosition().x < x)
		{
			currentAnimation = &animations.get(Animations::HOBBIN_MOVE_LEFT);
			timerForMovment = 0.f;
			x--;
		}
		else if (y % 5 == 1 && player->getPosition().x > x)
		{
			currentAnimation = &animations.get(Animations::HOBBIN_MOVE_RIGHR);
			timerForMovment = 0.f;
			x++;
		}
		else if (x % 5 == 1 && player->getPosition().y < y)
		{
			timerForMovment = 0.f;
			y--;
		}
		else if (x % 5 == 1 && player->getPosition().y > y)
		{
			timerForMovment = 0.f;
			y++;
		}
		animatedSprite.setPosition(OFSET_LEFT + topLeftCorner.x + x * Map::PIXELS_BETWEEN_TWO_CIRCLES, OFSET_TOP + topLeftCorner.y + y * Map::PIXELS_BETWEEN_TWO_CIRCLES);
		map->createCircle(x, y);
	}
	animatedSprite.play(*currentAnimation);
}

//copy
void Enemy::copyEnemy(const Enemy& other)
{
	x = other.x;
	y = other.y;
	topLeftCorner = other.topLeftCorner;
	facing = other.facing;

	timerForMovment = other.timerForMovment;

	timerForChanege = other.timerForChanege;
	type = other.type;

	currentAnimation = currentAnimation;

}


//public
//constructors destructor
Enemy::Enemy(int x, int y, sf::Vector2f topLeftCorner, TextureHolder& textures, AnimationHolder& animations) : textures(textures) , animations(animations)
{
	srand(time(NULL));
	this->x = x;
	this->y = y;
	this->topLeftCorner = topLeftCorner;
	
	type = enemy::NOBBIN;
	facing = enemy::RIGHT;

	initAnimation();
}
const Enemy& Enemy::operator=(const Enemy& other)
{
	if (this != &other)
	{
		copyEnemy(other);
	}
	return *this;
}

//update
void Enemy::update(sf::Time& elapsedTime, Map* map, DiggerPlayer* player)
{
	timerForChanege += elapsedTime.asSeconds();
	if (timerForChanege >= TIME_BEFORE_CHANGE)
	{
		if (type == enemy::HOBBIN)
		{
			type = enemy::NOBBIN;
			timerForChanege = 0.f;			
		}
		else
		{
			type = enemy::HOBBIN;
			timerForChanege = 0.f;
			currentAnimation = &animations.get(Animations::HOBBIN_MOVE_RIGHR);
		}
	}
	
	if (type == enemy::HOBBIN)
	{
		hobbinMove(elapsedTime,map,player);
	}
	if (type == enemy::NOBBIN)
	{
		nobbinMove(elapsedTime, map, player);
	}

	
	animatedSprite.update(elapsedTime);
}

//render
void Enemy::render(sf::RenderTarget* target)
{
	target->draw(animatedSprite);
}

//get
sf::FloatRect Enemy::getBound() const
{
	return animatedSprite.getGlobalBounds();
}
enemy::Type Enemy::getTypeEnemy() const
{
	return type;
}
