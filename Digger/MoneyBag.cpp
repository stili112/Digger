#include "MoneyBag.h"
#include"Map.h"

//private
const float MoneyBag::movingEvrySeconds = 0.1f;

//public
MoneyBag::MoneyBag(int x, int y, sf::Vector2f topLeftPos, TextureHolder textures, float scale)
{
	this->x = x;
	this->y = y;
	falling = false;

	movingLeft = false;
	movingRight = false;

	sprite.setTexture(textures.get(Textures::MoneyBag));
	sprite.scale(scale, scale);
	sprite.setPosition(14 * x * topLeftPos.x + ofsetLeft, 14 * y * topLeftPos.y + ofsetTop);
}

void MoneyBag::update(sf::Time& elapsedTime, Map* diggedSpots)
{

}
void MoneyBag::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}

void MoneyBag::moveLeft()
{
	movingLeft = true;
}
void MoneyBag::moveRight()
{
	movingRight = true;
}

sf::FloatRect MoneyBag::getBounds() const
{
	return sprite.getGlobalBounds();
}