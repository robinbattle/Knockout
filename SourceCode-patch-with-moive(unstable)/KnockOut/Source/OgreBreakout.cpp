#include "OgreBreakout.h"
#include "World.h"
#include "InputHandler.h"
#include "AIManager.h"
#include "BreakoutListeners.h"
#include "BreakoutCamera.h"
#include "Constants.h"


#include "Ogre.h"
#include "OgreConfigFile.h"

using namespace Ogre;
 


OgreBreakout::OgreBreakout()
{
    mFrameListener = 0;
    mRoot = 0;
    // Provide a nice cross platform solution for locating the configuration files
    // On windows files are searched for in the current working directory, on OS X however 
    // you must provide the full path, the helper function macBundlePath does this for us.
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
    mResourcePath = macBundlePath() + "/Contents/Resources/";
#else 
    mResourcePath = "";
#endif
}

/// Standard destructor
OgreBreakout::~OgreBreakout()
{
    if (mFrameListener)
        delete mFrameListener;
    if (mRoot)
        delete mRoot;
}



void
OgreBreakout::createCamera()
{
	mCamera = mSceneMgr->createCamera("PlayerCam");
	mCamera->setPosition(Vector3(BOARD_WIDTH / 2,BOARD_HEIGHT / 2,100));
	mCamera->lookAt(Vector3(BOARD_WIDTH / 2, BOARD_HEIGHT / 2,0));
	mCamera->setNearClipDistance(10);
	mCamera->setFarClipDistance(5000);

	mCameraMan = new OgreBites::SdkCameraMan(mCamera);
}



// We will create a single frame listener, to handle our main event loop.  While we could
// add as many frame listeners as we want (and let the main rendering loop call them),
// we would not have as much control over the order that the listeners are called --
//  so we will just have one listener and handle everything ourselves.
void 
OgreBreakout::createFrameListener(void)
{
	mBreakoutFrameListener = new BreakoutFrameListener(mInputHandler, mAIManager, mWorld, mBreakoutCamera);
	mRoot->addFrameListener(mBreakoutFrameListener);
	// mFrameListener->showDebugOverlay(true);

}

// We will have a single viewport.  If you wanted splitscreen, or a rear-view mirror, then
// you may want multiple viewports.
void 
OgreBreakout::createViewports(void)
{
	    // Create one viewport, entire window
        Viewport* vp = mWindow->addViewport(mCamera);
        vp->setBackgroundColour(ColourValue(0,0,0));
        // Alter the camera aspect ratio to match the viewport
        mCamera->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));    
}

// Here is where we set up all of the non-rendering stuff (our world, various managers, etc)
void 
OgreBreakout::createScene() 
{
    mWorld = new BreakoutWorld(mSceneMgr, mWindow);
    mAIManager = new AIManager(mWorld);
    mBreakoutCamera = new BreakoutCamera(mCamera, mWorld, mCameraMan);
    mInputHandler = new InputHandler(mWindow, mWorld, mBreakoutCamera);
}

bool 
OgreBreakout::setup(void)
{

    String pluginsPath;

#ifdef _DEBUG
    char* pluginFilename = "plugins_d.cfg";
#else
    char* pluginFilename = "plugins.cfg";
#endif



    // only use plugins.cfg if not static
#ifndef OGRE_STATIC_LIB
    pluginsPath = mResourcePath + pluginFilename;
#endif

    mRoot = new Root(pluginsPath, 
        mResourcePath + "ogre.cfg", mResourcePath + "Ogre.log");

    setupResources();

    bool carryOn = configure();
    if (!carryOn) return false;

    // Create the SceneManager, in this case a generic one
    mSceneMgr = mRoot->createSceneManager(ST_GENERIC, "BreakoutSMInstance");
    createCamera();
    createViewports();

    // Set default mipmap level (NB some APIs ignore this)
    TextureManager::getSingleton().setDefaultNumMipmaps(5);

    ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    createScene();

    // When we start the renderer, it will run forever, making callbacks every
    // frame to the frame listeners.  These listeners are where all of the non-
    // rendering work is done.  
    createFrameListener();

    return true;

}
/** Configures the application - returns false if the user chooses to abandon configuration. */
bool 
OgreBreakout::configure(void)
{
    // Show the configuration dialog and initialise the system
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg
    if(mRoot->showConfigDialog())
    {
        // If returned true, user clicked OK so initialise
        // Here we choose to let the system create a default rendering window by passing 'true'
        mWindow = mRoot->initialise(true);
        return true;
    }
    else
    {
        return false;
    }
}

void
OgreBreakout::setupResources(void)
{
    // Load resource paths from config file
    ConfigFile cf;

#ifdef _DEBUG
    char* resourceFilename = "resources_d.cfg";
    char* pluginFilename = "plugins_d.cfg";
#else
    char* resourceFilename = "resources.cfg";
    char* pluginFilename = "plugins.cfg";
#endif




    cf.load(mResourcePath + resourceFilename);

    // Go through all sections & settings in the file
    ConfigFile::SectionIterator seci = cf.getSectionIterator();

    String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        ConfigFile::SettingsMultiMap *settings = seci.getNext();
        ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
            // OS X does not set the working directory relative to the app,
            // In order to make things portable on OS X we need to provide
            // the loading with it's own bundle path location
            ResourceGroupManager::getSingleton().addResourceLocation(
                String(macBundlePath() + "/" + archName), typeName, secName);
#else
            ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
#endif
        }
    }
}

void
OgreBreakout::destroyScene()
{
    delete mWorld;
    delete mAIManager;
    delete mBreakoutCamera;
    delete mInputHandler;

}

void 
OgreBreakout::go(void)
{
    if (!setup())
        return;

    mRoot->startRendering();

    // clean up
    destroyScene();
}


