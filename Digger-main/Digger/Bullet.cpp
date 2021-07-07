#include "Bullet.h"

//private
const float Bullet::OFSET_TOP = 9;
const float Bullet::OFSET_LEFT = 9;

const float Bullet::MOVING_SPEED=300.f;

void Bullet::getLastDiggedCircle(Map* map)
{
	const bool** diggedSpots = map->getDiggedSpots();
	bool flag = true;

	if (movingDirection == bulletMoving::UP)
	{
		while (flag)
		{
			flag = false;

			if (LastDiggedCircleY>1 && diggedSpots[LastDiggedCircleX][LastDiggedCircleY - 1])
			{
				flag = true;
				LastDiggedCircleY--;
			}
			if (LastDiggedCircleY > 2 && diggedSpots[LastDiggedCircleX][LastDiggedCircleY - 2])
			{
				flag = true;
				LastDiggedCircleY -= 2;
			}
			if (LastDiggedCircleY > 3 && diggedSpots[LastDiggedCircleX][LastDiggedCircleY - 3])
			{
				flag = true;
				LastDiggedCircleY -= 3;
			}
			if (LastDiggedCircleY > 4 && diggedSpots[LastDiggedCircleX][LastDiggedCircleY - 4])
			{
				flag = true;
				LastDiggedCircleY -= 4;
			}
		}
	}
	if (movingDirection == bulletMoving::DOWN)
	{
		while (flag)
		{
			flag = false;

			if (LastDiggedCircleY < Map::BR_ROWS - 1 && diggedSpots[LastDiggedCircleX][LastDiggedCircleY + 1])
			{
				flag = true;
				LastDiggedCircleY++;
			}
			if (LastDiggedCircleY < Map::BR_ROWS - 2 && diggedSpots[LastDiggedCircleX][LastDiggedCircleY + 2])
			{
				flag = true;
				LastDiggedCircleY += 2;
			}
			if (LastDiggedCircleY < Map::BR_ROWS - 3 && diggedSpots[LastDiggedCircleX][LastDiggedCircleY + 3])
			{
				flag = true;
				LastDiggedCircleY += 3;
			}
			if (LastDiggedCircleY < Map::BR_ROWS - 4 && diggedSpots[LastDiggedCircleX][LastDiggedCircleY + 4])
			{
				flag = true;
				LastDiggedCircleY += 4;
			}
		}
	}
	if (movingDirection == bulletMoving::LEFT)
	{
		while (flag)
		{
			flag = false;

			if (LastDiggedCircleX > 1 && diggedSpots[LastDiggedCircleX - 1][LastDiggedCircleY])
			{
				flag = true;
				LastDiggedCircleX--;
			}
			if (LastDiggedCircleX > 2 && diggedSpots[LastDiggedCircleX - 2][LastDiggedCircleY])
			{
				flag = true;
				LastDiggedCircleX -= 2;
			}
			if (LastDiggedCircleX > 3 && diggedSpots[LastDiggedCircleX - 3][LastDiggedCircleY])
			{
				flag = true;
				LastDiggedCircleX -= 3;
			}
			if (LastDiggedCircleX > 4 && diggedSpots[LastDiggedCircleX - 4][LastDiggedCircleY])
			{
				flag = true;
				LastDiggedCircleX -= 4;
			}
		}
	}
	if (movingDirection == bulletMoving::RIGHT)
	{
		while (flag)
		{
			flag = false;

			if (LastDiggedCircleX < Map::BR_COLLS-1 && diggedSpots[LastDiggedCircleX + 1][LastDiggedCircleY])
			{
				flag = true;
				LastDiggedCircleX++;
			}
			if (LastDiggedCircleX < Map::BR_COLLS - 2 && diggedSpots[LastDiggedCircleX + 2][LastDiggedCircleY])
			{
				flag = true;
				LastDiggedCircleX += 2;
			}
			if (LastDiggedCircleX < Map::BR_COLLS - 3 && diggedSpots[LastDiggedCircleX + 3][LastDiggedCircleY])
			{
				flag = true;
				LastDiggedCircleX += 3;
			}
			if (LastDiggedCircleX < Map::BR_COLLS - 4 && diggedSpots[LastDiggedCircleX + 4][LastDiggedCircleY])
			{
				flag = true;
				LastDiggedCircleX += 4;
			}
		}
	}
}

//public
Bullet::Bullet(int x, int y, sf::Vector2f topLeftCorner, AnimationHolder& animations, playerFacing::Facing movingDirection) : animations(animations)
{
	this->x = x;
	this->y = y;

	LastDiggedCircleX = x;
	LastDiggedCircleY = y;

	this->topLeftCorner = topLeftCorner;
	if (movingDirection==playerFacing::UP)
	{
		this->movingDirection = bulletMoving::UP;
		xOfset = Map::TUNNEL_WIDTH;
		yOfset = -OFSET_TOP;
	}
	else if (movingDirection == playerFacing::DOWN)
	{
		this->movingDirection = bulletMoving::DOWN;
		xOfset = Map::TUNNEL_WIDTH;
		yOfset = 2 * Map::TUNNEL_WIDTH + OFSET_TOP;
	}
	else if (movingDirection == playerFacing::LEFT)
	{
		this->movingDirection = bulletMoving::LEFT;
		xOfset = -OFSET_LEFT;
		yOfset = Map::TUNNEL_WIDTH;
	}
	else if (movingDirection == playerFacing::RIGHT)
	{
		this->movingDirection = bulletMoving::RIGHT;
		xOfset = 2 * Map::TUNNEL_WIDTH + OFSET_LEFT;
		yOfset = Map::TUNNEL_WIDTH;
	}
	
	animationSprite.setPosition(x * Map::PIXELS_BETWEEN_TWO_CIRCLES + topLeftCorner.x + OFSET_LEFT , y * Map::PIXELS_BETWEEN_TWO_CIRCLES + topLeftCorner.y + OFSET_TOP);
	animationSprite.play(animations.get(Animations::BULLET_ANIMATIONS));
	animationSprite.scale(3,3);

	hitWall = false;

	if (movingDirection == bulletMoving::DOWN)
	{
		moving.x = 0;
		moving.y = 1;
	}
	if (movingDirection == bulletMoving::UP)
	{
		moving.x = 0;
		moving.y = -1;
	}
	if (movingDirection == bulletMoving::LEFT)
	{
		moving.x = -1;
		moving.y = 0;
	}
	if (movingDirection == bulletMoving::RIGHT)
	{
		moving.x = 1;
		moving.y = 0;
	}
}

//update
void Bullet::update(sf::Time& elapsedTime, Map* map)
{
	animationSprite.move(moving * MOVING_SPEED*elapsedTime.asSeconds());

	getLastDiggedCircle(map);

	animationSprite.update(elapsedTime);

	sf::Vector2f tempPoint(topLeftCorner.x + LastDiggedCircleX * Map::PIXELS_BETWEEN_TWO_CIRCLES + xOfset, topLeftCorner.y + LastDiggedCircleY * Map::PIXELS_BETWEEN_TWO_CIRCLES + yOfset);
	if (animationSprite.getGlobalBounds().contains(tempPoint.x, tempPoint.y))
	{
		hitWall = true;
	}
}

//render
void Bullet::render(sf::RenderTarget* target)
{
	target->draw(animationSprite);
}

sf::FloatRect Bullet::getBounds() const
{
	return animationSprite.getGlobalBounds();
}
bool Bullet::getHitWall() const
{
	return hitWall;
}