#pragma once
#include "Common.h"
#include "BaseObject.h"
#include "EnemyFactory.h"
#include "DebugOverlay.h"
namespace KnockOut
{

	using namespace Ogre;

	class Bullet : public BaseObject
	{
		
	public:
		Bullet(int ID, Vector3 position, Quaternion orientation, BULLET_TYPE type): BaseObject(ID), position(position), orientation(orientation),type(type)
		{

		}
		~Bullet();

		BULLET_TYPE type;


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

		DebugOverlay *debug;
	protected:
		std::string appropriateName(NAME_TYPE type);
		ParticleSystem* ps;
		void chaseTarget(float time);
		bool yes;
	};
}

