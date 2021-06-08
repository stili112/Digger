#include "Emerald.h"

//public
Emerald::Emerald(int x, int y, sf::Vector2f topLeftPos, TextureHolder textures, float scale)
{
	sprite.setTexture(textures.get(Textures::Emerald));
	sprite.scale(scale,scale);
	sprite.setPosition(14*x*topLeftPos.x + ofsetLeft, 14 * y * topLeftPos.y + ofsetTop);
}

sf::FloatRect Emerald::getBounds() const
{
	return sprite.getGlobalBounds();
}