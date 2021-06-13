#pragma once

#include<SFML/System.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#include "Animation.h"

class AnimatedSprite : public sf::Drawable, public sf::Transformable
{
private:
    const Animation* animation;
    sf::Time frameTime;
    sf::Time currentTime;
    std::size_t currentFrame;
    bool paused;
    bool looped;
    const sf::Texture* texture;
    sf::Vertex vertices[4];

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void setAnimation(const Animation& animation);
    void setFrameTime(sf::Time time);

public:
    explicit AnimatedSprite(sf::Time frameTime = sf::seconds(0.2f), bool paused = false, bool looped = true);

    void update(sf::Time deltaTime);
    void play();
    void play(const Animation& animation);
    void pause();
    void stop();
    void setLooped(bool looped);

    const Animation* getAnimation() const;
    sf::FloatRect getLocalBounds() const;
    sf::FloatRect getGlobalBounds() const;
    bool isLooped() const;
    bool isPlaying() const;
    sf::Time getFrameTime() const;
    void setFrame(std::size_t newFrame, bool resetTime = true);
};

