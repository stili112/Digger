#include "Play.h"
#include <iostream>

//private
const float Play::TIME_SPAWN_ENEMY=5.f;
const float Play::SPACE_BETWEEN_LIVES=14.f;
const float Play::TIME_SPAWN_BONUS = 15.f;

const sf::Vector2f Play::OFSET_MAP=sf::Vector2f(0,70);

const float Play::BONUS_TIME_DURATION = 20.f;

const float Play::TIME_BEFORE_RESTART = 5.f;
 
//collision
void Play::collision()
{
	playerEnemiesCollision();
	enemiesBagCollision();
	playerBagCollision();
	bulletCollision();
	colectBonus();
	colectEmerald();
}
void Play::playerEnemiesCollision()
{
	if (player != nullptr)
	{
		for (size_t i = 0; i < enemys.size(); i++)
		{
			if (player->getBound().intersects(enemys[i].getBound()))
			{
				if (bonusRound)
				{
					highScoreSystem.addToCurrentScore(ENEMY_EATEN_POINTS);
					enemyEatenMultiplayer++;
					enemys.erase(enemys.begin() + i);
					i--;
				}
				else
				{
					playerDied();
					return;
				}
			}
		}
	}
	
	
}
void Play::enemiesBagCollision()
{
	for (size_t j = 0; j < enemys.size(); j++)
	{
		for (size_t i = 0; i < map->getMoneyBags().size(); i++)
		{
			if (enemys.size() == 0 || map->getMoneyBags().size() == 0)
			{
				return;
			}
			if (enemys[j].getBound().intersects(map->getMoneyBags()[i].getBounds()))
			{
				if (map->getMoneyBags()[i].moneyBagIsFalling())
				{
					enemys.erase(enemys.begin() + j);
					j--;
				}
				else
				{
					map->getMoneyBags().erase(map->getMoneyBags().begin() + i);
					i--;
				}

			}
		}
	}
	
}
void Play::playerBagCollision()
{
	if (player != nullptr)
	{
		for (size_t i = 0; i < map->getMoneyBags().size(); i++)
		{
			if (player->getBound().intersects(map->getMoneyBags()[i].getBounds()))
			{
				if (map->getMoneyBags()[i].getMoneyBagIsBrocken())
				{
					highScoreSystem.addToCurrentScore(ENEMY_DEATH_AND_MONEY_POINTS);
					map->getMoneyBags().erase(map->getMoneyBags().begin() + i);
					i--;
				}
				else if (map->getMoneyBags()[i].moneyBagIsFalling())
				{
					playerDied();
					map->getMoneyBags().erase(map->getMoneyBags().begin() + i);

				}
				else
				{
					if (map->getMoneyBags()[i].getPosition().y == player->getPosition().y)
					{
						if (map->getMoneyBags()[i].getPosition().x < player->getPosition().x)
						{
							map->getMoneyBags()[i].moveLeft();
							player->setPosition(player->getPosition().x + 1, player->getPosition().y);
						}
						if (map->getMoneyBags()[i].getPosition().x > player->getPosition().x)
						{
							map->getMoneyBags()[i].moveRight();
							player->setPosition(player->getPosition().x - 1, player->getPosition().y);
						}
					}
					if (map->getMoneyBags()[i].getPosition().x == player->getPosition().x)
					{
						if (map->getMoneyBags()[i].getPosition().y < player->getPosition().y)
						{
							player->setPosition(player->getPosition().x, player->getPosition().y + 1);
						}
						if (map->getMoneyBags()[i].getPosition().y > player->getPosition().y)
						{
							player->setPosition(player->getPosition().x, player->getPosition().y - 1);
						}
					}
				}


			}
		}
	}	
}
void Play::bulletCollision()
{
	if (player != nullptr)
	{
		if (player->getBullet() != nullptr)
		{
			for (size_t i = 0; i < enemys.size(); i++)
			{
				if (player->getBullet()->getBounds().intersects(enemys[i].getBound()))
				{					
					highScoreSystem.addToCurrentScore(ENEMY_DEATH_AND_MONEY_POINTS);
					enemys.erase(enemys.begin() + i);
					player->deleteBullet();
					i--;
					return;
				}
			}

		}
	}	
}
void Play::colectBonus()
{
	if (player != nullptr && map->getBonus() != nullptr)
	{
		if (player->getBound().intersects(map->getBonus()->getBounds()))
		{
			highScoreSystem.addToCurrentScore(BONUS_EATEN_POINTS);
			enemyLeftToSpawn += BONUS_ENEMY_SPAWN;
			map->deleteBonus();
			bonusRound = true;

			deathMusic.stop();
			normalMusic.stop();
			bonusRoundMusic.play();
		}
	}
}
void Play::colectEmerald()
{
	if (map != nullptr && player!=nullptr)
	{
		for (size_t i = 0; i < map->getEmeralds().size(); i++)
		{
			if (player->getBound().intersects(map->getEmeralds()[i].getBounds()))
			{
				highScoreSystem.addToCurrentScore(EMERALD_POINTS);
				map->getEmeralds().erase(map->getEmeralds().begin() + i);
				i--;
			}
		}
	}
	
}

//init
void Play::initVariables()
{
	enemyLeftToSpawn = MAX_BR_ENEMYS;
	
	paused = false;
	gameOver = false;
	bonusLassSpawned = false;	

	timerSpawnMoreEnemy = 0.f;
	timerSpawnBonus = 0.f;

	timerBeforeRestart = 0.f;
}
void Play::initText()
{
	points.setFont(fonts.get(Fonts::TextFont));
	points.setPosition(10, 10);
	points.setCharacterSize(25);
	points.setString("00000");
}
void Play::initMap()
{
	map = new Map(currentLevel, OFSET_MAP,textures);
}
void Play::initPlayer()
{
	player = new DiggerPlayer(map->getPlayerStartPos().x, map->getPlayerStartPos().y,OFSET_MAP,textures,animations);
}

void Play::copyPlay(const Play& other)
{
	enemyEatenMultiplayer = other.enemyEatenMultiplayer;
	timerSpawnBonus = other.timerSpawnBonus;
	bonusLassSpawned = other.bonusLassSpawned;

	timerBonus = other.timerBonus;
	bonusRound = other.bonusRound;

	points = other.points;
	currentLevel = other.currentLevel;
	paused = other.paused;
	gameOver = other.gameOver;
	brLifes = other.brLifes;

	lives = other.lives;

	map = new Map(*other.map);

	player = new DiggerPlayer(*other.player);
	enemys = other.enemys;

	enemyLeftToSpawn = other.enemyLeftToSpawn;
	timerSpawnMoreEnemy = other.timerSpawnMoreEnemy;

}
void Play::deletePlay()
{
	delete map;
	map = nullptr;
	delete player;
	player = nullptr;
}

//update
void Play::spawnEnemy(sf::Time& elapsedTime)
{
	if (enemyLeftToSpawn > 0)
	{
		timerSpawnMoreEnemy += elapsedTime.asSeconds();
		if (timerSpawnMoreEnemy >= TIME_SPAWN_ENEMY)
		{
			timerSpawnMoreEnemy = 0.f;
			Enemy temp(map->getEnemySpawnPos().x, map->getEnemySpawnPos().y,OFSET_MAP , textures, animations);
			enemys.push_back(temp);
			enemyLeftToSpawn--;
		}
	}
}
void Play::spawnBonus(sf::Time& elapsedTime)
{
	if (bonusLassSpawned == false && enemyLeftToSpawn == 0)
	{
		timerSpawnBonus += elapsedTime.asSeconds();
		if (timerSpawnBonus >= TIME_SPAWN_BONUS)
		{
			timerSpawnBonus = 0;
			map->spawnBonus();
			bonusLassSpawned = true;
		}
	}
}
void Play::updateDeathPlayer(sf::Time& elapsedTime)
{
	if (player != nullptr)
	{
		if (player->getDeath())
		{
			timerBeforeRestart += elapsedTime.asSeconds();
			if (timerBeforeRestart >= TIME_BEFORE_RESTART)
			{
				delete player;
				player = nullptr;
				initPlayer();
				timerBeforeRestart = 0.f;

				deathMusic.stop();
				normalMusic.play();
				bonusRoundMusic.stop();
			}
		}
	}
}
void Play::updateBonusMode(sf::Time& elapsedTime)
{
	if (bonusRound)
	{
		timerBonus += elapsedTime.asSeconds();
		if (timerBonus >= BONUS_TIME_DURATION)
		{
			timerBonus = 0.f;
			deathMusic.stop();
			normalMusic.play();
			bonusRoundMusic.stop();
		}
	}
}
void Play::updateNextMap()
{
	if ((enemyLeftToSpawn == 0 && enemys.size() == 0) || map->getEmeralds().size()==0)
	{
		currentLevel++;
		currentLevel = std::min(currentLevel,BR_LEVELS);

		nextLevel();
		normalMusic.play();
		deathMusic.stop();
		bonusRoundMusic.stop();

		delete player;
		initPlayer();

		initVariables();

		enemys.clear();
	}
}
void Play::updateLivesAndGameOver()
{
	int ofsetLeft = 120;
	if (brLifes == 2 && lives.size() != 2)
	{
		sf::Sprite liveIcone(textures.get(Textures::LIVE_ICONE));
		liveIcone.scale(3, 3);
		liveIcone.setPosition((float)ofsetLeft,10);

		lives.clear();
		lives.push_back(liveIcone);
		liveIcone.setPosition(ofsetLeft + liveIcone.getGlobalBounds().width + SPACE_BETWEEN_LIVES, 10);
		lives.push_back(liveIcone);
	}
	if (brLifes == 1 && lives.size() != 1)
	{
		sf::Sprite liveIcone(textures.get(Textures::LIVE_ICONE));
		liveIcone.scale(3, 3);
		liveIcone.setPosition((float)ofsetLeft, 10);

		lives.clear();
		lives.push_back(liveIcone);
	}
	if (brLifes == 0 && lives.size() != 0)
	{
		lives.clear();
	}
	
}

void Play::nextLevel()
{
	delete map; 
	initMap();
}
void Play::playerDied()
{
	brLifes--;
	player->deathPlayer();
	if (brLifes == -1)
	{
		gameOver = true;
		deathMusic.stop();
		normalMusic.stop();
		bonusRoundMusic.stop();
	}
	else
	{
		deathMusic.play();
		normalMusic.stop();
		bonusRoundMusic.stop();
		enemys.clear();
		timerSpawnMoreEnemy = 0.f;
	}

}
void Play::updatePoints()
{
	std::string pointsStr;
	std::string temp =toString(highScoreSystem.getCurrentScore());
	if (temp.length() == 1)
	{
		pointsStr = "0000";
	}
	if (temp.length() == 2)
	{
		pointsStr = "000";
	}
	if (temp.length() == 3)
	{
		pointsStr = "00";
	}
	if (temp.length() == 4)
	{
		pointsStr = "0";
	}
	std::stringstream pointsStream;
	pointsStream << pointsStr << temp;
	points.setString(pointsStream.str());
}

//public
Play::Play(TextureHolder& textures, AnimationHolder& animations, FontHolder& fonts, HighScoreSystem& system) :textures(textures) , animations(animations) , fonts(fonts) , highScoreSystem(system)
{
	currentLevel = 1;
	brLifes = 2;
	initVariables();

	initText();
	initMap();
	initPlayer();

	deathMusic.openFromFile("Music/DeathMusic.ogg");
	deathMusic.setLoop(true);
	normalMusic.openFromFile("Music/NormalMode.ogg");
	normalMusic.setLoop(true);
	bonusRoundMusic.openFromFile("Music/BonusMode.ogg");
	bonusRoundMusic.setLoop(true);

	normalMusic.play();
	deathMusic.stop();
	bonusRoundMusic.stop();
}
Play::Play(const Play& other) : textures(other.textures), animations(other.animations), fonts(other.fonts), highScoreSystem(other.highScoreSystem)
{
	copyPlay(other);
}
Play::~Play()
{
	deletePlay();
}

const Play& Play::operator=(const Play& other)
{
	if (this != &other)
	{
		deletePlay();
		copyPlay(other);
	}
	return *this;
}

//update
void Play::update(sf::Time& elapsedTime)
{
	if (gameOver == false)
	{
		updatePoints();

		updateNextMap();

		updateLivesAndGameOver();

		collision();
		spawnEnemy(elapsedTime);
		spawnBonus(elapsedTime);
		updateBonusMode(elapsedTime);

		updateDeathPlayer(elapsedTime);

		if (player != nullptr)
		{
			player->update(elapsedTime, map);
		}
		if (map != nullptr)
		{
			map->update(elapsedTime);
		}

		for (size_t i = 0; i < enemys.size(); i++)
		{
			enemys[i].update(elapsedTime, map, player);
		}
	}	
}

//render
void Play::render(sf::RenderTarget* target)
{

	if (map != nullptr)
	{
		map->render(target);
	}
	if (player != nullptr)
	{
		player->render(target);
	}	

	for (size_t i = 0; i < enemys.size(); i++)
	{
		enemys[i].render(target);
	}

	for (size_t i = 0; i < lives.size(); i++)
	{
		target->draw(lives[i]);
	}

	target->draw(points);
}

bool Play::getGameOver() const
{
	return gameOver;
}