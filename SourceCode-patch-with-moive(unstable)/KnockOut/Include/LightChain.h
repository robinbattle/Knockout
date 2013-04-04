#pragma once
#include "Common.h"
#include "Bullet.h"
#include "EnemyFactory.h"
#include "DebugOverlay.h"
namespace KnockOut
{

	using namespace Ogre;

	class LightChain : public Bullet
	{
		
	public:
		LightChain(int ID, Vector3 position, Quaternion orientation, BULLET_TYPE type): Bullet(ID, position, orientation,type)
		{

		}
		~LightChain();

		typedef std::list<Enemy*>::iterator TargetIterator;
		std::list<Enemy*> targetList;
	

		virtual void setUp();
		void update(float time);
		void destroy();

		bool die;
		float lifeTime;

		EnemyFactory *enemyFactory;
		Enemy *currentTarget;

		Vector3 position;
		Quaternion orientation;

		Ogre::Real speed;

		int rebound;

		DebugOverlay *debug;
	protected:
		std::string appropriateName(NAME_TYPE type);
		ParticleSystem* ps;
		void chaseTarget(float time);
		bool yes;

		bool alreadyPickUpTarget;
	};
}

