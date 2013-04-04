#pragma once
#include "Common.h"
#include "BaseObject.h"


namespace KnockOut
{

	using namespace Ogre;

	class Player : public BaseObject
	{
		
	public:
		Player(int ID): BaseObject(ID)
		{
			//setUp();
		}
		~Player();

		virtual void setUp();
		void update(float time);
		void destroy();

		bool die;

		ParticleSystem* ps;
		Real tolerance; 

		Real happy2Dead;
		bool nearlyDie;
		

		Ogre::AnimationState *mAnimationState; // The current animation state of the object
		Ogre::Real mWalkSpeed;                 // The speed at which the object is moving
		Ogre::Real mDistance;                  // The distance the object has left to travel
		Ogre::Vector3 mDirection;              // The direction the object is moving
		Ogre::Vector3 mDestination;            // The destination the object is moving towards

		Ogre::Vector3 lastValidStep;


		void moveForward(float timeSinceLastFrame);
		void moveBackward(float timeSinceLastFrame);
		void turnLeft(float timeSinceLastFrame);
		void turnRight(float timeSinceLastFrame);
		void highJump();

		void setDie();
		void setIdle();
		void setRun();
		void setHighJump();
		void setHappyJump();

		Ogre::Real jumpFinishedHold;
		bool startJumpFinishedHoldCount;

		bool ifIdle;

	protected:
		std::string appropriateName(NAME_TYPE type);
		ParticleSystem* ps2;
	};
}

