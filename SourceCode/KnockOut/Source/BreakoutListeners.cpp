#include "BreakoutListeners.h"
#include "AIManager.h"
#include "InputHandler.h"
#include "World.h"
#include "BreakoutCamera.h"
#include <stdio.h>

BreakoutFrameListener::BreakoutFrameListener(InputHandler *inputHandler, AIManager *aiManager, BreakoutWorld *world, BreakoutCamera *cam) :
	mInputHandler(inputHandler), mAIManager(aiManager), mWorld(world), mBreakoutCamera(cam)
{
	
	
}       

// On every frame, call the appropriate managers
bool 
BreakoutFrameListener::frameStarted(const Ogre::FrameEvent &evt)
{
	
	

	mAIManager->Think(evt.timeSinceLastFrame);
    //  The only reason we have the Think method of the InputHandler return
    //   a value, is for the escape key to cause our application to end.
    //   Feel free to change this to something that makes more sense to you.
	bool keepGoing = mInputHandler->Think(evt.timeSinceLastFrame);
	mWorld->Think(evt.timeSinceLastFrame);
    mBreakoutCamera->Think(evt.timeSinceLastFrame);
	mBreakoutCamera->mCameraMan->frameRenderingQueued(evt);
	return keepGoing;
}

bool
BreakoutFrameListener::frameRenderingQueued(const Ogre::FrameEvent &evt)
{
	mInputHandler->mKeyboard->capture();	
	mInputHandler->mMouse->capture();

	mInputHandler->mMouse->setEventCallback(this);
    mInputHandler->mKeyboard->setEventCallback(this);

	mBreakoutCamera->mCameraMan->frameRenderingQueued(evt);

	

	return true;
}


bool
BreakoutFrameListener::keyPressed(const OIS::KeyEvent& evt){	
	mBreakoutCamera->mCameraMan->injectKeyDown(evt);
	return true;
}
bool
BreakoutFrameListener::keyReleased(const OIS::KeyEvent& evt){ 
	mBreakoutCamera->mCameraMan->injectKeyUp(evt);
	return true;
}
bool 
BreakoutFrameListener::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
    /* normal mouse processing here... */
    mBreakoutCamera->mCameraMan->injectMouseDown(evt, id);
    return true;
}
 
bool 
BreakoutFrameListener::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
    /* normal mouse processing here... */
    mBreakoutCamera->mCameraMan->injectMouseUp(evt, id);
    return true;
}
 
bool 
BreakoutFrameListener::mouseMoved(const OIS::MouseEvent& evt)
{
    /* normal mouse processing here... */
    mBreakoutCamera->mCameraMan->injectMouseMove(evt);
    return true;
}
 