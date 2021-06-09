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

	//game info
	int currentLevel;
	
	bool paused;
	bool gameOver;
	int brLifes;

	//Entitys
	Map* map;

	DiggerPlayer* player;
	std::vector<Enemy> enemys;

	//enemies spawn

	//Resource holder
	TextureHolder& textures;
	AnimationHolder& animations;
	FontHolder& fonts;
	HighScoreSystem& system;

	//collision
	void collision();
	void playerEnemiesCollision();
	void enemiesBagCollision();
	void playerBagCollision();

	//init
	void initText();
	void initMap();
	void initPlayer();

public:
	Play(TextureHolder& textures, AnimationHolder& animations, FontHolder& fonts, HighScoreSystem& system);
	~Play();

	//update
	void update(sf::Time& elapsedTime);

	//render
	void render(sf::RenderTarget* target);

	bool getGameOver() const;
};

