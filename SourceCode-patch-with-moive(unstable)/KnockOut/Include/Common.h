#pragma once
#include <string>
#include "Ogre.h"
#include "SingletonT.h"
#include "DebugOverlay.h"
namespace KnockOut
{
	
	enum QueryFlags
	{
			TOWER_BULLET_MASK = 1<<0,
			TOWER_FIRE_MASK = 1<<1,
			TOWER_AREA_MASK = 1<<2,
			TOWER_CHAIN_MASK = 1<<3,
			TOWER_FROST_MASK = 1<<4,
			OBSTACLE_MASK = 1<<5,
			CATCHUP_MASK = 1<<6,
			NONE_MASK = 1<<7
	};


	
	enum BULLET_TYPE{

		BULLET_NORMAL = 1<<0,
		LIGHT_CHAIN = 1<<1
	
	};

	enum ENEMY_TYPE{

		ENEMY_NORMAL = 1<<0,
		ENEMY_TROLL = 1<<1,
		ENEMY_DRAGON = 1<<2,
		ENEMY_BOSS1 = 1<<3,
		ENEMY_BOSS2 = 1<<4,
	
	};
}
