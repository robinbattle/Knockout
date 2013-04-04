

#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <RendererModules/Ogre/CEGUIOgreRenderer.h>
#include <CEGUI.h>
#include <Ogre.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>

#include "Common.h"
#include "SingletonT.h"
#include "World.h"
#include "InputHandler.h"

namespace KnockOut{

	

	class CEGUIManager: public Ogre::FrameListener, public Ogre::WindowEventListener,  public OIS::KeyListener, public OIS::MouseListener, public SingletonT<CEGUIManager>
	{
		SINGLETON_DEFINE(CEGUIManager)
	public:
		
		CEGUIManager();

		void handleEscKey();

		bool ifPause();

		bool frameRenderingQueued(const Ogre::FrameEvent &evt);

	protected:
		
		bool ifMenu;
		bool pause;
		bool mShutDown;
		
		// OIS::KeyListener
		virtual bool keyPressed( const OIS::KeyEvent &arg );
		virtual bool keyReleased( const OIS::KeyEvent &arg );
		// OIS::MouseListener
		virtual bool mouseMoved( const OIS::MouseEvent &arg );
		virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
		virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

		//OIS Input devices
		OIS::InputManager* mInputManager;
		OIS::Mouse*    mMouse;
		OIS::Keyboard* mKeyboard;

		Ogre::Root *mRoot;
		Ogre::RenderWindow* mWindow;
		Ogre::SceneManager* mSceneMgr;
		InputHandler *mInputHandler;

		bool ESCDown;


		CEGUI::OgreRenderer* mRenderer;
		
		//CEGUI::WindowManager &wmgr;
		CEGUI::Window *sheet;
		
		CEGUI::Window *new_game;
		CEGUI::Window *load_classic;
		CEGUI::Window *battle_editor;
		CEGUI::Window *quit;
		KnockOutWorld *mWorld;
		CEGUI::Window *mini_map;

		//static CEGUI::WindowManager* getWindowManager() { return CEGUI::WindowManager::getSingletonPtr(); }

		bool newGame(const CEGUI::EventArgs &e);
		bool loadClassic(const CEGUI::EventArgs &e);
		bool battleEditor(const CEGUI::EventArgs &e);
		bool quitGame(const CEGUI::EventArgs &e);

		

		void miniMap();
		Ogre::Camera *cam;

		bool ifstart;  /* handled problem that first open the menu and press esc*/

	private:
		void showMenu();
		void hideMenu();
		
		void initGUI();
		void setupVariables();
		void setupMenuGUI();
		void setupMenuBackGround();

		bool ifNewGame;
		bool ifLoadedClassic;

		int level;
		float range;


	};
}

#endif