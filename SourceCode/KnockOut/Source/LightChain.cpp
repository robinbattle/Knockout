#include "LightChain.h"


namespace KnockOut
{

	LightChain::~LightChain()
	{
		destroy();
	
	}


	void LightChain::setUp()
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
        ps = mSceneManager->createParticleSystem("LightChainParticle" + convertInt(ID), "TRPlayer/Torch");
		sceneNode->attachObject(ps);
		ps->setVisible(true);

		debug = DebugOverlay::getSingletonPtr();
		yes = true;
		rebound = 6;
		currentTarget = 0;

		speed = 3;


		alreadyPickUpTarget = false;

		int i = 0;
		for (EnemyFactory::EnemyIterator ei = enemyFactory->enemyList.begin(); ei != enemyFactory->enemyList.end(); ei++){
			targetList.push_back(*ei);
			i++;
			if(i > 3)
				break;
		}
	}

	
	std::string LightChain::appropriateName(NAME_TYPE type)
	{
		if(type == SCENE_NODE)
			return "LightChainScenenode" + convertInt(ID);
		else if(type == ENTITY)
			return "LightChainEntity" + convertInt(ID);
		
		return NULL;
	}

	

	void LightChain::update(float time)
	{
		    //lifeTime -= time;

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
						if(currentTarget != NULL){
							break;
						}
							
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

	void LightChain::chaseTarget(float time)
	{
		if(currentTarget != NULL)  //make sure
		{
			sceneNode->translate( (currentTarget->getSceneNode()->getPosition() - sceneNode->getPosition()) * time * speed); 
		}
	
	}


	


	void LightChain::destroy()
	{
		mSceneManager->destroyEntity("LightChainScenenode" + convertInt(ID));
		mSceneManager->destroySceneNode("LightChainEntity" + convertInt(ID));
		mSceneManager->destroyParticleSystem("LightChainParticle" + convertInt(ID));
	}
}

