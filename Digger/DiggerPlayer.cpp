#include "DiggerPlayer.h"
//private
const int DiggerPlayer::OFSET_TOP = 0;
const int DiggerPlayer::OFSET_LEFT = 0;

const float DiggerPlayer::TIME_BEFORE_MOVE = 0.11f;

//init
void DiggerPlayer::initAnimation()
{
	currentAnimation = &animations.get(Animations::DiggerMoveRight);
	animatedSprite.play(*currentAnimation);
	animatedSprite.setPosition(topLeftCorner.x+ (1+x) * Map::PIXELS_BETWEEN_TWO_CIRCLES + OFSET_LEFT, topLeftCorner.y +(1+ y) * Map::PIXELS_BETWEEN_TWO_CIRCLES + OFSET_TOP);
	animatedSprite.scale(3, 3);
}

//update
void DiggerPlayer::moving(sf::Time& elapsedTime, Map* map)
{
    timerForMovment += elapsedTime.asSeconds();
    if (x % 5 == 1 && y % 5 == 1)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && y > 1)
        {
            moveUp(map);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && y < Map::BR_ROWS - 3)
        {
            moveDown(map);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && x > 1)
        {
            moveLeft(map);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && x <Map::BR_COLLS - 3)
        {
            moveRight(map);
        }
    }
    else
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            
            if (timerForMovment >= TIME_BEFORE_MOVE)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)  &&  (playerIsFacing == playerFacing::Up || playerIsFacing == playerFacing::Down))
                {
                    moveUp(map);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (playerIsFacing == playerFacing::Up || playerIsFacing == playerFacing::Down))
                {
                    moveDown(map);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (playerIsFacing == playerFacing::Left || playerIsFacing == playerFacing::Right))
                {
                    moveLeft(map);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (playerIsFacing == playerFacing::Left || playerIsFacing == playerFacing::Right))
                {
                    moveRight(map);
                }
                else
                {
                    if (playerIsFacing == playerFacing::Up)
                    {
                        moveUp(map);
                    }
                    if (playerIsFacing == playerFacing::Down)
                    {
                        moveDown(map);
                    }
                    if (playerIsFacing == playerFacing::Left)
                    {
                        moveLeft(map);
                    }
                    if (playerIsFacing == playerFacing::Right)
                    {
                        moveRight(map);
                    }
                }               
            }            
        }
    } 

    animatedSprite.play(*currentAnimation);
}
void DiggerPlayer::moveUp(Map* map)
{
    if (timerForMovment > TIME_BEFORE_MOVE)
    {
        playerIsFacing = playerFacing::Up;
        y--;
        map->createCircle(x, y - 1);
        currentAnimation = &animations.get(Animations::DiggerMoveUp);
        animatedSprite.move(0, -Map::PIXELS_BETWEEN_TWO_CIRCLES);
        timerForMovment = 0.f;
    }   
}
void DiggerPlayer::moveDown(Map* map)
{
    if (timerForMovment > TIME_BEFORE_MOVE)
    {
        playerIsFacing = playerFacing::Down;
        y++;
        map->createCircle(x, y + 1);
        currentAnimation = &animations.get(Animations::DiggerMoveDown);
        animatedSprite.move(0, Map::PIXELS_BETWEEN_TWO_CIRCLES);
        timerForMovment = 0.f;
    }
}
void DiggerPlayer::moveLeft(Map* map)
{
    if (timerForMovment > TIME_BEFORE_MOVE)
    {
        playerIsFacing = playerFacing::Left;
        x--;
        map->createCircle(x- 1, y);
        currentAnimation = &animations.get(Animations::DiggerMoveLeft);
        animatedSprite.move(-Map::PIXELS_BETWEEN_TWO_CIRCLES, 0);
        timerForMovment = 0.f;
    }
}
void DiggerPlayer::moveRight(Map* map)
{
    if (timerForMovment > TIME_BEFORE_MOVE)
    {
        playerIsFacing = playerFacing::Right;
        x++;
        map->createCircle(x + 1, y);
        currentAnimation = &animations.get(Animations::DiggerMoveRight);
        animatedSprite.move(Map::PIXELS_BETWEEN_TWO_CIRCLES, 0);
        timerForMovment = 0.f;
    }
}

//public
DiggerPlayer::DiggerPlayer(int x, int y, sf::Vector2f topLeftCorner, TextureHolder& textures, AnimationHolder& animations) : textures(textures) , animations(animations)
{
	this->x = x;
	this->y = y;
	this->topLeftCorner = topLeftCorner;
	initAnimation();

    playerIsFacing = playerFacing::Right;

	timerForMovment = 0.f;
}

//update
void DiggerPlayer::update(sf::Time& elapsedTime, Map* map)
{
    moving(elapsedTime,map);
	animatedSprite.update(elapsedTime);
}

//render
void DiggerPlayer::render(sf::RenderTarget* target)
{
	target->draw(animatedSprite);
}

//get
sf::FloatRect DiggerPlayer::getBound() const
{
    return animatedSprite.getGlobalBounds();
}