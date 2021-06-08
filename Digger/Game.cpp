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
void Game::initAnimation()
{
	//digger
	sf::Texture& diggerTexture = textures.get(Textures::Digger);

	Animation diggerWalkingAnimationRight;
	diggerWalkingAnimationRight.setSpriteSheet(diggerTexture);
	diggerWalkingAnimationRight.addFrame(sf::IntRect(0, 0, 16, 16));
	diggerWalkingAnimationRight.addFrame(sf::IntRect(16, 0, 16, 16));
	diggerWalkingAnimationRight.addFrame(sf::IntRect(32, 0, 16, 16));
	diggerWalkingAnimationRight.addFrame(sf::IntRect(48, 0, 16, 16));

	Animation diggerWalkingAnimationUp;
	diggerWalkingAnimationUp.setSpriteSheet(diggerTexture);
	diggerWalkingAnimationUp.addFrame(sf::IntRect(0, 16, 16, 16));
	diggerWalkingAnimationUp.addFrame(sf::IntRect(16, 16, 16, 16));
	diggerWalkingAnimationUp.addFrame(sf::IntRect(32, 16, 16, 16));
	diggerWalkingAnimationUp.addFrame(sf::IntRect(48, 16, 16, 16));

	Animation diggerWalkingAnimationLeft;
	diggerWalkingAnimationLeft.setSpriteSheet(diggerTexture);
	diggerWalkingAnimationLeft.addFrame(sf::IntRect(0, 32, 16, 16));
	diggerWalkingAnimationLeft.addFrame(sf::IntRect(16, 32, 16, 16));
	diggerWalkingAnimationLeft.addFrame(sf::IntRect(32, 32, 16, 16));
	diggerWalkingAnimationLeft.addFrame(sf::IntRect(48, 32, 16, 16));

	Animation diggerWalkingAnimationDown;
	diggerWalkingAnimationDown.setSpriteSheet(diggerTexture);
	diggerWalkingAnimationDown.addFrame(sf::IntRect(0, 48, 16, 16));
	diggerWalkingAnimationDown.addFrame(sf::IntRect(16, 48, 16, 16));
	diggerWalkingAnimationDown.addFrame(sf::IntRect(32, 48, 16, 16));
	diggerWalkingAnimationDown.addFrame(sf::IntRect(48, 48, 16, 16));

	//Hobbin
	sf::Texture& hobbinTexture = textures.get(Textures::Hobbin);

	Animation hobbinWalkingAnimationRight;
	hobbinWalkingAnimationRight.setSpriteSheet(hobbinTexture);
	hobbinWalkingAnimationRight.addFrame(sf::IntRect(0, 0, 16, 16));
	hobbinWalkingAnimationRight.addFrame(sf::IntRect(16, 0, 16, 16));
	hobbinWalkingAnimationRight.addFrame(sf::IntRect(32, 0, 16, 16));
	hobbinWalkingAnimationRight.addFrame(sf::IntRect(48, 0, 16, 16));

	Animation hobbinrWalkingAnimationLeft;
	hobbinrWalkingAnimationLeft.setSpriteSheet(hobbinTexture);
	hobbinrWalkingAnimationLeft.addFrame(sf::IntRect(0, 16, 16, 16));
	hobbinrWalkingAnimationLeft.addFrame(sf::IntRect(16, 16, 16, 16));
	hobbinrWalkingAnimationLeft.addFrame(sf::IntRect(32, 16, 16, 16));
	hobbinrWalkingAnimationLeft.addFrame(sf::IntRect(48, 16, 16, 16));

	//Nobbin
	sf::Texture& nobbinTexture = textures.get(Textures::Nobbin);

	Animation nobbinWalkingAnimationRight;
	nobbinWalkingAnimationRight.setSpriteSheet(nobbinTexture);
	nobbinWalkingAnimationRight.addFrame(sf::IntRect(0, 0, 16, 16));
	nobbinWalkingAnimationRight.addFrame(sf::IntRect(16, 0, 16, 16));
	nobbinWalkingAnimationRight.addFrame(sf::IntRect(32, 0, 16, 16));
	nobbinWalkingAnimationRight.addFrame(sf::IntRect(48, 0, 16, 16));
	
	//add to animation holder
	//digger
	std::unique_ptr<Animation> diggerResourceRight(new Animation(diggerWalkingAnimationRight));
	animations.insertResource(Animations::DiggerMoveRight, std::move(diggerResourceRight));

	std::unique_ptr<Animation> diggerResourceLeft(new Animation(diggerWalkingAnimationLeft));
	animations.insertResource(Animations::DiggerMoveLeft, std::move(diggerResourceLeft));

	std::unique_ptr<Animation> diggerResourceUp(new Animation(diggerWalkingAnimationUp));
	animations.insertResource(Animations::DiggerMoveUp, std::move(diggerResourceUp));

	std::unique_ptr<Animation> diggerResourceDown(new Animation(diggerWalkingAnimationDown));
	animations.insertResource(Animations::DiggerMoveDown, std::move(diggerResourceDown));

	//hobbin
	std::unique_ptr<Animation> hobbinResourceRight(new Animation(hobbinWalkingAnimationRight));
	animations.insertResource(Animations::HobbinMoveRight, std::move(hobbinResourceRight));

	std::unique_ptr<Animation> hobbinResourceLeft(new Animation(hobbinrWalkingAnimationLeft));
	animations.insertResource(Animations::HobbinMoveLeft, std::move(hobbinResourceLeft));

	//nobbin
	std::unique_ptr<Animation> nobbinResource(new Animation(nobbinWalkingAnimationRight));
	animations.insertResource(Animations::Nobbin, std::move(nobbinResource));
	
}
void Game::initSound()
{
	
}
void Game::initMusic()
{

}
void Game::initFonts()
{
	fonts.load(Fonts::TextFont, "Fonts/Roboto-Regular.ttf");
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
void Game::update(sf::Time& elapsedTime)
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
	initSound();
	initMusic();
	initFonts();
	initAnimation();
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
