#include "MainMenu.h"

//private
//init
void MainMenu::initSpritesAndAnimations()
{
	digger.play(animation.get(Animations::DIGGER_MOVE_RIGHT_CAN_FIRE));
	digger.setScale(3, 3);
	digger.setPosition(600,200);

	nobbin.play(animation.get(Animations::NOBBIN_ANIMATION));
	nobbin.setScale(3, 3);
	nobbin.setPosition(600, 275);

	hobbin.play(animation.get(Animations::HOBBIN_MOVE_RIGHR));
	hobbin.setScale(3, 3);
	hobbin.setPosition(600, 350);

	goldBag.setTexture(textures.get(Textures::MONEY_BAG));
	goldBag.setScale(3, 3);
	goldBag.setPosition(600, 425);

	emerald.setTexture(textures.get(Textures::EMERALD));
	emerald.setScale(3, 3);
	emerald.setPosition(600, 500);

	bonus.setTexture(textures.get(Textures::BONUS));
	bonus.setScale(3, 3);
	bonus.setPosition(600, 575);

}
void MainMenu::initHightScore()
{
	hightScoreText.setFont(fonts.get(Fonts::TextFont));
	hightScoreText.setCharacterSize(25);
	hightScoreText.setPosition(50, 150);

	score.updateHightScore();
	score.reseteCurrentScore();

	std::stringstream sstream;
	for (size_t i = 0; i < HighScoreSystem::MAX_BR_SCORES_SAVED; i++)
	{
		sstream << score.getScores()[i].getName()<<"        "<< score.getScores()[i].getScore() << std::endl;
	}

	hightScoreText.setFont(fonts.get(Fonts::TextFont));
	hightScoreText.setCharacterSize(25);
	hightScoreText.setPosition(100, 200);
	hightScoreText.setString(sstream.str());
}
void MainMenu::initTexts()
{
	maintText.setFont(fonts.get(Fonts::TextFont));
	maintText.setCharacterSize(25);
	maintText.setString("DIGGER");
	maintText.setPosition(450, 20);

	hightScore.setFont(fonts.get(Fonts::TextFont));
	hightScore.setCharacterSize(25);
	hightScore.setPosition(100, 125);
	hightScore.setString("HIGH SCORE");

	diggerText.setFont(fonts.get(Fonts::TextFont));
	diggerText.setCharacterSize(25);
	diggerText.setPosition(700, 200);
	diggerText.setString("DIGGER");

	nobbinText.setFont(fonts.get(Fonts::TextFont));
	nobbinText.setCharacterSize(25);
	nobbinText.setPosition(700, 275);
	nobbinText.setString("NOBBIN");

	hobbinText.setFont(fonts.get(Fonts::TextFont));
	hobbinText.setCharacterSize(25);
	hobbinText.setPosition(700, 350);
	hobbinText.setString("HOBBIN");

	goldBagText.setFont(fonts.get(Fonts::TextFont));
	goldBagText.setCharacterSize(25);
	goldBagText.setPosition(700, 425);
	goldBagText.setString("GOLD");

	emeraldText.setFont(fonts.get(Fonts::TextFont));
	emeraldText.setCharacterSize(25);
	emeraldText.setPosition(700, 500);
	emeraldText.setString("EMERALD");

	bonusText.setFont(fonts.get(Fonts::TextFont));
	bonusText.setCharacterSize(25);
	bonusText.setPosition(700, 575);
	bonusText.setString("BONUS");
}

//update
void MainMenu::keyPress()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) 
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		goToPlay = true;
	}
}

//public
MainMenu::MainMenu(HighScoreSystem& score, AnimationHolder& animation, FontHolder& fonts, TextureHolder& textures) : score(score) , animation(animation),fonts(fonts), textures(textures)
{
	goToPlay = false;
	initSpritesAndAnimations();
	initHightScore();
	initTexts();
}

//update
void MainMenu::update(sf::Time& elapsedTime)
{
	digger.update(elapsedTime);
	nobbin.update(elapsedTime);
	hobbin.update(elapsedTime);

	keyPress();
}

//render
void MainMenu::render(sf::RenderTarget* target)
{
	target->draw(digger);
	target->draw(nobbin);
	target->draw(hobbin);
	target->draw(emerald);
	target->draw(bonus);
	target->draw(goldBag);

	target->draw(hightScoreText);

	target->draw(maintText);
	target->draw(hightScore);
	target->draw(diggerText);
	target->draw(nobbinText);
	target->draw(hobbinText);
	target->draw(bonusText);
	target->draw(goldBagText);
	target->draw(emeraldText);
}

bool MainMenu::getGoToPlay() const
{
	return goToPlay;
}