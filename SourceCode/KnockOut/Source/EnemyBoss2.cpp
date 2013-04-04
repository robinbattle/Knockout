#include "EnemyBoss2.h"

#include "World.h"

namespace KnockOut
{
	

	void EnemyBoss2::setUp()
	{
		
		userGUI = UserGUI::getSingletonPtr();
		entity = mSceneManager->createEntity(appropriateName(ENTITY), "boss2.mesh");
		entity->setQueryFlags(NONE_MASK);
		sceneNode = mSceneManager->getRootSceneNode()->createChildSceneNode(appropriateName(SCENE_NODE));
		sceneNode->attachObject(entity);
		sceneNode->scale(3,3,3);
		sceneNode->scale(10,10,10);
		moveCD = 0.8f;
		allowMoving = false;
		finishedCurrentMovingSegment = true;
		assignedCurrentMovingSegment = false;

		mAnimationState = entity->getAnimationState("Run");
		mAnimationState->setLoop(true);
        entity->getAnimationState("Run")->setEnabled(true); 
		entity->getAnimationState("Run")->setWeight(1.0);

		killed = false;
		caught = false;
		fall = false;
		tolerance = 4.0f;

		mWalkSpeed = 235.0f;
        mDirection = Ogre::Vector3::ZERO;

		happy2Dead = 5.0f;
		nearlyDieTime = 3.0f;
		nearlyDie = false;
		die = false;
		reachHome = false;
		saveBody = 5.0f;
        ps = mSceneManager->createParticleSystem("EnemyBoss2Blast" + convertInt(ID), "TRPlayer/Torch");
		sceneNode->attachObject(ps); 
		ps->setVisible(false);
		lifeValue = 750;
		worthMoney = 15;
		
		mtext = new MovableText("EnemyBoss2TXT" + convertInt(ID), convertInt(lifeValue), "StarWars");
		mtext->setTextAlignment(MovableText::H_CENTER, MovableText::V_ABOVE); // Center horizontally and display above the node
		mtext->setLocalTranslation(Vector3(0,60,0));
		sceneNode->attachObject(mtext);
		attackToHome = false;
		mtext->setCharacterHeight(0.3);
		fireLastingTime = 0.0f;
	}

	
	std::string EnemyBoss2::appropriateName(NAME_TYPE type)
	{
		if(type == SCENE_NODE)
			return "EnemyBoss2Scenenode" + convertInt(ID);
		else if(type == ENTITY)
			return "EnemyBoss2Entity" + convertInt(ID);
		
		return NULL;
	}

	




	void EnemyBoss2::update(float time)
	{
			
			if(fireLastingTime > 0)
			{
				fireLastingTime -= time;
				ps->setVisible(true);
			}else
				ps->setVisible(false);	

			if(frostLastingTime <=0)
				frostCoefficient = 1;
			else
				frostLastingTime -= time;

			if(attackToHome)
			{
				attackToHome = false;
				userGUI->resetHealthBar(250);
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
				mAnimationState= entity->getAnimationState("Death");
				mAnimationState->setLoop(false);
				mAnimationState->setEnabled(true);
				nearlyDieTime -= time;

				if(nearlyDieTime < 0)
				{
					saveBody -= time;
					mAnimationState= entity->getAnimationState("Death");
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
						mAnimationState = entity->getAnimationState("Death");
						mAnimationState->setLoop(true);
						mAnimationState->setEnabled(true);
						nearlyDie = true;  
						attackToHome = true;
						mtext->setCaption("0");
					}else{
						// Rotation Code will go here later
						Ogre::Vector3 src = sceneNode->getOrientation() *(- Ogre::Vector3::UNIT_Z);
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


	void EnemyBoss2::destroy()
	{
		mSceneManager->destroyEntity(appropriateName(ENTITY));
		mSceneManager->destroySceneNode(appropriateName(SCENE_NODE));
		//mSceneManager->destroyParticleSystem("blast" + convertInt(ID));

		
		delete mtext;
	}
}

