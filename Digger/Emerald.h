#pragma once

#include<SFML/System.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#include"ResourceHolder.hpp"
#include"ResourceIdentifiers.hpp"

class Map;

class Emerald
{
private:
	//const
	static const int ofsetTop;
	static const int ofsetLeft;

	sf::Sprite sprite;

	sf::Vector2f topLeftPos;
public:
	Emerald(int x, int y, sf::Vector2f topLeftPos, TextureHolder& textures, float scale);

	void render(sf::RenderTarget* target);

	sf::FloatRect getBounds() const;
};

