#pragma once
#include<sstream>

#include<SFML/System.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#include"HighScoreSystem.h"
#include"AnimatedSprite.h"
#include"Animation.h"
#include"ResourceIdentifiers.hpp"
#include"ResourceHolder.hpp"

class MainMenu
{
private:
	//texts
	sf::Text maintText;
	sf::Text hightScore;
	sf::Text diggerText;
	sf::Text nobbinText;
	sf::Text hobbinText;
	sf::Text goldBagText;
	sf::Text emeraldText;
	sf::Text bonusText;

	sf::Text hightScoreText;

	AnimatedSprite digger;
	AnimatedSprite nobbin;
	AnimatedSprite hobbin;
	sf::Sprite goldBag;
	sf::Sprite emerald;
	sf::Sprite bonus;

	//go to play
	bool goToPlay;

	//init
	void initSpritesAndAnimations();
	void initHightScore();
	void initTexts();

	//resource
	TextureHolder& textures;
	HighScoreSystem& score;
	AnimationHolder& animation;
	FontHolder& fonts;

	//update
	void keyPress();
public:
	MainMenu(HighScoreSystem& score, AnimationHolder& animation, FontHolder& fonts, TextureHolder& textures);

	//update
	void update(sf::Time& elapsedTime);

	//render
	void render(sf::RenderTarget* target);

	bool getGoToPlay() const;
};

