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
#include"DiggerPlayer.h"
#include"Map.h"

class Game
{
private:
	//window
	sf::RenderWindow* window;

	//Resource houders
	TextureHolder textures;
	MusicHolder musics;
	SoundHolder sounds;
	AnimationHolder animations;
	FontHolder fonts;

	//temp
	Map* map;
	DiggerPlayer* player;

	//init
	void initVariables();
	void initWindow();
	void initTextures();
	void initAnimation();
	void initSound();
	void initMusic();
	void initFonts();

	//update
	void processEvents();
	void update(sf::Time& elapsedTime);

	//render
	void render(sf::RenderTarget* target);

	//delete 
	void deleteVariables();
	
	
public:
	//Constructor
	Game();
	~Game();

	void run();
};

