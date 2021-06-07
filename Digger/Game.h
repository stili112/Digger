#pragma once

#include<SFML/System.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#include"StringHelpers.hpp"
#include"ResourceHolder.hpp"
#include"ResourceIdentifiers.hpp"

class Game
{
private:

	//window
	sf::RenderWindow* window;

	//Resource houders
	TextureHolder textures;

	//init
	void initVariables();
	void initWindow();
	void initTextures();

	//update
	void processEvents();
	void update(sf::Time elapsedTime);

	//render
	void render(sf::RenderTarget* target);

	//delete 
	void deleteVariables();
public:
	Game();
	~Game();

	void run();
};

