
#include "BaseTower.h"



namespace KnockOut
{

	BaseTower::~BaseTower()
	{
		destroy();
		
	}


	void BaseTower::setUp()
	{
		
		entity = mSceneManager->createEntity(appropriateName(ENTITY), "Tower1.mesh");
		entity->setQueryFlags(TOWER_BULLET_MASK);
		sceneNode = mSceneManager->getRootSceneNode()->createChildSceneNode(appropriateName(SCENE_NODE));
		sceneNode->attachObject(entity);
		sceneNode->scale(1,1,1);

		bulletFactory = BulletFactory::getSingletonPtr();
		enemyFactory = EnemyFactory::getSingletonPtr();
		
		die = false;
		fireCD = 2.0f;
		range = 550;
		debug = DebugOverlay::getSingletonPtr();
        //ps = mSceneManager->createParticleSystem(appropriateName(PARTICLE), "TRPlayer/Torch");
		//sceneNode->attachObject(ps);
		//ps->setVisible(false);
	}

	
	std::string BaseTower::appropriateName(NAME_TYPE type)
	{
		if(type == SCENE_NODE)
			return "TowerScenenode" + convertInt(ID);
		else if(type == ENTITY)
			return "TowerEntity" + convertInt(ID);
		else if(type == PARTICLE)
			return "TowerParticle" + convertInt(ID);
		
		return NULL;
	}



	void BaseTower::update(float time)
	{
		if(die)
			return;

		fireCD -= time;

		if(fireCD < 0 && !enemyFactory->enemyList.empty())
		{
			/*
			if(enemyFactory->enemyList.size() == 1)
			{
				Enemy *e= *enemyFactory->enemyList.begin();
				if(e->nearlyDie)
					return;
			}
			*/

			enemy = *enemyFactory->enemyList.begin();


			if(!ifInRange(enemy->getSceneNode()->getPosition(),sceneNode->getPosition(), range))
			{
				return;
			}

			fireCD = 2.0f;
			Ogre::Vector3 src = sceneNode->getOrientation() * Ogre::Vector3::UNIT_X;
			src.y = 0;

			Ogre::Vector3 direction = enemy->getSceneNode()->getPosition() - sceneNode->getPosition();
			direction.y = 0;
			Ogre::Quaternion quat = src.getRotationTo(direction); //direction
			sceneNode->rotate(quat);
			//sceneNode->yaw(Ogre::Degree(90));	

			Bullet *b = bulletFactory->generate(sceneNode->getPosition(), sceneNode->getOrientation(), BULLET_NORMAL);
			Vector3 v = b->getSceneNode()->getPosition();
			v.y = 160;
			b->getSceneNode()->setPosition(v);

			

		}
		
	}


	bool BaseTower::ifInRange(Vector3 p, Vector3 q, Real range){
		Vector3 distance = p - q;
		
		if(distance.x * distance.x + distance.y * distance.y + distance.z * distance.z < range * range)
			return true;
		else 
			return false; 
	}

	void BaseTower::destroy()
	{
		if(type == 1)
		{
			mSceneManager->destroyEntity(appropriateName(ENTITY));
			mSceneManager->destroySceneNode(appropriateName(SCENE_NODE));
			mSceneManager->destroyParticleSystem(appropriateName(PARTICLE));
		}else if (type == 2){
		
			mSceneManager->destroyEntity("TowerFireEntity" + convertInt(ID));
			mSceneManager->destroySceneNode("TowerFireScenenode" + convertInt(ID));
			mSceneManager->destroyParticleSystem("TowerABlast" + convertInt(ID));
		
		}else if (type == 3){
		
			mSceneManager->destroyEntity("TowerFrostEntity" + convertInt(ID));
			mSceneManager->destroySceneNode("TowerFrostScenenode" + convertInt(ID));
			mSceneManager->destroyParticleSystem("TowerBBlast" + convertInt(ID));
		
		}
	}
}

