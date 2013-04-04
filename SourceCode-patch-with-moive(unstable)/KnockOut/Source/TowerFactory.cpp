#include "TowerFactory.h"
#include "Enemy.h"


namespace KnockOut
{
	//InputHandler *ih = InputHandler::getSingletonPtr();

	TowerFactory::TowerFactory()
	{
		mSceneManager = Ogre::Root::getSingletonPtr()->getSceneManager("KnockOutSMInstance");
		IDCounter = 0;
		debug = DebugOverlay::getSingletonPtr();
		
	}




	BaseTower* TowerFactory::generate(QueryFlags type)
	{
		
		BaseTower *base;
		
		if(type == TOWER_BULLET_MASK)
		{
			base = new BaseTower(IDCounter);
			base->setUp();
			base->type = 1;
		}else if(type == TOWER_FIRE_MASK)
		{
			
			base = new TowerA(IDCounter);
			base->setUp();
			towerAList.push_back(base);
			base->type = 2;
		}else if(type == TOWER_FROST_MASK)
		{
			
			base = new TowerB(IDCounter);
			base->setUp();
			//towerAList.push_back(base);
			base->type = 3;
		}

		
		
		//debug->setText("entity: " + entity->getName() + ", Node: " + sceneNode->getName() );
		//enemyList.push_back(base);

		TowerIterator itr = towerList.insert(towerList.end(), base);
		
		base->getSceneNode()->scale(3,3,3);

		

		IDCounter++;
	
		return  base;
	}

	void TowerFactory::cleanUp(){
		BaseTower *t;
		for (TowerIterator ei = towerList.begin(); ei != towerList.end(); ){
			t = *ei;
			ei++;

			t->die = true;
		}
	
	}
	
	void TowerFactory::update( float time )
	{
		
		
		BaseTower* b;
		std::string name;

		


		for (TowerIterator ei = towerList.begin(); ei != towerList.end(); ){
			b = *ei;
			//name = b->getName();
			//sillyRotation(time, b->getSceneNode());

			b->update(time);
			ei++;
			if(b->die == true)
			{
				towerAList.remove(b);
				towerList.remove(b);
				delete b;
				b = 0;
			}

			
		}


	}

	

	 bool TowerFactory::destroy(const std::string &name){
		return true;
	}


	

}