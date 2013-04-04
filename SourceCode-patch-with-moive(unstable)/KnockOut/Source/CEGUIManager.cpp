#include "CEGUIManager.h"
#include "World.h"



namespace KnockOut
{
	OverlayManager *olmGUI;
	OverlayContainer *panelGUI ;
	Overlay *overlayGUI;
	TextAreaOverlayElement *textAreaGUI;
	String szElementGUI;
	OverlayContainer *panelGUI2 ;
	Overlay *overlayGUI2;
	TextAreaOverlayElement *textAreaGUI2;
			
	OverlayContainer *attackMode;
	OverlayContainer *defenceMode;
	OverlayContainer *tankExp;

	float previouslife;
	char cc[70];

	CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID)
	{
		switch (buttonID)
		{
		case OIS::MB_Left:
			return CEGUI::LeftButton;
 
		case OIS::MB_Right:
			return CEGUI::RightButton;
 
		case OIS::MB_Middle:
			return CEGUI::MiddleButton;
 
		default:
			return CEGUI::LeftButton;
		}
	}


	//-------------------------------------------------------------------------------------
	CEGUIManager::CEGUIManager()
	{
		setupVariables();
		initGUI();
		setupMenuGUI();

		//miniMap();
	
		mWorld = KnockOutWorld::getSingletonPtr();
		mInputHandler = InputHandler::getSingletonPtr();
		mWindow = Ogre::Root::getSingletonPtr()->getAutoCreatedWindow();

		ESCDown = false;
	}

	void CEGUIManager::initGUI(){ 
		mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();
		CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
		CEGUI::Font::setDefaultResourceGroup("Fonts");
		CEGUI::Scheme::setDefaultResourceGroup("Schemes");
		CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
		CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
		CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");
		CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");

		//setupMenuBackGround();

		/*healthy bar  temporary*/                                                    //healthy bar
		
	}

	void CEGUIManager::setupMenuBackGround(){
		olmGUI=OverlayManager::getSingletonPtr();
		overlayGUI=olmGUI->create("GUIOverlay");  // We can call this anything we like, 
		// Next, we create a panel within this overlay:
		panelGUI=static_cast<OverlayContainer*>(olmGUI->createOverlayElement("Panel","TextPanelGUI"));
		panelGUI->setMetricsMode(Ogre::GMM_RELATIVE); // Use relative dimensions for positions, size, etc
		//panelGUI->setPosition(.,.2);                // Panel starts at 20$ to the right, and 20% down from the top

		panelGUI->setDimensions(1.0, 1.0);           // Panel is half the width and half the height of the screen
		panelGUI->setMaterialName("background");       // Give the panel a background material.
		overlayGUI->add2D(panelGUI);                   // Add our panel to the overlay

		// Show the overlay
		overlayGUI->show();
		
	
	}

	void CEGUIManager::setupVariables(){
		mShutDown = false;
		pause = true;	
		ifNewGame = false;
		ifLoadedClassic = false;
		ifstart = false;
	}

	void CEGUIManager::setupMenuGUI(){

		CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
		sheet = wmgr.createWindow("DefaultWindow", "TankWarMenu");

		/* new game button  */
		new_game = wmgr.createWindow("TaharezLook/Button", "newgame");
		new_game->setText("New Game");
		new_game->setSize(CEGUI::UVector2(CEGUI::UDim(0.4, 0), CEGUI::UDim(0.1, 0)));
		new_game->setPosition(CEGUI::UVector2(CEGUI::UDim(0.3f, 0),CEGUI::UDim(0.2f, 0)));
		sheet->addChildWindow(new_game);
		new_game->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIManager::newGame, this));

		/* load classic button  */
		load_classic = wmgr.createWindow("TaharezLook/Button", "load");
		load_classic->setText("Load Classic");
		load_classic->setSize(CEGUI::UVector2(CEGUI::UDim(0.4, 0), CEGUI::UDim(0.1, 0)));
		load_classic->setPosition(CEGUI::UVector2(CEGUI::UDim(0.3f, 0),CEGUI::UDim(0.4f, 0)));
		sheet->addChildWindow(load_classic);
		load_classic->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIManager::loadClassic, this));

		/* battle editor button  */
		battle_editor = wmgr.createWindow("TaharezLook/Button", "editor");
		battle_editor->setText("Battle Editor");
		battle_editor->setSize(CEGUI::UVector2(CEGUI::UDim(0.4, 0), CEGUI::UDim(0.1, 0)));
		battle_editor->setPosition(CEGUI::UVector2(CEGUI::UDim(0.3f, 0),CEGUI::UDim(0.6f, 0)));
		sheet->addChildWindow(battle_editor);
		battle_editor->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIManager::battleEditor, this));
	
		/* quit game button  */
		quit = wmgr.createWindow("TaharezLook/Button", "quit");
		quit->setText("Quit");
		quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.4, 0), CEGUI::UDim(0.1, 0)));
		quit->setPosition(CEGUI::UVector2(CEGUI::UDim(0.3f, 0),CEGUI::UDim(0.8f, 0)));
		sheet->addChildWindow(quit);
		quit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&CEGUIManager::quitGame, this));

		
		
		CEGUI::System::getSingleton().setGUISheet(sheet);
		
	}

	void CEGUIManager::miniMap(){
		Ogre::TexturePtr tex = mRoot->getTextureManager()->createManual(
			"RTT",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			Ogre::TEX_TYPE_2D,
			512,
			512,
			0,
			Ogre::PF_R8G8B8,
			Ogre::TU_RENDERTARGET);

		Ogre::RenderTexture *rtex = tex->getBuffer()->getRenderTarget();
		cam = mSceneMgr->createCamera("RearCam");
		//Vector3 fool = Ogre::Vector3(1550,0,1250);
		cam->setPosition(1250, 300, 1000);
		//cam->lookAt(0,0,0);
		
		Ogre::Viewport *v = rtex->addViewport(cam);
		v->setOverlaysEnabled(false);
		v->setClearEveryFrame(true);
		v->setBackgroundColour(Ogre::ColourValue::Black);
		CEGUI::Texture &guiTex = mRenderer->createTexture(tex);
		CEGUI::Imageset &imageSet =
		CEGUI::ImagesetManager::getSingleton().create("RTTImageset", guiTex);
	imageSet.defineImage("RTTImage",
						 CEGUI::Point(0.0f, 0.0f),
						 CEGUI::Size(guiTex.getSize().d_width,
									 guiTex.getSize().d_height),
						 CEGUI::Point(0.0f, 0.0f));

		mini_map = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage", "RTTWindow");
		mini_map->setSize(CEGUI::UVector2(CEGUI::UDim(0.3f, 0),CEGUI::UDim(0.2f, 0)));
		mini_map->setPosition(CEGUI::UVector2(CEGUI::UDim(0.69f, 0),CEGUI::UDim(0.0f, 0)));
		mini_map->setProperty("Image", CEGUI::PropertyHelper::imageToString(&imageSet.getImage("RTTImage")));
		sheet->addChildWindow(mini_map);
		mini_map->setVisible(false);
	
	}




	void
	CEGUIManager::handleEscKey(){	

		//ESCAPE
		if(!pause)
			showMenu(); //true now
		else{
			if(ifstart)
				hideMenu(); //false now
		}
				

	}

	bool CEGUIManager::ifPause(){
		return pause;
	}
	

	void CEGUIManager::showMenu(){
		overlayGUI->show();
		pause = true;
		new_game->setVisible(true);
		load_classic->setVisible(true);
		battle_editor->setVisible(true);
		quit->setVisible(true);

		mini_map->setVisible(false);
		overlayGUI2->hide();
	}
	void CEGUIManager::hideMenu(){
		overlayGUI->hide();
		pause = false;
		new_game->setVisible(false);
		load_classic->setVisible(false);
		battle_editor->setVisible(false);
		quit->setVisible(false);

		mini_map->setVisible(true);
		overlayGUI2->show();
	}



	
	//-------------------------------------------------------------------------------------


	bool CEGUIManager::newGame(const CEGUI::EventArgs &e)
	{
		hideMenu();
		ifstart = true;
		
		if(!ifNewGame){
			mWorld->SetupDefaultGame();
			ifNewGame = true;
		}else{
			//mWorld->clearAll();
			//mWorld->createTanks();
			
			//player score = 0;
		}
		
		return true;
	}

	bool CEGUIManager::loadClassic(const CEGUI::EventArgs &e)
	{	
		if(ifstart){
			hideMenu();
			ifstart = true;
			if(!ifLoadedClassic){		
				ifLoadedClassic = true;
			}else{
				load_classic->setText("Already loaded");
			}
			
		}
		
		return true;
	}


	bool CEGUIManager::battleEditor(const CEGUI::EventArgs &e)
	{
		//hideMenu();
		battle_editor->setText("Not finished");
		return true;
	}

	bool CEGUIManager::quitGame(const CEGUI::EventArgs &e)
	{	
		mShutDown = true;
		return true;
	}




	bool
	CEGUIManager::keyReleased(const OIS::KeyEvent& evt){ 


		CEGUI::System::getSingleton().injectKeyUp(evt.key);

		return true;
	}

		bool
	CEGUIManager::keyPressed(const OIS::KeyEvent& evt){ 

		CEGUI::System::getSingleton().injectKeyDown(evt.key);

		if(evt.key == OIS::KC_ESCAPE)
			handleEscKey();

		return true;
	}


	bool 
	CEGUIManager::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
	{

		CEGUI::System::getSingleton().injectMouseButtonDown(convertButton(id));

		return true;
	}
 
	bool 
	CEGUIManager::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
	{
		/* normal mouse processing here... */
		//if(mInputHandler->godMode == true){
		//	mTankWarCamera->mCameraMan->injectMouseUp(evt, id);
		//}

		CEGUI::System::getSingleton().injectMouseButtonUp(convertButton(id));

		return true;
	}
 
	bool 
	CEGUIManager::mouseMoved(const OIS::MouseEvent& evt)
	{
		/* normal mouse processing here... */
		//if(mInputHandler->godMode == true){
		//	mTankWarCamera->mCameraMan->injectMouseMove(evt);
		//}


		CEGUI::System &sys = CEGUI::System::getSingleton();
		sys.injectMouseMove(evt.state.X.rel, evt.state.Y.rel);
		// Scroll wheel.
		if (evt.state.Z.rel)
			sys.injectMouseWheelChange(evt.state.Z.rel / 120.0f);

		return true;
	}


	bool
	CEGUIManager::frameRenderingQueued(const Ogre::FrameEvent &evt)
	{
			mInputHandler->mKeyboard->capture();	
			mInputHandler->mMouse->capture();
			mInputHandler->mMouse->setEventCallback(this);
			mInputHandler->mKeyboard->setEventCallback(this);

			if(mShutDown)return false;
			if(mWindow->isClosed())return false;


			if(mInputHandler->mKeyboard->isKeyDown(OIS::KC_ESCAPE))
				ESCDown = true;

			if(ESCDown && mInputHandler->mKeyboard->isKeyDown(OIS::KC_ESCAPE))
			{
				ESCDown = false;
				handleEscKey();
			
			}


			return true;

	}
	

}


