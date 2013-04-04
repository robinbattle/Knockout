#include "BulletFactory.h"


namespace KnockOut
{
	//InputHandler *ih = InputHandler::getSingletonPtr();

	BulletFactory::BulletFactory()
	{
		mSceneManager = Ogre::Root::getSingletonPtr()->getSceneManager("KnockOutSMInstance");
		IDCounter = 0;
		debug = DebugOverlay::getSingletonPtr();
		
	}


	Bullet* BulletFactory::generate(Vector3 position, Quaternion orientation, BULLET_TYPE type)
	{
		
		
		
		Bullet *base;
		if(type == BULLET_NORMAL)
		{
			base = new Bullet(IDCounter, position, orientation, type);
			base->setUp();
		}else if(type == LIGHT_CHAIN)
		{
			base = new LightChain(IDCounter, position, orientation, type);
			base->setUp();
		}


		
		//debug->setText("entity: " + entity->getName() + ", Node: " + sceneNode->getName() );
		//ObstacleList.push_back(base);

		//BulletIterator itr = bulletList.insert(bulletList.end(), base);
		bulletList.push_back(base);


		IDCounter++;

		
	
		return  base;
	}

	void BulletFactory::cleanUp(){

		for (BulletIterator ei = bulletList.begin(); ei != bulletList.end(); ){
			Bullet *b = *ei;
			//bulletList.remove(b);
			bullet->die = true;
			ei++;
		}

	}


	void BulletFactory::update(float time)
	{
		
		

		for (BulletIterator ei = bulletList.begin(); ei != bulletList.end(); ){
			bullet = *ei;
			bullet->update(time);
			ei++;
			
			if(bullet->die == true)
			{
				
				bulletList.remove(bullet);
				delete bullet;
				bullet = 0;
			}

		}
	}

	bool BulletFactory::destroy(const std::string &name)
	{
		return true;
	}
	

}