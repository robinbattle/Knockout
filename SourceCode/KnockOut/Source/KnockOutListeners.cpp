#include "KnockOutListeners.h"
#include "KnockOutCamera.h"

namespace KnockOut
{
	KnockOutFrameListener::KnockOutFrameListener()
	{
		ef = EnemyFactory::getSingletonPtr();
		mInputHandler =InputHandler::getSingletonPtr();
		mAIManager = AIManager::getSingletonPtr();
		mKnockOutCamera = KnockOutCamera::getSingletonPtr();
		mWorld = KnockOutWorld::getSingletonPtr();
		pathManager = PathManager::getSingletonPtr();
		playerFactory = PlayerFactory::getSingletonPtr();
		collisionManager = CollisionManager::getSingletonPtr();
		bulletFactory = BulletFactory::getSingletonPtr();
		towerFactory = TowerFactory::getSingletonPtr();
		obstacleFactory = ObstacleFactory::getSingletonPtr();
		wallFactory = WallFactory::getSingletonPtr();
		userGUI = UserGUI::getSingletonPtr();
	}       

	// On every frame, call the appropriate managers
	bool 
	KnockOutFrameListener::frameStarted(const Ogre::FrameEvent &evt)
	{
		bool keepGoing = true;
	
		keepGoing = mInputHandler->Think(evt);


		if(!mInputHandler->pause)
		{
			mAIManager->Think(evt.timeSinceLastFrame);
			//  The only reason we have the Think method of the InputHandler return
			//   a value, is for the escape key to cause our application to end.
			//   Feel free to change this to something that makes more sense to you.
		
			mWorld->Think(evt.timeSinceLastFrame);
			mKnockOutCamera->Think(evt.timeSinceLastFrame);
			ef->update(evt.timeSinceLastFrame);
			pathManager->Think(evt.timeSinceLastFrame);
			playerFactory->update(evt.timeSinceLastFrame);
			collisionManager->update(evt.timeSinceLastFrame);
			bulletFactory->update(evt.timeSinceLastFrame);
			towerFactory->update(evt.timeSinceLastFrame);
			obstacleFactory->update(evt.timeSinceLastFrame);
			wallFactory->update(evt.timeSinceLastFrame);
			userGUI->update(evt.timeSinceLastFrame);
		}
		    
		
	
		return keepGoing;
	}

	
	
}
 