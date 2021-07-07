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
		DIGGER_CAN_FIRE,
		DIGGER_CANT_FIRE,
		RIP,
		NOBBIN,
		HOBBIN,
		BONUS,
		EMERALD,
		MONEY_BAG,
		COINS,
		BULLET,
		BACKGROUND,
		LIVE_ICONE
	};
}

namespace Animations
{
	enum ID
	{
		DIGGER_MOVE_LEFT_CANT_FIRE,
		DIGGER_MOVE_RIGHT_CANT_FIRE,
		DIGGER_MOVE_UP_CANT_FIRE,
		DIGGER_MOVE_DOWN_CANT_FIRE,
		DIGGER_MOVE_LEFT_CAN_FIRE,
		DIGGER_MOVE_RIGHT_CAN_FIRE,
		DIGGER_MOVE_UP_CAN_FIRE,
		DIGGER_MOVE_DOWN_CAN_FIRE,
		RIP_ANIMATION,
		HOBBIN_MOVE_LEFT,
		HOBBIN_MOVE_RIGHR,
		NOBBIN_ANIMATION,
		BULLET_ANIMATIONS
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

typedef ResourceHolder<Animation, Animations::ID> AnimationHolder;

typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;