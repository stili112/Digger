#pragma once

#include"Animation.h"

namespace sf
{
	class Texture;
}

namespace Textures
{
	enum ID
	{
		Digger,
		Nobbin,
		Hobbin,
		Bonus,
		Emerald,
		MoneyBag,
		Coins
	};
}

namespace Sound
{
	enum ID
	{
		d
	};
}

namespace Music
{
	enum ID
	{
		d
	};
}
namespace Animations
{
	enum ID
	{
		DiggerMoveLeft,
		DiggerMoveRight,
		DiggerMoveUp,
		DiggerMoveDown,
		HobbinMoveLeft,
		HobbinMoveRight,
		Nobbin
	};
}

namespace Fonts
{
	enum ID
	{
		TextFont
	};
}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

typedef ResourceHolder<sf::Sound, Sound::ID> SoundHolder;

typedef ResourceHolder<sf::Music, Music::ID> MusicHolder;

typedef ResourceHolder<Animation, Animations::ID> AnimationHolder;

typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;