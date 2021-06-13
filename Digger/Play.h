#pragma once

#include<sstream>

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
#include"HighScoreSystem.h"
#include"Score.h"
#include"Bullet.h"

class Play
{
private:
	static const float SPACE_BETWEEN_LIVES;

	static const sf::Vector2f OFSET_MAP;

	//Enemy bonus
	static const int BONUS_ENEMY_SPAWN = 2;

	//levels
	static const int BR_LEVELS = 2;

	//points
	static const int EMERALD_POINTS = 25;
	static const int ENEMY_DEATH_AND_MONEY_POINTS = 250;
	static const int ENEMY_EATEN_POINTS = 200;
	static const int BONUS_EATEN_POINTS = 1000;

	int enemyEatenMultiplayer;

	//Musics
	sf::Music deathMusic;
	sf::Music normalMusic;
	sf::Music bonusRoundMusic;

	//Death
	static const float TIME_BEFORE_RESTART;
	float timerBeforeRestart;

	//bonus
	static const float TIME_SPAWN_BONUS;
	float timerSpawnBonus;
	bool bonusLassSpawned;

	static const float BONUS_TIME_DURATION;
	float timerBonus;
	bool bonusRound;

	//main Menu


	//text
	sf::Text points;

	//game info
	int currentLevel;	
	bool paused;
	bool gameOver;
	int brLifes;
	std::vector<sf::Sprite> lives;

	//Entitys
	Map* map;

	DiggerPlayer* player;
	std::vector<Enemy> enemys;

	//enemies spawn
	static const float TIME_SPAWN_ENEMY;
	static const int MAX_BR_ENEMYS = 5;
	int enemyLeftToSpawn;
	float timerSpawnMoreEnemy;

	//Resource holder
	TextureHolder& textures;
	AnimationHolder& animations;
	FontHolder& fonts;
	HighScoreSystem& highScoreSystem;

	//collision
	void collision();
	void playerEnemiesCollision();
	void enemiesBagCollision();
	void playerBagCollision();
	void bulletCollision();
	void colectBonus();
	void colectEmerald();

	//init
	void initVariables();
	void initText();
	void initMap();
	void initPlayer();

	void copyPlay(const Play& other);
	void deletePlay();

	//update
	void spawnEnemy(sf::Time& elapsedTime);
	void spawnBonus(sf::Time& elapsedTime);
	void updateDeathPlayer(sf::Time& elapsedTime);
	void updateBonusMode(sf::Time& elapsedTime);
	void updateNextMap();
	void updateLivesAndGameOver();

	void nextLevel();
	void playerDied();
	void updatePoints();

public:
	Play(TextureHolder& textures, AnimationHolder& animations, FontHolder& fonts, HighScoreSystem& system);
	Play(const Play& other);
	~Play();

	const Play& operator=(const Play& other);

	//update
	void update(sf::Time& elapsedTime);

	//render
	void render(sf::RenderTarget* target);

	bool getGameOver() const;
};

