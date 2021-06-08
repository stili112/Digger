#pragma once

#include<SFML/System.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#include"ResourceHolder.hpp"
#include"ResourceIdentifiers.hpp"

class Emerald
{
private:
	//const
	static const int ofsetTop = 0;
	static const int ofsetLeft = 0;

	sf::Sprite sprite;

	sf::Vector2f topLeftPos;
public:
	Emerald(int x, int y, sf::Vector2f topLeftPos, TextureHolder textures, float scale);

	sf::FloatRect getBounds() const;
};

