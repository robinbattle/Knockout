#include "OgreCamera.h"
#include "BreakoutCamera.h"
#include "World.h"
#include "Constants.h"



BreakoutCamera::BreakoutCamera(Ogre::Camera *renderCamera, BreakoutWorld *world, OgreBites::SdkCameraMan *cameraMan) :
mRenderCamera(renderCamera), mWorld(world), mCameraMan(cameraMan)
{
    // Any other initialization that needs to happen
	
}


void
BreakoutCamera::Think(float time)
{
    // Any code needed here to move the camera about per frame
    //  (use mRenderCamera to get the actual render camera, of course!)

	
}

