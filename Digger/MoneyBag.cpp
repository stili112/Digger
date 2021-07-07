#include "MoneyBag.h"
#include"Map.h"

//private
const float MoneyBag::movingEvrySeconds = 0.1f;
const float MoneyBag::timeBeforeStartFalling = 1.75f;
const int MoneyBag::ofsetTop = 9;
const int MoneyBag::ofsetLeft = 9;

//public
MoneyBag::MoneyBag(int x, int y, sf::Vector2f topLeftPos, TextureHolder& textures, float scale) :textures(textures)
{
	this->x = x;
	this->y = y;
	falling = false;
	timerForMovment = 0.f;
	moneyBagIsBrocken = false;
	brTunelMoneyBagFallen = 0;
	timerBeforeFaling = 0.f;

	movingLeft = false;
	movingRight = false;

	sprite.setTexture(textures.get(Textures::MONEY_BAG));
	sprite.scale(scale, scale);
	sprite.setPosition(Map::PIXELS_BETWEEN_TWO_CIRCLES * x + topLeftPos.x + ofsetLeft, Map::PIXELS_BETWEEN_TWO_CIRCLES * y + topLeftPos.y + ofsetTop);
}

const MoneyBag& MoneyBag::operator=(const MoneyBag& other)
{
	if (this != &other)
	{
		x = other.x;
		y = other.y;
		falling = other.falling;
		timerForMovment = other.timerForMovment;
		moneyBagIsBrocken = other.moneyBagIsBrocken;
		brTunelMoneyBagFallen = other.brTunelMoneyBagFallen;
		timerBeforeFaling = other.timerBeforeFaling;

		movingLeft = other.movingLeft;
		movingRight = other.movingRight;

		sprite = other.sprite;
	}
	return *this;

}


void MoneyBag::update(sf::Time& elapsedTime, Map* diggedSpots)
{

	if (!moneyBagIsBrocken)
	{
		if (movingLeft)
		{
			timerForMovment += elapsedTime.asSeconds();
			if (timerForMovment >= movingEvrySeconds)
			{
				timerForMovment = 0.f;
				sprite.move(-Map::PIXELS_BETWEEN_TWO_CIRCLES, 0);
				x--;
				if (x % 5 == 1)
				{
					movingLeft = false;
				}
			}
		}
		else
		{
			if (movingRight)
			{
				timerForMovment += elapsedTime.asSeconds();
				if (timerForMovment >= movingEvrySeconds)
				{
					timerForMovment = 0.f;
					sprite.move(Map::PIXELS_BETWEEN_TWO_CIRCLES, 0);
					x++;
					if (x % 5 == 1)
					{
						movingRight = false;
					}
				}
			}
		}

		if (y < Map::BR_ROWS - 2)
		{
			const bool** diggedSpot = diggedSpots->getDiggedSpots();
			
			if (y % 5 == 1)
			{
				
				if (diggedSpot[x][y + 5] || (y<(Map::BR_ROWS - 7) && diggedSpot[x][y + 8])  )
				{
					if (falling)
					{
						brTunelMoneyBagFallen++;

						diggedSpots->createCircle(x, y);
						timerForMovment = 0.f;
						sprite.move(0, Map::PIXELS_BETWEEN_TWO_CIRCLES);
						y++;
					}
					else
					{
						timerBeforeFaling += elapsedTime.asSeconds();
					}
					if (timeBeforeStartFalling < timerBeforeFaling)
					{
						falling = true;
						timerBeforeFaling = 0.f;
					}
					
					
				}
				else
				{
					falling = false;
					if (brTunelMoneyBagFallen >= 2)
					{
						moneyBagIsBrocken = true;
					}
					brTunelMoneyBagFallen = 0;
				}
			}
			else
			{
				if (falling)
				{
					timerForMovment += elapsedTime.asSeconds();
					if (timerForMovment >= movingEvrySeconds)
					{
						diggedSpots->createCircle(x, y);
						timerForMovment = 0.f;
						sprite.move(0, Map::PIXELS_BETWEEN_TWO_CIRCLES);
						y++;
					}
				}
			}
		}
		else
		{
			falling = false;
			if (brTunelMoneyBagFallen >= 2)
			{
				moneyBagIsBrocken = true;
			}
			brTunelMoneyBagFallen = 0;
		}
		
	}
	else
	{
		sprite.setTexture(textures.get(Textures::COINS));
	}
}
void MoneyBag::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}

void MoneyBag::moveLeft()
{
	if (x > 1)
	{
		movingLeft = true;
		sprite.move(-Map::PIXELS_BETWEEN_TWO_CIRCLES, 0);
		x--;
	}	
}
void MoneyBag::moveRight()
{
	if (x<Map::BR_COLLS-2)
	{
		movingRight = true;
		sprite.move(Map::PIXELS_BETWEEN_TWO_CIRCLES, 0);
		x++;
	}
	
}

sf::FloatRect MoneyBag::getBounds() const
{
	return sprite.getGlobalBounds();
}
sf::Vector2i MoneyBag::getPosition() const
{
	sf::Vector2i pos(x,y);
	return pos;
}
bool MoneyBag::moneyBagIsFalling() const
{
	return falling;
}
bool MoneyBag::getMoneyBagIsBrocken() const
{
	return moneyBagIsBrocken;
}