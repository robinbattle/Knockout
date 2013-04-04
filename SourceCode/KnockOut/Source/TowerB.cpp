#include "TowerB.h"



namespace KnockOut
{

	TowerB::~TowerB()
	{
		destroy();
	
	}


	void TowerB::setUp()
	{
		
		entity = mSceneManager->createEntity("TowerFrostEntity" + convertInt(ID), "Dryad.mesh");
		entity->setQueryFlags(TOWER_FROST_MASK);
		sceneNode = mSceneManager->getRootSceneNode()->createChildSceneNode("TowerFrostScenenode" + convertInt(ID));
		sceneNode->attachObject(entity);
		sceneNode->scale(0.1,0.1,0.1);

		bulletFactory = BulletFactory::getSingletonPtr();
		enemyFactory = EnemyFactory::getSingletonPtr();
		
		die = false;
		range = 250;
		debug = DebugOverlay::getSingletonPtr();
		
        ps = mSceneManager->createParticleSystem("TowerBBlast" + convertInt(ID), "Examples/Snow");
		sceneNode->attachObject(ps);
		ps->setVisible(false);
		
	}

	
	std::string TowerB::appropriateName(NAME_TYPE type)
	{
		if(type == SCENE_NODE)
			return "TowerFrostSceneNode" + convertInt(ID);
		else if(type == ENTITY)
			return "TowerFrostEntity" + convertInt(ID);
		
		return NULL;
	}



	void TowerB::update(float time)
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
				enemy->frostLastingTime = 0.2f;
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


	void TowerB::destroy()
	{
		mSceneManager->destroyEntity("TowerFrostEntity" + convertInt(ID));
		mSceneManager->destroySceneNode("TowerFrostScenenode" + convertInt(ID));
		mSceneManager->destroyParticleSystem("TowerBFrost" + convertInt(ID));
		
	}
}

