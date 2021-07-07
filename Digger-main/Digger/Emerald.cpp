#include "Emerald.h"
#include"Map.h"

//private
const int Emerald::OFSET_TOP=9;
const int Emerald::OFSET_LEFT=9;

//public
Emerald::Emerald(int x, int y, sf::Vector2f topLeftPos, TextureHolder& textures, float scale)
{
	sprite.setTexture(textures.get(Textures::EMERALD));
	sprite.scale(scale,scale);
	sprite.setPosition(Map::PIXELS_BETWEEN_TWO_CIRCLES * x + topLeftPos.x + OFSET_LEFT, Map::PIXELS_BETWEEN_TWO_CIRCLES * y + topLeftPos.y + OFSET_TOP);
}

void Emerald::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}

sf::FloatRect Emerald::getBounds() const
{
	return sprite.getGlobalBounds();
}