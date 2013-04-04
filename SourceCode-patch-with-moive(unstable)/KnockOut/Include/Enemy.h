#pragma once
#include "Common.h"
#include "BaseObject.h"
#include "MovableText.h"
#include "UserGUI.h"

namespace KnockOut
{

	using namespace Ogre;

	class Enemy : public BaseObject
	{
		
	public:
		Enemy(int ID): BaseObject(ID)
		{

		}
		~Enemy();

		virtual void setUp();
		void update(float time);
		void destroy();

		bool die;
		float moveCD;
		bool allowMoving;
		bool finishedCurrentMovingSegment;
		bool assignedCurrentMovingSegment;

		int type;

		Vector3 targetPosition;
		Vector3 currentDirection;
		Vector3 currentPosition;

		Real frostLastingTime;
		Real frostCoefficient;

		Real fireLastingTime;

		Vector3 getCurrentDirection();

		bool ifToleranceReached();
		bool nextLocation();

		Real tolerance; 

		Real happy2Dead;
		bool nearlyDie;
		Real nearlyDieTime;
		bool reachHome;

		Real lifeValue;

		Real saveBody;
		bool cleanBody;
		MovableText *mtext;
		int worthMoney;

		Ogre::AnimationState *mAnimationState; // The current animation state of the object
		Ogre::Real mWalkSpeed;                 // The speed at which the object is moving
		Ogre::Real mDistance;                  // The distance the object has left to travel
		Ogre::Vector3 mDirection;              // The direction the object is moving
		Ogre::Vector3 mDestination;            // The destination the object is moving towards

		bool killed;

		bool caught;
		bool fall;

	protected:
		std::string appropriateName(NAME_TYPE type);
		ParticleSystem* ps;

		ParticleSystem* snow;
		bool showSnow;

		bool attackToHome;
		UserGUI *userGUI;

	};
}

