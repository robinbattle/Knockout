#include "Bullet.h"


namespace KnockOut
{

	Bullet::~Bullet()
	{
		destroy();
	
	}


	void Bullet::setUp()
	{
		
		entity = mSceneManager->createEntity(appropriateName(ENTITY), "bullet.mesh");
 
		sceneNode = mSceneManager->getRootSceneNode()->createChildSceneNode(appropriateName(SCENE_NODE));
		sceneNode->attachObject(entity);
		sceneNode->scale(10,10,10);
		sceneNode->setPosition(position);
		sceneNode->setOrientation(orientation);
		lifeTime = 6.0f;

		enemyFactory = EnemyFactory::getSingletonPtr();
		
		die = false;
        //ps = mSceneManager->createParticleSystem("blast" + convertInt(ID), "TRPlayer/Torch");
		//sceneNode->attachObject(ps);
		//ps->setVisible(false);

		debug = DebugOverlay::getSingletonPtr();
		yes = true;

		currentTarget = 0;

		speed = 6;
	}

	
	std::string Bullet::appropriateName(NAME_TYPE type)
	{
		if(type == SCENE_NODE)
			return "bulletScenenode" + convertInt(ID);
		else if(type == ENTITY)
			return "bulletEntity" + convertInt(ID);
		
		return NULL;
	}

	

	void Bullet::update(float time)
	{
		    lifeTime -= time;

			//sceneNode->translate(Ogre::Vector3(0,1,0));
			if(lifeTime < 0){
				die = true;
				return;
			}
			
			


			if(currentTarget == NULL)
			{
				
				if(!enemyFactory->enemyList.empty())   //try to find a target
				{
					for (EnemyFactory::EnemyIterator ei = enemyFactory->enemyList.begin(); ei != enemyFactory->enemyList.end(); ei++){
						currentTarget = *ei;
						if(currentTarget != NULL)
							break;
					}
					

					
				}
				
				
			}

			//if(yes)
				

			if(currentTarget != NULL)  //still no target
			{
				
				//currentTarget->getEntity();
				chaseTarget(time);
			}

			
		
	}

	void Bullet::chaseTarget(float time)
	{
		if(currentTarget != NULL)  //make sure
		{
			sceneNode->translate( (currentTarget->getSceneNode()->getPosition() - sceneNode->getPosition()) * time * speed); 
		}
	
	}


	


	void Bullet::destroy()
	{
		
		//mSceneManager->destroyParticleSystem("blast" + convertInt(ID));

		if(type == BULLET_NORMAL)
		{
			mSceneManager->destroyEntity(appropriateName(ENTITY));
			mSceneManager->destroySceneNode(appropriateName(SCENE_NODE));
		}else if(type == LIGHT_CHAIN)
		{
			mSceneManager->destroyEntity("LightChainScenenode" + convertInt(ID));
			mSceneManager->destroySceneNode("LightChainEntity" + convertInt(ID));
			mSceneManager->destroyParticleSystem("LightChainParticle" + convertInt(ID));
		}
	}
}

