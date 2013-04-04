#include "OgreFrameListener.h"

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>


class InputHandler;
class AIManager;
class BreakoutWorld;
class BreakoutCamera;

class BreakoutFrameListener : public Ogre::FrameListener, public OIS::KeyListener, public OIS::MouseListener,OgreBites::SdkTrayListener
{
public:
    BreakoutFrameListener(InputHandler *inputHandler, AIManager *aiManager, BreakoutWorld *world, BreakoutCamera *breakoutCam);

    virtual bool frameStarted(const Ogre::FrameEvent &evt);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    // OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

protected:
	InputHandler *mInputHandler;
	AIManager *mAIManager;
	BreakoutWorld *mWorld;
    BreakoutCamera *mBreakoutCamera;


};
