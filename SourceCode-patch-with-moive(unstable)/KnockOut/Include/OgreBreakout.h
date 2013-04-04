#ifndef __OgreBreakout_h_
#define __OgreBreakout_h_

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
//#include "../res/resource.h"
#endif

// Including header files within header files is frowned upon,
// but this one is requried for Ogre Strings.
#include "OgrePrerequisites.h"
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>
#include <SdkTrays.h>
#include <SdkCameraMan.h>
namespace Ogre {
    class Root;
    class RenderWindow;
    class Camera;
    class SceneManager;
}

class AIManager;
class InputHandler;
class BreakoutWorld;
class BreakoutFrameListener;
class BreakoutCamera;
class BreakoutFrameListener;

class OgreBreakout
{
public:
    OgreBreakout();
    ~OgreBreakout();

    // Do all the application setup
    bool setup(void);

    // Start runn
    void go(void);
	
protected:

    ///////////////////////////////////////////////////
    /// The following methods are all called by the public
    ///   setup method, to handle various initialization tasks
    //////////////////////////////////////////////////

    //  Load all the requrired resources (Mostly reading the file paths
    //  of various resources from the .cfg files)
    void setupResources(void);

    // Invoke the startup window for all of the Ogre settings (resolution, etc)
    bool configure(void);

    // Create all of the required classes and do setup for all non-rendering tasks
    void createScene(void);

    // Free up all memory & resources created in createScene
    void destroyScene(void);

    // Create the rendering camera (separate from the game camera -- the game camera
    //   contains the logic of how the camera should be moved, the rendering camera
    //   is used by the rendering system to render the scene.  So, the game camera 
    //   decides where the camera should be, and then makes calls to the rendering camera
    //   to move the camera
	void createCamera(void);

	void createViewports(void);

    // The FrameListener is what receives callbacks from the rendering loop to handle 
    //  game logic
	void createFrameListener(void);


	BreakoutFrameListener *mBreakoutFrameListener;

	AIManager *mAIManager;
	InputHandler *mInputHandler;
	BreakoutWorld *mWorld;
    BreakoutCamera *mBreakoutCamera;
	Ogre::RenderWindow* mWindow;
    Ogre::Root *mRoot;
    Ogre::Camera* mCamera;
    Ogre::SceneManager* mSceneMgr;
    BreakoutFrameListener* mFrameListener;
    
    Ogre::String mResourcePath;

	OgreBites::SdkCameraMan* mCameraMan;

};



#endif // #ifndef __OgreBreakout_h_