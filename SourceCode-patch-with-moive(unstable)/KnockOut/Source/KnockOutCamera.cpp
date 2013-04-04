#include "OgreCamera.h"
#include "KnockOutCamera.h"
#include "World.h"
#include "Constants.h"
#include "InputHandler.h"
namespace KnockOut
{
	InputHandler *MinputHandler;
	KnockOutCamera::KnockOutCamera()
	{
		// Any other initialization that needs to happen
		Ogre::Root *root = Ogre::Root::getSingletonPtr();
		mSceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager("KnockOutSMInstance");
		//InputHanlder *ih = InputHandler::getSingletonPtr();
		mRenderCamera = mSceneMgr->getCamera("PlayerCam");
		mCameraMan = new OgreBites::SdkCameraMan(mRenderCamera);
		mWorld = KnockOutWorld::getSingletonPtr();
		playerFactory = PlayerFactory::getSingletonPtr();
		MinputHandler = InputHandler::getSingletonPtr();

		
		mRenderCamera->setPosition(0, 800, 0);
		mRenderCamera->lookAt(-650, 0, -650);
	}


	void
	KnockOutCamera::Think(float time)
	{
		// Any code needed here to move the camera about per frame
		//  (use mRenderCamera to get the actual render camera, of course!)
		if(MinputHandler->freeLookMode){
			Vector3 v = mRenderCamera->getPosition();
			if(v.y < 120) v.y = 120;

			if(v.x > 740)
				v.x = 740;
			if(v.x < -740)
				v.x = -740;
			if(v.z > 740)
				v.z = 740;
			if(v.z < -740)
				v.z = -740;

			mRenderCamera->setPosition(v);
		}
		
		
		
	}

}



