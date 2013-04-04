#pragma once
#include "Common.h"
#include "Enemy.h"
#include "MovableText.h"
#include "UserGUI.h"

namespace KnockOut
{

	using namespace Ogre;

	class EnemyBoss1 : public Enemy
	{
		
	public:
		EnemyBoss1(int ID): Enemy(ID)
		{

		}
		~EnemyBoss1();

		void update(float time);

		void setUp();
		std::string appropriateName(NAME_TYPE type);
		void destroy();

		
	};
}

