#include "WallFactory.h"


namespace KnockOut
{
	//InputHandler *ih = InputHandler::getSingletonPtr();

	WallFactory::WallFactory()
	{
		mSceneManager = Ogre::Root::getSingletonPtr()->getSceneManager("KnockOutSMInstance");
		IDCounter = 0;
		debug = DebugOverlay::getSingletonPtr();
		
	}


	Wall* WallFactory::generate()
	{
		
		
		
		
		Wall *base = new Wall(IDCounter);
		base->setUp();
		//debug->setText("entity: " + entity->getName() + ", Node: " + sceneNode->getName() );
		//ObstacleList.push_back(base);

		WallIterator itr = WallList.insert(WallList.end(), base);
		


		IDCounter++;
	
		return  base;
	}

	void WallFactory::update(float time)
	{
		Wall *w;
		for (WallIterator ei = WallList.begin(); ei != WallList.end(); ){
			w = *ei;
			w->update(time);
			ei++;
			if(w->die == true)
			{
				WallList.remove(w);
				delete w;
				w = 0;
			}
		}
	}

	void WallFactory::cleanUp(){
		Wall *w;
		for (WallIterator ei = WallList.begin(); ei != WallList.end(); ){
			w = *ei;
			
			ei++;
			w->die = true;
		}
	
	}


	bool WallFactory::destroy(const std::string &name)
	{
		return true;
	}
	

}