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
#include"MainMenu.h"
#include"DiggerPlayer.h"
#include"Map.h"
#include"Play.h"

class Game
{
private:
	//window
	sf::RenderWindow* window;

	HighScoreSystem highScoreSystem;

	//main menu
	MainMenu* menu;

	//frame statistic
	sf::Text fpsText;
	sf::Time statisticsUpdateTime;
	std::size_t statisticsNumFrames;

	//in game
	Play* play;

	//Resource houders
	bool showFps;
	TextureHolder textures;
	AnimationHolder animations;
	FontHolder fonts;

	//init
	void initVariables();
	void initWindow();
	void initTextures();
	void initAnimation();
	void initFonts();
	void initStatistic();

	//update
	void processEvents();
	void update(sf::Time& elapsedTime);
	void updateStatistics(sf::Time& elapsedTime);

	//render
	void render(sf::RenderTarget* target);
	void renderStatistic();

	//delete 
	void deleteVariables();

	static Game instance;

	//Constructor
	Game();

public:
	//Destructor
	~Game();

	//get instance
	static Game& getInstance();

	void run();
};

