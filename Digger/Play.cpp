#include "Play.h"

//public
Play::Play(TextureHolder& textures, AnimationHolder& animations, FontHolder& fonts, HighScoreSystem& system) :textures(textures) , animations(animations) , fonts(fonts) , system(system)
{

}

//update
void Play::update(sf::Time& elapsedTime)
{

}

//render
void Play::render(sf::RenderTarget* target)
{

}

bool Play::getGameOver() const
{
	return gameOver;
}