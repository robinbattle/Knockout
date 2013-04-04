#include "TowerA.h"



namespace KnockOut
{

	TowerA::~TowerA()
	{
		destroy();
	
	}


	void TowerA::setUp()
	{
		
		entity = mSceneManager->createEntity("TowerFireEntity" + convertInt(ID), "tower2.mesh");
		entity->setQueryFlags(TOWER_FIRE_MASK);
		sceneNode = mSceneManager->getRootSceneNode()->createChildSceneNode("TowerFireScenenode" + convertInt(ID));
		sceneNode->attachObject(entity);
		sceneNode->scale(3,3,3);

		bulletFactory = BulletFactory::getSingletonPtr();
		enemyFactory = EnemyFactory::getSingletonPtr();
		
		die = false;
		range = 500;
		debug = DebugOverlay::getSingletonPtr();
		
        ps = mSceneManager->createParticleSystem("TowerABlast" + convertInt(ID), "TRPlayer/Torch");
		sceneNode->attachObject(ps);
		ps->setVisible(false);
		
	}

	
	std::string TowerA::appropriateName(NAME_TYPE type)
	{
		if(type == SCENE_NODE)
			return "TowerFireScenenode" + convertInt(ID);
		else if(type == ENTITY)
			return "TowerFireEntity" + convertInt(ID);
		
		return NULL;
	}



	void TowerA::update(float time)
	{
		if(die)
			return;
		bool atLeastOneInRange = false;
		for (EnemyFactory::EnemyIterator e = enemyFactory->enemyList.begin(); e != enemyFactory->enemyList.end(); e++ ){
			enemy = *e;
			if(enemy->nearlyDie)
				continue;   
			 

			if(ifInRange(enemy->getSceneNode()->getPosition(), sceneNode->getPosition(), range))
			{
				atLeastOneInRange = true;
				enemy->lifeValue -= 8 * time;
				enemy->fireLastingTime = 1.0f;
				if(enemy->lifeValue <= 0)
					enemy->nearlyDie = true;
				//break;
			}

		}
		if(atLeastOneInRange)
			ps->setVisible(true);
		else
			ps->setVisible(false);
	}


	void TowerA::destroy()
	{
		mSceneManager->destroyEntity("TowerFireEntity" + convertInt(ID));
		mSceneManager->destroySceneNode("TowerFireScenenode" + convertInt(ID));
		mSceneManager->destroyParticleSystem("TowerABlast" + convertInt(ID));
		
	}
}

