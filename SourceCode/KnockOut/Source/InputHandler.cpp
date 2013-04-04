#include "InputHandler.h"
#include "AIManager.h"
#include "BulletFactory.h"
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


namespace KnockOut
{
	using namespace Ogre;

	OverlayManager *olmGUIBG;
	OverlayContainer *panelGUIBG ;
	OverlayContainer *panelGUIMV ;
	Overlay *overlayGUIBG;

	InputHandler::InputHandler()
	{

		debug = DebugOverlay::getSingletonPtr();

		mKnockOutCamera = KnockOutCamera::getSingletonPtr();
		mSceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager("KnockOutSMInstance");
		mRenderWindow = Ogre::Root::getSingletonPtr()->getAutoCreatedWindow();
		objectPlacement = ObjectPlacement::getSingletonPtr();
		enemyFactory = EnemyFactory::getSingletonPtr();
		mWorld = KnockOutWorld::getSingletonPtr();
		playerFactory = PlayerFactory::getSingletonPtr();
		userGUI = UserGUI::getSingletonPtr();
		mRayScnQuery = mSceneMgr->createRayQuery(Ogre::Ray());	

		OIS::ParamList pl;
		size_t windowHnd = 0;
		std::ostringstream windowHndStr;
		Ogre::Root::getSingletonPtr()->getAutoCreatedWindow()->getCustomAttribute("WINDOW", &windowHnd);
		windowHndStr << windowHnd;
		pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

		mInputManager = OIS::InputManager::createInputSystem( pl );

		mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true /* buffered */ ));
		mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true /* buffered */ ));

		CEGUISetUP();
		setupMenuGUI();
		bLMouseDown = false;
		bRMouseDown = false;

		mRotateSpeed = 0.1f;
		mCount = 0;
		mCurrentObject = 0;

		jUpLastFrame = true;
		rUpLastFrame = true;
		mSpaceDown = true;
		ESCDown = true;
		pause = true;
		mShutDown = false;
		placeMode = true;
		ifStart = false;
		ifNewGame = false;

		mWindow = Ogre::Root::getSingletonPtr()->getAutoCreatedWindow();
		//mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", mWindow, mMouse, this);

		pathManager = PathManager::getSingletonPtr();
		setupMenuBackGround();
		//setUpMoive();
		freeLookMode = true;
		CurrentLevel = 1;

		skipMoive = true;

		ifESCHold = false;
		//new_game->setVisible(false);
		//free_look->setVisible(false);
		//control_menu->setVisible(false);
		//quit->setVisible(false);
	}

	void InputHandler::setUpMoive()
	{
		dshowMovieTextureSystem = new OgreUtils::DirectShowMovieTexture(mWindow->getWidth(), mWindow->getHeight());
		Ogre::Vector2 v = dshowMovieTextureSystem->getMovieDimensions();
		char c[100];
		sprintf(c, "w:%d,h:%d", mWindow->getWidth(), mWindow->getHeight());
		debug->setText4(c);

		Ogre::String movieName="Content/new2.avi";
		
		panelGUIMV=static_cast<OverlayContainer*>(olmGUIBG->createOverlayElement("Panel","TextPanelGUIMV"));
		panelGUIMV->setMetricsMode(Ogre::GMM_RELATIVE); // Use relative dimensions for positions, size, etc
		//panelGUI->setPosition(.,.2);                // Panel starts at 20$ to the right, and 20% down from the top
		
		panelGUIMV->setDimensions(1.0f, 1.0f);           // Panel is half the width and half the height of the screen
		panelGUIMV->setMaterialName("myMoive");       // Give the panel a background material.
	
		overlayGUIBG->add2D(panelGUIMV);                   // Add our panel to the overlay


		
		Ogre::String materialName="myMoive";
		if (!Ogre::MaterialManager::getSingleton().resourceExists(materialName))
		{
			  throw("Error, material doesn't exist!");
		}
		Ogre::MaterialPtr mat;
		Ogre::TextureUnitState* tex;
		mat=Ogre::MaterialManager::getSingleton().getByName(materialName);
		tex=mat->getTechnique(0)->getPass(0)->getTextureUnitState(0);
		tex->setTextureName(dshowMovieTextureSystem->getMovieTexture()->getName());
		dshowMovieTextureSystem->loadMovie(movieName);
		dshowMovieTextureSystem->playMovie();
		
		
		//OgreUtils::DirectShowManager::getSingleton().createDirectshowControl("videotest","../../Content/new2.mpg",mWindow->getWidth(),mWindow->getHeight());
		//Ogre::Root::getSingletonPtr()->addFrameListener(new OgreUtils::DirectShowManager(vp));
	}


	bool InputHandler::ifAllReleased()
	{
		for(int i = 0; i < 5; i++)
		{
			if(keyDown[i] == true) //not released yet
				return false;
		
		}
		return true;
	
	}
	
	bool 
	InputHandler::Think(const Ogre::FrameEvent &evt)
	{
	
		if(mRenderWindow->isClosed())
		{
			mShutDown = true;
			return true;
		}

		//dshowMovieTextureSystem->updateMovieTexture();
		// Capture input for this frame
		mKeyboard->capture();
		mMouse->capture();

		mMouse->setEventCallback(this);
		mKeyboard->setEventCallback(this);

		

		
		if(!mKeyboard->isKeyDown(OIS::KC_SPACE))
		{
			mSpaceDown = true;
		}


		if(!mKeyboard->isKeyDown(OIS::KC_ESCAPE))
			ESCDown = true;

		if(mKeyboard->isKeyDown(OIS::KC_6))
			mWorld->cleanUpAll();
		// Process input
		if(mKeyboard->isKeyDown(OIS::KC_ESCAPE) && ESCDown){
			ESCDown = false;
			//pause = !pause;
			if(!skipMoive)
			{
				skipMoive = true;
				dshowMovieTextureSystem->stopMovie();
				showMenu();
				panelGUIMV->hide();
			}


			if(ifStart)
			{
				if(!pause)
				{
					showMenu();
				}
				else
				{
					hideMenu();
				}
			
			}
		}
		
		
		
		if(!freeLookMode)
		{
		
			if(playerFactory->myPlayer != NULL)
			{
				if (mKeyboard->isKeyDown(OIS::KC_W)){
					playerFactory->myPlayer->moveForward(evt.timeSinceLastFrame);
				}
				if (mKeyboard->isKeyDown(OIS::KC_S)){
					playerFactory->myPlayer->moveBackward(evt.timeSinceLastFrame);
				}
				if (mKeyboard->isKeyDown(OIS::KC_A)){
					playerFactory->myPlayer->turnLeft(evt.timeSinceLastFrame);
				}
				if (mKeyboard->isKeyDown(OIS::KC_D)){
					playerFactory->myPlayer->turnRight(evt.timeSinceLastFrame);
				}
				if (mKeyboard->isKeyDown(OIS::KC_SPACE) && mSpaceDown){
					playerFactory->myPlayer->highJump();
					mSpaceDown = false;
					//Bullet* b;
					//b = BulletFactory::getSingletonPtr()->generate();
					//b->getSceneNode()->setPosition(playerFactory->myPlayer->getSceneNode()->getPosition());
				}


				if(!freeLookMode)
				{
					if(playerFactory->myPlayer != NULL)
					{
						
						Vector3 src = playerFactory->myPlayer->getSceneNode()->getOrientation() * Ogre::Vector3::UNIT_X * 100;
						src.y = -100;
						mKnockOutCamera->mRenderCamera->setPosition(playerFactory->myPlayer->getSceneNode()->getPosition() - src);

						if(!bRMouseDown)
						{
							src = playerFactory->myPlayer->getSceneNode()->getOrientation() * Ogre::Vector3::UNIT_X * 200;
							mKnockOutCamera->mRenderCamera->lookAt(playerFactory->myPlayer->getSceneNode()->getPosition() + src);
						}

					}
		
				}


			}
		
		
		
		}


		mKnockOutCamera->mCameraMan->frameRenderingQueued(evt);

		if(mShutDown)
			return false;
		return true;

	}

	bool InputHandler::CEGUISetUP()
	{
		//CEGUI setup
		mGUIRenderer = &CEGUI::OgreRenderer::bootstrapSystem();
 
		//show the CEGUI cursor
		CEGUI::SchemeManager::getSingleton().create((CEGUI::utf8*)"TaharezLook.scheme");
		CEGUI::MouseCursor::getSingleton().setImage("TaharezLook", "MouseArrow");


		CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
		CEGUI::Font::setDefaultResourceGroup("Fonts");
		CEGUI::Scheme::setDefaultResourceGroup("Schemes");
		CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
		CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
		CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");
		CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");

		//Button* b = mTrayMgr->createButton(TL_TOPLEFT, "MyButton", "Click Me!");
		//b->_assignListener(this);

		//CEGUI::System::getSingleton().setGUISheet(
		//CEGUI::WindowManager::getSingleton().loadWindowLayout("MyTest.layout"));

		return true;
	}

	bool
	InputHandler::keyPressed(const OIS::KeyEvent& evt){	

		if(pause)
			return true;
		if(playerFactory->myPlayer == NULL && !freeLookMode)
			return true;





		if(freeLookMode)
		{
			mKnockOutCamera->mCameraMan->injectKeyDown(evt);
			
		}
		else
		{//player mode
			if(	evt.key == OIS::KC_W){
				playerFactory->myPlayer->setRun();
				keyDown[0] = true;
			}
				
			if(	evt.key == OIS::KC_S){
				playerFactory->myPlayer->setRun();
				keyDown[1] = true;
			}
			if(	evt.key == OIS::KC_A){
				playerFactory->myPlayer->setRun();
				keyDown[2] = true;
			}
			if(	evt.key == OIS::KC_D){
				playerFactory->myPlayer->setRun();
				keyDown[3] = true;
			}


		
			if(evt.key == OIS::KC_SPACE){
				playerFactory->myPlayer->setHighJump();
				keyDown[4] = true;
			}

	
		}


		if(evt.key == OIS::KC_1){
				objectPlacement->currentType = TOWER_BULLET_MASK;
				userGUI->tower1->setDimensions(0.10f, 0.10f);
				userGUI->tower2->setDimensions(0.08f, 0.08f);
				userGUI->tower3->setDimensions(0.08f, 0.08f);
				userGUI->tower4->setDimensions(0.08f, 0.08f);
			}
			else if(evt.key == OIS::KC_2)
			{
				objectPlacement->currentType = TOWER_FIRE_MASK;
				userGUI->tower1->setDimensions(0.08f, 0.08f);
				userGUI->tower2->setDimensions(0.10f, 0.10f);
				userGUI->tower3->setDimensions(0.08f, 0.08f);
				userGUI->tower4->setDimensions(0.08f, 0.08f);
			}else if(evt.key == OIS::KC_3)
			{
				objectPlacement->currentType = TOWER_FROST_MASK;
				userGUI->tower1->setDimensions(0.08f, 0.08f);
				userGUI->tower2->setDimensions(0.08f, 0.08f);
				userGUI->tower3->setDimensions(0.10f, 0.10f);
				userGUI->tower4->setDimensions(0.08f, 0.08f);
			}else if(evt.key == OIS::KC_4)
			{
				objectPlacement->currentType = CATCHUP_MASK;
				userGUI->tower1->setDimensions(0.08f, 0.08f);
				userGUI->tower2->setDimensions(0.08f, 0.08f);
				userGUI->tower3->setDimensions(0.08f, 0.08f);
				userGUI->tower4->setDimensions(0.10f, 0.10f);
			}


		if (evt.key != OIS::KC_J)
		{
			jUpLastFrame = true;
		}
		if (evt.key != OIS::KC_R)
			rUpLastFrame = true;

		if(evt.key == OIS::KC_R && rUpLastFrame)
		{
			AIManager::getSingletonPtr()->playerRelease = true;
			rUpLastFrame = false;
		}else if(evt.key == OIS::KC_J && jUpLastFrame)
		{
			jUpLastFrame = false;
			enemyFactory->hit = !enemyFactory->hit;
		}else if(evt.key == OIS::KC_F)
			pathManager->showPath();
		


		return true;
	}
	bool
	InputHandler::keyReleased(const OIS::KeyEvent& evt){ 

		if(pause)
			return true;

		if(playerFactory->myPlayer == NULL && !freeLookMode)
			return true;

		if(freeLookMode)
			mKnockOutCamera->mCameraMan->injectKeyUp(evt);
		else
		{
			if(	evt.key == OIS::KC_W){
				keyDown[0] = false;
			}
				
			if(	evt.key == OIS::KC_S){
				keyDown[1] = false;
			}
			if(	evt.key == OIS::KC_A){
				keyDown[2] = false;
			}
			if(	evt.key == OIS::KC_D){
				keyDown[3] = false;
			}if( evt.key == OIS::KC_SPACE){
				keyDown[4] = false;
			}



			if(ifAllReleased())
				playerFactory->myPlayer->setIdle();
		
		}
		return true;
	}
	bool 
	InputHandler::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
	{
		//inject key to CEGUI
		CEGUI::System::getSingleton().injectMouseButtonDown(convertButton(id));

		if(pause)
			return true;


		/* normal mouse processing here... */
		mKnockOutCamera->mCameraMan->injectMouseDown(evt, id);



		



		if(id == OIS::MB_Left)
		{
			//show that the current object has been deselected by removing the bounding box visual
			
			//add press

			if(placeMode)
				objectPlacement->ObjectPlaceOnMousePressed();	

			bLMouseDown = true;
		}
		else if(id == OIS::MB_Right)	// if the right mouse button is held we hide the mouse cursor for view mode
		{
			CEGUI::MouseCursor::getSingleton().hide();
			bRMouseDown = true;
		}


		//now we show the bounding box so the user can see that this object is selected
		if(mCurrentObject)
		{
				mCurrentObject->showBoundingBox(true);
		}




		return true;
	}
 
	
	bool 
	InputHandler::mouseMoved(const OIS::MouseEvent& evt)
	{
		
		//updates CEGUI with mouse movement
		CEGUI::System::getSingleton().injectMouseMove(evt.state.X.rel, evt.state.Y.rel);

		if(pause)
			return true;
		
		/* normal mouse processing here... */
		//mKnockOutCamera->mCameraMan->injectMouseMove(evt);
		
		
 
		//if the left mouse button is held down
		if(bLMouseDown)
		{
			//add move
			if(placeMode)
				objectPlacement->ObjectPlaceOnMouseMoved();	
		}
		else if(bRMouseDown)	//if the right mouse button is held down, be rotate the camera with the mouse
		{
			mKnockOutCamera->mRenderCamera->yaw(Ogre::Degree(-evt.state.X.rel * mRotateSpeed));
			mKnockOutCamera->mRenderCamera->pitch(Ogre::Degree(-evt.state.Y.rel * mRotateSpeed));
		}



		return true;
	}


	bool 
	InputHandler::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
	{

		//inject key to CEGUI
		CEGUI::System::getSingleton().injectMouseButtonUp(convertButton(id));



		if(id  == OIS::MB_Left)
		{
			bLMouseDown = false;
		}
		else if(id == OIS::MB_Right)	//when the right mouse is released we then unhide the cursor
		{
			CEGUI::MouseCursor::getSingleton().show();
			bRMouseDown = false;
		}


		//if(pause)
		//	return true;

		/* normal mouse processing here... */
		mKnockOutCamera->mCameraMan->injectMouseUp(evt, id);


		
	

		

		if(placeMode)
			objectPlacement->ObjectPlaceOnMouseReleased();


		return true;
	}
 


	void InputHandler::setupMenuGUI(){

		CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
		sheet = wmgr.createWindow("DefaultWindow", "KnockOutMenu");

		/* new game button  */
		new_game = wmgr.createWindow("TaharezLook/Button", "newgame");
		new_game->setText("New Game");
		new_game->setSize(CEGUI::UVector2(CEGUI::UDim(0.4f, 0), CEGUI::UDim(0.1f, 0)));
		new_game->setPosition(CEGUI::UVector2(CEGUI::UDim(0.3f, 0),CEGUI::UDim(0.2f, 0)));
		sheet->addChildWindow(new_game);
		new_game->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&InputHandler::newGame, this));

		/* free look button  */
		free_look = wmgr.createWindow("TaharezLook/Button", "freelook");
		free_look->setText("Free Look");
		free_look->setSize(CEGUI::UVector2(CEGUI::UDim(0.4f, 0), CEGUI::UDim(0.1f, 0)));
		free_look->setPosition(CEGUI::UVector2(CEGUI::UDim(0.3f, 0),CEGUI::UDim(0.4f, 0)));
		sheet->addChildWindow(free_look);
		free_look->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&InputHandler::freeLook, this));

		/* placed mode  button  */
		control_menu = wmgr.createWindow("TaharezLook/Button", "controll menu");
		control_menu->setText("Control");
		control_menu->setSize(CEGUI::UVector2(CEGUI::UDim(0.4f, 0), CEGUI::UDim(0.1f, 0)));
		control_menu->setPosition(CEGUI::UVector2(CEGUI::UDim(0.3f, 0),CEGUI::UDim(0.6f, 0)));
		sheet->addChildWindow(control_menu);
		control_menu->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&InputHandler::controlMenu, this));
	
		/* quit game button  */
		quit = wmgr.createWindow("TaharezLook/Button", "quit");
		quit->setText("Quit");
		quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.4f, 0), CEGUI::UDim(0.1f, 0)));
		quit->setPosition(CEGUI::UVector2(CEGUI::UDim(0.3f, 0),CEGUI::UDim(0.8f, 0)));
		sheet->addChildWindow(quit);
		quit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&InputHandler::quitGame, this));

		/* back button  */
		back = wmgr.createWindow("TaharezLook/Button", "back");
		back->setText("<<< back to Menu");
		back->setSize(CEGUI::UVector2(CEGUI::UDim(0.2f, 0), CEGUI::UDim(0.1f, 0)));
		back->setPosition(CEGUI::UVector2(CEGUI::UDim(0.7f, 0),CEGUI::UDim(0.7f, 0)));
		sheet->addChildWindow(back);
		back->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&InputHandler::backToMenu, this));

		/* next level button  */
		next_level = wmgr.createWindow("TaharezLook/Button", "next level");
		next_level->setText("Next Level >>>");
		next_level->setSize(CEGUI::UVector2(CEGUI::UDim(0.2f, 0), CEGUI::UDim(0.1f, 0)));
		next_level->setPosition(CEGUI::UVector2(CEGUI::UDim(0.4f, 0),CEGUI::UDim(0.5f, 0)));
		sheet->addChildWindow(next_level);
		next_level->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&InputHandler::nextLevel, this));

		
		CEGUI::System::getSingleton().setGUISheet(sheet);
		next_level->hide();
		back->setVisible(false);
		miniMap();
	}


	bool InputHandler::newGame(const CEGUI::EventArgs &e)
	{
		
		hideMenu();
		ifStart = true;
		
		if(!ifNewGame){
			mWorld->SetupDefaultGame();
			ifNewGame = true;
		}else{
			mWorld->cleanUpAll();
			mWorld->newGame();
			new_game->setText("You have one");
		}
		
		return true;
	}

	bool InputHandler::freeLook(const CEGUI::EventArgs &e)
	{	
		if(!ifStart){
			free_look->setText("Start a new Game first");
			return true;
		}
		
		hideMenu();
		
		freeLookMode = !freeLookMode;

		updatePlaceModeText();

		return true;
	}

	void InputHandler::updatePlaceModeText()
	{
		if(freeLookMode)
			free_look->setText("Free Look Mode (on)");
		else
			free_look->setText("Free Look Mode (off)");
	}


	bool InputHandler::controlMenu(const CEGUI::EventArgs &e)
	{
		ifESCHold = true;
		userGUI->controlPic->show();
		new_game->setVisible(false);
		free_look->setVisible(false);
		control_menu->setVisible(false);
		quit->setVisible(false);
		back->setVisible(true);
		return true;
	}

	bool InputHandler::quitGame(const CEGUI::EventArgs &e)
	{	
		mShutDown = true;
		return true;
	}


	bool InputHandler::backToMenu(const CEGUI::EventArgs &e)
	{	
		ifESCHold = false;
		userGUI->controlPic->hide();

		new_game->setVisible(true);
		free_look->setVisible(true);
		control_menu->setVisible(true);
		quit->setVisible(true);
		back->setVisible(false);

		return true;
	}

	bool InputHandler::nextLevel(const CEGUI::EventArgs &e)
	{
		CurrentLevel++;
		mWorld->nextLevelClick = true;
		next_level->hide();
		return true;
	}

	void InputHandler::showMenu(){
		pause = true;
		new_game->setVisible(true);
		free_look->setVisible(true);
		control_menu->setVisible(true);
		quit->setVisible(true);
		overlayGUIBG->show();

		userGUI->hide();
		mini_map->setVisible(false);

		updatePlaceModeText();

	}
	void InputHandler::hideMenu(){
		pause = false;
		new_game->setVisible(false);
		free_look->setVisible(false);
		control_menu->setVisible(false);
		quit->setVisible(false);
		overlayGUIBG->hide();
		
		userGUI->show();
		mini_map->setVisible(true);
		next_level->hide();

		updatePlaceModeText();
	}

	void InputHandler::setupMenuBackGround(){
		olmGUIBG=OverlayManager::getSingletonPtr();
		overlayGUIBG=olmGUIBG->create("GUIOverlayBG");  // We can call this anything we like, 
		// Next, we create a panel within this overlay:
		panelGUIBG=static_cast<OverlayContainer*>(olmGUIBG->createOverlayElement("Panel","TextPanelGUIBG"));
		panelGUIBG->setMetricsMode(Ogre::GMM_RELATIVE); // Use relative dimensions for positions, size, etc
		//panelGUI->setPosition(.,.2);                // Panel starts at 20$ to the right, and 20% down from the top

		panelGUIBG->setDimensions(1.0, 1.0);           // Panel is half the width and half the height of the screen
		panelGUIBG->setMaterialName("background");       // Give the panel a background material.
	
		overlayGUIBG->add2D(panelGUIBG);                   // Add our panel to the overlay

		// Show the overlay
		overlayGUIBG->show();
		
	
	}


	void InputHandler::miniMap(){
		Ogre::TexturePtr tex = Ogre::Root::getSingletonPtr()->getTextureManager()->createManual(
			"RTT",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			Ogre::TEX_TYPE_2D,
			512,
			512,
			0,
			Ogre::PF_R8G8B8,
			Ogre::TU_RENDERTARGET);

		Ogre::RenderTexture *rtex = tex->getBuffer()->getRenderTarget();
		Ogre::Camera *cam = mSceneMgr->createCamera("MiniCam");
		//Vector3 fool = Ogre::Vector3(1550,0,1250);
		cam->setPosition(0, 300, 0);
		cam->lookAt(750,50,750);
		
		Ogre::Viewport *v = rtex->addViewport(cam);
		v->setOverlaysEnabled(false);
		v->setClearEveryFrame(true);
		v->setBackgroundColour(Ogre::ColourValue::Black);
		CEGUI::Texture &guiTex = mGUIRenderer->createTexture(tex);
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


}


