
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>
#include <SdkTrays.h>
#include <SdkCameraMan.h>

namespace Ogre
{
    class Camera;
    class Vector3;
}

class BreakoutWorld;


class BreakoutCamera
{



public:
	BreakoutCamera(Ogre::Camera *renderCamera, BreakoutWorld *world, OgreBites::SdkCameraMan *camera); 
    void Think(float time);
    // If you have a different cameras, you'll want some acessor methods here.
    //  If your camera always stays still, you could remove this class entirely
	OgreBites::SdkCameraMan* mCameraMan;



protected:

    Ogre::Camera *mRenderCamera;
    BreakoutWorld *mWorld;
	
};