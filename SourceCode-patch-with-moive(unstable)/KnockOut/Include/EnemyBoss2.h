#pragma once
#include "Common.h"
#include "Enemy.h"
#include "MovableText.h"
#include "UserGUI.h"

namespace KnockOut
{

	using namespace Ogre;

	class EnemyBoss2 : public Enemy
	{
		
	public:
		EnemyBoss2(int ID): Enemy(ID)
		{

		}
		~EnemyBoss2();

		void update(float time);

		void setUp();
		std::string appropriateName(NAME_TYPE type);
		void destroy();

		
	};
}

