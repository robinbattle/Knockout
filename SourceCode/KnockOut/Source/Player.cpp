#include "Player.h"



namespace KnockOut
{

	Player::~Player()
	{
		destroy();
	
	}


	void Player::setUp()
	{
		
		entity = mSceneManager->createEntity(appropriateName(ENTITY), "1.mesh");
		entity->setQueryFlags(NONE_MASK);
		sceneNode = mSceneManager->getRootSceneNode()->createChildSceneNode(appropriateName(SCENE_NODE));
		sceneNode->attachObject(entity);
		sceneNode->scale(25, 25, 25);
		mAnimationState = entity->getAnimationState("Fall");
		mAnimationState->setLoop(true);
        mAnimationState->setEnabled(true); 
		mAnimationState->setWeight(1.0);

		tolerance = 4.0f;

		mWalkSpeed = 60.0f;
        mDirection = Ogre::Vector3::ZERO;

		happy2Dead = 5.0f;
		nearlyDie = false;
		die = false;
        ps = mSceneManager->createParticleSystem("PlayerBlast" + convertInt(ID), "TRPlayer/Torch");
		sceneNode->attachObject(ps);
		ps->setVisible(false);

		startJumpFinishedHoldCount = false;
		jumpFinishedHold = 2.0f;

		ifIdle = true;

		lastValidStep = Ogre::Vector3::ZERO;
		
		//ps2 = mSceneManager->createParticleSystem("PlayerPenta", "PEExamples/pentagram");
		//sceneNode->attachObject(ps2);
		sceneNode->setPosition(0, 100, 0);
	}

	
	std::string Player::appropriateName(NAME_TYPE type)
	{
		if(type == SCENE_NODE)
			return "playerScenenode" + convertInt(ID);
		else if(type == ENTITY)
			return "playerEntity" + convertInt(ID);
		
		return NULL;
	}



	void Player::update(float time)
	{
		   
		mAnimationState->addTime(time);
		
		

		/*
		if(startJumpFinishedHoldCount == true)
		{
			jumpFinishedHold -= time;
			
			if(jumpFinishedHold < 0)
			{
				startJumpFinishedHoldCount = false;
				jumpFinishedHold = 2.0f;
			}
		}
		*/
	}


	void Player::destroy()
	{
		mSceneManager->destroyEntity(appropriateName(ENTITY));
		mSceneManager->destroySceneNode(appropriateName(SCENE_NODE));
		//mSceneManager->destroyParticleSystem("PlayerBlast" + convertInt(ID));
		//mSceneManager->destroyParticleSystem("PlayerPenta" + convertInt(ID));
		
	}





	void Player::moveForward(float timeSinceLastFrame){
		//if(!startJumpFinishedHoldCount)
		{
			sceneNode->translate(sceneNode->getOrientation() *Ogre::Vector3::UNIT_X * mWalkSpeed *timeSinceLastFrame);
		}	
	}

	void Player::moveBackward(float timeSinceLastFrame){
		//if(!startJumpFinishedHoldCount)
		{
			sceneNode->translate(-(sceneNode->getOrientation() *Ogre::Vector3::UNIT_X * mWalkSpeed *timeSinceLastFrame));
		}	
	}

	void Player::turnLeft(float timeSinceLastFrame){
		//rotate along y axis
		//if(!startJumpFinishedHoldCount)
		{
			Ogre::Radian degrees = Ogre::Radian(-timeSinceLastFrame);
			Ogre::Matrix3 tmp = Ogre::Matrix3(Ogre::Math::Cos(degrees), 0, -Ogre::Math::Sin(degrees),
															 0,1,0,
										Ogre::Math::Sin(degrees), 0, Ogre::Math::Cos(degrees)
													);

	
	
			sceneNode->setOrientation(sceneNode->getOrientation() * tmp);
		}
	}

	void Player::turnRight(float timeSinceLastFrame){
		//if(!startJumpFinishedHoldCount)
		{
			Ogre::Radian degrees = Ogre::Radian(timeSinceLastFrame);
			Ogre::Matrix3 tmp = Ogre::Matrix3(Ogre::Math::Cos(degrees), 0, -Ogre::Math::Sin(degrees),
															 0,1,0,
										Ogre::Math::Sin(degrees), 0, Ogre::Math::Cos(degrees)
													);
	
			sceneNode->setOrientation(sceneNode->getOrientation() * tmp);
		}
	}

	
	void Player::highJump()
	{
		setHighJump();
		startJumpFinishedHoldCount = true;
	
	}



	void Player::setDie()
	{
		mAnimationState = entity->getAnimationState("Death");
		mAnimationState->setLoop(true);
        mAnimationState->setEnabled(true); 
		mAnimationState->setWeight(1.0);
	}

	void Player::setIdle()
	{
		mAnimationState = entity->getAnimationState("Fall");
		mAnimationState->setLoop(true);
        mAnimationState->setEnabled(true); 
		mAnimationState->setWeight(1.0);
	}
	void Player::setRun()
	{
		mAnimationState = entity->getAnimationState("Run");
		mAnimationState->setLoop(true);
        mAnimationState->setEnabled(true); 
		mAnimationState->setWeight(1.0);
	}
	void Player::setHighJump()
	{
		mAnimationState = entity->getAnimationState("JumpStart1");
		mAnimationState->setLoop(true);
        mAnimationState->setEnabled(true); 
		mAnimationState->setWeight(1.0);
	}
	void Player::setHappyJump()
	{
		mAnimationState = entity->getAnimationState("JumpStart1");
		mAnimationState->setLoop(false);
        mAnimationState->setEnabled(true); 
		mAnimationState->setWeight(1.0);
	}


}

