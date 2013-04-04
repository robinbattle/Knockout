#pragma once
#include "Common.h"
#include "BaseObject.h"
#include "BulletFactory.h"
#include "EnemyFactory.h"

namespace KnockOut
{

	using namespace Ogre;

	class BaseTower : public BaseObject
	{
		
	public:
		BaseTower(int ID): BaseObject(ID)
		{

		}
		~BaseTower();

		virtual void setUp();
		void update(float time);
		void destroy();
		Enemy *enemy;
		bool die;

		Real fireCD;

		Real range;
		

		int type;

		virtual bool ifInRange(Vector3 p, Vector3 q, Real range);

		//Vector3 targetPosition;
		//Vector3 currentDirection;
		Vector3 position;
		Quaternion orientation;
		DebugOverlay *debug;
		



	protected:
		virtual std::string appropriateName(NAME_TYPE type);
		ParticleSystem* ps;
		BulletFactory *bulletFactory;
		EnemyFactory *enemyFactory;
	};
}

