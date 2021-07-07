#include "Game.h"
#include <iostream>

//private
Game Game::instance;

//init
void Game::initVariables()
{
	showFps = false;
	window = nullptr;
}
void Game::initWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(1074, 794), "Digger", sf::Style::Close | sf::Style::Titlebar);
}
void Game::initTextures()
{
	textures.load(Textures::DIGGER_CAN_FIRE, "Textures/DiggerCanFire.png");
	textures.load(Textures::DIGGER_CANT_FIRE, "Textures/DiggerCantFire.png");
	textures.load(Textures::HOBBIN, "Textures/Hobbin.png");
	textures.load(Textures::NOBBIN, "Textures/Nobbin.png");
	textures.load(Textures::BONUS, "Textures/Bonus.png");
	textures.load(Textures::MONEY_BAG, "Textures/MoneyBag.png");
	textures.load(Textures::EMERALD, "Textures/Emerald.png");
	textures.load(Textures::COINS, "Textures/Coins.png");
	textures.load(Textures::BULLET, "Textures/Bullet.png");
	textures.load(Textures::RIP, "Textures/Rip.png");
	textures.load(Textures::BACKGROUND, "Textures/Background.png");
	textures.load(Textures::LIVE_ICONE, "Textures/DiggerLiveIcone.png");

	textures.get(Textures::BACKGROUND).setRepeated(true);
}
void Game::initAnimation()
{
	//digger
	//can fire Bullet
	sf::Texture& diggerCanFireTexture = textures.get(Textures::DIGGER_CAN_FIRE);

	Animation diggerCanFireWalkingAnimationRight;
	diggerCanFireWalkingAnimationRight.setSpriteSheet(diggerCanFireTexture);
	diggerCanFireWalkingAnimationRight.addFrame(sf::IntRect(0, 0, 16, 16));
	diggerCanFireWalkingAnimationRight.addFrame(sf::IntRect(16, 0, 16, 16));
	diggerCanFireWalkingAnimationRight.addFrame(sf::IntRect(32, 0, 16, 16));
	diggerCanFireWalkingAnimationRight.addFrame(sf::IntRect(48, 0, 16, 16));

	Animation diggerCanFireWalkingAnimationUp;
	diggerCanFireWalkingAnimationUp.setSpriteSheet(diggerCanFireTexture);
	diggerCanFireWalkingAnimationUp.addFrame(sf::IntRect(0, 16, 16, 16));
	diggerCanFireWalkingAnimationUp.addFrame(sf::IntRect(16, 16, 16, 16));
	diggerCanFireWalkingAnimationUp.addFrame(sf::IntRect(32, 16, 16, 16));
	diggerCanFireWalkingAnimationUp.addFrame(sf::IntRect(48, 16, 16, 16));

	Animation diggerCanFireWalkingAnimationLeft;
	diggerCanFireWalkingAnimationLeft.setSpriteSheet(diggerCanFireTexture);
	diggerCanFireWalkingAnimationLeft.addFrame(sf::IntRect(0, 32, 16, 16));
	diggerCanFireWalkingAnimationLeft.addFrame(sf::IntRect(16, 32, 16, 16));
	diggerCanFireWalkingAnimationLeft.addFrame(sf::IntRect(32, 32, 16, 16));
	diggerCanFireWalkingAnimationLeft.addFrame(sf::IntRect(48, 32, 16, 16));

	Animation diggerCanFireWalkingAnimationDown;
	diggerCanFireWalkingAnimationDown.setSpriteSheet(diggerCanFireTexture);
	diggerCanFireWalkingAnimationDown.addFrame(sf::IntRect(0, 48, 16, 16));
	diggerCanFireWalkingAnimationDown.addFrame(sf::IntRect(16, 48, 16, 16));
	diggerCanFireWalkingAnimationDown.addFrame(sf::IntRect(32, 48, 16, 16));
	diggerCanFireWalkingAnimationDown.addFrame(sf::IntRect(48, 48, 16, 16));

	//cant Fire Bullet
	sf::Texture& diggerCantFireTexture = textures.get(Textures::DIGGER_CANT_FIRE);

	Animation diggerCantFireWalkingAnimationRight;
	diggerCantFireWalkingAnimationRight.setSpriteSheet(diggerCantFireTexture);
	diggerCantFireWalkingAnimationRight.addFrame(sf::IntRect(0, 0, 16, 16));
	diggerCantFireWalkingAnimationRight.addFrame(sf::IntRect(16, 0, 16, 16));
	diggerCantFireWalkingAnimationRight.addFrame(sf::IntRect(32, 0, 16, 16));
	diggerCantFireWalkingAnimationRight.addFrame(sf::IntRect(48, 0, 16, 16));

	Animation diggerCantFireWalkingAnimationUp;
	diggerCantFireWalkingAnimationUp.setSpriteSheet(diggerCantFireTexture);
	diggerCantFireWalkingAnimationUp.addFrame(sf::IntRect(0, 16, 16, 16));
	diggerCantFireWalkingAnimationUp.addFrame(sf::IntRect(16, 16, 16, 16));
	diggerCantFireWalkingAnimationUp.addFrame(sf::IntRect(32, 16, 16, 16));
	diggerCantFireWalkingAnimationUp.addFrame(sf::IntRect(48, 16, 16, 16));

	Animation diggerCantFireWalkingAnimationLeft;
	diggerCantFireWalkingAnimationLeft.setSpriteSheet(diggerCantFireTexture);
	diggerCantFireWalkingAnimationLeft.addFrame(sf::IntRect(0, 32, 16, 16));
	diggerCantFireWalkingAnimationLeft.addFrame(sf::IntRect(16, 32, 16, 16));
	diggerCantFireWalkingAnimationLeft.addFrame(sf::IntRect(32, 32, 16, 16));
	diggerCantFireWalkingAnimationLeft.addFrame(sf::IntRect(48, 32, 16, 16));

	Animation diggerCantFireWalkingAnimationDown;
	diggerCantFireWalkingAnimationDown.setSpriteSheet(diggerCantFireTexture);
	diggerCantFireWalkingAnimationDown.addFrame(sf::IntRect(0, 48, 16, 16));
	diggerCantFireWalkingAnimationDown.addFrame(sf::IntRect(16, 48, 16, 16));
	diggerCantFireWalkingAnimationDown.addFrame(sf::IntRect(32, 48, 16, 16));
	diggerCantFireWalkingAnimationDown.addFrame(sf::IntRect(48, 48, 16, 16));

	//Rip animation
	sf::Texture& ripTexture = textures.get(Textures::RIP);

	Animation ripAnimation;
	ripAnimation.setSpriteSheet(ripTexture);
	ripAnimation.addFrame(sf::IntRect(0, 0, 16, 16));
	ripAnimation.addFrame(sf::IntRect(16, 0, 16, 16));
	ripAnimation.addFrame(sf::IntRect(32, 0, 16, 16));
	ripAnimation.addFrame(sf::IntRect(48, 0, 16, 16));
	ripAnimation.addFrame(sf::IntRect(64, 0, 16, 16));

	//Hobbin
	sf::Texture& hobbinTexture = textures.get(Textures::HOBBIN);

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
	sf::Texture& nobbinTexture = textures.get(Textures::NOBBIN);

	Animation nobbinWalkingAnimationRight;
	nobbinWalkingAnimationRight.setSpriteSheet(nobbinTexture);
	nobbinWalkingAnimationRight.addFrame(sf::IntRect(0, 0, 16, 16));
	nobbinWalkingAnimationRight.addFrame(sf::IntRect(16, 0, 16, 16));
	nobbinWalkingAnimationRight.addFrame(sf::IntRect(32, 0, 16, 16));
	nobbinWalkingAnimationRight.addFrame(sf::IntRect(48, 0, 16, 16));

	//Bullet
	sf::Texture& bulletTexture = textures.get(Textures::BULLET);

	Animation bulletAnimation;
	bulletAnimation.setSpriteSheet(bulletTexture);
	bulletAnimation.addFrame(sf::IntRect(0, 0, 16, 16));
	bulletAnimation.addFrame(sf::IntRect(16, 0, 16, 16));
	bulletAnimation.addFrame(sf::IntRect(32, 0, 16, 16));
	
	//add to animation holder
	//digger
	//can fire
	std::unique_ptr<Animation> diggerCanFireResourceRight(new Animation(diggerCanFireWalkingAnimationRight));
	animations.insertResource(Animations::DIGGER_MOVE_RIGHT_CAN_FIRE, std::move(diggerCanFireResourceRight));

	std::unique_ptr<Animation> diggerCanFireResourceLeft(new Animation(diggerCanFireWalkingAnimationLeft));
	animations.insertResource(Animations::DIGGER_MOVE_LEFT_CAN_FIRE, std::move(diggerCanFireResourceLeft));

	std::unique_ptr<Animation> diggerCanFireResourceUp(new Animation(diggerCanFireWalkingAnimationUp));
	animations.insertResource(Animations::DIGGER_MOVE_UP_CAN_FIRE, std::move(diggerCanFireResourceUp));

	std::unique_ptr<Animation> diggerCanFireResourceDown(new Animation(diggerCanFireWalkingAnimationDown));
	animations.insertResource(Animations::DIGGER_MOVE_DOWN_CAN_FIRE, std::move(diggerCanFireResourceDown));

	//cant fire
	std::unique_ptr<Animation> diggerCantFireResourceRight(new Animation(diggerCantFireWalkingAnimationRight));
	animations.insertResource(Animations::DIGGER_MOVE_RIGHT_CANT_FIRE, std::move(diggerCantFireResourceRight));

	std::unique_ptr<Animation> diggerCantFireResourceLeft(new Animation(diggerCantFireWalkingAnimationLeft));
	animations.insertResource(Animations::DIGGER_MOVE_LEFT_CANT_FIRE, std::move(diggerCantFireResourceLeft));

	std::unique_ptr<Animation> diggerCantFireResourceUp(new Animation(diggerCantFireWalkingAnimationUp));
	animations.insertResource(Animations::DIGGER_MOVE_UP_CANT_FIRE, std::move(diggerCantFireResourceUp));

	std::unique_ptr<Animation> diggerCantFireResourceDown(new Animation(diggerCantFireWalkingAnimationDown));
	animations.insertResource(Animations::DIGGER_MOVE_DOWN_CANT_FIRE, std::move(diggerCantFireResourceDown));

	std::unique_ptr<Animation> ripAnimationResource(new Animation(ripAnimation));
	animations.insertResource(Animations::RIP_ANIMATION, std::move(ripAnimationResource));


	//hobbin
	std::unique_ptr<Animation> hobbinResourceRight(new Animation(hobbinWalkingAnimationRight));
	animations.insertResource(Animations::HOBBIN_MOVE_RIGHR, std::move(hobbinResourceRight));

	std::unique_ptr<Animation> hobbinResourceLeft(new Animation(hobbinrWalkingAnimationLeft));
	animations.insertResource(Animations::HOBBIN_MOVE_LEFT, std::move(hobbinResourceLeft));

	//nobbin
	std::unique_ptr<Animation> nobbinResource(new Animation(nobbinWalkingAnimationRight));
	animations.insertResource(Animations::NOBBIN_ANIMATION, std::move(nobbinResource));

	//bullet
	std::unique_ptr<Animation> bulletResource(new Animation(bulletAnimation));
	animations.insertResource(Animations::BULLET_ANIMATIONS, std::move(bulletResource));
	
}
void Game::initFonts()
{
	fonts.load(Fonts::TextFont, "Fonts/Roboto-Regular.ttf");
}
void Game::initStatistic()
{
	fpsText.setFont(fonts.get(Fonts::TextFont));
	fpsText.setPosition(850.f, 5.f);
	fpsText.setCharacterSize(18);
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
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::F)
			{
				showFps = !showFps;
			}
			break;
		}
	}
}
void Game::update(sf::Time& elapsedTime)
{
	processEvents();

	updateStatistics(elapsedTime);

	if (play != nullptr)
	{
		play->update(elapsedTime);

		if (play->getGameOver())
		{
			delete play;
			play = nullptr;
			menu = new MainMenu(highScoreSystem, animations, fonts, textures);
		}
	}
	if (menu != nullptr)
	{
		menu->update(elapsedTime);

		if (menu->getGoToPlay())
		{
			delete menu;
			menu = nullptr;
			play = new Play(textures, animations, fonts, highScoreSystem);
		}
	}
	
}
void Game::updateStatistics(sf::Time& elapsedTime)
{
	statisticsUpdateTime += elapsedTime;
	statisticsNumFrames += 1;

	if (statisticsUpdateTime >= sf::seconds(1.0f))
	{
		fpsText.setString(
			"Frames / Second = " + toString(statisticsNumFrames) + "\n" +
			"Time / Update = " + toString(statisticsUpdateTime.asMicroseconds() / statisticsNumFrames) + "us");

		statisticsUpdateTime -= sf::seconds(1.0f);
		statisticsNumFrames = 0;
	}
}


//render
void Game::render(sf::RenderTarget* target)
{
	//clear
	window->clear();

	//draw
	if (play != nullptr)
	{
		play->render(target);
	}
	if (menu != nullptr)
	{
		menu->render(target);
	}
	renderStatistic();

	//display
	window->display();
}
void Game::renderStatistic()
{
	if (showFps == true)
	{
		window->draw(fpsText);
	}
	
}

//delete 
void Game::deleteVariables()
{
	delete window;
	window = nullptr;

	delete play;
	play = nullptr;

	delete menu;
	menu = nullptr;
}
//Constructor
Game::Game()
{
	initVariables();
	initWindow();
	initTextures();
	initFonts();
	initAnimation();
	initStatistic();

	menu = new MainMenu(highScoreSystem, animations, fonts, textures);

}

//public
//Destructor
Game::~Game()
{
	deleteVariables();
}

//Functions
Game& Game::getInstance()
{
	return instance;
}

void Game::run()
{
	sf::Clock clock;
	sf::Time elapsedTime = sf::Time::Zero;

	while (window->isOpen())
	{
		elapsedTime = clock.restart();

		update(elapsedTime);
		render(window);
	}
}
