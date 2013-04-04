#include "UserGUI.h"



namespace KnockOut
{
	




	//-------------------------------------------------------------------------------------
	UserGUI::UserGUI()
	{
		lose = false;
		mRoot = Ogre::Root::getSingletonPtr();
		mSceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager("KnockOutSMInstance");


		//objectPlacement = ObjectPlacement::getSingletonPtr();
		initGUI();
		//setupMenuGUI();

		//miniMap();
		lifeValue = 700;
		
	}

	void UserGUI::resetHealthBar(Real val){

		if(lose)
			return;


		if(lifeValue - val <= 0)
		{
			lose = true;
			return;
		}else{
			lifeValue -= val;
			panelGUI2->setDimensions(lifeValue/700 * 0.4f, 0.02f);
		
		}
	
	}



	void UserGUI::hide()
	{
		tower1->hide();
		tower2->hide();
		tower3->hide();
		tower4->hide();
		tower1Money->hide();
		tower2Money->hide();
		tower3Money->hide();
		tower4Money->hide();
		money->hide();
		panelGUI2->hide();
		ifShow = false;
		winP->hide();
		loseP->hide();
	}
	void UserGUI::show(){
		tower1->show();
		tower2->show();
		tower3->show();
		tower4->show();
		tower1Money->show();
		tower2Money->show();
		tower3Money->show();
		tower4Money->show();
		money->show();
		panelGUI2->show();
		ifShow = true;
	}

	void UserGUI::HideOrShow(){
		
		if(!ifShow)
			show();
		else
			hide();
			
	}


	void UserGUI::initGUI(){ 
		
		ifShow = false;


		/*healthy bar  temporary*/                                                    //healthy bar
		olmGUI=OverlayManager::getSingletonPtr();
		overlayGUI2=olmGUI->create("GUIOverlay2");
		panelGUI2=static_cast<OverlayContainer*>(olmGUI->createOverlayElement("Panel","Health Bar"));
		panelGUI2->setMetricsMode(Ogre::GMM_RELATIVE);
		panelGUI2->setPosition(0.05f,0.05f);
		panelGUI2->setDimensions(0.4f, 0.02f);           
		panelGUI2->setMaterialName("healthy_bar");       
		overlayGUI2->add2D(panelGUI2);                  
		
		tower1=static_cast<OverlayContainer*>(olmGUI->createOverlayElement("Panel","Tower 1 Mode"));
		tower1->setMetricsMode(Ogre::GMM_RELATIVE);
		tower1->setPosition(0.05f,0.10f);
		tower1->setDimensions(0.08f, 0.08f);
		tower1->setMaterialName("tower1");       
		overlayGUI2->add2D(tower1);

		tower2=static_cast<OverlayContainer*>(olmGUI->createOverlayElement("Panel","Tower 2 Mode"));
		tower2->setMetricsMode(Ogre::GMM_RELATIVE);
		tower2->setPosition(0.15f,0.10f);
		tower2->setDimensions(0.08f, 0.08f);
		tower2->setMaterialName("tower2");       
		overlayGUI2->add2D(tower2);

		tower3=static_cast<OverlayContainer*>(olmGUI->createOverlayElement("Panel","Tower 3 Mode"));
		tower3->setMetricsMode(Ogre::GMM_RELATIVE);
		tower3->setPosition(0.25f,0.10f);
		tower3->setDimensions(0.08f, 0.08f);
		tower3->setMaterialName("tower3");       
		overlayGUI2->add2D(tower3);


		tower4=static_cast<OverlayContainer*>(olmGUI->createOverlayElement("Panel","Tower 4 Mode"));
		tower4->setMetricsMode(Ogre::GMM_RELATIVE);
		tower4->setPosition(0.35f,0.10f);
		tower4->setDimensions(0.08f, 0.08f);
		tower4->setMaterialName("tower4");       
		overlayGUI2->add2D(tower4);


		/*
		tankExp=static_cast<OverlayContainer*>(olmGUI->createOverlayElement("Panel","PlayerTank Exp"));
		tankExp->setMetricsMode(Ogre::GMM_RELATIVE);
		tankExp->setPosition(0.05f,0.10f);
		tankExp->setDimensions(0.005f, 0.02f);
		tankExp->setMaterialName("exp_bar");       
		overlayGUI2->add2D(tankExp);
		*/
		money=static_cast<OverlayContainer*>(olmGUI->createOverlayElement("Panel","Money Counter"));
		money->setMetricsMode(Ogre::GMM_RELATIVE);
		money->setPosition(0.5f,0.10f);
		money->setDimensions(0.08f, 0.08f);
		money->setMaterialName("money_icon");    
		overlayGUI2->add2D(money);
		

		loseP=static_cast<OverlayContainer*>(olmGUI->createOverlayElement("Panel","Game Over"));
		loseP->setMetricsMode(Ogre::GMM_RELATIVE);
		loseP->setPosition(0.2f,0.2f);
		loseP->setDimensions(0.6f, 0.6f);
		loseP->setMaterialName("game_over");    
		overlayGUI2->add2D(loseP);

		winP=static_cast<OverlayContainer*>(olmGUI->createOverlayElement("Panel","Game Win"));
		winP->setMetricsMode(Ogre::GMM_RELATIVE);
		winP->setPosition(0.2f,0.2f);
		winP->setDimensions(0.6f, 0.6f);
		winP->setMaterialName("game_win");    
		overlayGUI2->add2D(winP);


		controlPic=static_cast<OverlayContainer*>(olmGUI->createOverlayElement("Panel","Controll Menu"));
		controlPic->setMetricsMode(Ogre::GMM_RELATIVE);
		controlPic->setPosition(0.2f,0.2f);
		controlPic->setDimensions(0.6f, 0.6f);
		controlPic->setMaterialName("introduction");    
		overlayGUI2->add2D(controlPic);
		
		
		textAreaGUIMoney=static_cast<TextAreaOverlayElement*>(olmGUI->createOverlayElement("TextArea","Money Value"));
		textAreaGUIMoney->setFontName("StarWars");  	      
		textAreaGUIMoney->setMetricsMode(Ogre::GMM_PIXELS); 
		textAreaGUIMoney->setPosition(0.90f, 0.10f);
		textAreaGUIMoney->setCharHeight(45);
		//textAreaGUIMoney->setCaption("sdfasfsdf0");
		textAreaGUIMoney->show(); 
		panelGUI2->addChild(textAreaGUIMoney);
		panelGUI2->show();
		//level = 1; range = 2;
		textAreaGUI2=static_cast<TextAreaOverlayElement*>(olmGUI->createOverlayElement("TextArea","Tank Level"));
		textAreaGUI2->setFontName("StarWars");  	      
		textAreaGUI2->setMetricsMode(Ogre::GMM_PIXELS); 
		textAreaGUI2->setPosition(0.70f, 0.10f);
		textAreaGUI2->setCharHeight(35);
		textAreaGUI2->setCaption("0");
		textAreaGUI2->show();
		
		textAreaGUI2->setColour(Ogre::ColourValue(1.0f, 1.0f, 0, 1));
		money->addChild(textAreaGUI2);

		
		tower1Money=static_cast<TextAreaOverlayElement*>(olmGUI->createOverlayElement("TextArea","Tower 1 Money"));
		tower1Money->setFontName("StarWars");  	      
		tower1Money->setMetricsMode(Ogre::GMM_PIXELS); 
		//tower1Money->setPosition(0.70f, 0.10f);
		tower1Money->setCharHeight(25);
		tower1Money->setCaption("50");
		textAreaGUI2->show();
		tower1->addChild(tower1Money);
		tower1Money->setColour(Ogre::ColourValue::Green);

		tower2Money=static_cast<TextAreaOverlayElement*>(olmGUI->createOverlayElement("TextArea","Tower 2 Money"));
		tower2Money->setFontName("StarWars");  	      
		tower2Money->setMetricsMode(Ogre::GMM_PIXELS); 
		//tower1Money->setPosition(0.70f, 0.10f);
		tower2Money->setCharHeight(25);
		tower2Money->setCaption("100");
		textAreaGUI2->show();
		tower2->addChild(tower2Money);
		tower2Money->setColour(Ogre::ColourValue::Green);

		tower3Money=static_cast<TextAreaOverlayElement*>(olmGUI->createOverlayElement("TextArea","Tower 3 Money"));
		tower3Money->setFontName("StarWars");  	      
		tower3Money->setMetricsMode(Ogre::GMM_PIXELS); 
		//tower1Money->setPosition(0.70f, 0.10f);
		tower3Money->setCharHeight(25);
		tower3Money->setCaption("400");
		
		tower3Money->setColour(Ogre::ColourValue::Green);
		textAreaGUI2->show();
		tower3->addChild(tower3Money);

		tower4Money=static_cast<TextAreaOverlayElement*>(olmGUI->createOverlayElement("TextArea","Tower 4 Money"));
		tower4Money->setFontName("StarWars");  	      
		tower4Money->setMetricsMode(Ogre::GMM_PIXELS); 
		//tower1Money->setPosition(0.70f, 0.10f);
		tower4Money->setCharHeight(25);
		tower4Money->setCaption("0");
		textAreaGUI2->show();
		tower4->addChild(tower4Money);
		tower4Money->setColour(Ogre::ColourValue::Green);
		//sprintf(cc,  "Level %, damage: %d, defence: %d", level, tankFactory->playerTank->getDamage(), tankFactory->playerTank->getDefence());
		//textAreaGUI2->setCaption(cc);
		overlayGUI2->show();

		tower1->hide();
		tower2->hide();
		tower3->hide();
		tower4->hide();
		money->hide();
		panelGUI2->hide();

		winP->hide();
		loseP->hide();

		controlPic->hide();
	}


	void UserGUI::addMoney(int val){
		moneyVal += val;
		textAreaGUI2->setCaption(convertInt(moneyVal));

		resetTowerMoneyCostColour();
	}
	void UserGUI::substractMoney(int val){
		moneyVal -= val;
		textAreaGUI2->setCaption(convertInt(moneyVal));

		resetTowerMoneyCostColour();
	}

	int UserGUI::getMoney(){
		return moneyVal;
	}

	bool UserGUI::ifSubstractMoney(int val){
		return (getMoney() - val) >= 0;
	}

	void UserGUI::resetTowerMoneyCostColour()
	{
		if(moneyVal < 50)
			tower1Money->setColour(Ogre::ColourValue::Red);
		else
			tower1Money->setColour(Ogre::ColourValue::Green);

		if(moneyVal < 100)
			tower2Money->setColour(Ogre::ColourValue::Red);
		else
			tower2Money->setColour(Ogre::ColourValue::Green);

		if(moneyVal < 400)
			tower3Money->setColour(Ogre::ColourValue::Red);
		else
			tower3Money->setColour(Ogre::ColourValue::Green);

		if(moneyVal < 0)
			tower4Money->setColour(Ogre::ColourValue::Red);
		else
			tower4Money->setColour(Ogre::ColourValue::Green);
	
	}


	void UserGUI::setupMenuGUI(){

		CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
		sheet = wmgr.createWindow("DefaultWindow", "TankWarMenu");
		
		/* next wave button  */
		next_wave = wmgr.createWindow("TaharezLook/Button", "next wave");
		next_wave->setText("Next Wave");
		next_wave->setSize(CEGUI::UVector2(CEGUI::UDim(0.4f, 0), CEGUI::UDim(0.1f, 0)));
		next_wave->setPosition(CEGUI::UVector2(CEGUI::UDim(0.3f, 0),CEGUI::UDim(0.2f, 0)));
		sheet->addChildWindow(next_wave);
		next_wave->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&UserGUI::nextWave, this));

		

		
		
		CEGUI::System::getSingleton().setGUISheet(sheet);
		
	}

	void UserGUI::miniMap(){
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
		mini_map->setSize(CEGUI::UVector2(CEGUI::UDim(0.2f, 0),CEGUI::UDim(0.2f, 0)));
		mini_map->setPosition(CEGUI::UVector2(CEGUI::UDim(0.69f, 0),CEGUI::UDim(0.0f, 0)));
		mini_map->setProperty("Image", CEGUI::PropertyHelper::imageToString(&imageSet.getImage("RTTImage")));
		sheet->addChildWindow(mini_map);
		mini_map->setVisible(false);
	
	}


	//-------------------------------------------------------------------------------------
	
	void UserGUI::update(float time)
	{

		

		/*
			if(!pause){
				if(previouslife != tankFactory->playerTank->getLife()){
					//mSceneMgr->getCamera("RearCam")->lookAt(tankFactory->playerTank->getSceneNode()->getPosition());
					panelGUI2->setDimensions(tankFactory->playerTank->getLife()/100 * 0.15, 0.02);
					previouslife = tankFactory->playerTank->getLife();
				}
				
				tankExp->setDimensions(mCollisionManager->playerScore * 0.3 / range,0.02);
				if(mCollisionManager->playerScore >= range){

					tankFactory->playerTank->levelUp();
					mCollisionManager->playerScore = 0;
					level++;
					range++;
					sprintf(cc,  "Level %d, damage: %5.1f, defence: %5.1f", level, tankFactory->playerTank->getDamage(), tankFactory->playerTank->getDefence());
					textAreaGUI2->setCaption(cc);
				}

				sprintf(cc,  "Level %d, damage: %5.1f, defence: %5.1f", level, tankFactory->playerTank->getDamage(), tankFactory->playerTank->getDefence());
				textAreaGUI2->setCaption(cc);	 

				if(ifstart && tankFactory->playerTank != NULL){
				//Ogre::Vector3 p = ;
					cam->lookAt(tankFactory->playerTank->getSceneNode()->getPosition());//look at player
				}

			
			}
			//if(mInputHandler->godMode){
				//mTankWarCamera->mCameraMan->frameRenderingQueued(evt);
			//}

			if(mShutDown)return false;
			if(mWindow->isClosed())return false;

			return true;


			*/
	}

	//---------------------------------------------------------------


	bool UserGUI::nextWave(const CEGUI::EventArgs &e)
	{
		
		
		return true;
	}

	
	std::string UserGUI::convertInt(int n)
	{
		std::stringstream ss;
		ss << n;
		return ss.str();
	}
}


