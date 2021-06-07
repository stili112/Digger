#include "Game.h"
#include <iostream>

//private
//init
void Game::initVariables()
{
	window = nullptr;
}
void Game::initWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Digger", sf::Style::Close | sf::Style::Titlebar);
}
void Game::initTextures()
{
	textures.load(Textures::Digger, "Textures/Digger.png");
	textures.load(Textures::Hobbin, "Textures/Hobbin.png");
	textures.load(Textures::Nobbin, "Textures/Nobbin.png");
	textures.load(Textures::Bonus, "Textures/Bonus.png");
	textures.load(Textures::MoneyBag, "Textures/MoneyBag.png");
}

//update
void Game::processEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		}
	}
}
void Game::update(sf::Time elapsedTime)
{
	processEvents();
}

//render
void Game::render(sf::RenderTarget* target)
{
	//clear
	window->clear();

	//draw

	//display
	window->display();
}

//delete 
void Game::deleteVariables()
{
	delete window;
	window = nullptr;
}

//public
//Constructor Destructor
Game::Game()
{
	initVariables();
	initWindow();
	initTextures();
}
Game::~Game()
{
	deleteVariables();
}

//Functions
void Game::run()
{
	sf::Clock clock;
	sf::Time elapsedTime;

	while (window->isOpen())
	{
		elapsedTime = clock.restart();

		update(elapsedTime);
		render(window);
	}
}
