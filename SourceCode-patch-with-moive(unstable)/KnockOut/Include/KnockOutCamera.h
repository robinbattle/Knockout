#pragma once
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>
#include <SdkTrays.h>
#include <SdkCameraMan.h>
#include "Common.h"
#include "World.h"
#include "PlayerFactory.h"
namespace Ogre
{
    class Camera;
    class Vector3;
}


namespace KnockOut
{


	class KnockOutCamera : public SingletonT<KnockOutCamera>
	{

		SINGLETON_DEFINE(KnockOutCamera)

	public:
		KnockOutCamera(); 
		void Think(float time);
		// If you have a different cameras, you'll want some acessor methods here.
		//  If your camera always stays still, you could remove this class entirely
		OgreBites::SdkCameraMan* mCameraMan;

		Ogre::Camera *mRenderCamera;
		Ogre::SceneManager *mSceneMgr; 

	protected:

		Vector3 camPosition;
		KnockOutWorld *mWorld;
		PlayerFactory *playerFactory;
	};

}