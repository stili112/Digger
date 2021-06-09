#include "Emerald.h"
#include <iostream>

//private
const int Emerald::ofsetTop=9;
const int Emerald::ofsetLeft=9;

//public
Emerald::Emerald(int x, int y, sf::Vector2f topLeftPos, TextureHolder& textures, float scale)
{
	sprite.setTexture(textures.get(Textures::Emerald));
	sprite.scale(scale,scale);
	sprite.setPosition(14.f*x + topLeftPos.x + ofsetLeft, 14.f * y + topLeftPos.y + ofsetTop);
}

void Emerald::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}

sf::FloatRect Emerald::getBounds() const
{
	return sprite.getGlobalBounds();
}