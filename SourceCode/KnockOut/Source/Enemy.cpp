#include "Enemy.h"

#include "World.h"

namespace KnockOut
{
	KnockOutWorld *mWorld;
	Enemy::~Enemy()
	{
		destroy();
	
	}


	void Enemy::setUp()
	{
		mWorld = KnockOutWorld::getSingletonPtr();
		userGUI = UserGUI::getSingletonPtr();
		entity = mSceneManager->createEntity(appropriateName(ENTITY), "ogre.mesh");
		entity->setQueryFlags(NONE_MASK);
		sceneNode = mSceneManager->getRootSceneNode()->createChildSceneNode(appropriateName(SCENE_NODE));
		sceneNode->attachObject(entity);
		sceneNode->scale(9,9,9);

		moveCD = 0.8f;
		allowMoving = false;
		finishedCurrentMovingSegment = true;
		assignedCurrentMovingSegment = false;

		mAnimationState = entity->getAnimationState("Walk");
		mAnimationState->setLoop(true);
        entity->getAnimationState("Walk")->setEnabled(true); 
		entity->getAnimationState("Walk")->setWeight(1.0);

		killed = false;
		caught = false;
		fall = false;
		tolerance = 4.0f;

		mWalkSpeed = 35.0f;
        mDirection = Ogre::Vector3::ZERO;

		happy2Dead = 5.0f;
		nearlyDieTime = 3.0f;
		nearlyDie = false;
		die = false;
		reachHome = false;
		saveBody = 5.0f;
        ps = mSceneManager->createParticleSystem("blastEnemy" + convertInt(ID), "TRPlayer/Torch");
		sceneNode->attachObject(ps); 
		ps->setVisible(false);

	
		frostCoefficient = 1;
		lifeValue = 100;
		worthMoney = 5;
		
		mtext = new MovableText("EnemyTXT" + convertInt(ID), convertInt(lifeValue), "StarWars");
		mtext->setTextAlignment(MovableText::H_CENTER, MovableText::V_ABOVE); // Center horizontally and display above the node
		mtext->setLocalTranslation(Vector3(0,50,0));
		sceneNode->attachObject(mtext);
		attackToHome = false;
		frostLastingTime = 0;
		fireLastingTime = 0;
	}

	
	std::string Enemy::appropriateName(NAME_TYPE type)
	{
		if(type == SCENE_NODE)
			return "EnemyScenenode" + convertInt(ID);
		else if(type == ENTITY)
			return "EnemyEntity" + convertInt(ID);
		
		return NULL;
	}

	Vector3 Enemy::getCurrentDirection()
	{
		return Vector3(targetPosition.x - currentPosition.x, 0, targetPosition.y - currentPosition.y);
	}

	bool Enemy::ifToleranceReached()
	{
		if((currentPosition.x - targetPosition.x) * (currentPosition.x - targetPosition.x)
			+ (currentPosition.z - targetPosition.z) * (currentPosition.y - targetPosition.z) < tolerance)
		{
		
			return true;
		}
		return false;
	
	}

	bool Enemy::nextLocation(void)
	{
		if (ownPathPositionList.empty()) return false;

		 

		Ogre::Vector2 v = *ownPathPositionList.begin();

		mDestination = Vector3(v.x * 100 - 750, 0, v.y * 100 - 750);  // this gets the front of the deque
		//mDestination = Vector3(v.x, 0, v.y);  // this gets the front of the deque
		ownPathPositionList.pop_front();             // this removes the front of the deque
		mDirection = mDestination - sceneNode->getPosition();
		mDistance = mDirection.normalise();
		return true;
	}




	void Enemy::update(float time)
	{

			//if(caught)
			//	return;

			if(fireLastingTime > 0)
			{
				fireLastingTime -= time;
				ps->setVisible(true);
			}else
				ps->setVisible(false);


			if(frostLastingTime <=0){
				frostCoefficient = 1;
				//snow->setVisible(false);
			}
			else{
				frostLastingTime -= time;
				//snow->setVisible(true);
			}
			if(attackToHome)
			{
				attackToHome = false;
				userGUI->resetHealthBar(50);
				//mWorld->homeHealth -= 100;
				//mWorld->homeText->setCaption(convertInt(mWorld->homeHealth));
			}


			if(die){
				mtext->setCaption("0");
				mtext->setVisible(false);
				return;
			}
			if(saveBody < 0){
				die = true;
				mtext->setCaption("0");
				return;
			}
			 
			if(!nearlyDie && !die)
			{
				mtext->setCaption(convertInt(lifeValue));
			}else{
				mtext->setCaption("0");
				mtext->setVisible(false);
			}


			if(nearlyDie)
			{
				mAnimationState= entity->getAnimationState("Dying");
				mAnimationState->setLoop(false);
				mAnimationState->setEnabled(true);
				nearlyDieTime -= time;

				if(nearlyDieTime < 0)
				{
					saveBody -= time;
					mAnimationState= entity->getAnimationState("Dying");
					//die = true;
					//cleanBody = true;
				}
				mAnimationState->addTime(time * frostCoefficient);
				return;
			}


			if(caught)
				return;

		    if (mDirection == Ogre::Vector3::ZERO) {
				if (nextLocation()) {
					// Set walking animation
					mAnimationState = entity->getAnimationState("Run");
					mAnimationState->setLoop(true);
					mAnimationState->setEnabled(true);				
				}//if
			}else{
				Ogre::Real move = mWalkSpeed * time * frostCoefficient;
				mDistance -= move * frostCoefficient;
				if (mDistance <= 0.0f){                 
					sceneNode->setPosition(mDestination);
					mDirection = Ogre::Vector3::ZERO;				
					// Set animation based on if the robot has another point to walk to. 
					if (!nextLocation()){
						// Set Jump animation                     
						mAnimationState = entity->getAnimationState("Jump");
						mAnimationState->setLoop(true);
						mAnimationState->setEnabled(true);
						nearlyDie = true;
						attackToHome = true;
						mtext->setCaption("0");
					}else{
						// Rotation Code will go here later
						Ogre::Vector3 src = sceneNode->getOrientation() * Ogre::Vector3::UNIT_X;
						if ((1.0f + src.dotProduct(mDirection)) < 0.0001f) {
							sceneNode->yaw(Ogre::Degree(180));						
						}else{
							Ogre::Quaternion quat = src.getRotationTo(mDirection);
							sceneNode->rotate(quat);
							sceneNode->yaw(Ogre::Degree(90));	
						} // else
					}//else
				}else{
					sceneNode->translate(mDirection * move * frostCoefficient);
				} // else
			} // if
			mAnimationState->addTime(time * frostCoefficient);

			

			if(reachHome)
			{
				ps->setVisible(true);
				happy2Dead -= time;
				if(happy2Dead < 0)
				{
					die = true;
				}
			}

		
	}


	void Enemy::destroy()
	{
		if(type == 1)
		{
			mSceneManager->destroyEntity(appropriateName(ENTITY));
			mSceneManager->destroySceneNode(appropriateName(SCENE_NODE));
			mSceneManager->destroyParticleSystem("blastEnemy" + convertInt(ID));
			mSceneManager->destroyParticleSystem("Enemy" + convertInt(ID));
		}else if(type == 2)
		{
			mSceneManager->destroyEntity("EnemyTrollEntity" + convertInt(ID));
			mSceneManager->destroySceneNode("EnemyTrollScenenode" + convertInt(ID));
			mSceneManager->destroyParticleSystem("EnemyTrollBlast" + convertInt(ID));
		}else if(type == 3)
		{
			mSceneManager->destroyEntity("EnemyDragonEntity" + convertInt(ID));
			mSceneManager->destroySceneNode("EnemyDragonScenenode" + convertInt(ID));
			mSceneManager->destroyParticleSystem("EnemyDragonBlast" + convertInt(ID));
			
		}else if(type == 4)
		{
			mSceneManager->destroyEntity("EnemyBoss1Entity" + convertInt(ID));
			mSceneManager->destroySceneNode("EnemyBoss1Scenenode" + convertInt(ID));
			mSceneManager->destroyParticleSystem("EnemyBoss1Blast" + convertInt(ID));
		}else if(type == 5)
		{
			mSceneManager->destroyEntity("EnemyBoss2Entity" + convertInt(ID));
			mSceneManager->destroySceneNode("EnemyBoss2Scenenode" + convertInt(ID));
			mSceneManager->destroyParticleSystem("EnemyBoss2Blast" + convertInt(ID));
		}

		
		delete mtext;
	}
}

