#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>
#include "Common.h"
#include "World.h"
#include "KnockOutCamera.h"
#include "ObjectPlacement.h"
#include "EnemyFactory.h"

#include "KnockOutCamera.h"
#include "OgreRenderWindow.h"
#include "OgreStringConverter.h"
#include <OIS/OIS.h>
#include <stdio.h>
#include "OgreSceneManager.h"

#include<math.h>
#include <CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>

#include "PathManager.h"
#include "PlayerFactory.h"
#include "UserGUI.h"
#include "UtilsOgreDshow.h"

namespace Ogre {
    class RenderWindow;
}

namespace OIS {
    class Keyboard;
	class Mouse;
    class InputManager;
}

namespace KnockOut
{
	using namespace OgreBites;

	


	class InputHandler : public SingletonT<InputHandler>, public Ogre::FrameListener, public OIS::KeyListener, public OIS::MouseListener,OgreBites::SdkTrayListener
	{
		SINGLETON_DEFINE(InputHandler)

	

	public:
		InputHandler();
		bool Think(const Ogre::FrameEvent &evt);
	
		bool pause;
		bool ESCDown;

		CEGUI::Window *next_level;
		int CurrentLevel;

		OIS::Keyboard *mKeyboard;
		OIS::Mouse *mMouse;

		virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt){return true;}
		// OIS::KeyListener
		virtual bool keyPressed( const OIS::KeyEvent &arg );
		virtual bool keyReleased( const OIS::KeyEvent &arg );
		// OIS::MouseListener
		virtual bool mouseMoved( const OIS::MouseEvent &arg );
		virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
		virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

		bool freeLookMode;
		ObjectPlacement *objectPlacement;
	protected:

		Ogre::Vector3 getNewPosition(Ogre::Vector3 origin, Ogre::Vector3 direction, Ogre::Real distance);

		void miniMap();

		KnockOutWorld *mWorld;
		KnockOutCamera *mKnockOutCamera;
		Ogre::RenderWindow *mRenderWindow;
		PlayerFactory *playerFactory;
		OIS::InputManager* mInputManager;

		Ogre::SceneNode *mCurrentObject;	//pointer to our currently selected object
		Ogre::RaySceneQuery* mRayScnQuery;	//pointer to our ray scene query
		CEGUI::OgreRenderer* mGUIRenderer;		//our CEGUI renderer
		
		OgreUtils::DirectShowMovieTexture* dshowMovieTextureSystem;

		bool CEGUISetUP();
	
		bool mSpaceDown;

	
		bool jUpLastFrame;
		bool rUpLastFrame;


		bool bLMouseDown, bRMouseDown;	//true if mouse buttons are held down
		int mCount;						//number of objects created
		float mRotateSpeed;				//the rotation speed for the camera

		bool keyDown[5];

		bool ifAllReleased();

		
		
		Ogre::SceneManager *mSceneMgr; 
		EnemyFactory *enemyFactory;
		PathManager *pathManager;
		UserGUI *userGUI;
		OgreBites::SdkTrayManager *mTrayMgr;
		DebugOverlay * debug;

		CEGUI::Window *sheet;
		CEGUI::Window *new_game;
		CEGUI::Window *free_look;
		CEGUI::Window *control_menu;
		CEGUI::Window *quit;

		CEGUI::Window *back;
		
		CEGUI::Window *mini_map;

		Ogre::RenderWindow* mWindow;



		bool mShutDown;


		bool placeMode;

		bool ifStart;
		bool ifNewGame;
		bool skipMoive;

		void setUpMoive();


		bool newGame(const CEGUI::EventArgs &e);
		bool freeLook(const CEGUI::EventArgs &e);
		bool controlMenu(const CEGUI::EventArgs &e);
		bool quitGame(const CEGUI::EventArgs &e);
		bool backToMenu(const CEGUI::EventArgs &e);
		bool nextLevel(const CEGUI::EventArgs &e);

		void showMenu();
		void hideMenu();
		void setupMenuGUI();
		void setupMenuBackGround();

		void updatePlaceModeText();
	};


}


#endif