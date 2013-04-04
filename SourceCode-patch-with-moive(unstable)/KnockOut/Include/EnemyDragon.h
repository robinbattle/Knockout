#pragma once
#include "Common.h"
#include "Enemy.h"
#include "MovableText.h"
#include "UserGUI.h"

namespace KnockOut
{

	using namespace Ogre;

	class EnemyDragon : public Enemy
	{
		
	public:
		EnemyDragon(int ID): Enemy(ID)
		{

		}
		~EnemyDragon();

		void update(float time);

		void setUp();
		std::string appropriateName(NAME_TYPE type);
		void destroy();

		
	};
}

