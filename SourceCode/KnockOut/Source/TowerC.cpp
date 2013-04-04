#include "towerC.h"



namespace KnockOut
{

	towerC::~towerC()
	{
		destroy();
	
	}


	void towerC::setUp()
	{
		
		entity = mSceneManager->createEntity("TowerFrostEntity" + convertInt(ID), "Dryad.mesh");
		entity->setQueryFlags(TOWER_FROST_MASK);
		sceneNode = mSceneManager->getRootSceneNode()->createChildSceneNode("TowerFrostScenenode" + convertInt(ID));
		sceneNode->attachObject(entity);
		sceneNode->scale(0.1,0.1,0.1);

		bulletFactory = BulletFactory::getSingletonPtr();
		enemyFactory = EnemyFactory::getSingletonPtr();
		
		die = false;
		range = 150;
		debug = DebugOverlay::getSingletonPtr();
		
        ps = mSceneManager->createParticleSystem("towerCBlast" + convertInt(ID), "Examples/Snow");
		sceneNode->attachObject(ps);
		ps->setVisible(false);
		
	}

	
	std::string towerC::appropriateName(NAME_TYPE type)
	{
		if(type == SCENE_NODE)
			return "TowerChainSceneNode" + convertInt(ID);
		else if(type == ENTITY)
			return "TowerChainEntity" + convertInt(ID);
		
		return NULL;
	}



	void towerC::update(float time)
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
				enemy->lifeValue -= 4 * time;
				enemy->frostCoefficient = 0.3f;
				enemy->frostLastingTime = 4.0f;
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


	void towerC::destroy()
	{
		mSceneManager->destroyEntity("TowerChainEntity" + convertInt(ID));
		mSceneManager->destroySceneNode("TowerChainScenenode" + convertInt(ID));
		mSceneManager->destroyParticleSystem("towerCBlast" + convertInt(ID));
		
	}
}

