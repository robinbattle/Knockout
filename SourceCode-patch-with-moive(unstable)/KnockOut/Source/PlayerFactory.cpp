#include "PlayerFactory.h"


namespace KnockOut
{
	//InputHandler *ih = InputHandler::getSingletonPtr();

	PlayerFactory::PlayerFactory()
	{
		mSceneManager = Ogre::Root::getSingletonPtr()->getSceneManager("KnockOutSMInstance");
		IDCounter = 0;
		reBirthWaiting = 3.0f;
		allowRebirth = true;
	}


	Player* PlayerFactory::generate()
	{
		
		
		
		
		myPlayer = new Player(IDCounter);
		myPlayer->setUp();
		//debug->setText("entity: " + entity->getName() + ", Node: " + sceneNode->getName() );
		//enemyList.push_back(base);



		myPlayer->getSceneNode()->scale(1,1,1);

		//p->getSceneNode()->yaw(Ogre::Degree(90));

		//debug->setText("size is " + convertInt(enemyList.size()));

		//debug->setText(get(appropriateName(ENTITY).substr(8))->getName());


		IDCounter++;
	
		return  myPlayer;
	}


	void PlayerFactory::update( float time )
	{

		if(!allowRebirth)
			return;
		
		if(myPlayer != NULL)
		{
			myPlayer->update(time);
			
			if(myPlayer->die)
			{
				delete myPlayer;
				myPlayer = NULL;
			}
		
		}else
		{
			reBirthWaiting -= time;

			if(reBirthWaiting < 0)  //rebirth
			{
				reBirthWaiting = 3.0f;
				generate();
			}
		
		}


		//resetPath();
		//enemyList.clear();
	}

	





	

}