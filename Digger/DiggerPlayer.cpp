#include "DiggerPlayer.h"
#include"Bullet.h"

//private
const int DiggerPlayer::OFSET_TOP = 0;
const int DiggerPlayer::OFSET_LEFT = 0;

const float DiggerPlayer::TIME_BEFORE_MOVE = 0.11f;

const float DiggerPlayer::TIME_BEFORE_FIRE = 10.f;

//init
void DiggerPlayer::initAnimation()
{
	currentAnimation = &animations.get(Animations::DIGGER_MOVE_RIGHT_CAN_FIRE);
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
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)  &&  (playerIsFacing == playerFacing::UP || playerIsFacing == playerFacing::DOWN))
                {
                    moveUp(map);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (playerIsFacing == playerFacing::UP || playerIsFacing == playerFacing::DOWN))
                {
                    moveDown(map);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (playerIsFacing == playerFacing::LEFT || playerIsFacing == playerFacing::RIGHT))
                {
                    moveLeft(map);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (playerIsFacing == playerFacing::LEFT || playerIsFacing == playerFacing::RIGHT))
                {
                    moveRight(map);
                }
                else
                {
                    if (playerIsFacing == playerFacing::UP)
                    {
                        moveUp(map);
                    }
                    if (playerIsFacing == playerFacing::DOWN)
                    {
                        moveDown(map);
                    }
                    if (playerIsFacing == playerFacing::LEFT)
                    {
                        moveLeft(map);
                    }
                    if (playerIsFacing == playerFacing::RIGHT)
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
        playerIsFacing = playerFacing::UP;
        y--;
        map->createCircle(x, y - 1);
        animatedSprite.move(0, -Map::PIXELS_BETWEEN_TWO_CIRCLES);
        timerForMovment = 0.f;
    }   
}
void DiggerPlayer::moveDown(Map* map)
{
    if (timerForMovment > TIME_BEFORE_MOVE)
    {
        playerIsFacing = playerFacing::DOWN;
        y++;
        map->createCircle(x, y + 1);
        animatedSprite.move(0, Map::PIXELS_BETWEEN_TWO_CIRCLES);
        timerForMovment = 0.f;
    }
}
void DiggerPlayer::moveLeft(Map* map)
{
    if (timerForMovment > TIME_BEFORE_MOVE)
    {
        playerIsFacing = playerFacing::LEFT;
        x--;
        map->createCircle(x- 1, y);
        animatedSprite.move(-Map::PIXELS_BETWEEN_TWO_CIRCLES, 0);
        timerForMovment = 0.f;
    }
}
void DiggerPlayer::moveRight(Map* map)
{
    if (timerForMovment > TIME_BEFORE_MOVE)
    {
        playerIsFacing = playerFacing::RIGHT;
        x++;
        map->createCircle(x + 1, y);
        animatedSprite.move(Map::PIXELS_BETWEEN_TWO_CIRCLES, 0);
        timerForMovment = 0.f;
    }
}

void DiggerPlayer::updateAnimationCantAndCanFire()
{
    if (playerIsFacing == playerFacing::UP)
    {
        if (timerForFire >= TIME_BEFORE_FIRE)
        {
            currentAnimation = &animations.get(Animations::DIGGER_MOVE_UP_CAN_FIRE);
        }
        else
        {
            currentAnimation = &animations.get(Animations::DIGGER_MOVE_UP_CANT_FIRE);
        }
    }
    if (playerIsFacing == playerFacing::DOWN)
    {
        if (timerForFire >= TIME_BEFORE_FIRE)
        {
            currentAnimation = &animations.get(Animations::DIGGER_MOVE_DOWN_CAN_FIRE);
        }
        else
        {
            currentAnimation = &animations.get(Animations::DIGGER_MOVE_DOWN_CANT_FIRE);
        }
    }
    if (playerIsFacing == playerFacing::LEFT)
    {
        if (timerForFire >= TIME_BEFORE_FIRE)
        {
            currentAnimation = &animations.get(Animations::DIGGER_MOVE_LEFT_CAN_FIRE);
        }
        else
        {
            currentAnimation = &animations.get(Animations::DIGGER_MOVE_LEFT_CANT_FIRE);
        }
    }
    if (playerIsFacing == playerFacing::RIGHT)
    {
        if (timerForFire >= TIME_BEFORE_FIRE)
        {
            currentAnimation = &animations.get(Animations::DIGGER_MOVE_RIGHT_CAN_FIRE);
        }
        else
        {
            currentAnimation = &animations.get(Animations::DIGGER_MOVE_RIGHT_CANT_FIRE);
        }
    }
}

void DiggerPlayer::updateBullet(sf::Time& elapsedTime, Map* map)
{
    timerForFire += elapsedTime.asSeconds();
   
    fireBullet();

    if (bullet != nullptr)
    {
        bullet->update(elapsedTime, map);

        if (bullet->getHitWall())
        {
            deleteBullet();
        }
    }
}
void DiggerPlayer::fireBullet()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && timerForFire > TIME_BEFORE_FIRE && bullet==nullptr)
    {
        timerForFire = 0.f;
        bullet = new Bullet(x, y, topLeftCorner, animations, playerIsFacing);     
    }

}

//public
DiggerPlayer::DiggerPlayer(int x, int y, sf::Vector2f topLeftCorner, TextureHolder& textures, AnimationHolder& animations) : textures(textures) , animations(animations)
{
    bullet = nullptr;
	this->x = x;
	this->y = y;
	this->topLeftCorner = topLeftCorner;
	initAnimation();

    death = false;

    playerIsFacing = playerFacing::RIGHT;

	timerForMovment = 0.f;
    timerForFire = TIME_BEFORE_FIRE;
}

//update
void DiggerPlayer::update(sf::Time& elapsedTime, Map* map)
{
    if (death == false)
    {
        moving(elapsedTime, map);
        updateAnimationCantAndCanFire();
    }    

	animatedSprite.update(elapsedTime);
    updateBullet(elapsedTime, map);
}

//render
void DiggerPlayer::render(sf::RenderTarget* target)
{	

    if (bullet != nullptr)
    {
        bullet->render(target);
    }
    target->draw(animatedSprite);
}

void DiggerPlayer::deleteBullet()
{
    delete bullet;
    bullet = nullptr;
}

void DiggerPlayer::deathPlayer()
{
    death = true;
    animatedSprite.setLooped(false);
    currentAnimation = &animations.get(Animations::RIP_ANIMATION);
    animatedSprite.play(*currentAnimation);
    
    animatedSprite.setScale(3, 3);
}

//set
void DiggerPlayer::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
    animatedSprite.setPosition(topLeftCorner.x + (1 + x) * Map::PIXELS_BETWEEN_TWO_CIRCLES + OFSET_LEFT, topLeftCorner.y + (1 + y) * Map::PIXELS_BETWEEN_TWO_CIRCLES + OFSET_TOP);
}

//get
sf::FloatRect DiggerPlayer::getBound() const
{
    return animatedSprite.getGlobalBounds();
}
bool DiggerPlayer::getDeath() const
{
    return death;
}
const Bullet* DiggerPlayer::getBullet() const
{
    return bullet;
}
sf::Vector2i DiggerPlayer::getPosition() const
{
    sf::Vector2i position(x,y);
    return position;
}