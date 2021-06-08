#pragma once

#include<SFML/System.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#include"StringHelpers.hpp"
#include"ResourceHolder.hpp"
#include"ResourceIdentifiers.hpp"

#include"HighScoreSystem.h"
#include"Map.h"
#include"DiggerPlayer.h"
#include"Enemy.h"

class Play
{
private:
	//text
	sf::Text Points;

public:
	Play(TextureHolder& textures, AnimationHolder& animations, FontHolder& fonts);

	//update
	void update(sf::Time& elapsedTime);

	//render
	void render(sf::RenderTarget* target);
};

