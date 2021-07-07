#include "Bonus.h"
#include"Map.h"

//private
const int Bonus::OFSET_TOP = 9;
const int Bonus::OFSET_LEFT = 9;

//public
Bonus::Bonus(int x, int y, sf::Vector2f topLeftPos, TextureHolder& textures, float scale)
{
	sprite.setTexture(textures.get(Textures::BONUS));
	sprite.scale(scale, scale);
	sprite.setPosition(Map::PIXELS_BETWEEN_TWO_CIRCLES * x + topLeftPos.x + OFSET_LEFT, Map::PIXELS_BETWEEN_TWO_CIRCLES * y + topLeftPos.y + OFSET_TOP);
}

void Bonus::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}

sf::FloatRect Bonus::getBounds() const
{
	return sprite.getGlobalBounds();
}